/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbBreakpointAspect.h
 * @author      Francisco Herrero
 * @author      Leonardo Boquillón
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


#ifndef _GDB_BREAKPOINT_ASPECT_INCLUDE_H_
#define _GDB_BREAKPOINT_ASPECT_INCLUDE_H_

#include <memory>
#include "mi_gdb.h"
#include "common/exceptions.h"
#include "common/baseTypes.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbBreakpointAspect : public NextAspect, private IBreakpointProxy
{
public:

    using NextAspect::NextAspect;

    std::shared_ptr<IUserBreakpoint> addBreakpoint(const BreakpointLocation& loc, Callback callback);

protected:
    /** NextAspect implementation. */
    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& stopReason,
                                  moirai::PostIterationAction& nextAction) override;

private:

    inline bool breakCondition(std::size_t breakpointNumber, const std::string& condition);

    // From IBreakpointInternals:
    bool disableBreakpoint(IUserBreakpoint* breakpoint) override;
    bool enableBreakpoint(IUserBreakpoint* breakpoint) override;
    bool ignoreBreakpoint(IUserBreakpoint* breakpoint, int count) override;
    bool deleteBreakpoint(IUserBreakpoint* breakpoint) override;

    std::unordered_map<typename Breakpoint::BreakpointID, std::shared_ptr<IInternalBreakpoint>> breakpoints;
};

template<class NextAspect>
inline bool GdbBreakpointAspect<NextAspect>::breakCondition(std::size_t breakpointNumber, const std::string& condition)
{
    return gmi_break_set_condition(this->handler, breakpointNumber, condition.c_str()) != 0;
}

template<class NextAspect>
std::shared_ptr<IUserBreakpoint> GdbBreakpointAspect<NextAspect>::addBreakpoint(
        const BreakpointLocation& location, Callback callback)
{
    const auto insertedBr = gmi_break_insert(this->handler, location.file.c_str(), location.line);
    if (insertedBr == nullptr)
    {
        throw NSCommon::ErrorCreatingBreakpoint(mi_error_from_gdb);
    }

    std::shared_ptr<Breakpoint> insertedBreakpoint = std::make_shared<Breakpoint>(callback, insertedBr, static_cast<IBreakpointProxy*>(this));
    breakpoints[insertedBr->number] = insertedBreakpoint;
    if (!location.condition.empty())
    {
        breakCondition(insertedBr->number, location.condition.c_str());
    }
    return insertedBreakpoint;
}

template<class NextAspect>
inline bool GdbBreakpointAspect<NextAspect>::disableBreakpoint(IUserBreakpoint* breakpoint)
{
    return gmi_break_state(this->handler, breakpoint->id(), false) != 0;
}

template<class NextAspect>
inline bool GdbBreakpointAspect<NextAspect>::enableBreakpoint(IUserBreakpoint* breakpoint)
{
    return gmi_break_state(this->handler, breakpoint->id(), true) != 0;
}

template<class NextAspect>
inline bool GdbBreakpointAspect<NextAspect>::ignoreBreakpoint(IUserBreakpoint* breakpoint, int count)
{
    return gmi_break_set_times(this->handler, breakpoint->id(), count) != 0;
}

template<class NextAspect>
inline bool GdbBreakpointAspect<NextAspect>::deleteBreakpoint(IUserBreakpoint* breakpoint)
{
    return gmi_break_delete(this->handler, breakpoint->id()) != 0;
}

template<class NextAspect>
void GdbBreakpointAspect<NextAspect>::processStopReason(mi_output* const response, const NSCommon::StopReason& stopReason, moirai::PostIterationAction& nextAction)
{
    if (stopReason.reason == sr_bkpt_hit)
    {
        auto br = stopReason.bkptno;
        breakpoints.at(br)->hit(nextAction);
    }
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif /* _GDB_BREAKPOINT_ASPECT_INCLUDE_H_ */
