/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        RaiseRemoteCommand.h
 * @author      Emanuel Bringas
 * @date        2016-05-06
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

#ifndef _RAISE_REMOTE_COMMAND_INCLUDE_H_
#define _RAISE_REMOTE_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/argumentedCommand.h"

namespace NSCommands
{

class RaiseRemoteCommand : public ArgumentedCommand
{
private:
    enum ArgsIndex
    {
        Location,
        Program,
        ProgramArguments,
        NumberOfArgs
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif /* _RAISE_COMMAND_INCLUDE_H_ */
