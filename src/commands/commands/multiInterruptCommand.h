/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        multiInterruptCommand.h
 * @author      Gustavo Ojeda
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

#ifndef _MULTI_INTERRUPT_COMMAND_H_
#define _MULTI_INTERRUPT_COMMAND_H_

#include <string>
#include "common/exceptions.h"
#include "ICommand.h"

namespace NSCommands
{

/**
 * @brief Multi interrupt command.
 * @details Interrupts all running instances.
 */
class MultiInterruptCommand : public ICommand
{
private:

    /**
     * @brief Iterrupts all instances.
     * @param[in/out] ctx Current context.
     */
    static void multipleInterrupt(NSDebuggingContext::Context& ctx);

    /**
     * @brief Interrupt ids indicated by args.
     * @param[in]     args Instance ids.
     * @param[in/out] ctx  Current context.
     */
    static void interruptIds(const Arguments& args, NSDebuggingContext::Context& ctx);

    /** @brief ICommand implementation. */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

} // namespace NSCommands

#endif // _MULTI_INTERRUPT_COMMAND_H_
