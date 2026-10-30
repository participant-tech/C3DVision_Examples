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
// Created by al-maks on 03.09.23.
//

#ifndef __MX_MODEL_EXTENSION_H
#define __MX_MODEL_EXTENSION_H

#include <assembly.h>
#include <model_entity.h>
#include <mx_model_tree.h>
#include <mb_visiondef.h>

/*
     C3D Model Extension Classes. Mx-classes.
     Folder: 'Modex'

  What design techniques and concepts are used:

  1. Extension objects pattern. All objects derived from `MbItem` serves as internal base to implement Mx-objects.
     Collection of Mx-classes extends functionality of `MbModel`.
  2. Sample code for apply. It is open source class library for C3D customers.
  3. Sample code for demonstration. To be a sample of embedding C3D Model to your CAD Application.
  4. Sample code for internal use. The model is used by the C3D developers themselves for their tasks, 
     such as testing graphic interface intendent to develop new functionality, and writing examples for customers.
  5. The structure base of the model extension is Expanded Model Tree (EMT). `MxModelTree`.
  6. Lazy initialization. It is delaying the creation and initialization of the expanded model tree (EMT)
     until the first time it is needed. The immediate data structures inside are `MbModel` items.
  7. Memory managment. Bottom-Up owning through the shared pointers and backward linked list of parents 
     to flexable memory managment.
  8. Many of Mx-classes are lightweight copiable objects expressing model-specific entities.
  9. Clear and compact class interfaces that provide a convenient API wrapper. Minimalistic connectivity
     between elements of class hierarhy for flexible maintaining and refactoring.

    Architectural constraints
    
  10.Non-mutable and mutable classes of the model extension. Some subset of the Mx-classes
     are strictly read only, i.e ...     
 */

//---------------------------------------------------------------------------------------
// Unique sequence that addresses any node in the tree (path topdown from the root to a node).
//---
// class MxTreePath
// {  
//   MxTreePath(); // Construct an empty path.
// 
// public:
//   SimpleName OldStyleHash() const;
// };

class MxTreeNodeId;

//---------------------------------------------------------------------------------------
// Unique identifier within the entire expanded model tree.
//---
class MxObjectId
{

public:
    static const MxObjectId null; // Undefined value of the identifier.

public:    
    MxObjectId(const MxTreeNodeConstPtr& node, const MxTreeNodeId& nodeId);
    MxObjectId(const MxObjectId&) = default;
    MxObjectId(MxObjectId&&) = default;

private:
    MxObjectId();

public:
    bool operator==(const MxObjectId& objId) const { return objId.m_objectId==m_objectId; }
    bool operator==(const MxTreeNodeId& objId) const { return objId==m_objectId; }
    bool operator<(const MxObjectId& objId) const { return m_objectId < objId.m_objectId; }        
    bool operator< (const MxTreeNodeId& objId) const { return m_objectId < objId; }
    template<typename ObjectId>
    bool operator> (const ObjectId& objId) const { return !(*this < objId); }
    template<typename ObjectId>
    bool operator!= (const ObjectId& objId) const { return !(*this == objId); }    
    // 64-bit unique value of the identifier.
    uint64 Descriptor() const { return m_objectId.Descriptor(); }
    // Returns a platform depended hash to use in std::unordered_set.
    size_t Hash() const { return m_objectId.Hash(); }
    // Convert to a 64-bit identifier format.
    operator const MxTreeNodeId& () const { return m_objectId; }
    // Return true if the object Id is null.
    bool IsNull() const { return m_objectId == MxTreeNodeId::null; }
    // Return true if the object Id denotes a top node of the model tree.
    bool IsRoot() const { return m_objectId.Tag() == MxTreeNodeId::rootNode; }
    // Local Id that unique within a parent node of the entity.
    //MxTreeLocalId LocalId() const;

protected:
    // Internal use only.
    const MxTreeNodeBase* TreeNode() const;

private:
    MxTreeNodeId m_objectId;
    // These data is not essential part of `MxObjectId` and is restored in the runtime.
    mutable MxTreeNodeConstPtr m_treeNode; // for quick access.
};

//---------------------------------------------------------------------------------------
//
//---
class MxGrEntityId : public MxObjectId
{
  // This class has no its own data. But it can implement specific methods are encapsulated inside.
};

//---------------------------------------------------------------------------------------
// Base class for all C3D Model objects having a graphical representation.
// Not all 'MxGrEntity' objects represent 'MbItem'. For example, MxGrDimension isn't
// represented by `MbItem` object.
//---
class MxGrEntity
{
public:
    MxObjectId ParentId() const { /* Yet not implemented. */ return MxObjectId::null; }
    MxObjectId ObjectId() const { /* Yet not implemented. */ return MxObjectId::null; }

protected: // Some constructors are yet not allowed.
    MxGrEntity() = default;
    MxGrEntity( const MxGrEntity & ) = delete;
    MxGrEntity & operator = ( const MxGrEntity & ) = delete;
   ~MxGrEntity() {}

protected:
    // Пока не решено, где будет реализован узел дерева (как виртуальная функция или как поле данных).
    // Но функция TreeNode_() уже предусмотрена.
    virtual MxTreeNodeConstPtr TreeNode_() const = 0;
};

