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

#ifndef __MX_MODEL_TREE_H
#define  __MX_MODEL_TREE_H

#include <mx_types.h>
#include <mb_class_traits.h>
#include <assembly.h>
#include <mb_visiondef.h>

//---------------------------------------------------------------------------------------
// Unique identifier within the entire expanded model tree.
/*
    This simple data structure implements a form of the 64-bit key, i.e.
    it has a following record in the hex format: TTNNNNNN:HHHHHHHH.
    The bit fields are following:
        - TT is 8-bit tag that specify a method witch encodes an idetifier.
        - NN is 24-bit number that initialiaze the hash function.
        - HH is 32-bit hash or a simple name that locally adresses `MbItem`s.
*/
//---
class MxTreeNodeId
{
public:    
    enum tag : uint8
    {
        undefined   = 0x00,
        rootNode    = 0x01,
        global      = 0x02,
        simpleName  = 0x03,
        simplePair  = 0x04,
        hashPacked  = 0x10, // Hash32 function value dependent on the model tree path.
    };
    static const MxTreeNodeId null; // Undefined value of the identifier.
    static const uint64 mainAssmId = uint64(global)<<56|0x1;    // Default Id for the main assembly.

public:
    // Construct an undefined id.
    MxTreeNodeId() : m_64bits(0) { SetTag(undefined); }
    // Construct id by a tag.
    MxTreeNodeId(tag t) : m_64bits(0) { SetTag(t); }
    // Construct a simple id of the assembly sub-item.
    explicit MxTreeNodeId(SimpleName id) 
      : m_64bits(id)
    {
        SetTag(simpleName);
    }
    // Construct id by a 64-bit descriptor.
    explicit MxTreeNodeId(uint64 id) 
      : m_64bits(id)
    {
        C3D_ASSERT(Tag() == hashPacked);
    }

    MxTreeNodeId(const MxTreeNodeId&) = default;
    MxTreeNodeId(MxTreeNodeId&&) = default;

public:
    MxTreeNodeId& operator=(const MxTreeNodeId& nodeId) = default;
    bool operator==(const MxTreeNodeId& nodeId) const { return m_64bits == nodeId.m_64bits; }
    bool operator!=(const MxTreeNodeId& nodeId) const { return m_64bits != nodeId.m_64bits; }
    bool operator<(const MxTreeNodeId& nodeId) const { return m_64bits < nodeId.m_64bits; }

    reader& Read(reader& in) { in.readUInt64(m_64bits); return in; }
    writer& Write(writer& out) const { out.writeUInt64(m_64bits); return out; }
    // 64-bit unique value of the identifier.
    const uint64& Descriptor() const { return m_64bits; }
    tag     Tag() const { return static_cast<tag>(m_hash.uWord >> 24); }
    // Returns a platform depended hash to use in std::unordered_set.
    size_t  Hash() const;

private:
    void SetTag(tag t)
    {
        m_hash.uWord &= 0x00ffffff;
        m_hash.uWord |= (uint32(t) << 24);
    }
    // Returns 32-bit mixed hash to use in the unordered sets (hash tables).
    uint32  Hash32() const;
    // Returns 64-bit mixed hash to use in the unordered sets (hash tables).
    uint64  Hash64() const;

private:
    union
    {
        uint64 m_64bits;  // 64-bit persistent identifier.
        struct
        {
            uint32 value;   // Lower word is 32-bit hash value.        
            uint32 uWord;   // Upper word of id intendent to avoid a hash collision.
        
        } m_hash;
    };
};


inline reader& operator>>(reader& in, MxTreeNodeId& id) { return id.Read(in); }
inline writer& operator<<(writer& out, const MxTreeNodeId& id) { return id.Write(out); }


using MxTreeLocalId = SimpleName; // Local 32-bit key that is unique within a level of the model tree (not unique to the entire model).
class MxTreeNodeIdTable;

