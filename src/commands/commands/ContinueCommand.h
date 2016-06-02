/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ContinueCommand.h
 * @author      Emanuel Brinags
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

#ifndef _CONTINUE_COMMAND_INCLUDE_H_
#define _CONTINUE_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

/**
 * @brief Continue command.
 * @details Continues current instance execution if stopped.
 */
class ContinueCommand : public ICommand
{
private:

    /** @brief ICommand implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif /* _CONTINUE_COMMAND_INCLUDE_H_ */
