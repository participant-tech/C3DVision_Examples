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
// Created by al-maks on 03.09.2023.
//

#include <mx_model_extension.h>
#include <mx_model_routines.h>
#include <vsn_last.h>

const MxObjectId MxObjectId::null; // Undefined value of the identifier.


//---------------------------------------------------------------------------------------
// 
//---
MxObjectId::MxObjectId()
    : m_objectId(MxTreeNodeId::null)
    , m_treeNode(nullptr)
{}

//---------------------------------------------------------------------------------------
// 
//---
MxObjectId::MxObjectId(const MxTreeNodeConstPtr& node, const MxTreeNodeId& nodeId)
    : m_objectId(nodeId)
    , m_treeNode(node)
{}

//---------------------------------------------------------------------------------------
// Access to a tree node inside the Modex library.
//---
const MxTreeNodeBase* MxObjectId::TreeNode() const
{
    return m_treeNode.get();
}

//---------------------------------------------------------------------------------------
// Internal use only.
//---
class MxGrItemId final: public MxObjectId
{
public:    
    MxGrItemId(const MxObjectId& objId): MxObjectId(objId) {}
    const MxTreeNodeConstPtr Parent() const
    {
        if (const MxTreeNodeBase* treeNode = TreeNode())
        {
            return treeNode->Parent();
        }
        return {nullptr};
    }
    const MbItem* MathItem() const
    {
        if (const MxTreeNodeBase* treeNode = TreeNode())
        {
            return isa_cast<const MbItem*>(treeNode->RefItem());
        }
        return nullptr;
    }
};

//---------------------------------------------------------------------------------------
//
//---
MxGrItem::MxGrItem()
    : MxGrEntity()
    , m_treeNode(std::make_shared<MxTreeItem>(nullptr, SPtr<const MbItem>(nullptr)))
{
}

//---------------------------------------------------------------------------------------
//
//---
MxGrItem::MxGrItem(const MxTreeNodeConstPtr & parent, const MbItem * mathItem)
  : MxGrEntity()
  , m_treeNode( std::make_shared<MxTreeItem>(parent, SPtr<const MbItem>(mathItem)) )
{}

MxGrItem& MxGrItem::Init(const MxTreeNodeConstPtr& parent, const MbItem* mathItem)
{ m_treeNode = std::make_shared<MxTreeItem>(parent, SPtr<const MbItem>(mathItem)); return *this; }

//---------------------------------------------------------------------------------------
//
//---
MxGrItem::MxGrItem(const SPtr<MbAssembly> && assmItem )
  : MxGrEntity()
  , m_treeNode( std::make_shared<MxTreeItem>(assmItem) )
{}

//---------------------------------------------------------------------------------------
//
//---
MxGrItem & MxGrItem::SetAsRootAssembly(MbAssembly* assmItem)
{
  m_treeNode = std::make_shared<MxTreeItem>(SPtr<MbAssembly>(assmItem));
  return *this;
}

//---------------------------------------------------------------------------------------
// 
//---
MxGrItem& MxGrItem::Init(const MxGrItem& mxItem) 
{
    m_treeNode = mxItem.m_treeNode;
    return *this;
}

//---------------------------------------------------------------------------------------
//
//---
MxGrItem& MxGrItem::Init(MxGrItem&& mxItem)
{
    m_treeNode = std::move(mxItem.m_treeNode);
    return *this;
}

//---------------------------------------------------------------------------------------
// Local coordinate system of the item positioning one in parental LCS.
//---
const MbPlacement3D & MxGrItem::LocalPlacement() const
{
  if (const MbInstance * inst = isa_cast<const MbInstance*>(MathItem()))
  {
    return inst->GetPlacement();
  }

  return MbPlacement3D::global;
}

//---------------------------------------------------------------------------------------
// Local coordinate system of the item transforming the entity into the world.
//---
MbPlacement3D MxGrItem::Placement() const
{
    MbPlacement3D lcsInWorld;
    MbMatrix3D trans;
    GetMatrixTo(RootNode(*m_treeNode), trans);
    return lcsInWorld.Transform(trans);
}

