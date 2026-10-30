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
// Created by al-maks on 12.07.2025
//

#ifndef __MX_BREP_MODEL_H
#define __MX_BREP_MODEL_H

#include <mb_topology_item.h>
#include <mx_model_extension.h>

//---------------------------------------------------------------------------------------
// This entity represents geometric object that is a primitive consisting `MbItem`, topologic primitive, curve, point etc.
//---
class MxGrRefItem : public MxGrEntity
{
protected:
    const MbRefItem* RefItem() const;
};

//---------------------------------------------------------------------------------------
//
//---
class MxGrTopologyItem: public MxGrEntity
{
public:
    MxGrTopologyItem(const MxGrItem& solid, const MbTopologyItem* topElem);

public:
    MxTreeLocalId LocalId() const;
};


//---------------------------------------------------------------------------------------
// Class represents BRep-geometry i.e. solid or solid instance.
/*
  Copiable and moving data structure.
*/
//---
class MxGrSolid : public MxGrItem
{
protected:
    MxGrSolid() = default;

public:
    MxGrSolid(const MxTreeNodeConstPtr& parent, const MbItem* mathItem)
        : MxGrItem(parent, mathItem)
    {
        if (const MbItem* src = ::SourceItem(mathItem))
        {
            switch (mathItem->Type())
            {
                case st_Solid: break;
                default:
                    Init(nullptr, nullptr);
                    break;
            }
        }
    }

    MxGrSolid(const MxGrSolid&) = default;
    MxGrSolid(MxGrSolid&&) = default;
    // MxGrSolid& operator=(const MxGrComponentItem&) = default;
    // MxGrSolid& operator=(MxGrComponentItem&&) = default;
public:
    // The owning assembly of the component.
    const MbSolid* MathSolid() const;
    MxGrTopologyItem SubItem(MxTreeLocalId localId) const;
};

// Final implemention of the MxGrSolid with assignment operators.
using MxGrSolidF = MxFinalItem<MxGrSolid>;

#endif // __MX_BREP_MODEL_H
