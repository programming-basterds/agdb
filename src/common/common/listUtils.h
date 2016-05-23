/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        listUtils.h
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

#ifndef _GDB_LIST_UTILS_INCLUDE_H_
#define _GDB_LIST_UTILS_INCLUDE_H_

#include <iterator>

namespace NSCommon
{

template<class MIValueType>
class ConstIterableType
{
public:

    using value_type = MIValueType;

    ConstIterableType(value_type* const asmInsns) :
        _value(asmInsns)
    {}

    ~ConstIterableType()
    {
        delete _value;
    }

    class const_iterator: public std::iterator<std::forward_iterator_tag, typename ConstIterableType::value_type>
    {
    public:
        const_iterator(value_type* const valueType) :
            currentMiTypeValue(valueType)
        {}

        const_iterator& operator++()
        {
            assert(currentMiTypeValue != nullptr);
            currentMiTypeValue = currentMiTypeValue->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const auto result(*this);
            ++(*this);
            return result;
        }

        bool operator==(const const_iterator& other) const
        {
            return currentMiTypeValue == other.currentMiTypeValue;
        }

        inline bool operator!=(const const_iterator& other) const
        {
            return not operator==(other);
        }

        value_type operator*() const
        {
            return *currentMiTypeValue;
        }

        value_type* operator->() const
        {
            return currentMiTypeValue;
        }

        value_type* currentMiTypeValue = nullptr;
    };

    inline const_iterator begin() const
    {
        return _value;
    }


    inline const_iterator end() const
    {
        return nullptr;
    }

    bool empty() const
    {
        return _value == nullptr;
    }


private:
    value_type* const _value = nullptr;
};

} // End of namespace NSCommon

#endif // _GDB_LIST_UTILS_INCLUDE_H_
