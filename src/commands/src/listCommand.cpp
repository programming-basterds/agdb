/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        listCommand.cpp
 * @author      Gustavo Ojeda
 * @date        2016-06-02
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
#include "commands/listCommand.h"

namespace NSCommands
{

void ListCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    Message message;
    const auto cID = ctx.getCurrentInstance();
    const auto instance = ctx.getInstance(cID).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));
    if (args.size() == ArgumentsNumber)
    {
        auto lineNumber = 0u;
        auto lineCounter = 0u;
        const auto validArguments = mili::from_string<LineIndex>(args[LineNumber], lineNumber) and
                                    mili::from_string<LineIndex>(args[LineCounter], lineCounter);

        mili::assert_throw<NSCommon::InvalidArgumentNumbers>(validArguments);

        instance->list(args[Filename], lineNumber, lineCounter, message);
    }
    else if (args.size() == 0u)
    {
        instance->list(message);
    }
    else
    {
        throw NSCommon::InvalidArgumentNumbers{};
    }

    std::cout << message << std::endl;
}

} // namespace NSCommands
