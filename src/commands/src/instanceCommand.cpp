/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        instanceCommand.cpp
 * @author      Francisco Herrero
 * @date        2016-05-05
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

#include <cstdlib>
#include <cassert>
#include "common/exceptions.h"
#include "commands/instanceCommand.h"

namespace NSCommands
{

using NSGdbProxy::GdbProxy;

void InstanceCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    if (args.empty())
    {
        auto id = ctx.getCurrentInstance();

        if (id == NSDebuggingContext::Context::NoInstance)
        {
            std::cout << "No instances yet.\n";
        }
        else
        {
            std::cout << "  Num\tConn\tState\tExecutable" << std::endl;
            for (auto& inst : ctx)
            {
                const auto insId = inst.first;
                const auto& ins = *inst.second;
                const auto isLocal = ins.getConnectionType() == GdbProxy::ConnectionType::Local;

                std::cout << (id == insId ? '*' : ' ') << " " << insId
                          << "\t" << (isLocal ? "local" : "remote")
                          << "\t" << (ins.isRunning() ? "running" : "stopped")
                          << "\t" << ins.getProgramName() << " " << ins.getArgs();
                std::cout << " [";
                if (isLocal)
                {
                    std::cout << "pid: " << ins.getPID();
                }
                else
                {
                    std::cout << "location: " << ins.getLocation();
                }
                std::cout << "]" << std::endl;
            }
        }
    }
    else
    {
        mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 1u);
        const auto id = mili::from_string<NSCommon::InstanceId>(args[0u]);
        ctx.setCurrentInstance(id);
        std::cout << "Instance number " << id << std::endl;
    }
}

} // namespace NSCommands
