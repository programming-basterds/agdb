/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ICommand.h
 * @author      Leonardo Boquillón
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

#ifndef _I_COMMAND_INCLUDE_H_
#define _I_COMMAND_INCLUDE_H_

#include <vector>
#include <string>

#include "debuggingContext/Context.h"

namespace NSCommands
{

using Argument = std::string;
using Arguments = std::vector<Argument>;

/**
 * @brief Command interface.
 * @details Execution interface for commands.
 */
struct ICommand
{
    /**
     * @brief Executes command.
     * @param[in] args Container of command arguments.
     * @param[in] ctx  Command current context.
     */
    virtual void execute(const Arguments& args, NSDebuggingContext::Context& ctx) = 0;

    /** @brief Destructor */
    virtual ~ICommand() = default;
};

} // namespace NSCommands

#endif /* _I_COMMAND_INCLUDE_H_ */
