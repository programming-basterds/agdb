/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        baseTypes.h
 * @author      Francisco Herrero
 * @author      Gustavo Ojeda
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

#ifndef _BASE_TYPES_INCLUDE_H_
#define _BASE_TYPES_INCLUDE_H_

#include <string>
#include "mi_gdb.h"

namespace NSCommon
{

using FilePath = std::string;
using Lines = std::string;
using LineNumber = unsigned;
using LineCount = unsigned;
using GDBExpression = std::string;
using EvaluationMessage = std::string;

struct StopReason
{
    StopReason()
    {}

    StopReason(mi_stop_struct* stop) :
        reason(stop->reason),
        haveThreadOId(stop->have_thread_id),
        haveBkptno(stop->have_bkptno),
        haveExitCode(stop->have_exit_code),
        threadId(stop->thread_id),
        bkptno(stop->bkptno),

        exitCode(stop->exit_code)
    {
        if (stop->signal_name != nullptr)
        {
            signalName = std::string(stop->signal_name);
        }

        if (stop->signal_meaning != nullptr)
        {
            signalMeaning = std::string(stop->signal_meaning);
        }
    }

    mi_stop_reason  reason;
    bool            haveThreadOId;
    bool            haveBkptno;
    bool            haveExitCode;
    unsigned int    threadId;
    unsigned int    bkptno;
    std::string     signalName;
    std::string     signalMeaning;
    int             exitCode;
};

using InstanceId = unsigned int;

} // End of namespace NSCommon

#endif // _BASE_TYPES_INCLUDE_H_

 /* Flags indicating if non-pointer fields are filled. */
