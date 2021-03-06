/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbSteppingAspect.h
 * @author      Emanuel Bringas
 * @date        2016-05-12
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

#ifndef GDB_STEPPING_ASPECT_H
#define GDB_STEPPING_ASPECT_H

#include <string>
#include <thread>
#include <future>
#include "mi_gdb.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbSteppingAspect : public NextAspect
{
public:
    using NextAspect::NextAspect;

    inline std::future<bool> next();
    inline std::future<bool> nextInstruction();
    inline std::future<bool> step();
    inline std::future<bool> stepInstruction();

protected:
    using SteppingFn = int (*)(mi_h*);
    std::future<bool> performStepping(SteppingFn fn);
    void processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction) override;

private:
    std::unique_ptr<std::promise<bool>> _prm;
};

template<class NextAspect>
std::future<bool> GdbSteppingAspect<NextAspect>::performStepping(SteppingFn fn)
{
    const bool success = (bool) fn(this->handler) != 0;
    this->threadLoop.resume();
    mili::assert_throw<NSCommon::SteppingExecutionFailed>(success);
    _prm.reset(new std::promise<bool>());
    return _prm->get_future();
}

template<class NextAspect>
inline std::future<bool> GdbSteppingAspect<NextAspect>::next()
{
    return performStepping(gmi_exec_next);
}

template<class NextAspect>
inline std::future<bool> GdbSteppingAspect<NextAspect>::nextInstruction()
{
    return performStepping(gmi_exec_next_instruction);
}

template<class NextAspect>
inline std::future<bool> GdbSteppingAspect<NextAspect>::step()
{
    return performStepping(gmi_exec_step);
}

template<class NextAspect>
inline std::future<bool> GdbSteppingAspect<NextAspect>::stepInstruction()
{
    return performStepping(gmi_exec_step_instruction);
}

template<class NextAspect>
inline void GdbSteppingAspect<NextAspect>::processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason,
        moirai::PostIterationAction& nextAction)
{
    const auto stopByStepReason = (stopReason.reason == sr_end_stepping_range);
    if (stopByStepReason)
    {
        nextAction = moirai::SuspendLooping;
    }
    if (_prm != nullptr)
    {
        _prm->set_value(stopByStepReason);
    }
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif // GDB_STEPPING_ASPECT_H
