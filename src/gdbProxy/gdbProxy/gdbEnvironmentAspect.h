/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbEnvironmentAspect.h
 * @author      Francisco Herrero
 * @date        2016-06-01
 * @brief       Contains GDB Proxy Environment aspect.
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

#ifndef GDB_ENVIRONMENT_ASPECT_H
#define GDB_ENVIRONMENT_ASPECT_H

#include <string>
#include "common/exceptions.h"

namespace NSGdbProxy
{

template<class NextAspect>
class GdbEnvironmentAspect: public NextAspect
{
public:

    using NextAspect::NextAspect;

    inline void setValue(const std::string& var, const std::string& value);

protected:

    /** NextAspect implementation. */
    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& stopReason,
                                  moirai::PostIterationAction& nextAction) override;
};

template<class NextAspect>
inline void GdbEnvironmentAspect<NextAspect>::setValue(const std::string& var, const std::string& value)
{
    const auto response = gmi_gdb_set(this->handler, var.c_str(), value.c_str());
    mili::assert_throw<NSCommon::ErrorSet>(response != 0);
}

template<class NextAspect>
inline void GdbEnvironmentAspect<NextAspect>::processStopReason(mi_output* const response,
                                                        const NSCommon::StopReason& stopReason,
                                                        moirai::PostIterationAction& nextAction)
{
    NextAspect::processStopReason(response, stopReason, nextAction);
}

} // namespace NSGdbProxy

#endif // GDB_ENVIRONMENT_ASPECT_H
