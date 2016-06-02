/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        MultiBreakpointCommand.cpp
 * @author      Emanuel Bringas
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

#include "common/exceptions.h"
#include "commands/MultiBreakpointCommand.h"

namespace NSCommands
{

using NSDebuggingContext::BreakpointId;
using NSDebuggingContext::MultiBreakpointId;

const char MultiBreakpointCommand::IF_WORD[] = "if";
const char MultiBreakpointCommand::WHEN_WORD[] = "when";

/*mbr NID1 location1:number1 when NID2 location2:number2 [if condition] */
void MultiBreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() > Location2);
    if (args[WhenWord] != WHEN_WORD)
    {
        throw NSCommon::ArgumentMissing(WHEN_WORD);
    }

    auto instance1 = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[Instance1])).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance1));
    const auto location1 = BreakpointLocation::fromArgument(args[Location1]);

    auto instance2 = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[Instance2])).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance2));
    auto location2 = BreakpointLocation::fromArgument(args[Location2]);

    if (args.size() == NumberOfArgs)
    {
        if (args[IfWord] != IF_WORD)
        {
            throw NSCommon::ArgumentMissing(IF_WORD);
        }
        location2.condition = args[Condition];
    }
    // else there is no condition on second breakpoint.

    auto mbc = new NSDebuggingContext::MultiBreakpoint();
    mbc->addInconditionalBreakpoint(instance1, location1);
    mbc->addConditionalBreakpoint(instance2, location2);

    auto mbrId = ctx.addMultiBreakpoint(mbc);

    std::cout << "Multibreakpoint " << mbrId << " created" << std::endl;
}

void EnableMultibreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<MultiBreakpointId>(args[MbrInstance]);
    auto mbr = ctx.getMultiBreakpoint(mbrId);
    mbr->enable();
}

void DisableMultibreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<MultiBreakpointId>(args[MbrInstance]);
    auto mbr = ctx.getMultiBreakpoint(mbrId);
    mbr->disable();
}

void IgnoreMultibreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<MultiBreakpointId>(args[MbrInstance]);
    const auto count = mili::from_string<int>(args[Count]);
    auto mbr = ctx.getMultiBreakpoint(mbrId);
    mbr->ignore(count);
}

} // namespace NSCommands
