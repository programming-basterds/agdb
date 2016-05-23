/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbPrintAspect.h
 * @author      Leonardo Boquillón, Francisco Herrero, Gustavo Ojeda
 * @date        2016-05-03
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

#ifndef _GDB_PRINT_ASPECT_INCLUDE_H_
#define _GDB_PRINT_ASPECT_INCLUDE_H_

#include <string>
#include "mi_gdb.h"
#include "common/exceptions.h"
#include "common/baseTypes.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbPrintAspect : public NextAspect
{
public:
    using NextAspect::NextAspect;

    inline void evaluateExpression(const NSCommon::GDBExpression& expression, NSCommon::EvaluationMessage& evaluationMessage);

protected:

    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& stopReason,
                                  moirai::PostIterationAction& nextAction) override;

};

template<class NextAspect>
inline void GdbPrintAspect<NextAspect>::evaluateExpression(const std::string& expression,
        std::string& evaluationMessage)
{
    const char* answer = gmi_data_evaluate_expression(this->handler, expression.c_str());
    const auto validExpression = answer != nullptr;
    if (validExpression)
    {
        evaluationMessage = answer;
    }
    else
    {
        throw NSCommon::InvalidExpressionToValidate(expression);
    }
}

template<class NextAspect>
inline void GdbPrintAspect<NextAspect>::processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif /* _GDB_PRINT_ASPECT_INCLUDE_H_ */