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

////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Глобальные объявления типов и определения.
         \en Global type declarations and defines. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __QT_GLOBAL_H
#define __QT_GLOBAL_H

#include <vsn_global.h>

using namespace VSN;
namespace VSN {

#if defined(_WIN32) // only windows
// если не статическая линковка
#if !defined(QT_VISION_STATIC)
#if defined (_BUILDQTVISIONDLL)
#define  __QTVISION_DECL_SPEC __declspec( dllexport )
#else // _BUILDQTVISIONDLL
#define  __QTVISION_DECL_SPEC __declspec( dllimport )
#endif
#else // QT_VISION_STATIC
#if defined(QT_VISION_EXPORT) 
#define  __QTVISION_DECL_SPEC __declspec( dllexport )
#endif
#endif 
#else  // _WIN32
#define  __QTVISION_DECL_SPEC
#endif

#define QT_CLASS         __QTVISION_DECL_SPEC
#define QT_FUNC(retType) __QTVISION_DECL_SPEC retType CALL_DECLARATION
#define QT_FUNC_EX       __QTVISION_DECL_SPEC 


namespace Utils {
QT_FUNC(void) writeAssertLocation(const char* msg);
QT_FUNC(void) dumpBacktrace(int maxdepth);

template<typename T, typename F>
bool allOf(const T& container, F predicate)
{
    return std::all_of(std::begin(container), std::end(container), predicate);
}

} // namespace Utils

#define QTV_PREPEND_NAMESPACE(name) name
#define QTV_ASSERT_STRINGIFY_HELPER(x) #x
#define QTV_ASSERT_STRINGIFY(x) QTV_ASSERT_STRINGIFY_HELPER(x)
#define QTV_ASSERT_STRING(cond) VSN::Utils::writeAssertLocation(\
    "\"" cond"\" in " __FILE__ ":" QTV_ASSERT_STRINGIFY(__LINE__))

// Идиома do {...} while (0)' здесь не используется для основного блока
// возможность использовать «перерыв» и «продолжение» в качестве «действий».
#define QTV_ASSERT(cond, action) if (cond) {} else { QTV_ASSERT_STRING(#cond); action; } do {} while (0)
#define QTV_CHECK(cond) if (cond) {} else { QTV_ASSERT_STRING(#cond); } do {} while (0)
#define QTV_GUARD(cond) (cond ? true : (QTV_ASSERT_STRING(#cond), false))

} // namespace VSN


#endif //__QT_GLOBAL_H

