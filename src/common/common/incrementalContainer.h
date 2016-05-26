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

namespace NSCommon
{

/**
 * @brief Container of incremental indexed values.
 * @details Mantains the last inserted id and
 *          allows to remove elemends in the middle.
 *
 * @tparam Index Index type.
 * @tparam Value Value type.
 */
template<class Index, class Value>
class IncrementalContainer
{
    using InnerContainer = std::unordered_map<Index, Value>;

public:
    static_assert(std::is_integral<Index>::value, "Index must be integral.");

    using const_iterator = typename InnerContainer::const_iterator;

    /**
     * @brief Emplaces an element in container.
     * @param[in] args Element constructor arguments.
     * @return Index of inserted element.
     */
    template<class... Args>
    Index emplace(Args&&... args);

    /**
     * @brief Removes element.
     * @param[in] index Element index.
     * @return True if element previously existed. False otherwhise.
     */
    inline bool remove(Index index);

    /**
     * @brief Indicates if element exists.
     * @param[in] index Element index.
     * @return True if element exists. False otherwhise.
     */
    inline bool exists(Index index) const;

    /**
     * @brief Retrieves an indexed element.
     * @param[in] index Index of element to retrieve.
     * @return Element
     */
    inline const Value& get(Index index) const;

    /**
     * @brief Retrieves an indexed element.
     * @param[in] index Index of element to retrieve.
     * @return Element
     */
    inline Value& get(Index index);

    /**
     * @brief Constant begin iterator.
     * @return Begin iterator.
     */
    inline const_iterator cbegin() const;

    /**
     * @brief Constant end iterator.
     * @return End iterator.
     */
    inline const_iterator cend() const;

private:

    /** @brief Elements container */
    InnerContainer _container;

    /** @brief Last element index */
    Index          _lastIndex = Index(0);
};

} // namespace NSCommon

#define INCREMENTAL_CONTAINER_INLINE_H
#include "incrementalContainerInline.h"
#undef INCREMENTAL_CONTAINER_INLINE_H

#endif // INCREMENTAL_CONTAINER_H
