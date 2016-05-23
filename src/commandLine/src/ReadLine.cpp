/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ReadLine.cpp
 * @author      Leonardo Boquillon
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

#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "commandLine/ReadLine.h"

namespace NSCommandLine
{

const std::string ReadLine::prompt("\033[1;36m(agdb) \033[0m");

bool ReadLine::read(std::string& line)
{
    char* read = readline(prompt.c_str());
    const auto success = (read != nullptr);

    if (success)
    {
        line = read;
        add_history(read);
        free(read);
    }

    return success;
}

} // namespace NSCommandLine
