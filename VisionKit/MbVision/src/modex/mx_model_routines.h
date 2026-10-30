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
// Additional auxiliary procedures to work with the model extension lib (MxModelExtension)
// Created by al-maks on 09.01.2025
//

#ifndef __MX_MODEL_ROUTINES_H
#define __MX_MODEL_ROUTINES_H

#include <mx_model_extension.h>

class MbVisual;
class MbColor;
//---------------------------------------------------------------------------------------
// Get the visibility property.
//---
bool IsVisible(const MxGrItem& grItem);

//---------------------------------------------------------------------------------------
// Set the visibility property.
//---
void SetVisible(MxGrItem& grItem, bool visibility);

//---------------------------------------------------------------------------------------
// Get the material properties of the graphic item recursively.
// It implements a recursive rule defining which of items of the parental branch specify 
// a visual properties of the instance.
//---
const MbVisual* MaterialPropertiesRecursively(const MxGrItem& grItem);

//---------------------------------------------------------------------------------------
// The functions works same as `MaterialPropertiesRecursively` for supporting old-style 
// data attribute `MbColor`. It is recommended to use `MbVisual` instead.
//---
const MbColor* ColorPropertyRecursively(const MxGrItem& grItem);

//---------------------------------------------------------------------------------------
// Get the material properties of the graphic item immediatly.
//---
const MbVisual* MaterialProperties(const MxGrItem& grItem);

//---------------------------------------------------------------------------------------
// Query material properties to change.
//---
MbVisual* QueryMaterialProperties(MxGrItem& grItem);

//---------------------------------------------------------------------------------------
// Retrieve a model tree item by a sequence of MbPath IDs.
// MbPath contains only non-null MbItem identifiers.
// Parameters:
//  - currItem is a node of the supertree that contains the requested resulting sub-element.
//  - path is the sequence of IDs leading to the target subitem.
//  - currIdx is the current index in the path being matched.
// Returns the matching subitem if found; otherwise, returns a null item.
//---
MxGrItem SubItemByPath(const MxGrItem& currItem, const MbPath& path, size_t currIdx = 0);

//---------------------------------------------------------------------------------------
// This function intended to implement `std::unordered_map<MxObjectId,ValueType>`.
//---
struct MxObjectIdHasher
{
    size_t operator()(const MxObjectId& objId) const { return objId.Hash(); }
    size_t operator()(const MxTreeNodeId& nodeId) const { return nodeId.Hash(); }
};

//---------------------------------------------------------------------------------------
// STL-based hash-table with a key MxObjectId.
//---
template<typename ValueType>
using MxObjectHashTable = std::unordered_map<MxObjectId,ValueType,MxObjectIdHasher>;
template<typename ValueType>
using MxTreeNodeHashTable = std::unordered_map<MxTreeNodeId,ValueType,MxObjectIdHasher>;

#endif // __MX_MODEL_ROUTINES_H
