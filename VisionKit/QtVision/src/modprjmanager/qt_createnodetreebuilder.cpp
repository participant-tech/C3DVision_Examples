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

#include <qt_createnodetreebuilder.h>
#include <qt_createprjnodes.h>
#include <qt_projectmodels.h>

#include <attr_product.h>
#include <mx_model_extension.h>
#include <mx_model_routines.h>
#include <mb_scenegenerator.h>
#include <vsn_string.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {
// ---
static QString itemName(const String& _name, const MbItem* pItem)
{
    VSN_ASSERT(pItem != nullptr);
    String name = _name;
    std::vector<MbAttribute*> attrib;
    pItem->GetAttributes(attrib, at_ProductAttribute, at_ProductInfo);
    if (!attrib.empty())
    {
        MbProductInfo* prod = static_cast<MbProductInfo*>(attrib.front());
        c3d::string_t sId, sName, sDescr;
        prod->GetData(sId, sName, sDescr);
        name = (sName.c_str() + String("-(") + _name + String(')'));
    }
    return name.c_str();
}

// ---
static void createFinalTree(const MxGrItem& grItem, FolderNode* node)
{
    const MbItem* pItem = grItem.MathItem();   // It may by `MbInstance`.
    const MbItem* sItem = grItem.SourceItem(); // It is a source geometry, not `MbInstance`.
    if (sItem == nullptr || pItem == nullptr)
        return;

//    const MbeSpaceType sType = sItem->IsA(); // Характеристический тип геометрии (никогда не бывает типом `MbInstance`).
//    const std::vector<MbeSpaceType>& spaceTypes = SceneGenerator::DefaultSpaceTypes();
//    if (std::find(spaceTypes.cbegin(), spaceTypes.cend(), sType) == spaceTypes.cend())
//        return; // Reject geometry type that out of enabling list `spaceTypes`.

//    if (sType == st_Solid || sType == st_Mesh /* || sType == st_WireFrame*/)
    {
        auto bodyNode = std::make_unique<BodyNode>(itemName("Body", sItem), grItem);
        bodyNode->setCheck(IsVisible(grItem) ? Qt::Checked : Qt::Unchecked);
        node->addNode(std::move(bodyNode));
    }
}

// ---
static void createTree(const MxGrItem& grItem, FolderNode* node)
{
    const MbItem* pItem = grItem.MathItem();   // It may by `MbInstance`.
    const MbItem* sItem = grItem.SourceItem(); // It is a source geometry, not `MbInstance`.
    if (sItem == nullptr || pItem == nullptr)
        return;

    const MbeSpaceType sType = sItem->IsA(); // Характеристический тип геометрии (никогда не бывает типом `MbInstance`).
    const std::vector<MbeSpaceType>& spaceTypes = SceneGenerator::DefaultSpaceTypes();
    if (std::find(spaceTypes.cbegin(), spaceTypes.cend(), sType) == spaceTypes.cend())
        return; // Reject geometry type that out of enabling list `spaceTypes`.

    // Пока оставляем старые "правила игры" - на всякий `MbInstance` заводится соотвествующий `SceneSegment`.
    switch (sType) // Тип узла по его оранизации (может быть типом `MbInstance`).
    {
        case st_Assembly:
        {
            auto assembly = std::make_unique<AssemblyNode>(itemName("Assembly", sItem), grItem);
            for (MxGrItem subItem : grItem.SubItems()) // Пока итератор предоставляет `subItem` "по значению".
                createTree(subItem, assembly.get());
            assembly->setCheck(IsVisible(grItem) ? Qt::Checked : Qt::Unchecked);
            node->addNode(std::move(assembly));
            return;
        }
        default:
            // Call this to build a final node of the scene.
            return createFinalTree(grItem, node);
    }
}

// ---
std::unique_ptr<MathModelNode> CreateNodeTreeBuilder::buildTree(MxModelExtension* modExt)
{
    auto root = std::make_unique<MathModelNode>(QObject::tr("Model"));
    root->setMathModel(modExt);
    createTree(/*modExt,*/ modExt->MainAssembly(), root.get());
    return root;
}

} // namespace QtVision
} // namespace VSN
