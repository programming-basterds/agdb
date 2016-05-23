/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbFwdAspect.h
 * @author      Emanuel Bringas
 * @date        2016-05-09
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

#ifndef GDB_FWD_ASPECT_H
#define GDB_FWD_ASPECT_H

#include <string>
#include "mi_gdb.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbFwdAspect : public NextAspect
{
public:
    using NextAspect::NextAspect;

    bool sendMessageToGDB(const std::string& msg);

protected:
    void processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction) override;
};


template<class NextAspect>
bool GdbFwdAspect<NextAspect>::sendMessageToGDB(const std::string& msg)
{
    std::cout << "fwd: " << msg << std::endl;

    /* Sends a message to gdb. */
    const auto o1 = mi_send(this->handler, msg.c_str());
    std::cout << o1 << std::endl;

    /* Wait until gdb sends a response. */
    const auto o2 = mi_get_response_blk(this->handler);
    std::cout << o2 << std::endl;

    /* Check if gdb sent a complete response. Use with mi_retire_response. */
    const auto o3 = mi_get_response(this->handler);
    std::cout << o3 << std::endl;

    /* Get the last response. Use with mi_get_response. */
    const auto o4 = mi_retire_response(this->handler);
    std::cout << o4 << std::endl;

    /* Look for a result record in gdb output. */
    mi_output* const o5 = mi_get_rrecord(o4);
    std::cout << o5->c->v.cstr << std::endl;

    return true;
}

template<class NextAspect>
inline void GdbFwdAspect<NextAspect>::processStopReason(mi_output* const response,
        const NSCommon::StopReason& reason,
        moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, reason, nextAction);
}

} // namespace NSGdbProxy

#endif // GDB_FWD_ASPECT_H
