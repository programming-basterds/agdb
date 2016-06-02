/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        FwdCommand.cpp
 * @author      Emanuel Bringas
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

#include "gdbProxy/GdbProxy.h"
#include "commands/FwdCommand.h"

namespace NSCommands
{

void FwdCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    const auto instance = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[InstanceNumber])).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    std::string msg;
    for (unsigned int i = GDBMessage; i < args.size(); ++i)
    {
        msg += " " + args[i];
    }

    instance->sendMessageToGDB(msg);
}

} // namespace NSCommands
