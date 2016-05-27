/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        argumentedCommand.h
 * @author      Francisco Herrero
 * @date        2016-05-27
 * @brief       ArgumentedCommand class declaration.
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

#ifndef ARGUMENTED_COMMAND_H
#define ARGUMENTED_COMMAND_H

#include <vector>
#include <string>
#include "commands/ICommand.h"

namespace NSCommands
{

using Argument = std::string;
using Arguments = std::vector<Argument>;

/**
 * @brief Argumented Command abstract class.
 * @details Represents a command with space separated arguments.
 */
class ArgumentedCommand : public ICommand
{
protected:

    /**
     * @brief Execute argumented command.
     * @param[in] args Arguments
     * @param[in/out] ctx Context.
     */
    virtual void execute(const Arguments& args, NSDebuggingContext::Context& ctx) = 0;

private:

    /**
     * @brief Fetch arguments from expression.
     * @param[in] expression Expression.
     * @return Arguments parsed.
     */
    static Arguments getArguments(const Expression& expression);

    /** ICommand interface implementation. */
    void execute(const Expression& expression, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // ARGUMENTED_COMMAND_H
