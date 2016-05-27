/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        argumentedCommand.cpp
 * @author      Francisco Herrero
 * @date        2016-05-27
 * @brief       ArgumentedCommand class definition.
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

#include "commands/argumentedCommand.h"

namespace NSCommands
{

Arguments ArgumentedCommand::getArguments(const Expression& expression)
{
    Arguments arguments;
    std::stringstream ss(expression);
    Argument arg;
    while (ss >> arg);
    {
        arguments.push_back(std::move(arg));
        arg = Argument();
    }
    return arguments;
}

void ArgumentedCommand::execute(const Expression& expression, NSDebuggingContext::Context& ctx)
{
    execute(getArguments(expression), ctx);
}

} // namespace NSCommands
