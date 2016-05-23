/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        CommandsInterpreterInline.h
 * @author      Daniel Guston, Emanuel Bringas
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

#ifndef COMMANDS_INTERPRETER_INLINE_H
#error Do_not_include_this_file
#endif

namespace NSCommandLine
{

inline Interpreter::Interpreter(NSDebuggingContext::Context& ctx)
    : _commands(
{
#define SEPARATOR   ,
#define LAST_SEPARATOR
#define COMMANDS_TABLE(cmd, name, desc)   { name, &cmd##_instance }
#include "commandLine/CommandList.h"
}),
_ctx(ctx)
{
}

} // namespace NSCommandLine
