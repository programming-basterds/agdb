/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        CommandsInterpreter.cpp
 * @author      Daniel Gutson
 * @author      Emanuel Bringas
 * @author      Francisco Herrero
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

#include <iomanip>
#include "commandLine/CommandsInterpreter.h"

namespace NSCommandLine
{

void HelpCommand::execute(NSDebuggingContext::Context& /*ctx*/)
{
    std::cout << "Commands:" << std::endl;

#define SEPARATOR
#define LAST_SEPARATOR
#define COMMANDS_TABLE(cmd, name, desc)   std::cout << std::left << std::setw(15) << name << std::setw(50) << desc << std::endl;
#include "commandLine/CommandList.h"
}

const std::regex Interpreter::ARG_RE("^[ ]*(([^ \\{\\}]+)|\\{([^\\}]+)\\})");

Arguments Interpreter::processArguments(std::string&& str)
{
    Arguments ret;
    std::smatch sm;
    while (std::regex_search(str, sm, ARG_RE))
    {
        Argument arg = sm[SimpleArgIndex].length() ? sm[SimpleArgIndex].str() : sm[BracedArgIndex].str();
        ret.push_back(std::move(arg));
        str = sm.suffix().str();
    }
    return ret;
}

void Interpreter::execute(const std::string& line)
{
    const auto separator = line.find(':');
    if (separator != std::string::npos)
    {
        const auto cmdName = line.substr(0, separator);
        const auto cmd = _commands.find(cmdName);
        if (cmd != _commands.end())
        {
            cmd->second->execute(processArguments(line.substr(separator + 1)), _ctx);
        }
        else
        {
            throw "Command not found";
        }
    }
    else
    {
        throw "Malformed command line.";
    }
}

} // namespace NSCommandLine