//---------------------------------------------------------------------------------------
// Base class of the expanded model tree node.
//---
class MxTreeNodeBase
{
public:
    using TreeNodeConstPtr = std::shared_ptr<const MxTreeNodeBase>;
protected:
    explicit MxTreeNodeBase(const TreeNodeConstPtr& parent);
    explicit MxTreeNodeBase(TreeNodeConstPtr&& parent);
    virtual ~MxTreeNodeBase() = default;
public:
    // Pointer to the parent node.
    TreeNodeConstPtr Parent() const { return m_parent; }
    // 64-bit identifier that is unique in the entire tree.
    MxTreeNodeId ObjectId() const;
    // Get a simple item name, a local id. `LocalId` is not unique in the entire hierarhy.
    virtual MxTreeLocalId LocalId() const { return GetItemName(); }
    // The main subject of the node is a som math base object of type `MbRefItem`
    virtual const MbRefItem* RefItem() const { return MathItem(); }

protected:
    // C3D-model item that is represented by this node, including a type of `MbInstance`. See also SourceItem().
    virtual const MbItem * MathItem() const = 0;
    // Get a simple item name, a local id.
    SimpleName GetItemName() const;

protected:
    MxTreeNodeBase() : m_parent(nullptr), m_nodeId() {}
    void PresetId_(MxTreeNodeId id);

private:
    TreeNodeConstPtr    m_parent;  // Parent node of this node in Expanded Model Tree.
  //TreeNodeConstPtr    m_next;    // The next node is on the same level (possibility in the future).
    mutable MxTreeNodeId m_nodeId; // Unique tree node 64 bit identifier.
};

//---------------------------------------------------------------------------------------
// Get math item pointer from th `NodalData` generic type.
//---
inline const MbItem* MathItem(const SPtr<const MbItem>& nodalData) { return nodalData.get(); }

//---------------------------------------------------------------------------------------
// Get math item name.
//---
inline SimpleName LocalId(const SPtr<const MbItem>& nodalData) { return nodalData->GetItemName(); }

//---------------------------------------------------------------------------------------
// C3D-model item that discribes geometry of the graphical node (MxGrItem).
/*
  \details  It never be an `MbInstance`. This function returns only C3D-item that represents 
            geometry itself, for example, `MbSolid`, `MbMesh` or `MbAssembly`.
*/
//---
template<class RefItem>
inline const RefItem* SourceItem(const RefItem* pItem)
{
    if (const MbInstance* inst = isa_cast<const MbInstance*>(pItem))
        return inst->GetItem();
    return pItem;
}

//---------------------------------------------------------------------------------------
// Returns an assembly item if a node represents the assembly.
//---
inline const MbAssembly* AssemblyItem(const MxTreeNodeBase* assemblyNode)
{
    return isa_cast<const MbAssembly*>(SourceItem(assemblyNode->RefItem()));
}

//---------------------------------------------------------------------------------------
// Nodal object of the model Tree.
// Generic type `NodalData` may be arbitrary user specified data associated with model tree node.
// `NodalData` object have a pointer to `MbItem` avalaible via `MathItem` func.
// The template class is assumed to be an abstract form of a generic wrapper for domain-specific modeling data.
//---
template<typename NodalData>
class MxTreeNodeImpl: public MxTreeNodeBase
{
public:
    MxTreeNodeImpl(const TreeNodeConstPtr& parent, const NodalData& data)
        : MxTreeNodeBase(parent)
        , m_data(data)
    {}
    explicit MxTreeNodeImpl(const NodalData& data) // for the root node.
        : MxTreeNodeBase(nullptr)
          , m_data(data)
    {}
    explicit MxTreeNodeImpl(const NodalData&& data) // for the root node.
        : MxTreeNodeBase(nullptr)
        , m_data(std::move(data))
    {}

public:
    const NodalData & Data() const { return m_data; }
    // C3D-model item that is represented by this node, including a type of `MbInstance`. See also SourceItem().
    const MbItem * MathItem() const final { return ::MathItem(m_data); }
    MxTreeLocalId  LocalId() const final { return ::LocalId(m_data); }


private:
    NodalData m_data;
};

