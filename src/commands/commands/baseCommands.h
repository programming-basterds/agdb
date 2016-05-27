/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        baseCommands.h
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

#ifndef _BASE_COMMANDS_H_
#define _BASE_COMMANDS_H_

#include "commands/argumentedCommand.h"

namespace NSCommands
{

class NoArgsCommand : public ArgumentedCommand
{
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override final
    {
        if (not args.empty())
        {
            throw "This command shall not receive arguments.";
        }
        execute(ctx);
    }

    virtual void execute(NSDebuggingContext::Context& ctx) = 0;
};

class QuitCommand : public NoArgsCommand
{
    void execute(NSDebuggingContext::Context& ctx) override;
};

class ShowVersion : public NoArgsCommand
{
    void execute(NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // _BASE_COMMANDS_H_
