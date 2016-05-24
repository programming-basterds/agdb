/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbBaseAspect.h
 * @author      Daniel Gutson
 * @author      Francisco Herrero
 * @author      Leonardo Boquillón
 * @date        2016-05-03
 * @brief
 *
 * This file is part of agdb
 *
 * agdb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * agdb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with agdb.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GDB_BASE_ASPECT_INCLUDE_H_
#define _GDB_BASE_ASPECT_INCLUDE_H_

#include <cstdlib>
#include <string>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <iostream>
#include <functional>
#include <forward_list>

#include "common/exceptions.h"
#include "moirai/threadLoop.h"
#include "common/Breakpoint.h"

#include "mi_gdb.h"
#include "common/baseTypes.h"

namespace NSGdbProxy
{

using TerminationCallback = std::function<void()>;
using TerminationCallbackCollection = std::forward_list<TerminationCallback>;

template<class Type>
class GdbBaseAspect
{
public:

    GdbBaseAspect(const std::string& programName);

    virtual ~GdbBaseAspect();

    void setGdbPath(const std::string& gdbPathFile);

    void continueExecution();

    void waitForFinalization();

    void forceQuit();

    void registerTerminationCallback(TerminationCallback cb);

    bool isRunning() const;

protected:

    virtual void processStopReason(mi_output* const response,
                                   const NSCommon::StopReason& stopReason,
                                   moirai::PostIterationAction& nextAction) = 0;

    mi_h*               handler;
    std::string         path;
    const std::string   program;
    std::atomic<bool>   alive;
    std::atomic<bool>   running;
    moirai::ThreadLoop<GdbBaseAspect<Type>> threadLoop;

private:

    void mainLoop();

    moirai::PostIterationAction mainCycle();

    void continueExec();

    bool waitForStop(NSCommon::StopReason& reason, mi_output*& response);

    moirai::SignalWaiter                    notifier;
    std::thread                             thread;
    TerminationCallbackCollection           terminationCallbacks;
};

template<class Type>
GdbBaseAspect<Type>::GdbBaseAspect(const std::string& programName)
    : path("/usr/bin/gdb")
    , program(programName)
    , alive(true)
    , running(false)
    , thread([this]()
    {
        mainLoop();
    })
{}

template<class Type>
GdbBaseAspect<Type>::~GdbBaseAspect()
{
    forceQuit();
    free(handler);
}

template<class Type>
void GdbBaseAspect<Type>::mainLoop()
{
    threadLoop.run(this,
                   &GdbBaseAspect<Type>::mainCycle,
                   moirai::ThreadLoop<GdbBaseAspect<Type>>::StartSuspended,
                   notifier);
}

template<class Type>
moirai::PostIterationAction GdbBaseAspect<Type>::mainCycle()
{
    auto nextAction = moirai::KeepLooping;
    running = true;
    while (nextAction == moirai::KeepLooping && alive)
    {
        NSCommon::StopReason  reason;
        mi_output*  response;

        if (waitForStop(reason, response))
        {
            std::cout << "Stop: " << mi_reason_enum_to_str(reason.reason) << std::endl;
            processStopReason(response, reason, nextAction);
            if (nextAction == moirai::KeepLooping && alive)
                continueExec();
        }
        else
        {
            // TODO : critical exception
            continue;
        }
    }
    if (!alive)
    {
        nextAction = moirai::QuitLooping;
    }
    running = false;
    return nextAction;
}




template<class Type>
void GdbBaseAspect<Type>::setGdbPath(const std::string& gdbPathFile)
{
    path = gdbPathFile;
}

template<class Type>
void GdbBaseAspect<Type>::processStopReason(mi_output* const /*response*/,
                                            const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction)
{
    if (stopReason.reason == sr_exited || stopReason.reason == sr_exited_normally)
    {
        std::cout << "Exiting...!" << std::endl;
        for (auto callback : terminationCallbacks)
        {
            callback();
        }
        nextAction = moirai::QuitLooping;
    }
}

template<class Type>
void GdbBaseAspect<Type>::continueExec()
{
    auto response =  gmi_exec_continue(handler);
    mili::assert_throw<NSCommon::ErrorContinue>(response != 0);
}

template<class Type>
void GdbBaseAspect<Type>::continueExecution()
{
    continueExec();
    threadLoop.resume();
}

template<class Type>
void GdbBaseAspect<Type>::waitForFinalization()
{
    thread.join();
}

template<class Type>
void GdbBaseAspect<Type>::forceQuit()
{
    alive = false;
    threadLoop.asynchQuit();
    waitForFinalization();
}

template<class Type>
bool GdbBaseAspect<Type>::waitForStop(NSCommon::StopReason& reason, mi_output*& response)
{
    while (!mi_get_response(handler) && alive)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    mi_stop *sr = mi_res_stop(handler);
    const auto result = sr != nullptr;
    if (result)
    {
        reason = NSCommon::StopReason(sr);
        mi_free_stop(sr);
    }

    response = mi_retire_response(handler);
    return result;
}

template<class Type>
void GdbBaseAspect<Type>::registerTerminationCallback(TerminationCallback cb)
{
    terminationCallbacks.push_front(cb);
}

template<class Type>
inline bool GdbBaseAspect<Type>::isRunning() const
{
    return running;
}

} // namespace NSGdbProxy

#endif /* _GDB_BASE_ASPECT_INCLUDE_H_ */
