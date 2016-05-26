/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        Breakpoint.cpp
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

#include "common/Breakpoint.h"

Breakpoint::Breakpoint(Callback callback, mi_bkpt* breakpointImple,
                       IBreakpointProxy* const internals) :
    _breakpoint(breakpointImple),
    _callback(callback),
    _internals(internals)
{}

Breakpoint::~Breakpoint()
{
    mi_free_bkpt(_breakpoint);
}

Breakpoint::BreakpointID Breakpoint::id() const
{
    return _breakpoint->number;
}

void Breakpoint::hit(moirai::PostIterationAction& nextAction)
{
    _callback(this, nextAction);
}

void Breakpoint::enable()
{
    _internals->enableBreakpoint(this);
}

void Breakpoint::disable()
{
    _internals->disableBreakpoint(this);
}

void Breakpoint::ignore(const int count)
{
    _internals->ignoreBreakpoint(this, count);
}
