/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbRaiseAspect.h
 * @author      Leonardo Boquillón
 * @author      Emanuel Bringas
 * @author      Francisco Herrero
 * @author      Gustavo Ojeda
 *
 * @date        2016-05-06
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

#ifndef _GDB_RAISE_ASPECT_INCLUDE_H_
#define _GDB_RAISE_ASPECT_INCLUDE_H_

#include <iostream>
#include "mi_gdb.h"
#include "common/miUtils.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbRaiseAspect : public NextAspect
{

public:
    enum class ConnectionType
    {
        Local,
        Remote
    };

    using NextAspect::NextAspect;

    bool connectLocal();

    bool connectRemote(const std::string& location);

    void run();

    inline void disconnect();

    bool loadSymbols();

    bool setProgramArguments(const std::string& args);

    inline void interrupt();

    inline ConnectionType getConnectionType() const;

    inline const std::string& getLocation() const;

    inline const std::string& getArgs() const;

    inline pid_t getPID() const;

protected:
    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& reason,
                                  moirai::PostIterationAction& nextAction) override;
private:
    pid_t           pid = -1;
    std::string     location;
    ConnectionType  connectionType;
    std::string     args;
};

template<class NextAspect>
bool GdbRaiseAspect<NextAspect>::connectLocal()
{
    std::cout << "Connecting with local gdb" << std::endl;
    this->handler = mi_connect_local();
    auto connected = this->handler != nullptr;
    if (connected)
    {
        this->connectionType = ConnectionType::Local;
        // TODO: Check if its needed to interrupt
        //mili::assert_throw<NSCommon::MiAsyncModeError>(gmi_gdb_set(this->handler, "mi-async", "on"));
    }
    return connected;
}

template<class NextAspect>
bool GdbRaiseAspect<NextAspect>::connectRemote(const std::string& location)
{
    std::cout << "Connecting with remote gdb at " << location << std::endl;
    gmi_target_select(this->handler, "extended-remote", location.c_str());
    const auto connected = this->handler != nullptr;
    if (connected)
    {
        this->connectionType = ConnectionType::Remote;
        this->location = location;
    }
    return connected;
}

template<class NextAspect>
void GdbRaiseAspect<NextAspect>::run()
{
    // This pointer is setted to stop execution at begining of local program
    auto br = gmi_break_insert_full(this->handler, 1, 0, NULL, -1, -1, "_start");
    mili::assert_throw<NSCommon::RaiseLocalBreakpointError>(br != nullptr);

    auto success = gmi_exec_run(this->handler);
    mili::assert_throw<NSCommon::RaiseLocalBreakpointError>(success);

    while (!mi_get_response(this->handler))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    char* reason;
    mi_output* response = mi_retire_response(this->handler);
    success = mi_get_async_stop_reason(response, &reason);
    if (!success)
    {
        throw NSCommon::RaiseLocalBreakpointError(reason);
    }
    this->pid = NSCommon::getProcessPid(this->handler);
}

template<class NextAspect>
inline void GdbRaiseAspect<NextAspect>::interrupt()
{
    NSCommon::interrupt(this->pid);
}

template<class NextAspect>
inline void GdbRaiseAspect<NextAspect>::disconnect()
{
    gmi_gdb_exit(this->handler);
    mi_disconnect(this->handler);
}

template<class NextAspect>
bool GdbRaiseAspect<NextAspect>::setProgramArguments(const std::string& args)
{
    std::cout << "Program: " << this->program << "\nArguments: " << args << std::endl;
    const auto success = gmi_set_exec(this->handler, this->program.c_str(), args.c_str()) != 0;
    if (success)
    {
        this->args = args;
    }
    return success;
}

template<class NextAspect>
bool GdbRaiseAspect<NextAspect>::loadSymbols()
{
    std::cout << "Loading symbols for: " << this->program << std::endl;
    return gmi_file_symbol_file(this->handler, this->program.c_str());
}

template<class NextAspect>
inline void GdbRaiseAspect<NextAspect>::processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason,
        moirai::PostIterationAction& nextAction)
{
    if (stopReason.reason == sr_signal_received && stopReason.signalName == "SIGINT")
    {
        nextAction = moirai::SuspendLooping;
    }

    NextAspect::processStopReason(response, stopReason, nextAction);
}

template<class NextAspect>
inline typename GdbRaiseAspect<NextAspect>::ConnectionType
GdbRaiseAspect<NextAspect>::getConnectionType() const
{
    return connectionType;
}

template<class NextAspect>
inline const std::string& GdbRaiseAspect<NextAspect>::getLocation() const
{
    return location;
}

template<class NextAspect>
inline const std::string& GdbRaiseAspect<NextAspect>::getArgs() const
{
    return args;
}

template<class NextAspect>
inline pid_t GdbRaiseAspect<NextAspect>::getPID() const
{
    return pid;
}

} // namespace NSGdbProxy

#endif /* _GDB_RAISE_ASPECT_INCLUDE_H_ */