/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        agdb.cpp
 * @author      Daniel Gutson, Emanuel Bringas
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

#include "debuggingContext/MultiBreakpoint.h"
#include "debuggingContext/Context.h"
#include "gdbProxy/GdbProxy.h"
#include "commandLine/ReadLine.h"
#include "commandLine/CommandsInterpreter.h"

using namespace NSCommandLine;

int main()
{
    int ret = EXIT_SUCCESS;
    NSDebuggingContext::Context ctx;
    Interpreter interpreter(ctx);
    const std::string errorTag = "\033[1;31m[Error] \033[0m ";
    std::string line;
    while (ctx.running)
    {
        ctx.running = ReadLine::read(line);
        if (ctx.running && !line.empty())
        {
            try
            {
                interpreter.execute(line);
            }
            catch (const std::exception& e)
            {
                std::cerr << errorTag << e.what() << std::endl;
            }
            catch (const char* msg)
            {
                std::cerr << errorTag << msg << std::endl;
            }
            catch (...)
            {
                std::cerr << errorTag << "Uncaught error... please call Boquillon" << std::endl;
            }
        }
    }
    std::cout << std::endl;

    return ret;
}