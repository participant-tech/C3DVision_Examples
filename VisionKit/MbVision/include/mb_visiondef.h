////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Глобальные объявления типов и определения.
         \en Global type declarations and defines. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_VISIONDEF_H
#define __MB_VISIONDEF_H

#include <vsn_global.h>

using namespace VSN;
namespace VSN {

#if defined(_WIN32) // only windows
// если не статическая линковка
#if !defined(MB_VISION_STATIC)
#if defined (_BUILDMBVISIONDLL)
#define  __MBVISION_DECL_SPEC __declspec( dllexport )
#else // _BUILDMBVISIONDLL
#define  __MBVISION_DECL_SPEC __declspec( dllimport )
#endif
#else // MB_VISION_STATIC
#if defined(MB_VISION_EXPORT) 
#define  __MBVISION_DECL_SPEC __declspec( dllexport )
#endif
#endif 
#else  // _WIN32
#define  __MBVISION_DECL_SPEC
#endif

#define MB_CLASS         __MBVISION_DECL_SPEC
#define MB_FUNC(retType) __MBVISION_DECL_SPEC retType CALL_DECLARATION
#define MB_FUNC_EX       __MBVISION_DECL_SPEC 

} // namespace VSN

#endif //__MB_VISIONDEF_H

