/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        setCommand.cpp
 * @author      Francisco Herrero
 * @date        2016-06-01
 * @brief       SetCommand class definition.
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

#include <regex>
#include "commands/setCommand.h"

namespace NSCommands
{

void parseVar(const std::string& text, std::string& var, std::string& value)
{
    std::smatch sm;
    const auto matched = std::regex_search(text, sm, std::regex("="));
    if (!matched)
    {
        throw NSCommon::InvalidArgument(text);
    }
}

void SetCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    auto instanceId = ctx.getCurrentInstance();
    auto& instance = ctx.getInstance(instanceId);
    //instance.setValue(const std::string& var, const std::string& value);
}

} // namespace NSCommands