//---------------------------------------------------------------------------------------
// Class represents an abstract interface of assembly node of the model tree.
// It yet used for internal purposes.
//---
class MxIfAssembly
{
protected:
    virtual ~MxIfAssembly() {}
public:
    // Returns the assembly tree node.
    virtual const MxTreeNodeBase* TreeNode() const = 0;
    // C3D kernel assembly representation.
    virtual const MbAssembly& MathAssembly() const = 0;
};

// This pointer type guarantees that the node is an assembly.
using MxTreeAssemblyPtr = std::pair<MxTreeItemConstPtr, const MxIfAssembly*>;

//---------------------------------------------------------------------------------------
// Returns an assembly item if a node represents the assembly.
//---
inline const MbAssembly* AssemblyItem(const MxTreeAssemblyPtr& assemblyNode);

//---------------------------------------------------------------------------------------
// Iterator traversing all child sub-items of the model tree node.
// Type `SubItemType` must have constructor by parental node and `MbItem`.
//---
template<typename ParentPtrType, typename SubItemType>
class MxAssemblyIterator
{
public:
    using value_type = SubItemType;
    using reference  = const SubItemType&;
    
public:
    explicit MxAssemblyIterator(const ParentPtrType& parent, size_t itemIdx)
        : m_parent(parent)
        , m_assembly(AssemblyItem(parent))
        , m_itemIdx(itemIdx)
        , m_subItem(m_parent, nullptr)
    {}

    reference operator* (void) const;
    bool operator == ( const MxAssemblyIterator& other ) const { C3D_ASSERT(m_parent==other.m_parent); return (m_itemIdx == other.m_itemIdx); }
    bool operator != ( const MxAssemblyIterator& other ) const { return !operator==(other); }
    MxAssemblyIterator & operator ++() { ++m_itemIdx; return *this; }

private:
    const ParentPtrType m_parent;
    const MbAssembly*   m_assembly;
    size_t              m_itemIdx;
    mutable SubItemType m_subItem;
};

//---------------------------------------------------------------------------------------
//
//---
template<typename ParentPtrType, typename SubItemType>
inline const SubItemType& MxAssemblyIterator<ParentPtrType, SubItemType>::operator*(void) const
{
    return m_subItem.Init(m_parent, m_assembly->GetItem(m_itemIdx));
}

//---------------------------------------------------------------------------------------
// Graphic properties of the `MxGrItem`
//---
class MxGrConstProperties
{
public:
    MxGrConstProperties() = delete;
    MxGrConstProperties(const MxTreeItemConstPtr&);
    MxGrConstProperties(const MxGrConstProperties&) = default;
    MxGrConstProperties(MxGrConstProperties&&) = default;
    MxGrConstProperties& operator=(const MxGrConstProperties&) = default;
public: // Permanent properties (attributes).
    // Is the object visible?
    bool IsVisible() const;
public: // Run-time properties.
    uint64 Identifier() const;
private:
    std::weak_ptr<MxTreeItem> m_item;
};

//---------------------------------------------------------------------------------------
// Graphic properties of the `MxGrItem`
//---
class MxGrProperties : public MxGrConstProperties
{
public: // Permanent properties.
    // Set visibility.
    void SetVisible(bool vis);
};

