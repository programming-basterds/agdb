/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        MultiBreakpoint.h
 * @author      Leonardo Boquillón
 * @author      Francisco Herrero
 * @date        2016-05-02
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

#ifndef _MULTI_BREAKPOINT_INCLUDE_H_
#define _MULTI_BREAKPOINT_INCLUDE_H_

#include <atomic>
#include <string>
#include "gdbProxy/GdbProxy.h"

namespace NSDebuggingContext
{

class IHitBreakpointObserver;

class MultiBreakpoint
{
public:
    MultiBreakpoint();

    void addInconditionalBreakpoint(NSGdbProxy::GdbProxy& instance, const BreakpointLocation& location);

    void addConditionalBreakpoint(NSGdbProxy::GdbProxy& instance, const BreakpointLocation& location);

    void enable();

    void disable();

    void ignore(int count);

private:
    std::atomic<bool> _synchronizationFlag;

    std::shared_ptr<IUserBreakpoint> _conditionalBreakpoint;
    std::shared_ptr<IUserBreakpoint> _inconditionalBreakpoint;

    void changeSynchronizationFlagStatus(bool status);

    bool getSynchronizationFlag() const;
};

} // end namespace NSDebuggingContext

#endif /* _MULTI_BREAKPOINT_INCLUDE_H_ */