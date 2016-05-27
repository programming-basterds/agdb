/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        MultiBreakpointCommand.h
 * @author      Emanuel Bringas
 * @author      Leonardo Boquillón
 * @author      Francisco Herrero
 * @date        2016-05-04
 * @brief       Contains Multibreakpoint manipulation commands.
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

#ifndef _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_
#define _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/ICommand.h"
#include "commands/argumentedCommand.h"

namespace NSCommands
{

/**
 * @brief MultiBreakpoint creation command.
 * @details Is responsible of the building of
 *          a multibreakpoint in context.
 */
class MultiBreakpointCommand : public ICommand
{
    /**
     * @brief Parse mbr command.
     * @details Supported syntax:
     *              mbr: NID1 location1:number1 when NID2 location2:number2 [if condition]
     *
     * @param[in]     expression Expression to parse.
     * @param[in/out] ctx Current context.
     */
    void execute(const Expression& expression, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Enable MultiBreakpoint command.
 */
class EnableMultibreakpointCommand : public ArgumentedCommand
{

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        MbrInstance,
        // leave this at the end
        NumberOfArgs
    };

    /** ArgumentedCommand interface implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Disable MultiBreakpoint command.
 */
class DisableMultibreakpointCommand : public ArgumentedCommand
{

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        MbrInstance,
        // leave this at the end
        NumberOfArgs
    };

    /** ArgumentedCommand interface implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Ignore MultiBreakpoint command.
 */
class IgnoreMultibreakpointCommand : public ArgumentedCommand
{

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        MbrInstance,
        Count,
        // leave this at the end
        NumberOfArgs
    };

    /** ArgumentedCommand interface implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_