//---------------------------------------------------------------------------------------
// Get a matrix to transform up to the given component.
//---
MbMatrix3D MxGrItem::MatrixTo(const MxGrItem& superComp) const
{
    // `superComp` is a model tree item including `this` recursively.
    MbMatrix3D res;
    GetMatrixTo(superComp.TreeNode(), res);
    return res;
}

// static bool IsVisibleHelper(const MxGrItem& grItem)
// {
//     if (grItem.IsRoot())
//         return IsVisible(grItem);
// 
//     return IsVisible(grItem) && IsVisibleHelper(grItem.Parent());
// }

//---------------------------------------------------------------------------------------
// Get an unique id of the tree node.
//---
MxObjectId MxGrItem::ObjectId() const
{    
    return {m_treeNode, m_treeNode->ObjectId()};
}

//---------------------------------------------------------------------------------------
// Parent item that contains this item. If the parent is the root its `MbItem` representation may be `nullptr`.
//---
MxGrItem MxGrItem::Parent() const
{    
    C3D_ASSERT(!IsRoot());
    if (auto parent = m_treeNode->Parent())
        return {parent->Parent(), ParentItem()};
    return {m_treeNode->Parent(), nullptr};
}

//---------------------------------------------------------------------------------------
// Returns true if the item is a top of the model hierarchy.
//---
bool MxGrItem::IsRoot() const {return ObjectId().IsRoot();}

//---------------------------------------------------------------------------------------
// Special implementation of the assembly tree node providing the abstract `MxIfAssembly`.
//---
class MxTreeAssembly : public MxTreeItem,
                       public MxIfAssembly
{
public:
    const MxTreeNodeBase* TreeNode() const override {return this;}
    // C3D kernel assembly representation.
    const MbAssembly& MathAssembly() const override 
    { 
        const MbItem* assemblyInstance = SourceItem(MathItem());
        C3D_ASSERT(SourceItem(assemblyInstance)->IsA() == st_Assembly);
        return *static_cast<const MbAssembly*>(SourceItem(assemblyInstance));
    }

public:
    // Creates a new assembly node by its parental node and the math source of the `MbAssembly` type.
    MxTreeAssembly( const MxTreeNodeConstPtr& parent, const MbItem* assemblyInstance)
          : MxTreeItem(parent, SPtr<const MbItem>(assemblyInstance))
    {
        C3D_ASSERT(SourceItem(assemblyInstance)->IsA() == st_Assembly);
    }
};

//---------------------------------------------------------------------------------------
// Both graphic items represent same model tree node (i.e. equal).
//---
bool MxGrItem::operator==(const MxGrItem& grItem) const
{
    if (m_treeNode == grItem.m_treeNode)
    {
        return true;
    }
    return m_treeNode->ObjectId() == grItem.m_treeNode->ObjectId();
}

//---------------------------------------------------------------------------------------
// An Id of the parent tree node that owns this item.
//---
MxObjectId MxGrItem::ParentId() const 
{ 
    auto parent = m_treeNode->Parent();
    if (parent == nullptr)
        return MxObjectId::null;
    return {parent, parent->ObjectId()};
}

//---------------------------------------------------------------------------------------
// C3D-model item that is represented by the parent node.
//---
const MbItem* MxGrItem::ParentItem() const
{
  if (const MxTreeNodeConstPtr parent = m_treeNode->Parent())
  {
    return isa_cast<const MbItem*>(parent->RefItem());
  }
  return nullptr;
}

//---------------------------------------------------------------------------------------
// C3D-model item that is represented by this node, including a type of `MbInstance`. 
// See also SourceItem().
//---
const MbItem * MxGrItem::MathItem() const 
{
  return m_treeNode->MathItem();
}

