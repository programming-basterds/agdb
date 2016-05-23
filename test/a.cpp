#include <iostream>
#include <unistd.h>
int main()
{
	for (int i = 0; i < 5000; ++i){
		sleep(1);
	}
    //auto a = 2/0;

    return 0;
}
