/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        MultiBreakpoint.cpp
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

#include "debuggingContext/MultiBreakpoint.h"

#include "gdbProxy/GdbProxy.h"

#include <iostream>
#include <future>

namespace NSDebuggingContext
{

MultiBreakpoint::MultiBreakpoint() :
    _synchronizationFlag(false)
{}

// En realidad es importante que los usuarios del proxy se enteren de que una instancia terminó.
// Para eso debería haber un registerTerminationCallback(callback)
// y el mbr debería registrar ahí. Cada vez q una instancia termina, el mbr checkea si tiene
// mbrs con esa instancia; si sí, frena la instancia contraria (master o slave), le saca el
// breakpoint (agregar remove breakpoint al aspecto de breakpointing), la continúa, elimina
// el mbr, y avisa al usuario que un mbr fue removido porque una instancia de sus dos puntas terminó.

void MultiBreakpoint::addInconditionalBreakpoint(NSGdbProxy::GdbProxy& instance, const BreakpointLocation& location)
{
    _inconditionalBreakpoint = instance.addBreakpoint(location, [this](IUserBreakpoint * breakpoint, moirai::PostIterationAction & nextAction)
    {
        if (getSynchronizationFlag())
        {
            breakpoint->disable();
            nextAction = moirai::SuspendLooping;
        }
    });
    instance.registerTerminationCallback([this]()
    {
        _conditionalBreakpoint->disable();
    });
}

void MultiBreakpoint::addConditionalBreakpoint(NSGdbProxy::GdbProxy& instance, const BreakpointLocation& location)
{
    _conditionalBreakpoint = instance.addBreakpoint(location, [this](IUserBreakpoint* /*breakpoint*/, moirai::PostIterationAction& /*nextAction*/)
    {
        changeSynchronizationFlagStatus(true);
    });
    instance.registerTerminationCallback([this]()
    {
        _inconditionalBreakpoint->disable();
    });
}

void MultiBreakpoint::changeSynchronizationFlagStatus(bool status)
{
    _synchronizationFlag = status;
}

bool MultiBreakpoint::getSynchronizationFlag() const
{
    return _synchronizationFlag.load();
}

void MultiBreakpoint::enable()
{
    _conditionalBreakpoint->enable();
    _inconditionalBreakpoint->enable();
}

void MultiBreakpoint::disable()
{
    _conditionalBreakpoint->disable();
    _inconditionalBreakpoint->disable();
}

void MultiBreakpoint::ignore(const int count)
{
    _conditionalBreakpoint->ignore(count);
    _inconditionalBreakpoint->ignore(count);
}

} // namespace