//---------------------------------------------------------------------------------------
// C3D-model item that discribes geometry of the graphical node (MxGrItem).
/*
  \details  It never be an `MbInstance`. This function returns only C3D-item that represents 
            geometry itself, for example, `MbSolid`, `MbMesh` or `MbAssembly`.
*/
//---
const MbItem * MxGrItem::SourceItem() const 
{
  return ::SourceItem(MathItem());
}

//---------------------------------------------------------------------------------------
// The range for traversing the child tree items.
//---
MxGrItem::SubItemsRange MxGrItem::SubItems() const
{
    SubItemsIterator first(m_treeNode, 0);
    if (const MbAssembly* assm = isa_cast<const MbAssembly*>(SourceItem()))
    {
        SubItemsIterator second(m_treeNode, assm->ItemsCount());
        return c3d::make_range(first, second);
    }
    return c3d::make_range(first, first);
}

//---------------------------------------------------------------------------------------
// Get .
//---
// MxGrItem MxGrItem::SubItem(const MxObjectId& objId) const
// {
//     MxGrItemId itemId(objId);
//     C3D_ASSERT(this->ParentId() == itemId.Parent()->ObjectId());
//     return {itemId.Parent(), itemId.MathItem()};
// }

//---------------------------------------------------------------------------------------
//
//---
MxTreeAssemblyPtr MxGrItem::SubAssembly() const
{
    if (const MbAssembly* assm = isa_cast<const MbAssembly*>(SourceItem()))
    {
        auto assmNodeSPtr = std::make_shared<MxTreeAssembly>(m_treeNode->Parent(), MathItem());
        return {assmNodeSPtr, assmNodeSPtr.get()};
    }
    return {nullptr, nullptr};
}

//---------------------------------------------------------------------------------------
// Get transformation matrix into a superior model tree node.
//---
void MxGrItem::GetMatrixTo(const MxTreeNodeConstPtr& top, MbMatrix3D& matrix2) const
{
    matrix2 = LocalPlacement().GetMatrixFrom();

    auto parent = m_treeNode->Parent();
    while ((parent != top) && (parent!=nullptr))
    {        
        matrix2.Transform(::LocalPlacement(*parent).GetMatrixFrom());
        parent = parent->Parent();
    }
}


//---------------------------------------------------------------------------------------
// The owning assembly of the component.
//---
MxTreeAssemblyPtr MxGrComponentItem::ParentAssembly() const
{   
    auto parentalNode = static_cast<const MxTreeItem*>(TreeNode()->Parent().get());
    MxTreeItemConstPtr parent(TreeNode()->Parent(), parentalNode);
    C3D_ASSERT(isa_cast<const MbAssembly*>(::SourceItem(parentalNode->MathItem()))!=nullptr);
    return {parent, static_cast<const MxTreeAssembly*>(parent.get())};
}

//---------------------------------------------------------------------------------------
//
//---
MxGrAssembly::MxGrAssembly(MxTreeAssemblyPtr&& node)
    : MxGrItem(std::move(node.first))
{
    C3D_ASSERT(TreeNode().get() == node.second->TreeNode());
}

//---------------------------------------------------------------------------------------
// 
//---
bool MxGrAssembly::operator==(const MxTreeAssemblyPtr& assmPtr) const
{
    C3D_ASSERT(assmPtr.first != nullptr);
    if (TreeNode() == assmPtr.first)
    {
        return true;
    }
    return assmPtr.first->ObjectId() == ObjectId();
}

//---------------------------------------------------------------------------------------
// Get a range of all assembly components.
//---
MxGrAssembly::ComponentsRange MxGrAssembly::Components() const
{
    ComponentsIterator first(AssemblyNode(), 0);
    ComponentsIterator second(AssemblyNode(), MathAssembly().ItemsCount());
    return c3d::make_range(first, second);
}

//---------------------------------------------------------------------------------------
// Get an assembly subitem by its object ID.
//---
MxGrItem MxGrAssembly::SubItem(const MxObjectId& objId) const
{
    MxGrItemId itemId(objId);
    C3D_ASSERT(ObjectId() == itemId.Parent()->ObjectId());
    return {itemId.Parent(), itemId.MathItem()};
}

