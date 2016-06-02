/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        baseCommands.cpp
 * @author      Daniel Gutson, Emanuel Bringas, Leonardo Boquillon
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

#include "commands/baseCommands.h"

namespace NSCommands
{

void NoArgsCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    if (not args.empty())
    {
        throw "This command shall not receive arguments.";
    }
    execute(ctx);
}

void QuitCommand::execute(NSDebuggingContext::Context& ctx)
{
    ctx.running = false; /* etc */
}

void ShowVersion::execute(NSDebuggingContext::Context& /*ctx*/)
{
    std::cout << "Agdb version 1.0beta, Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,"
              "Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,"
              "Taller Technologies.\n";
}

} // namespace NSCommands
