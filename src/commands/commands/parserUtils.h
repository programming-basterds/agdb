/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        parserUtils.h
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


#ifndef COMMAND_PARSER_UTILS_H
#define COMMAND_PARSER_UTILS_H

#include <regex>
#include "commands/ICommand.h"
#include "common/Breakpoint.h"
#include "debuggingContext/ContextMultiBreakpointAspect.h"

namespace NSCommands
{

using NSDebuggingContext::BreakpointId;

static const std::string FSP = "[ ]*";
static const std::string SP = "[ ]+";
static const std::string NUMBER = "[1-9]+[0-9]*";
static const std::string PATH ="[A-Za-z_./]+";
static const std::string PRINTABLE = "[ -~]+";

/**
 * @brief Cleans first spaces from expression.
 * @param[in/out] expr Expression to proccess.
 */
inline void cleanSpaces(Expression& expr)
{
    std::smatch sm;
    std::regex_search(expr, sm, std::regex("^" + FSP));
    expr = sm.suffix().str();
}

/**
 * @brief Consumes when word and surrounding spaces.
 * @param[in/out] expr Expression to proccess.
 * @return True if parse was successfull. False otherwise.
 */
inline bool parseWhen(Expression& expr)
{
    std::smatch sm;
    const auto matched = std::regex_search(expr, sm, std::regex("^" + SP + "when" + SP));
    if (matched)
    {
        expr = sm.suffix().str();
    }
    return matched;
}

/**
 * @brief Process breakpoint Id
 * @param[in/out] expr Expression to proccess.
 * @return Breakpoint id
 */
BreakpointId parseBreakpointId(Expression& expr);

/**
 * @brief Process breakpoint location.
 * @param[in/out] expr Expression to proccess.
 * @return Breakpoint location
 */
BreakpointLocation parseBreakpointLocation(Expression& expr);

/**
 * @brief Process breakpoint condition.
 * @param[in/out] expr Expression to proccess.
 * @return Breakpoint condition.
 */
BreakpointCondition parseBreakpointCondition(Expression& expr);

} // namespace NSCommands

#endif // COMMAND_PARSER_UTILS_H