//---------------------------------------------------------------------------------------
// Add new instance component of a shared math base item to the assembly.
// Refactoring: TODO: It would be better if `MbItem* sample` was const.
//---
MxGrAssembly::result<MxGrComponentItem> 
MxGrAssembly::AddInstance( MbItem* sample, const MbPlacement3D& place)
{    
    const MxGrComponentItem emptyComp{AssemblyNode(), nullptr};    
    if (sample ==nullptr)
        return std::make_pair(emptyComp, MxResultCode::None);    
    
    if (sample->IsA() == st_Instance)
        return std::make_pair(emptyComp, MxResultCode::DoubleInstance);    

    MbAssembly* assm = this->MutableAssembly();
    if (assm == nullptr)
        return std::make_pair(emptyComp, MxResultCode::Error);
    // Transform into the subspace of the current assembly.
    const MbMatrix3D toLocal = this->Placement().GetMatrixInto(); 
    if (const MbItem* instance = assm->AddInstance(*sample, place*toLocal))
    {
        
        MxGrComponentItem component{AssemblyNode(), instance};
        return std::make_pair(component, MxResultCode::Ok);
    }        

    return std::make_pair(emptyComp, MxResultCode::None);
}

//---------------------------------------------------------------------------------------
// Remove the assembly component.
//---
MxResultCode MxGrAssembly::RemoveComponent(const MxGrItem& grItem)
{
    MbAssembly* assm = this->MutableAssembly();
    if (assm == nullptr)
        return MxResultCode::Error;    

    SPtr<const MbItem> mathItem(grItem.MathItem());
    if (mathItem)
    {
        if ( assm->DeleteItem(const_cast<MbItem*>(mathItem.get())) )
        {
            return MxResultCode::Ok;
        }
    }
    
    return MxResultCode::None;
}

//---------------------------------------------------------------------------------------
// C3D kernel assembly representation.
//---
const MbAssembly& MxGrAssembly::MathAssembly() const
{
    C3D_ASSERT(isa_cast<const MbAssembly*>(SourceItem()) != nullptr);
    return *isa_cast<const MbAssembly*>(SourceItem());
}

//---------------------------------------------------------------------------------------
// Non-const access to the attributes of the main assembly (it may be unsafe).
//---
MbAttributeContainer& MxGrAssembly::Attributes()
{
    return const_cast<MbAssembly&>(MathAssembly());
}

//---------------------------------------------------------------------------------------
// Give access to modify the assembly.
//---
MbAssembly* MxGrAssembly::MutableAssembly()
{
    const MbAssembly& assm = MathAssembly();
    return const_cast<MbAssembly*>(&assm);
}

//---------------------------------------------------------------------------------------
// 
//---
const MxTreeAssembly& MxGrAssembly::Impl() const
{return static_cast<const MxTreeAssembly&>(*TreeNode());}

//---------------------------------------------------------------------------------------
// 
//---
MxTreeAssembly& MxGrAssembly::Impl()
{   
    const MxTreeItem* itemNode = TreeNode().get();
    return static_cast<MxTreeAssembly&>(*const_cast<MxTreeItem*>(itemNode));
}

//---------------------------------------------------------------------------------------
// 
//---
MxTreeAssemblyPtr MxGrAssembly::AssemblyNode() const { return {TreeNode(), &Impl()}; }

//-----------------------------------------------------------------------------
// 
//---
MxGrAssembly MxModelExtension::SubAssembly(const MxGrItem& grItem)
{
    return grItem.SubAssembly();
}

//---------------------------------------------------------------------------------------
// Pointer to root assembly node implementation.
//---
const MxTreeAssembly* MxModelExtension::MainAssemblyImpl() const
{
    C3D_ASSERT(AssemblyItem(m_expTree.MainAssmNode()) != nullptr);
    return m_mainAssembly;
}

