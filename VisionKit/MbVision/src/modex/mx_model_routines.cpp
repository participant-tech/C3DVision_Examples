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
// Created by al-maks on 09.01.2025
//

#include <mx_model_routines.h>
#include <attr_color.h>
#include <vsn_last.h>

//---------------------------------------------------------------------------------------
// Get the visibility property.
//---
bool IsVisible(const MxGrItem& grItem)
{
    if (const MbItem* mbItem = grItem.MathItem())
    {
        return mbItem->IsVisible();
    }
    return false;
}

//---------------------------------------------------------------------------------------
// Set the visibility property.
//---
void SetVisible(MxGrItem& grItem, bool visibility)
{
    if (const MbItem* mbItem = grItem.MathItem())
    {
        const_cast<MbItem*>(mbItem)->SetVisible(visibility);
    }
}

//---------------------------------------------------------------------------------------
// Get the material properties.
//---
const MbVisual* MaterialProperties(const MxGrItem& grItem)
{
    if (const MbItem* pItem = grItem.MathItem())
    {
        return static_cast<const MbVisual*>(pItem->GetSimpleAttribute(at_Visual));
    }
    return nullptr;    
}


//---------------------------------------------------------------------------------------
// Get the material properties recursively. 
// It implements a rule of the visual attribute selection of a model tree node.
//---
template<typename AttributeType, MbeAttributeType attributeEnum>
const AttributeType* MaterialPropertiesRecursiveRule(const MxTreeNodeBase* pMxTreeNode)
{    
    if (pMxTreeNode == nullptr)
    {
        return nullptr;
    }

    const MbItem* pInstanceItem = isa_cast<const MbItem*>(pMxTreeNode->RefItem());
    const MbItem* pSampleItem = SourceItem(pInstanceItem);

    if (pInstanceItem == nullptr || pSampleItem == nullptr)
    {
        return nullptr;
    }

    // (1) First for all query a sample of the instance.
    if (const AttributeType* sampleVis = static_cast<const AttributeType*>(pSampleItem->GetSimpleAttribute(attributeEnum)))
    {
        return sampleVis;
    }
    
    // (2) Secondly query an immediate instance.        
    if (pInstanceItem != pSampleItem)
    {            
        if (const AttributeType* instanceVis = static_cast<const AttributeType*>(pInstanceItem->GetSimpleAttribute(attributeEnum)))
        {
            return instanceVis;
        }
    }
    
    // (3) Thirdly ask the parent recirsively.   
    return MaterialPropertiesRecursiveRule<AttributeType,attributeEnum>(pMxTreeNode->Parent().get());
}

//---------------------------------------------------------------------------------------
// Get the material properties recursively.
//---
const MbVisual* MaterialPropertiesRecursively(const MxGrItem& grItem)
{    
    return MaterialPropertiesRecursiveRule<MbVisual,at_Visual>(grItem.TreeNode().get());
}

//---------------------------------------------------------------------------------------
// The functions works same as `MaterialPropertiesRecursively` for supporting old-style 
// data attribute `MbColor`. It is recommended to use `MbVisual` instead.
//---
const MbColor* ColorPropertyRecursively(const MxGrItem& grItem)
{
    return MaterialPropertiesRecursiveRule<MbColor,at_Color>(grItem.TreeNode().get());
}

//---------------------------------------------------------------------------------------
// Query material properties to change.
//---
MbVisual* QueryMaterialProperties(MxGrItem& grItem) 
{ 
    if (const MbVisual* visProps = MaterialProperties(grItem))
    {
        return const_cast<MbVisual*>(visProps);
    }
    if (MbItem* pItem = const_cast<MbItem*>(grItem.MathItem()))
    {
        pItem->SetVisual(MB_AMBIENT, MB_DIFFUSE, MB_SPECULARITY, MB_SHININESS, MB_OPACITY, MB_EMISSION, MB_C3DCOLOR);
    }
    if (const MbVisual* visProps = MaterialProperties(grItem))
    {
        return const_cast<MbVisual*>(visProps);
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------
// Get a child subitem of the given item by its local 32-bit ID.
// `currItem` должен быть по типу сборочной конструкцией.
//---
MxGrItem LocalSubItem(const MxGrItem& currItem, MxTreeLocalId subItemId)
{
    if (const MbAssembly* mbItem = isa_cast<const MbAssembly*>(currItem.MathItem()))
    {
        return {currItem.TreeNode(), mbItem->SubItem(subItemId)};
    }
    return {nullptr, nullptr};
}

//---------------------------------------------------------------------------------------
// Retrieve a model tree item by a sequence of MbPath IDs.
// MbPath contains only non-null MbItem identifiers.
// Parameters:
//  - currItem is a node of the supertree that contains the requested resulting sub-element.
//  - path is the sequence of IDs leading to the target subitem.
//  - currIdx is the current index in the path being matched.
// Returns the matching subitem if found; otherwise, returns a null item.
//---
MxGrItem SubItemByPath(const MxGrItem& currItem, const MbPath& path, size_t currIdx)
{
    C3D_ASSERT(currIdx < path.size());
    const auto localId = path[currIdx];
    if (const MbItem* mbItem = currItem.MathItem())
    {
        if (mbItem->GetItemName() != localId)
        {
            return {nullptr, nullptr};
        }
        const MbItem* srcItem = currItem.SourceItem();
        if (mbItem != srcItem)
        {
            // Special index increment when reusing `srcItem` through an instance.
            ++currIdx;

            if (srcItem->GetItemName() != path[currIdx] || currIdx >= path.size())
            {
                return {nullptr, nullptr};
            }
        }

        if (path.size() - 1 == currIdx)
            return currItem; // it's a final item of the path.
        auto subItem = LocalSubItem(currItem, path[currIdx + 1]);
        return SubItemByPath(subItem, path, currIdx + 1);
    }
    return {nullptr, nullptr};
}

#ifdef _DEBUG
void test(const MxObjectId& objId)
{
    MxObjectHashTable<SPtr<MbVisual>> visualPropTable;
    visualPropTable[objId];
}
#endif // _DEBUG
