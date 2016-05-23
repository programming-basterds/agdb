/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        RaiseRemoteCommand.cpp
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

#include "mili/mili.h"

#include "gdbProxy/GdbProxy.h"
#include "common/exceptions.h"
#include "commands/RaiseRemoteCommand.h"

namespace NSCommands
{

void RaiseRemoteCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    std::unique_ptr<NSGdbProxy::GdbProxy> proxy(new NSGdbProxy::GdbProxy(args[Program]));
    mili::assert_throw<NSCommon::LocalGDBConnectionFailed>(proxy->connectLocal());
    mili::assert_throw<NSCommon::RemoteGDBConnectionFailed>(proxy->connectRemote(args[Location]));
    mili::assert_throw<NSCommon::ParameterSettingFailed>(proxy->loadSymbols());

    const auto nid = ctx.addGdbInstance(std::move(proxy));
    ctx.setCurrentInstance(nid);
    std::cout << "Instance number " << nid << std::endl;
}

} // namespace NSCommands
