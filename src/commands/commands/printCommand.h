/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        printCommand.h
 * @author      Gustavo Ojeda
 * @date        2016-05-04
 * @brief       PrintCommand class declaration.
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
#include "commands/ICommand.h"

namespace NSCommands
{

/**
 * @brief Print command.
 * @details Evaluates an expression in current instance.
 */
class PrintCommand : public ICommand
{
    using Message = std::string;

    /** @brief Arguments index. */
    enum ArgumentsIndex
    {
        Expression,
        ArgumentsNumber
    };

    /** ICommand implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // _COMMAND_PRINT_H_
