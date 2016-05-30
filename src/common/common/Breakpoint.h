/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        Breakpoint.h
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

#ifndef _BREAKPOINT_INCLUDE_H_
#define _BREAKPOINT_INCLUDE_H_

#include <utility>
#include <functional>

#include "moirai/threadLoop.h"
#include "mi_gdb.h"

struct IUserBreakpoint
{
    using BreakpointID = decltype(std::declval<mi_bkpt*>()->number);

    virtual BreakpointID id() const = 0;

    virtual void enable() = 0;

    virtual void disable() = 0;

    virtual void ignore(int count) = 0;

    virtual ~IUserBreakpoint() = default;
};

struct IInternalBreakpoint
{
    virtual void hit(moirai::PostIterationAction& nextAction) = 0;
};

using Callback = std::function<void(IUserBreakpoint*, moirai::PostIterationAction& nextAction)>;

struct IBreakpointProxy
{
    virtual bool enableBreakpoint(IUserBreakpoint* breakpoint) = 0;

    virtual bool disableBreakpoint(IUserBreakpoint* breakpoint) = 0;

    virtual bool ignoreBreakpoint(IUserBreakpoint* breakpoint, int count) = 0;

    virtual bool deleteBreakpoint(IUserBreakpoint* breakpoint) = 0;

    virtual ~IBreakpointProxy() = default;
};

struct BreakpointLocation
{
    std::string file;
    std::size_t line;
    std::string condition;
};

class Breakpoint : public IUserBreakpoint, public IInternalBreakpoint
{
public:

    using IUserBreakpoint::BreakpointID;

    Breakpoint(Callback callback, mi_bkpt* breakpointImple,
               IBreakpointProxy* const internals);

    Breakpoint& operator=(Breakpoint&) = delete;

    ~Breakpoint();

private:

    // IUserBreakpoint implementation.
    BreakpointID id() const override;
    void enable() override;
    void disable() override;
    void ignore(int count) override;

    // IInternalBreakpoint implementation.
    void hit(moirai::PostIterationAction& nextAction) override;

    mi_bkpt* const          _breakpoint;
    Callback                _callback;
    IBreakpointProxy* const _internals;
};

#endif /* _BREAKPOINT_INCLUDE_H_ */