using MxTreeNodeConstPtr = MxTreeNodeBase::TreeNodeConstPtr;
// Tree node represented by geometric object `MbItem`.
using MxTreeItem = MxTreeNodeImpl<SPtr<const MbItem>>;
using MxTreeItemPtr = std::shared_ptr<MxTreeItem>;
using MxTreeItemConstPtr = std::shared_ptr<const MxTreeItem>;
class MxTreeRoot: public MxTreeNodeBase {};
using MxTreeRootPtr = std::shared_ptr<MxTreeRoot>;
using MxTreeRootConstPtr = std::shared_ptr<const MxTreeRoot>;


//---------------------------------------------------------------------------------------
// Returns an assembly item if a node represents the assembly.
//---
inline const MbAssembly* AssemblyItem(const MxTreeItemConstPtr& assemblyNode)
{
    return isa_cast<const MbAssembly*>(SourceItem(assemblyNode->MathItem()));
}

//---------------------------------------------------------------------------------------
// Unique sequence that addresses any node in the tree (path topdown from the root to a node).
//---
class MxTreePath
{  
    MxTreePath(); // Construct an empty path.

public:
    SimpleName OldStyleHash() const;
};

class MxTreeNodeId;

//---------------------------------------------------------------------------------------
/** \brief  \ru Развернутое дерево модели.
            \en Expanded model tree.
    \details \ru Интерфейс данного класса предоставляет функциональность для работы со структурой дерева модели.
             \en The interface of this class provides functionality to work with the model tree structure.

    \note Resposibilities:\n
    1. Tree-like representation of the model.
    2. Generating unique identifiers of the tree nodes.
*/
//---
class MxModelTree
{
public:
    MxModelTree();
    MxModelTree(const MxModelTree&) = delete;
    MxModelTree& operator=(const MxModelTree&) = delete;

public:
    // The root node is always an assembly, namely Main Assembly containing entire model.
    const MbAssembly* MainAssembly() const;
    // Assign an `MbAssembly` to be root of the model tree.
    // Initialize the model tree with assigning the main assembly.
    template<class AssemblyNodeType>
    std::shared_ptr<AssemblyNodeType> SetMainAssembly(MbAssembly*);
    MxTreeRootPtr       RootNode() {return m_rootNode;}
    MxTreeRootConstPtr  RootNode() const {return m_rootNode;}
    MxTreeItemPtr       MainAssmNode() {return m_assmNode;}
    MxTreeItemConstPtr  MainAssmNode() const {return m_assmNode;}
    // Call this before writing the model to the *.c3d file.
    MxResultCode Prepare2Write() const;

public:
    using Node = MxTreeNodeBase;

private:
    MxTreeRootPtr m_rootNode;
    MxTreeItemPtr m_assmNode; // The main assembly.
};

//-----------------------------------------------------------------------------
// Assign an `MbAssembly` to be root of the model tree.
//---
template<class AssemblyNodeType>
std::shared_ptr<AssemblyNodeType> MxModelTree::SetMainAssembly(MbAssembly* assmItem)
{
    auto assmNode = std::make_shared<AssemblyNodeType>(m_rootNode, assmItem);
    m_assmNode = assmNode;
    return assmNode;
}

//---------------------------------------------------------------------------------------
// Get to the root of the tree using the `Parent()` function.
// Return `nullptr` if `node` is already a root.
//---
MxTreeRootConstPtr RootNode(const MxTreeNodeBase& node);

//---------------------------------------------------------------------------------------
// Local coordinate system of the item positioning one in parental LCS.
//---
const MbPlacement3D& LocalPlacement(const MxTreeNodeBase& node);

#endif // __MX_MODEL_TREE_H
