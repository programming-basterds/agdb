/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ReadLine.h
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

#ifndef _READ_LINE_INCLUDE_H_
#define _READ_LINE_INCLUDE_H_

#include <string>

namespace NSCommandLine
{

class ReadLine
{
public:
    static bool read(std::string& line);

private:
    static const std::string prompt;
};

} // namespace NSCommandLine

#endif /* _READ_LINE_INCLUDE_H_ */
