/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        diffCommand.cpp
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
#include "commands/diffCommand.h"

namespace NSCommands
{

void DiffCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 2);
    auto& instance1 = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[InstanceNumber1]));
    auto& instance2 = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[InstanceNumber2]));
    mili::assert_throw<NSCommon::InstancesAreNotStopped>(not instance1.isRunning() and not instance2.isRunning());

    std::cout << instance1.frame() << std::endl;
    instance1.next();
    sleep(1);
    std::cout << instance1.frame() << std::endl;
    instance1.next();
    std::cout << instance1.frame() << std::endl;
    instance1.next();

    // while ((instance1.isRunning() and instance2.isRunning()) and (instance1.frame() == instance2.frame()))
    // {
    //     auto future = instance1.next();
    //     auto future2 = instance1.next();
    //     future.wait();
    //     future2.wait();

    //     instance2.next();
    //     wait of

    // }

    // if (instance1.isRunning() and instance2.isRunning())
    // {
    //     std::cout << "A difference of exceution was found:" << std::endl;
    //     std::cout << "Instance " << InstanceNumber1 << " " << instance1.frame() << std::endl;
    //     std::cout << "instance " << InstanceNumber2 << " " << instance2.frame() << std::endl;
    // }
    // else if (instance1.frame() != instance2.frame())
    // {
    //     std::cout << "instance " << InstanceNumber1 << (instance1.isRunning() ? " still running" : " has stoped") << std::endl;
    //     std::cout << "instance " << InstanceNumber2 << (instance1.isRunning() ? " still running" : " has stoped") << std::endl;
    // }
    // else
    // {
    //     std::cout << "Error occur while run diff command." << std::endl;
    // }

}

} // namespace NSCommands
