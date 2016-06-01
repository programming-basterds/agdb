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

#include "commands/setCommand.h"

namespace NSCommands
{

void SetCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 1u || args.size() == 2u);

    auto instanceId = ctx.getCurrentInstance();
    auto& instance = ctx.getInstance(instanceId);

    if (args.size() == 1u)
    {
        const auto& assignation = args[0u];
        auto pos = assignation.find('=');
        if (pos == std::string::npos)
        {
            throw NSCommon::InvalidArgument(assignation);
        }
        instance.setVariable(assignation.substr(0u, pos), assignation.substr(pos+1u));
    }
    else // args.size() == 2u
    {
        instance.setEnvironment(args[0u], args[1u]);
    }
}

} // namespace NSCommands
