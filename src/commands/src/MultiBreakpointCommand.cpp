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
#include "commands/parserUtils.h"

namespace NSCommands
{

using NSDebuggingContext::BreakpointId;
using NSDebuggingContext::MultiBreakpointId;

void MultiBreakpointCommand::execute(const Expression& expression, NSDebuggingContext::Context& ctx)
{
    Expression expr = expression;
    cleanSpaces(expr);
    auto instanceId1 = parseBreakpointId(expr);
    auto location1 = parseBreakpointLocation(expr);

    if(!parseWhen(expr))
        throw NSCommon::InvalidArguments(expr);

    auto instanceId2 = parseBreakpointId(expr);
    auto location2 = parseBreakpointLocation(expr);
    location2.condition = parseBreakpointCondition(expr);

    if(!expr.empty())
        throw NSCommon::InvalidArguments(expr);

    auto mbc = new NSDebuggingContext::MultiBreakpoint(); // TODO: make unique in case of exception.

    mbc->addInconditionalBreakpoint(ctx.getInstance(instanceId1), location1);
    mbc->addConditionalBreakpoint(ctx.getInstance(instanceId2), location2);

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
