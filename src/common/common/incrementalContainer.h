/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        incrementalContainer.h
 * @author      Francisco Herrero
 * @date        2016-05-20
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

#ifndef INCREMENTAL_CONTAINER_H
#define INCREMENTAL_CONTAINER_H

#include "common/exceptions.h"

namespace NSCommon
{

template<class Index, class Value>
class IncrementalContainer
{
    using InnerContainer = std::unordered_map<Index, Value>;

public:
    static_assert(std::is_integral<Index>::value, "Index must be integral.");

    using const_iterator = typename InnerContainer::const_iterator;

    template<class... Args>
    Index emplace(Args&&... args)
    {
        ++_lastIndex;
        assert(_lastIndex != Index(0));
        _container.emplace(_lastIndex, Value{std::forward<Args>(args)...});
        return _lastIndex;
    }

    bool remove(Index index)
    {
        return _container.erase(index) != 0u;
    }

    bool exists(Index index) const
    {
        return _container.count(index) != 0u;
    }

    const Value& get(Index index) const
    try
    {
        return _container.at(index);
    }
    catch (std::out_of_range)
    {
        throw NSCommon::InvalidMultibreakpoint();
    }

    Value& get(Index index)
    try
    {
        return _container.at(index);
    }
    catch (std::out_of_range)
    {
        throw NSCommon::InvalidMultibreakpoint();
    }

    const_iterator cbegin() const
    {
        return _container.cbegin();
    }

    const_iterator cend() const
    {
        return _container.cend();
    }

private:
    InnerContainer _container;
    Index          _lastIndex = Index(0);
};

} // namespace NSCommon

#endif // INCREMENTAL_CONTAINER_H
