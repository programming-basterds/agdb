/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        incrementalContainerInline.h
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

#ifndef INCREMENTAL_CONTAINER_INLINE_H
#error Do not include this.
#endif

#include "common/exceptions.h"

namespace NSCommon
{

template<class Index, class Value>
template<class... Args>
Index IncrementalContainer<Index, Value>::emplace(Args&&... args)
{
    ++_lastIndex;
    assert(_lastIndex != Index(0));
    _container.emplace(_lastIndex, Value{std::forward<Args>(args)...});
    return _lastIndex;
}

template<class Index, class Value>
inline bool IncrementalContainer<Index, Value>::remove(Index index)
{
    return _container.erase(index) != 0u;
}

template<class Index, class Value>
inline bool IncrementalContainer<Index, Value>::exists(Index index) const
{
    return _container.count(index) != 0u;
}

template<class Index, class Value>
inline const Value& IncrementalContainer<Index, Value>::get(Index index) const
try
{
    return _container.at(index);
}
catch (std::out_of_range)
{
    throw NSCommon::InvalidMultibreakpoint();
}

template<class Index, class Value>
inline Value& IncrementalContainer<Index, Value>::get(Index index)
try
{
    return _container.at(index);
}
catch (std::out_of_range)
{
    throw NSCommon::InvalidMultibreakpoint();
}

template<class Index, class Value>
inline typename IncrementalContainer<Index, Value>::const_iterator
    IncrementalContainer<Index, Value>::cbegin() const
{
    return _container.cbegin();
}

template<class Index, class Value>
inline typename IncrementalContainer<Index, Value>::const_iterator
    IncrementalContainer<Index, Value>::cend() const
{
    return _container.cend();
}

} // namespace NSCommon
