/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        stepCommand.h
 * @author      Emanuel Bringas
 * @date        2016-05-12
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

#ifndef _STEP_COMMAND_INCLUDE_H_
#define _STEP_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

/**
 * @brief Step command.
 * @details Executes step gdb command in current instance.
 *
 */
class StepCommand : public ICommand
{
private:
    /** @brief Argument indexes */
    enum ArgsIndex
    {
        InstanceNumber,
        NumberOfArgs
    };

    /** ICommand implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif /* _STEP_COMMAND_INCLUDE_H_ */