//---------------------------------------------------------------------------------------
// Class represents a graphical node of expanded model tree.
// MxGrEntity is an item of the expanded model tree.
/*
  Requirements:
    - Copyable and moving data structure.
    - Any `MxGrItem` object corresponds to a `MbItem` element of C3D Model.
    - `MxGrItem` provides read only access to C3D Model data.
*/
//---
class MxGrItem: public MxGrEntity
{
public:
    using SubItemsIterator = MxAssemblyIterator<MxTreeItemConstPtr,MxGrItem>;
    using SubItemsRange = c3d::range<SubItemsIterator>;
public:
    MxGrItem(const MxGrItem& grItem): m_treeNode(grItem.m_treeNode) {}
    MxGrItem(MxGrItem&&) = default;
    MxGrItem(const MxTreeNodeConstPtr& parent, const MbItem* mathItem);
    MxGrItem& Init(const MxTreeNodeConstPtr& parent, const MbItem* mathItem);
protected:
    MxGrItem();  // Default constructor must be protected. See an inherented implemention `MxFinalItem` that publicates this constructor.
    explicit MxGrItem(const SPtr<MbAssembly>&&);
    MxGrItem(MxTreeItemConstPtr&& node)
        : MxGrEntity()
        , m_treeNode(node)
    {}
    MxGrItem& Init(const MxGrItem&);
    MxGrItem& Init(MxGrItem&&);

public:
    // This setter used only for specialization of `MxGrItem`, namely `MxGrRootAssembly`.
    MxGrItem & SetAsRootAssembly(MbAssembly* assmItem);
    // The model tree node wrapped by this `MxGrItem` interface class.
    MxTreeItemConstPtr TreeNode() const { return m_treeNode; }
public:
    // Get a matrix to transform up to the given component.
    MbMatrix3D MatrixTo(const MxGrItem& superComp) const; // `superComp` is a model tree item including `this` recursively.
    // Local coordinate system of the item positioning globally in the world space.
    MbPlacement3D Placement() const;  // into WCS.
    // Local coordinate system of the item positioning one in parental LCS.
    const MbPlacement3D& LocalPlacement() const;  // into Parent.
    // Get an unique id of the tree node.
    MxObjectId ObjectId() const;
    // An Id of the parent tree node that contains this item.
    MxObjectId ParentId() const;
    // Parent item that contains this item. If the parent is the root its `MbItem` representation may be `nullptr`.
    MxGrItem Parent() const;
    // Returns true if the item is a top of the model hierarchy.
    bool IsRoot() const;
    // C3D-model item that is represented by the parent node.
    const MbItem* ParentItem() const;
    // C3D-model item that is represented by this node, including a type of `MbInstance`. See also SourceItem().
    const MbItem* MathItem() const;
    /// C3D-model item that discribes geometry of the graphical node (MxGrItem).
    /*
      \details  It never be an `MbInstance`. This function returns only C3D-item that represents 
                geometry itself, for example, `MbSolid`, `MbMesh` or `MbAssembly`.
    */
    const MbItem* SourceItem() const;
    // The range for traversing the child tree items.
    SubItemsRange SubItems() const;
    // Return non-null pointer if this component is an sub-assembly.
    MxTreeAssemblyPtr SubAssembly() const;
    /*
    MxGrConstProperties Properties() const;
         MxGrProperties Properties();
    */
    // Both graphic items represent same model tree node (i.e. equal).
    bool operator == (const MxGrItem&) const;
    bool operator!=(const MxGrItem& mxItem) const { return !this->operator == (mxItem); }
    MxGrItem& operator=(const MxGrItem&) = delete; // Issue: It will be incorrect for the inheritors.
private:
    // Get transformation matrix into a superior model tree node.
    void GetMatrixTo(const MxTreeNodeConstPtr&, MbMatrix3D&) const;

    virtual MxTreeNodeConstPtr TreeNode_() const { return TreeNode_();  }   

private:
    MxTreeItemConstPtr m_treeNode;
};

//---------------------------------------------------------------------------------------
// Final implementation of `MxGrItem`. 
// Guarantees an correct assinment operator.
//---
template<class BaseItem>
class MxFinalItem final: public BaseItem
{
public:
    MxFinalItem(): BaseItem() {} // public default constructure for empty object.
    MxFinalItem(const BaseItem& other): BaseItem(other) {}
    MxFinalItem(BaseItem&& other) : BaseItem(std::move(other)) {}
    MxFinalItem(const MxFinalItem&) = default;
    MxFinalItem(MxFinalItem&&) = default;
    // copy assignment.
    MxFinalItem& operator=(const MxFinalItem& mxItem) 
    { 
        BaseItem::Init(mxItem);
        return *this;
    }
    // moving assignment.
    MxFinalItem& operator=(MxFinalItem&& mxItem)
    {
        BaseItem::Init(mxItem);
        return *this;
    }
};

// Final implemention of the MxGrItem.
using MxGrItemF = MxFinalItem<MxGrItem>; // It may be renamed after refactoring.

//---------------------------------------------------------------------------------------
// Class represents any entity that is a immediate part of an assembly.
/*
  Copiable and moving data structure.
*/
//---
class MxGrComponentItem final : public MxGrItem
{
public:
    MxGrComponentItem() = delete;
    MxGrComponentItem(const MxTreeAssemblyPtr& parent, const MbItem* mathItem)
        : MxGrItem(parent.first, mathItem) {}
    MxGrComponentItem& Init(const MxTreeAssemblyPtr& parent, const MbItem* mathItem)
        { MxGrItem::Init(parent.first, mathItem); return *this; }
    MxGrComponentItem(const MxGrComponentItem&) = default;
    MxGrComponentItem(MxGrComponentItem&&) = default;
    MxGrComponentItem& operator= (const MxGrComponentItem&) = default;
    MxGrComponentItem& operator= (MxGrComponentItem&&) = default;
public:
    // The owning assembly of the component.
    MxTreeAssemblyPtr ParentAssembly() const;
};

