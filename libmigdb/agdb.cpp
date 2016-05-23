/**[txh]********************************************************************

  Copyright (c) 2004 by Salvador E. Tropea.
  Covered by the GPL license.

  Comment:
  Remote example/test of the libmigdb.
  To run it you must:

1) Copy "test_target" to the "remote" host (it could be the same machine if
you want).
2) In the "remote" end run "gdbserver :6000 ./test_target 1 2 3"
3) Run this example in the "local" end.

You should edit the remote IP and port before compiling.

***************************************************************************/

#include <stdio.h>
#include <unistd.h> //usleep
#include <string.h>

#include <iostream>
#include <pthread.h>

#include "mi_gdb.h"


// Example: "192.168.1.3:5500"
#define REMOTE_MACHINE ":1234"
#define REMOTE_MACHINE2 ":1235"
void cb_console(const char *str, void *data)
{
	printf("CONSOLE> %s\n",str);
}

/* Note that unlike what's documented in gdb docs it isn't usable. */
void cb_target(const char *str, void *data)
{
 	printf("TARGET> %s\n",str);
}

void cb_log(const char *str, void *data)
{
 	printf("LOG> %s\n",str);
}

void cb_to(const char *str, void *data)
{
 	printf(">> %s",str);
}

void cb_from(const char *str, void *data)
{
 	printf("<< %s\n",str);
}

volatile int async_c=0;

void cb_async(mi_output *o, void *data)
{
	printf("ASYNC\n");
	async_c++;
}

int wait_for_stop(mi_h *h)
{
	mi_output *o;
	int res=1;
	char *aux;

	while (!mi_get_response(h))
		usleep(1000);
	/* The end of the async. */
	o=mi_retire_response(h);

	if (mi_get_async_stop_reason(o,&aux))
		printf("Stopped, reason: %s\n",aux);
	else
	{
		printf("Error while waiting: %s\n",aux);
		res=0;
	}
	mi_free_output(o);
	return res;
}

void *thread1_task(void *);
void *thread2_task(void *);
int flag;
pthread_t thread1, thread2;
pthread_mutex_t lock;


int main(int argc, char *argv[])
{
	mi_bkpt *bk, *bk2;
	//mi_h *h, *h2;
	mi_h *h = new mi_h;
	mi_h *h2 = new mi_h;

	mi_set_gdb_exe("/home/aurelio-remonda/gdb_hipervisor/rtems/rtems-toolchain/bin/arm-rtems4.11-gdb");


    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	h=mi_connect_local();
	if (!h)
	{
		printf("Connect failed\n");
	}
	printf("Connected to gdb!\n");

	h2=mi_connect_local();
	if (!h2)
	{
		printf("Connect failed\n");
	}
	printf("Connected to gdb!\n");

	mi_set_console_cb(h,cb_console,NULL);
	mi_set_target_cb(h,cb_target,NULL);
	mi_set_log_cb(h,cb_log,NULL);
	mi_set_async_cb(h,cb_async,NULL);
	mi_set_to_gdb_cb(h,cb_to,NULL);
	mi_set_from_gdb_cb(h,cb_from,NULL);

	mi_set_console_cb(h2,cb_console,NULL);
	mi_set_target_cb(h2,cb_target,NULL);
	mi_set_log_cb(h2,cb_log,NULL);
	mi_set_async_cb(h2,cb_async,NULL);
	mi_set_to_gdb_cb(h2,cb_to,NULL);
	mi_set_from_gdb_cb(h2,cb_from,NULL);

	if (!gmi_file_symbol_file(h,"/home/aurelio-remonda/gdb_hipervisor/libmigdb/examples/prog1RTEMS/app.exe"))
	{
		printf("Error loading symbols\n");
		mi_disconnect(h);
	}

	if (!gmi_file_symbol_file(h2,"/home/aurelio-remonda/gdb_hipervisor/libmigdb/examples/prog2RTEMS/app.exe"))
	{
		printf("Error loading symbols\n");
		mi_disconnect(h2);
	}
	if (!gmi_target_select(h,"extended-remote",REMOTE_MACHINE))
	{
		printf("Error connecting to gdb server\n");
		mi_disconnect(h);
	}

	if (!gmi_target_select(h2,"extended-remote",REMOTE_MACHINE2))
	{
		printf("Error connecting to gdb server\n");
		mi_disconnect(h2);
	}

	bk=gmi_break_insert(h,"/home/aurelio-remonda/gdb_hipervisor/libmigdb/examples/prog1RTEMS/app.cpp",17);
	if (!bk)
	{
		printf("Error setting breakpoint 1\n");
		mi_disconnect(h);
		return 1;
	}
	printf("Breakpoint %d @ function: %s\n",bk->number,bk->func);

	bk2=gmi_break_insert(h2,"/home/aurelio-remonda/gdb_hipervisor/libmigdb/examples/prog2RTEMS/app.cpp",17);
	if (!bk2)
	{
		printf("Error setting breakpoint 2\n");
		mi_disconnect(h2);
		return 1;
	}
	printf("Breakpoint %d @ function: %s\n",bk2->number,bk2->func);
	gmi_break_set_condition(h2, bk2->number, "x == 1800");

	pthread_create(&thread1, 0, thread1_task, h);
	pthread_create(&thread2, 0, thread2_task, h2);

	pthread_join(thread1, 0);
	pthread_join(thread2, 0);

	pthread_mutex_destroy(&lock);
	return 0;
}

void *thread1_task(void *i)
{

	mi_h *h= (mi_h *) i;
	printf("THREAD 1 TASK\n");
	printf("FLAG=%i\n", flag);
	if (!gmi_exec_continue(h))
	    {
	        printf("Error in run!\n");
	        mi_disconnect(h);
	    }
	while(1)
	{
		if (!wait_for_stop(h))
		{
			mi_disconnect(h);
		}
		printf("VALUE of i %s\n", gmi_data_evaluate_expression(h, "i"));
		pthread_mutex_lock(&lock);
		printf("FLAG=%i\n", flag);
		if(flag==0)
		{
			if (!gmi_exec_continue(h))
		    {
		        printf("Error in run!\n");
		        mi_disconnect(h);
		    }
		}
		pthread_mutex_unlock(&lock);
	}

    /* Exit from gdb. */
	gmi_gdb_exit(h);
	/* Close the connection. */
	mi_disconnect(h);

}

void *thread2_task(void *i)
{

	mi_h *h= (mi_h *) i;
	//pthread_mutex_lock(&lock);
	printf("THREAD 2 TASK\n");

	if (!gmi_exec_continue(h))
    {
        printf("Error in run!\n");
        mi_disconnect(h);
    }

    if (!wait_for_stop(h))
	{
		mi_disconnect(h);
	}
	printf("VALUE of x %s\n", gmi_data_evaluate_expression(h, "x"));

	pthread_mutex_lock(&lock);
	flag = 1;
	pthread_mutex_unlock(&lock);

	if (!gmi_exec_continue(h))
    {
        printf("Error in run!\n");
        mi_disconnect(h);
    }

    /* Exit from gdb. */
	gmi_gdb_exit(h);
	/* Close the connection. */
	mi_disconnect(h);
}

