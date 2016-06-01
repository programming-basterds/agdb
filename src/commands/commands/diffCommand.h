/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        diffCommand.h
 * @author      Emanuel Bringas
 * @date        2016-05-09
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

#ifndef _DIFF_COMMAND_INCLUDE_H_
#define _DIFF_COMMAND_INCLUDE_H_

#include <future>
#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

class DiffCommand : public ICommand
{
protected:
    virtual std::future<bool> steppingMethod(NSGdbProxy::GdbProxy& instance) = 0;

private:
    enum ArgsIndex
    {
        InstanceNumber1,
        InstanceNumber2,
        NumberOfArgs
    };

    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

class NextDiffCommand : public DiffCommand
{
    std::future<bool> steppingMethod(NSGdbProxy::GdbProxy& instance) override;
};

class NextInstructionDiffCommand : public DiffCommand
{
    std::future<bool> steppingMethod(NSGdbProxy::GdbProxy& instance) override;
};

class StepDiffCommand : public DiffCommand
{
    std::future<bool> steppingMethod(NSGdbProxy::GdbProxy& instance) override;
};

class StepInstructionDiffCommand : public DiffCommand
{
    std::future<bool> steppingMethod(NSGdbProxy::GdbProxy& instance) override;
};

} // namespace NSCommands

#endif /* _DIFF_COMMAND_INCLUDE_H_ */