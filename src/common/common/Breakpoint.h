/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        Breakpoint.h
 * @author      Leonardo Boquillón
 * @author      Francisco Herrero
 * @date        2016-05-02
 * @brief       Breakpoint interfaces and classes declaration.
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

#include <regex>
#include <utility>
#include <functional>

#include "moirai/threadLoop.h"
#include "mi_gdb.h"

/**
 * @brief User interface for breakpoint.
 */
struct IUserBreakpoint
{
    using BreakpointID = decltype(std::declval<mi_bkpt*>()->number);

    /**
     * @brief Fetch breakpoint id.
     * @return Breakpoint id.
     */
    virtual BreakpointID id() const = 0;

    /**
     * @brief Enables breakpoint.
     */
    virtual void enable() = 0;

    /**
     * @brief Disables breakpoint.
     */
    virtual void disable() = 0;

    /**
     * @brief Ignores breakpoint.
     * @param[in] count Times to ignore.
     */
    virtual void ignore(int count) = 0;

    /** @brief Destructor. */
    virtual ~IUserBreakpoint() = default;
};

/**
 * @brief Breakpoint for internal usage.
 */
struct IInternalBreakpoint
{
    /**
     * @brief Instruction to execute when breakpoint is hitted.
     * @param[out] nextAction Next action.
     */
    virtual void hit(moirai::PostIterationAction& nextAction) = 0;
};

using Callback = std::function<void(IUserBreakpoint*, moirai::PostIterationAction& nextAction)>;

/**
 * @brief Proxy interface to interact with gdb breakpoint.
 */
struct IBreakpointProxy
{
    /**
     * @brief Enables breakpoint in proxy
     * @param[in/out] breakpoint Breakpoint who invoke it.
     * @return True if enable was successfully executed. False otherwhise.
     */
    virtual bool enableBreakpoint(IUserBreakpoint* breakpoint) = 0;

    /**
     * @brief Disables breakpoint in proxy
     * @param[in/out] breakpoint Breakpoint who invoke it.
     * @return True if disable was successfully executed. False otherwhise.
     */
    virtual bool disableBreakpoint(IUserBreakpoint* breakpoint) = 0;

    /**
     * @brief Ignores breakpoint in proxy
     * @param[in/out] breakpoint Breakpoint who invoke it.
     * @return True if ignore was successfully executed. False otherwhise.
     */
    virtual bool ignoreBreakpoint(IUserBreakpoint* breakpoint, int count) = 0;

    /**
     * @brief Deletes breakpoint in proxy
     * @param[in/out] breakpoint Breakpoint who invoke it.
     * @return True if delete was successfully executed. False otherwhise.
     */
    virtual bool deleteBreakpoint(IUserBreakpoint* breakpoint) = 0;

    /** @brief Destructor */
    virtual ~IBreakpointProxy() = default;
};

/**
 * @brief   Breakpoint location.
 * @details Represents a location and condition of a breakpoint.
 */
class BreakpointLocation
{
public:

    /**
     * @brief Builds location from argument.
     * @details Expected notation:
     *              <source file>:<line number>
     * @param[in] text Location to parse.
     * @return BreakpointLocation generated.
     */
    static BreakpointLocation fromArgument(const std::string& text);

    /** @brief File name. */
    std::string file;

    /** @brief Breakpoint Line. */
    std::size_t line;

    /** @brief Breakpoint condition. */
    std::string condition;

private:

    /** @brief Regular expression used to parse argument. */
    static const std::regex LOCATION_RE;

    /** Location regular expression group indexes. */
    enum LocationReIndex
    {
        PathReIndex = 1u,
        LineNumReIndex
    };
};

/**
 * @brief Breakpoint implementation for libmigdb.
 */
class Breakpoint : public IUserBreakpoint, public IInternalBreakpoint
{
public:

    using IUserBreakpoint::BreakpointID;

    /**
     * @brief Constructor.
     * @param[in] callback Callback to execute on breakpoint hit.
     * @param[in/out] breakpointImple Breakpoint
     * @param[in/out] internals Proxy to send breakpoint commands.
     */
    Breakpoint(Callback callback, mi_bkpt* breakpointImple,
               IBreakpointProxy* const internals);

    Breakpoint& operator=(Breakpoint&) = delete;

    /** @brief Destructor. */
    ~Breakpoint();

private:

    /** IUserBreakpoint implementation. */
    BreakpointID id() const override;
    void enable() override;
    void disable() override;
    void ignore(int count) override;

    /** IInternalBreakpoint implementation. */
    void hit(moirai::PostIterationAction& nextAction) override;

    /** Breakpont libmigdb. */
    mi_bkpt* const          _breakpoint;

    /** Invocation hit callback. */
    Callback                _callback;

    /** Proxy breakpoints. */
    IBreakpointProxy* const _internals;
};

#endif /* _BREAKPOINT_INCLUDE_H_ */
