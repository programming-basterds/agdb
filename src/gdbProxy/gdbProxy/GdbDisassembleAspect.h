/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbDisassembleAspect.h
 * @author      Francisco Herrero, Gustavo Ojeda
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

#ifndef _GDB_DISASSEMBLE_ASPECT_INCLUDE_H_
#define _GDB_DISASSEMBLE_ASPECT_INCLUDE_H_

#include <cassert>
#include <string>
#include "mi_gdb.h"
#include "common/exceptions.h"
#include "common/baseTypes.h"
#include "common/listUtils.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbDisassembleAspect : public NextAspect
{
    using Dissasembled = NSCommon::ConstIterableType<mi_asm_insns>;
    using ASMInstruction = NSCommon::ConstIterableType<mi_asm_insn>;
public:

    using NextAspect::NextAspect;

    enum DisassembleMode
    {
        DisassemblyOnly = 0,
        SourceAndDisassemblyDeprecated,
        DisassemblyWithRawOpCodes,
        SourceAndDisassemblyWithRawOpCodesDeprecated,
        SourceAndDisassembly,
        SourceAndDisassemblyWithRawOpCodes
    };

    inline void disassemble(const NSCommon::FilePath& file,
                            NSCommon::LineNumber line,
                            NSCommon::LineCount count,
                            DisassembleMode mode,
                            NSCommon::Lines& lines) const;

protected:

    inline void processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction) override;

private:
    static inline void addInstructions(const NSCommon::LineNumber lineNumber,
                                       const ASMInstruction& instructions,
                                       NSCommon::Lines& lines);
};

template<class NextAspect>
inline void GdbDisassembleAspect<NextAspect>::disassemble(const NSCommon::FilePath& file,
        NSCommon::LineNumber line,
        NSCommon::LineCount count,
        DisassembleMode mode,
        NSCommon::Lines& lines) const
{
    Dissasembled dissasemble(gmi_data_disassemble_fl(this->handler, file.c_str(), line, count, mode));

    mili::assert_throw<NSCommon::DisassembleExecutionFailed>(not dissasemble.empty());

    for (const auto assembler : dissasemble)
    {
        addInstructions(assembler.line, assembler.ins, lines);
    }
}

template<class NextAspect>
inline void GdbDisassembleAspect<NextAspect>::processStopReason(mi_output* const response,
                                                                const NSCommon::StopReason& stopReason,
                                                                moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, stopReason, nextAction);
}

template<class NextAspect>
inline void GdbDisassembleAspect<NextAspect>::addInstructions(const NSCommon::LineNumber lineNumber,
        const ASMInstruction& instructions,
        NSCommon::Lines& lines)
{
    for (const auto instruction : instructions)
    {
        lines += std::to_string(lineNumber) + ":\t" + instruction.inst + '\n'; //TODO: Change line number by address
    }
}

} // namespace NSGdbProxy

#endif // _GDB_DISASSEMBLE_ASPECT_INCLUDE_H_
