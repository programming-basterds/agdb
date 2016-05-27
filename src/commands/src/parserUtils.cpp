/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        parserUtils.cpp
 * @author      Francisco Herrero
 * @date        2016-05-27
 * @brief       Utils for parsing commands.
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

#include "commands/parserUtils.h"

namespace NSCommands
{

BreakpointCondition parseBreakpointCondition(Expression& expr)
{
    std::smatch sm;
    BreakpointCondition condition;
    const auto matched = regex_search(expr, sm, std::regex("^" + SP + "if" + SP + "(" + PRINTABLE + ")"));
    if (matched)
    {
        condition = sm[1u];
        expr = sm.suffix().str();
    }
    return condition;
}

BreakpointLocation parseBreakpointLocation(Expression& expr)
{
    std::smatch sm;
    const auto matched = regex_search(expr, sm, std::regex("^(" + PATH + "):(" + NUMBER + ")"));

    if(!matched)
        throw NSCommon::InvalidArguments(expr);

    const BreakpointLocation location = {sm[1u], mili::from_string<NSCommon::LineNumber>(sm[2u]), BreakpointCondition()};
    expr = sm.suffix().str();
    return location;
}

BreakpointId parseBreakpointId(Expression& expr)
{
    std::smatch sm;
    const auto matched = regex_search(expr, sm, std::regex("^(" + NUMBER + ")" + SP));
    if(!matched)
        throw NSCommon::InvalidArguments(expr);
    const auto id = mili::from_string<BreakpointId>(sm[1u]);
    expr = sm.suffix().str();
    return id;
}

} // namespace NSCommands
