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

//
// File contains basic data types (and enums) of the Model Extension Library
// Created by al-maks on 24.12.24.
//

#ifndef __MX_MODEL_TYPES_H
#define __MX_MODEL_TYPES_H

#include <utility>
#include <mb_visiondef.h>

//---------------------------------------------------------------------------------------
// The class enumerates the resulting codes of the function call results.
//---
enum class MxResultCode: char
{
      Ok    // Successful result.
    , None  // No result code.
    // The values below are error codes.
    , Error // Unknown system error.
    , DoubleInstance  // Instance based on other instance is not allowed.
    , InappropriateForInstance
    , SingleMainAssemblyRequired  // `MbModel` must consist of only one root assembly.
};

//---------------------------------------------------------------------------------------
// Resulting value with diagnostic code.
// It wraps the function result and mixes diagnostic code into it.
//---
template<class T>
using MxResultValueBase = std::pair<T,MxResultCode>;

//---------------------------------------------------------------------------------------
// Resulting value with diagnostic code.
// It wraps the function result and mixes diagnostic code into it.
//---
template<class T>
struct MxResultValue: public MxResultValueBase<T>
{
    operator bool () const { return this->second == MxResultCode::Ok; }
    operator const T& () const { return std::get<T>(*this); }
    MxResultValue() = delete;
    MxResultValue(const MxResultValue&) = default;
    MxResultValue(const T& resObject, MxResultCode resCode) 
        : MxResultValueBase<T>(resObject, resCode) {}
    MxResultValue(const std::pair<T,MxResultCode>& pair)
        : MxResultValueBase<T>(pair) {}
};

//---
template<typename T>
bool ok(const MxResultValue<T>& resVal) { return resVal.second == MxResultCode::Ok; }

#endif // __MX_MODEL_TYPES_H
