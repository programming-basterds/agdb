/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        backtraceCommand.cpp
 * @author      Gustavo Ojeda
 * @date        2016-06-02
 * @brief       BacktraceCommand class definition.
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

#include "commands/backtraceCommand.h"

namespace NSCommands
{

void BacktraceCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 0);
    Message message;
    const auto cID = ctx.getCurrentInstance();
    const auto instance = ctx.getInstance(cID).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    instance->backtrace(message);

    std::cout << message << std::endl;
}

} // namespace NSCommands
