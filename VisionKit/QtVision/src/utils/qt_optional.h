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

#ifndef __QT_OPTIONAL_H
#define __QT_OPTIONAL_H

/*
    optional<T>
    make_optional(t)

    See std(::experimental)::optional.
*/

// std::optional from Apple's Clang supports methods that throw std::bad_optional_access only
// with deployment target >= macOS 10.14
// TODO: Use std::optional everywhere when we can require macOS 10.14
#if !defined(__apple_build_version__)

#include <optional>

namespace VSN {
namespace QtVision {

using std::optional;
using std::nullopt;
using std::nullopt_t;
using std::in_place;

// make_optional is a copy, since there is no sensible way to import functions in C++
template<class T>
constexpr optional<std::decay_t<T>> make_optional(T &&v)
{
    return optional<std::decay_t<T>>(std::forward<T>(v));
}

template<class T, class... Args>
optional<T> make_optional(Args &&... args)
{
    return optional<T>(in_place, std::forward<Args>(args)...);
}

template<class T, class Up, class... Args>
constexpr optional<T> make_optional(std::initializer_list<Up> il, Args &&... args)
{
    return optional<T>(in_place, il, std::forward<Args>(args)...);
}

} // namespace QtVision
} // namespace VSN

#else

#include <3rdparty/optional/optional.hpp>

namespace VSN {
namespace QtVision {

// --> Utils::optional
using std::experimental::optional;
// --> Utils::nullopt
using std::experimental::nullopt;
using std::experimental::nullopt_t;
// --> Utils::in_place
using std::experimental::in_place;

// TODO: make_optional is a copy, since there is no sensible way to import functions in C++
template <class T>
constexpr optional<typename std::decay<T>::type> make_optional(T&& v)
{
  return optional<typename std::decay<T>::type>(std::experimental::constexpr_forward<T>(v));
}

template <class X>
constexpr optional<X&> make_optional(std::reference_wrapper<X> v)
{
  return optional<X&>(v.get());
}

} // namespace QtVision
} // namespace VSN

#endif

#endif /* __QT_OPTIONAL_H */