//---------------------------------------------------------------------------------------
// 
//---
MxGrAssembly MxModelExtension::MainAssembly()
{
    if (m_mainAssembly == nullptr)
    {
        auto assemblyItem = c3d::make_sptr<MbAssembly>();
        m_mainAssembly = m_expTree.SetMainAssembly<MxTreeAssembly>(assemblyItem).get();
    }
    C3D_ASSERT(AssemblyItem(m_expTree.MainAssmNode()) != nullptr);
    MxGrAssembly mainAssembly({m_expTree.MainAssmNode(), MainAssemblyImpl()});
    return mainAssembly;
}

//---------------------------------------------------------------------------------------
// Set the model empty.
//---
MxModelExtension& MxModelExtension::Clear()
{
    auto assmItem = c3d::make_sptr<MbAssembly>();
    m_mainAssembly = m_expTree.SetMainAssembly<MxTreeAssembly>(assmItem).get();
    C3D_ASSERT(m_expTree.MainAssembly() == assmItem);
    return *this;
}

//---------------------------------------------------------------------------------------
// This function requires single root assembly in the model.
//---
MxResultCode MxModelExtension::ImportFromC3DModel(MbModel& mbModel)
{    
    if (MbAssembly* assmItem = UniteToMainAssembly(&mbModel))
    {
        m_mainAssembly = m_expTree.SetMainAssembly<MxTreeAssembly>(assmItem).get();
        return m_expTree.MainAssembly() == assmItem ? MxResultCode::Ok : MxResultCode::Error;
    }
    else
        return MxResultCode::SingleMainAssemblyRequired;
}

//-----------------------------------------------------------------------------
// Prepare the MbModel for writing *.c3d file.
//---
MxResultValue<SPtr<MbModel>> MxModelExtension::ExportToC3DModel() const
{ 
    auto res = m_expTree.Prepare2Write();
    if (res != MxResultCode::Ok)
    {
        return {nullptr, res}; // something went wrong.
    }
    auto c3dModel = c3d::make_sptr<MbModel>();
    if (const MbAssembly* mainAssm = m_expTree.MainAssembly())
    {
        c3dModel->AddItem(*const_cast<MbAssembly*>(mainAssm));
        return {c3dModel, MxResultCode::Ok};
    }
    return {nullptr, MxResultCode::None};
}


//-----------------------------------------------------------------------------
// Функция возвращает основную сборку модели, если она существует.
// The function returns the main assembly of the model, if it exists.
// ---
static const MbAssembly* MainAssemblyHelper(const MbModel* pModel)
{
    if (pModel == nullptr)
        return nullptr;
   
    // It is considered the first found assembly is the main.    
    if (pModel->ItemsCount() == 1)
    {
        if (const MbAssembly* assmItem = isa_cast<const MbAssembly*>(*pModel->CBegin()))
        {
            return assmItem;
        }
    }    

    return nullptr;
}

//-----------------------------------------------------------------------------
// The function returns the main assembly of the model, if it exists.
// ---
const MbAssembly* MainAssembly( const MbModel* pModel ) { return MainAssemblyHelper(pModel); }

//-----------------------------------------------------------------------------
// The function returns the main assembly of the model, if it exists.
// ---
MbAssembly* MainAssembly( MbModel* pModel ) { return const_cast<MbAssembly*>(MainAssemblyHelper(pModel)); }

//-----------------------------------------------------------------------------
// Функция возвращает существующую основную сборку или создает ее, объединяя все элементы модели.
// The function returns an existing main assembly or creates one by uniting all elements of the model.
// ---
MbAssembly* UniteToMainAssembly(MbModel* pModel)
{
    if (pModel == nullptr)
        return nullptr;

    if (MbAssembly* assmItem = MainAssembly(pModel))
        return assmItem;

    // If the model is yet empty or hasn't assembly, create a new root assembly.
    std::vector<MbItem*> unitedItems; // (!) It is not owning.
    pModel->DetachItems(unitedItems);

    SPtr<MbAssembly> pNewAssm(new MbAssembly(unitedItems));
    if (pModel->AddItem(*pNewAssm) != nullptr)
        return pNewAssm.get();

    return nullptr;
}

// eof
