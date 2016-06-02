/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        diffCommand.h
 * @author      Emanuel Bringas
 * @date        2016-05-09
 * @brief       Diff commands classes declaration.
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

#ifndef _DIFF_COMMAND_INCLUDE_H_
#define _DIFF_COMMAND_INCLUDE_H_

#include <future>
#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

/**
 * @brief Diff command abstract class.
 * @details Provides a generic implementation for Diff command.
 */
class DiffCommand : public ICommand
{
protected:

    /**
     * @brief Steps an instance.
     * @param[in/out] instance Instance to step.
     * @return        Result of stepping implementation.
     */
    virtual std::future<bool> steppingMethod(std::shared_ptr<NSGdbProxy::GdbProxy>& instance) = 0;

private:

    /** @brief Argument index */
    enum ArgsIndex
    {
        InstanceNumber1,
        InstanceNumber2,
        NumberOfArgs
    };

    /**
     * @brief Executes diff command with steppingMethod.
     * @param[in] args Container of command arguments.
     * @param[in] ctx  Command current context.
     */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Next Diff command.
 * @details Implements diff using GDB command n.
 */
class NextDiffCommand : public DiffCommand
{
private:

    /** @brief DiffCommand implementation. */
    std::future<bool> steppingMethod(std::shared_ptr<NSGdbProxy::GdbProxy>& instance) override;
};

/**
 * @brief Next Istruction Diff command.
 * @details Implements diff using GDB command ni.
 */
class NextInstructionDiffCommand : public DiffCommand
{
private:

    /** @brief DiffCommand implementation. */
    std::future<bool> steppingMethod(std::shared_ptr<NSGdbProxy::GdbProxy>& instance) override;
};

/**
 * @brief Step Diff command.
 * @details Implements diff using GDB command s.
 */
class StepDiffCommand : public DiffCommand
{
private:

    /** @brief DiffCommand implementation. */
    std::future<bool> steppingMethod(std::shared_ptr<NSGdbProxy::GdbProxy>& instance) override;
};

/**
 * @brief Step Instruction Diff command.
 * @details Implements diff using GDB command si.
 */
class StepInstructionDiffCommand : public DiffCommand
{
private:

    /** @brief DiffCommand implementation. */
    std::future<bool> steppingMethod(std::shared_ptr<NSGdbProxy::GdbProxy>& instance) override;
};

} // namespace NSCommands

#endif /* _DIFF_COMMAND_INCLUDE_H_ */