class MxTreeAssembly;

//---------------------------------------------------------------------------------------
// 
//---
inline const MbAssembly* AssemblyItem(const MxTreeAssemblyPtr& assemblyNode)
{
    if (assemblyNode.second != nullptr)
        return &assemblyNode.second->MathAssembly();
    return nullptr;
}


class MxTreeAssembly; // Implementation of `MxIfAssembly`.

//---------------------------------------------------------------------------------------
// Class represents an aggregating entity, i.e. assembly.
// Attention: This class represents namely instance of an assembly in the model tree.
//            It is possible two and more 'MxGrAssembly' class instances for a shared 'MbAssembly'.
/*
  Requirements:
    - This class can represent extra data beyond that provided by the C3D model,
      and this class also allow to save the extra data persistently in the attributes
      of the C3D model.
    - `MxGrAssembly` provides an interface for edit assembly, i.e. it has functions
      modifying C3D Assembly data and constraint system.
 */
//---
class MxGrAssembly final: public MxGrItem
{
    using ComponentsIterator = MxAssemblyIterator<MxTreeAssemblyPtr,MxGrComponentItem>;
    using ComponentsRange = c3d::range<ComponentsIterator>;
    template<class ValueType>
    using result = MxResultValue<ValueType>;
public:
    MxGrAssembly() = delete;
    MxGrAssembly(MxTreeAssemblyPtr&& node);
    MxGrAssembly(const MxGrAssembly& ) = default;
    MxGrAssembly(MxGrAssembly&&) = default;
public:
    // C3D kernel assembly representation.
    const MbAssembly& MathAssembly() const;
    // Non-const access to the attributes of the main assembly (it may be unsafe).
    MbAttributeContainer& Attributes();
    // Add new instance component of a shared math base item to the assembly.
    // `place` is specidied in the world coordinate system of the entire model.
    // (Возможно стоит перенести в абстрактный интерфейс, который наделить мутабельностью).
    result<MxGrComponentItem> AddInstance(MbItem* srcItem, const MbPlacement3D& place);
    //    
    bool operator==(const MxTreeAssemblyPtr& ) const;
    // Remove the assembly component.
    MxResultCode RemoveComponent(const MxGrItem&);
    // Get a range of all assembly components.
    ComponentsRange Components() const;
private:
    // Get an assembly subitem by its object ID.
    MxGrItem  SubItem(const MxObjectId& objId) const;

private:
          // Give access to modify the assembly.
          MbAssembly * MutableAssembly(); 
    const MxTreeAssembly& Impl() const;
          MxTreeAssembly& Impl();
    MxTreeAssemblyPtr AssemblyNode() const;
};

//---------------------------------------------------------------------------------------
/** \brief  \ru Расширение геометрической модели C3D.
            \en C3D Model eXtension.
    \details This class extends C3D model functionality which able to build CAD modeling samples.
*/
class MxModelExtension
{
public:
    MxModelExtension() = default;
    MxModelExtension(const MxModelExtension &) = delete;
    MxModelExtension & operator = (const MxModelExtension &) = delete;
public:
    MxGrAssembly MainAssembly();
    MxGrAssembly SubAssembly(const MxGrItem&);
    // Returns model extension item by its permanent object Id.
    MxGrItem        Item(const MxObjectId&) const;
    // Prepare the MbModel for writing *.c3d file.
    MxResultValue<SPtr<MbModel>> ExportToC3DModel() const;
    /**  \brief \ru Функция захватывает всю иерархию `MbModel`, включая все ее суб-элементы.
                \en The function captures `MbModel` hierarchy with all its subitems recursively.  
          \note \ru Требуется единственность корневной (главной) сборки внутри контейнера `MbModel`.
                \en The function requires single root assembly in the model container.
    */
    MxResultCode ImportFromC3DModel(MbModel &);
    // Set the model empty.
    MxModelExtension& Clear();
protected:
    // Pointer to root assembly node implementation.
    const MxTreeAssembly* MainAssemblyImpl() const;
private:
    MxModelTree     m_expTree;  // Expanded C3D model tree.
    MxTreeAssembly* m_mainAssembly = nullptr;
};

//-----------------------------------------------------------------------------
// The function returns the main assembly of the model, if it exists.
// ---
const MbAssembly* MainAssembly(const MbModel* pModel);
      MbAssembly* MainAssembly(MbModel* pModel);

//-----------------------------------------------------------------------------
// The function returns an existing main assembly or creates one by uniting all elements of the model.
// ---
MbAssembly* UniteToMainAssembly(MbModel* pModel);

#endif // __MX_MODEL_EXTENSION_H
