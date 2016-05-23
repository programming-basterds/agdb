/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ContextMultiBreakpointAspect.h
 * @author      Leonardo Boquillón
 * @author      Francisco Herrero
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

#ifndef _CONTEXT_MULTI_BREAKPOINT_ASPECT_INCLUDE_H_
#define _CONTEXT_MULTI_BREAKPOINT_ASPECT_INCLUDE_H_

#include <vector>
#include <memory>
#include <cassert>
#include "common/exceptions.h"
#include "common/incrementalContainer.h"
#include "debuggingContext/MultiBreakpoint.h"

namespace NSDebuggingContext
{

using MultiBreakpointId = std::size_t;
using BreakpointId = std::size_t;
using NSCommon::IncrementalContainer;

template<class NextAspect>
class ContextMultiBreakpointAspect : public NextAspect
{
private:

    using MultiBreakpointContainer = IncrementalContainer<MultiBreakpointId, std::unique_ptr<MultiBreakpoint>>;
    using BreakpointContainer = IncrementalContainer<BreakpointId, std::shared_ptr<IUserBreakpoint>>;

public:
    using NextAspect::NextAspect;

    MultiBreakpointId addMultiBreakpoint(MultiBreakpoint* const mbr);
    MultiBreakpoint* getMultiBreakpoint(MultiBreakpointId id); // SHARED?
    BreakpointId addBreakpoint(const std::shared_ptr<IUserBreakpoint>& breakpoint);
    std::shared_ptr<IUserBreakpoint> getBreakpoint(BreakpointId id);

protected:

    MultiBreakpointContainer _multibreakpoints;
    BreakpointContainer      _breakpoints;
};

template<class NextAspect>
MultiBreakpointId ContextMultiBreakpointAspect<NextAspect>::addMultiBreakpoint(MultiBreakpoint* const mbr)
{
    return _multibreakpoints.emplace(mbr);
}

template<class NextAspect>
MultiBreakpoint* ContextMultiBreakpointAspect<NextAspect>::getMultiBreakpoint(MultiBreakpointId id)
{
    return _multibreakpoints.get(id).get();
}

template<class NextAspect>
BreakpointId ContextMultiBreakpointAspect<NextAspect>::addBreakpoint(const std::shared_ptr<IUserBreakpoint>& breakpoint)
{
    return _breakpoints.emplace(breakpoint);
}

template<class NextAspect>
std::shared_ptr<IUserBreakpoint> ContextMultiBreakpointAspect<NextAspect>::getBreakpoint(BreakpointId id)
{
    return _breakpoints.get(id);
}

} // end namespace NSDebuggingContext

#endif /* _CONTEXT_MULTI_BREAKPOINT_ASPECT_INCLUDE_H_ */
