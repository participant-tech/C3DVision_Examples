/****************************************************************************
**
** MIT License
** Copyright(c) 2025 C3D-Labs
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files(the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and / or sell copies of the Software, and to permit persons to whom
** the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
** OTHERWISE,ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
** USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef __QT_PREDICATES_H
#define __QT_PREDICATES_H

#include <functional>
#include <type_traits>
#include <utility>

namespace VSN {
namespace QtVision {

//////////////////
// find helpers
//////////////////
template<typename R, typename S, typename T>
decltype(auto) equal(R (S::*function)() const, T value)
{
    // This should use std::equal_to<> instead of std::equal_to<T>,
    // but that's not supported everywhere yet, since it is C++14
    return std::bind<bool>(std::equal_to<T>(), value, std::bind(function, std::placeholders::_1));
}

template<typename R, typename S, typename T>
decltype(auto) equal(R S::*member, T value)
{
    return std::bind<bool>(std::equal_to<T>(), value, std::bind(member, std::placeholders::_1));
}

//////////////////
// comparison predicates
//////////////////
template <typename Type>
auto equalTo(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of equalTo should be the same to prevent "
                      "unnecessary conversion.");
        return entry == value;
    };
}

template <typename Type>
auto unequalTo(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of unequalTo should be the same to prevent "
                      "unnecessary conversion.");
        return !(entry == value);
    };
}

template <typename Type>
auto lessThan(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of unequalTo should be the same to prevent "
                      "unnecessary conversion.");
        return entry < value;
    };
}

template <typename Type>
auto lessEqualThan(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of lessEqualThan should be the same to "
                      "prevent unnecessary conversion.");
        return !(value < entry);
    };
}

template <typename Type>
auto greaterThan(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of greaterThan should be the same to "
                      "prevent unnecessary conversion.");
        return value < entry;
    };
}

template <typename Type>
auto greaterEqualThan(Type &&value)
{
    return [value = std::forward<Type>(value)] (const auto &entry)
    {
        static_assert(std::is_same<std::decay_t<Type>,
                      std::decay_t<decltype(entry)>>::value,
                      "The container and predicate type of greaterEqualThan should be the same to "
                      "prevent unnecessary conversion.");
        return !(entry < value);
    };
}

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PREDICATES_H */
