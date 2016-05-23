/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbStackFrameAspect.h
 * @author      Gustavo Ojeda
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

#ifndef _GDB_STACK_FRAME_ASPECT_INCLUDE_H_
#define _GDB_STACK_FRAME_ASPECT_INCLUDE_H_

#include <cassert>
#include <string>
#include <sstream>
#include "mi_gdb.h"
#include "common/exceptions.h"
#include "common/listUtils.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbStackFrameAspect : public NextAspect
{
    using FrameNumber  = unsigned;
    using FrameInfo    = mi_frames_struct;
    using FrameInfoStr = std::string;
    using FunctionName = std::string;
    using StackFrames  = NSCommon::ConstIterableType<mi_frames>;
    using Arguments    = NSCommon::ConstIterableType<mi_results>;

public:
    using NextAspect::NextAspect;

    inline void backtrace(NSCommon::EvaluationMessage& message);

protected:

    inline void processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction) override;

private:
    inline FrameInfoStr getStrFrom(const FrameInfo& frameInfo) const;

    static inline FrameInfoStr getFunctionInfo(const FunctionName& funcName, const Arguments& arguments);
};

template<class NextAspect>
inline typename GdbStackFrameAspect<NextAspect>::FrameInfoStr GdbStackFrameAspect<NextAspect>::getStrFrom(const FrameInfo& frameInfo) const
{
    std::stringstream ss;
    ss << "[Thread " << frameInfo.thread_id                            // Thread info
       << " -> Frame " << frameInfo.level << "] "                       // Frame info
       << std::hex << frameInfo.addr << std::dec                  // Address info
       << " in " << getFunctionInfo(frameInfo.func, frameInfo.args) // Function info
       << " at " << frameInfo.file << ':' << frameInfo.line;        // File info
    return ss.str();
}

template<class NextAspect>
inline typename GdbStackFrameAspect<NextAspect>::FrameInfoStr
GdbStackFrameAspect<NextAspect>::getFunctionInfo(const FunctionName& funcName,
        const Arguments& arguments)
{
    FrameInfoStr argsInfo(funcName + "(");
    for (const auto arg : arguments)
    {
        argsInfo += arg.var + '\n';
    }
    argsInfo += ")";
    return argsInfo;
}

template<class NextAspect>
inline void GdbStackFrameAspect<NextAspect>::backtrace(NSCommon::EvaluationMessage& message)
{
    StackFrames stackFrames(gmi_stack_list_frames(this->handler));
    if (not stackFrames.empty())
    {
        for (const auto stackFrame : stackFrames)
        {
            message += getStrFrom(stackFrame) + '\n';
        }
    }
    else
    {
        message = "No stack info";
    }
}

template<class NextAspect>
inline void GdbStackFrameAspect<NextAspect>::processStopReason(mi_output* const response,
        const NSCommon::StopReason& stopReason,
        moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif // _GDB_STACK_FRAME_ASPECT_INCLUDE_H_
