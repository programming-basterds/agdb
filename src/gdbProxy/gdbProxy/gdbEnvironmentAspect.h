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

/**
 * @brief GDB Proxy Environment aspect.
 * @details Is responsable of the environment
 *          variables manipulation.
 *
 * @tparam NextAspect Next aspect in AOP weave.
 */
template<class NextAspect>
class GdbEnvironmentAspect: public NextAspect
{
public:
    /** Use NextAspect constructor */
    using NextAspect::NextAspect;

    /**
     * @brief Sets a program or gdb variable.
     * @param[in] var Variable to assign.
     * @param[in] value Value or expression to assign to variable.
     */
    inline void setVariable(const std::string& var, const std::string& value);

    /**
     * @brief Sets a gdb environment variable.
     * @param[in] var Variable to assign.
     * @param[in] value Value to assign to variable.
     */
    inline void setEnvironment(const std::string& var, const std::string& value);

protected:

    /** NextAspect implementation. */
    inline void processStopReason(mi_output* const response,
                                  const NSCommon::StopReason& stopReason,
                                  moirai::PostIterationAction& nextAction) override;

};

template<class NextAspect>
inline void GdbEnvironmentAspect<NextAspect>::setVariable(const std::string& var, const std::string& value)
{
    const auto response = gmi_gdb_set_var(this->handler, var.c_str(), value.c_str());
    if (response == 0)
    {
        throw NSCommon::ErrorSet(mi_error_from_gdb);
    }
}

template<class NextAspect>
inline void GdbEnvironmentAspect<NextAspect>::setEnvironment(const std::string& var, const std::string& value)
{
    const auto response = gmi_gdb_set(this->handler, var.c_str(), value.c_str());
    if (response == 0)
    {
        throw NSCommon::ErrorSet(mi_error_from_gdb);
    }
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
