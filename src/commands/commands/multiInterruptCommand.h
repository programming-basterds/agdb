/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        multiInterruptCommand.h
 * @author      Gustavo Ojeda
 * @date        2016-05-11
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

#ifndef _MULTI_INTERRUPT_COMMAND_H_
#define _MULTI_INTERRUPT_COMMAND_H_

#include <string>
#include "common/exceptions.h"
#include "ICommand.h"

namespace NSCommands
{

class MultiInterruptCommand : public ICommand
{
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override
    {
        if (args.empty())
        {
            multipleInterrupt(ctx);
        }
        else
        {
            interruptIds(args, ctx);
        }
    }

    static void multipleInterrupt(NSDebuggingContext::Context& ctx)
    {
        for (auto& proxy : ctx)
        {
            proxy.second->interrupt();
        }
    }

    static void interruptIds(const Arguments& args, NSDebuggingContext::Context& ctx)
    {
        for (const auto& arg : args)
        {
            auto id = 0u;
            mili::assert_throw<NSCommon::InvalidInstanceID>(mili::from_string<NSCommon::InstanceId>(arg, id));
            const auto instance = ctx.getInstance(id).lock();
            mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));
            instance->interrupt();
        }
    }
};

} // namespace NSCommands

#endif // _MULTI_INTERRUPT_COMMAND_H_
