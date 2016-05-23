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
#include "mi_gdb.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbSteppingAspect : public NextAspect
{
public:
    using NextAspect::NextAspect;

    bool next();

    bool step();

protected:
    void processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction) override;
};


template<class NextAspect>
bool GdbSteppingAspect<NextAspect>::next()
{
    const bool ret = (bool) gmi_exec_next(this->handler) != 0;
    this->threadLoop.resume();
    return ret;
}

template<class NextAspect>
bool GdbSteppingAspect<NextAspect>::step()
{
    const bool ret = (bool) gmi_exec_step(this->handler) != 0;
    this->threadLoop.resume();
    return ret;
}

template<class NextAspect>
inline void GdbSteppingAspect<NextAspect>::processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason,
        moirai::PostIterationAction& nextAction)
{
    if (stopReason.reason == sr_end_stepping_range)
    {
        nextAction = moirai::SuspendLooping;
    }
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif // GDB_STEPPING_ASPECT_H
