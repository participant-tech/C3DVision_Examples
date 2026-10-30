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
// Created by al-maks on 18.07.2025
//

#ifndef __MX_DIMENSION_H
#define __MX_DIMENSION_H

#include <mx_model_extension.h>

//---------------------------------------------------------------------------------------
// Generic parameters of a dimension style (line thin, color, arrow style and so on).
//---
struct MxDimensionStyle 
{
};

//---------------------------------------------------------------------------------------
// Base class for all angular and distance dimensions.
//---
class MxGrDimension : public MxGrEntity
{
public:
    struct BasePars // Generic dimension parameters (distance, angular and radial).
    {
        double dimValue;
        double offset;  // high of linear dimension or radius of the angular
        double ratio;
    };
public:
    // Actual dimension value in the text form of record.
    c3d::string_t TextValue() const;
    MbCartPoint3D TextPosition() const;
    // Basic scalar characteristics of the generic dimension  (independed to the datum LCS).
    BasePars         DimPars() const;
    // Additional characteristics of the dimension  (style).
    MxDimensionStyle DimStype() const { return {}; /*yet not implemented*/ }
    // Get a datum LCS of the dimension specified in the world CS.
    const MbPlacement3D& DatumPlace() const;

public:
    // The function Parent returns an `MxModel` object to which the dimension blongs.
    using MxGrEntity::ParentId;
    MxObjectId DimSchemeId() const { return ParentId(); }

private:
};

//---------------------------------------------------------------------------------------
// Assumed derived dimension-classes
//---
class MxGrRadialDimension : public MxGrDimension {};
class MxGrDiametricDimension : public MxGrDimension {};

// others autocad-like angular dimensions.
class MxGr2LineAngularDimension;
class MxGr3PointAngularDimension;
class MxGrArcDimension;

//---------------------------------------------------------------------------------------
//
/*
    Выбранный подход состоит в том , что всякий размер хранится не, как самостоятельный экземпляр класса,
    а его основные характеристики содержатся в таблице размеров.
    Это удобно, поскольку всякий размер имеет локальный 32-битный ID, который может быть заимствован из
    системы ограничений и размеров (GCM_sysstem, GCE_system). Таким образом, любой размер 
    регистрируется в общем месте - в размерной схеме.
*/
//---
class MxGrDimensionScheme : public MxGrEntity
{
public:
    
private:
};

#endif // __MX_DIMENSION_H
