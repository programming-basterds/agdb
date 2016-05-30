/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        CommandPrint.h
 * @author      Gustavo Ojeda
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

#ifndef _COMMAND_PRINT_H_
#define _COMMAND_PRINT_H_

#include <string>
#include "common/exceptions.h"
#include "commands/ICommand.h"

namespace NSCommands
{

class PrintCommand : public ICommand
{
    using Message = std::string;

    enum ArgumentsIndex
    {
        Expression,
        ArgumentsNumber
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override
    {
        mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == ArgumentsNumber);

        Message msg;
        const auto cID = ctx.getCurrentInstance();
        auto& instance = ctx.getInstance(cID);
        instance.evaluateExpression(args[Expression], msg);

        std::cout << args[Expression] << " = " << msg << std::endl;
    }
};

} // namespace NSCommands

#endif // _COMMAND_PRINT_H_
