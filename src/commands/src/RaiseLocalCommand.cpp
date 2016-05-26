/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        RaiseLocalCommand.cpp
 * @author      Emanuel Bringas
 * @author      Leonardo Boquillón
 * @author      Francisco Herrero
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

#include "commands/RaiseLocalCommand.h"
#include "gdbProxy/GdbProxy.h"

namespace NSCommands
{

void RaiseLocalCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(0u < args.size() && args.size() <= unsigned(NumberOfArgs));

    NSGdbProxy::GdbProxy* proxy = new NSGdbProxy::GdbProxy(args[Program]);
    mili::assert_throw<NSCommon::LocalGDBConnectionFailed>(proxy->connectLocal());

    const auto progArgs = (args.size() == ProgramArguments) ? Argument{} :
                          args[ProgramArguments];
    mili::assert_throw<NSCommon::LocalGDBConnectionFailed>(proxy->setProgramArguments(progArgs));

    proxy->run();

    const auto nid = ctx.addGdbInstance(proxy);
    ctx.setCurrentInstance(nid);

    std::cout << "Instance number " << nid << std::endl;
}

} // namespace NSCommands
