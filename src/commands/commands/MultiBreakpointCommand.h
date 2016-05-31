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

#ifndef _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_
#define _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

class MultiBreakpointCommand : public ICommand
{
private:
    enum ArgsIndex
    {
        Instance1,
        Location1,
        WhenWord,
        Instance2,
        Location2,
        IfWord,
        Condition,
        // leave this at the end
        NumberOfArgs
    };

    enum LocationReIndex
    {
        PathReIndex = 1u,
        LineNumReIndex
    };

    /** ICommand interface implementation */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;

    static BreakpointLocation parseLocation(const std::string& text);

    static const std::regex LOCATION_RE;

};

class EnableMultibreakpointCommand : public ICommand
{
    enum ArgsIndex
    {
        MbrInstance,
        // leave this at the end
        NumberOfArgs
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

class DisableMultibreakpointCommand : public ICommand
{
    enum ArgsIndex
    {
        MbrInstance,
        // leave this at the end
        NumberOfArgs
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

class IgnoreMultibreakpointCommand : public ICommand
{
    enum ArgsIndex
    {
        MbrInstance,
        Count,
        // leave this at the end
        NumberOfArgs
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // _MULTI_BREAKPOINT_COMMAND_INCLUDE_H_
