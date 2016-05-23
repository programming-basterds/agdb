/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbListAspect.h
 * @author      Francisco Herrero, Gustavo Ojeda
 * @date        2016-05-06
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

#ifndef _GDB_LIST_ASPECT_INCLUDE_H_
#define _GDB_LIST_ASPECT_INCLUDE_H_

#include <cassert>
#include <memory>
#include <fstream>
#include "mi_gdb.h"
#include "common/exceptions.h"
#include "common/baseTypes.h"
#include "gdbProxy/GdbBaseAspect.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbListAspect : public NextAspect
{
    using FramePtr = std::unique_ptr<mi_frames>;
    using Path = std::string;
public:
    using NextAspect::NextAspect;

    static inline void list(const NSCommon::FilePath& file,
                            const NSCommon::LineNumber lineNumber,
                            const NSCommon::LineCount count,
                            NSCommon::EvaluationMessage& lines);

    inline void list(NSCommon::EvaluationMessage& lines);

protected:

    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& stopReason,
                                  moirai::PostIterationAction& nextAction) override;

private:
    static inline void loadFile(std::ifstream& inputFile, const NSCommon::FilePath& file);

    static inline void advanceLines(std::ifstream& inputFile, const NSCommon::LineNumber lineNumber);

    static inline void addLines(std::ifstream& inputFile, const NSCommon::LineCount count, NSCommon::EvaluationMessage& lines);

    static const auto DefaultLinesCount = 5u;
};

template<class NextAspect>
inline void GdbListAspect<NextAspect>::loadFile(std::ifstream& inputFile, const NSCommon::FilePath& file)
{
    inputFile.open(file);
    mili::assert_throw<NSCommon::InvalidFilename>(inputFile.is_open());
    inputFile.unsetf(std::ios_base::skipws);
}

template<class NextAspect>
inline void GdbListAspect<NextAspect>::advanceLines(std::ifstream& inputFile, const NSCommon::LineNumber lineNumber)
{
    auto currentLine = 0u;
    std::istream_iterator<char> eof;
    std::istream_iterator<char> it(inputFile);

    bool found = (lineNumber == currentLine);
    while (it != eof and not found)
    {
        ++it;
        if (*it == '\n')
        {
            ++currentLine;
            found = (lineNumber == currentLine);
        }
    }

    mili::assert_throw<NSCommon::InvalidLineNumber>(found);
}

template<class NextAspect>
inline void GdbListAspect<NextAspect>::addLines(std::ifstream& inputFile, const NSCommon::LineCount count, NSCommon::EvaluationMessage& lines)
{
    auto currentCount = 0u;
    while (not inputFile.eof() and count != currentCount)
    {
        NSCommon::Lines currentLine;
        std::getline(inputFile, currentLine);
        lines += std::move(currentLine) + '\n';
        ++currentCount;
    }
}

template<class NextAspect>
inline void GdbListAspect<NextAspect>::list(const NSCommon::FilePath& file,
        const NSCommon::LineNumber lineNumber,
        const NSCommon::LineCount count,
        NSCommon::EvaluationMessage& lines)
{
    std::ifstream inputFile;
    loadFile(inputFile, file);
    advanceLines(inputFile, lineNumber);
    addLines(inputFile, count, lines);
}

template<class NextAspect>
inline void GdbListAspect<NextAspect>::list(NSCommon::EvaluationMessage& lines)
{
    const FramePtr frameInfo(gmi_stack_info_frame(this->handler));

    if (frameInfo.get() != nullptr)
    {
        Path path(frameInfo->from);
        path += frameInfo->file;
        list(path, frameInfo->line, DefaultLinesCount, lines);
    }
    else
    {
        lines += "There is not info available.";
    }
}

template<class NextAspect>
inline void GdbListAspect<NextAspect>::processStopReason(mi_output* const response,
                                                        const NSCommon::StopReason& stopReason,
                                                        moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif // _GDB_LIST_ASPECT_INCLUDE_H_
