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

#include "mx_model_tree.h"
#include <hash32.h>
#include <unordered_map>
#include <vsn_last.h>

const MxTreeNodeId MxTreeNodeId::null; // Undefined value of the identifier.

//---------------------------------------------------------------------------------------
// Returns 32-bit mixed hash to use in the unordered sets (hash tables).
//---
inline uint32 MxTreeNodeId::Hash32() const
{
    switch(Tag())
    {
        case MxTreeNodeId::hashPacked:
            return m_hash.value; // just use the ready hash value.
        default:
        {
            uint32 a = c3d::GOLDENRATIO, b = m_hash.uWord, c = m_hash.value;
            c3d::mix(a, b, c);
            return c;
        }        
    }
}

//---------------------------------------------------------------------------------------
// Returns 64-bit mixed hash to use in the unordered sets (hash tables).
//---
inline uint64 MxTreeNodeId::Hash64() const
{
    switch(Tag())
    {
        case MxTreeNodeId::hashPacked:
        {
            uint64 hashVal = m_64bits;              // The lower word has already an appropriate hash.
            hashVal ^= ((uint64)m_hash.value<<32);  // Mix upper word with the lower one.
            return hashVal;
        }
        default:
        {
            uint32 a = c3d::GOLDENRATIO, b = m_hash.uWord, c = m_hash.value;
            c3d::mix(a, b, c);
            return c;
        }        
    }
}

//---------------------------------------------------------------------------------------
// Returns a platform depended hash to use in std::unordered_set.
//---
size_t MxTreeNodeId::Hash() const 
{
#if defined(PLATFORM_64)
    return static_cast<size_t>(Hash64());
#else
    return static_cast<size_t>(Hash32());
#endif
}

//---------------------------------------------------------------------------------------
// It's a pair (parentId localId). This pair uniquely identifies a model tree node.
//---
struct MxTreeNodeIdPair
{        
    MxTreeNodeId    parentId = MxTreeNodeId::null;  // The global Id of the parent of the node.
    MxTreeLocalId   localId = c3d::UNDEFINED_SNAME; // The local Id of the node.
    bool operator==(const MxTreeNodeIdPair& other) const {return parentId==other.parentId && localId==other.localId;}
};

//---------------------------------------------------------------------------------------
// This function intended to implement `std::unordered_map<MxTreeNodeIdPair,ValueType>`.
//---
struct MxTreeNodeIdHasher
{
    mutable uint32 a = c3d::INIT_HASH32_VAL;
    mutable uint32 b = c3d::GOLDENRATIO;
    mutable uint32 c = c3d::GOLDENRATIO;

    inline const MxTreeNodeIdHasher& Init(const MxTreeNodeIdPair& idPair) const
    {
        a = c3d::INIT_HASH32_VAL;
        b = c = c3d::GOLDENRATIO;        
        a += HiUint32(idPair.parentId.Descriptor());
        b += LoUint32(idPair.parentId.Descriptor());
        c += idPair.localId;
        c3d::mix(a, b, c); // Generating Jenkins's hash.
        return *this;
    }
    inline uint32 Hash32() const { return c; }
    inline uint64 Hash64() const { return ((uint64)b<<32) + c; }

    size_t operator()(const MxTreeNodeIdPair& idPair) const
    { 
#if defined(PLATFORM_64)
        return static_cast<size_t>(Init(idPair).Hash64());
#else
        return static_cast<size_t>(Init(idPair).Hash32());
#endif
    }
    size_t operator()(const MxTreeNodeId& nodeId) const { return nodeId.Hash(); }
};

//---------------------------------------------------------------------------------------
// Expanded tree node identification table.
// Note: The element of the table is a tuple (objectId (parentId localId))
//---
class MxTreeNodeIdTable
{
public:
    MxTreeNodeIdTable() = default;
    MxTreeNodeIdTable(const MxTreeNodeIdTable&) = delete;
    MxTreeNodeIdTable& operator=(const MxTreeNodeIdTable&) = delete;

public:
    using key = MxTreeNodeId;
    using id_record = MxTreeNodeIdPair; // it's a pair (nodeId parentId).    
    static const id_record nullRec;
    
public:    
    const id_record& operator[] (const MxTreeNodeId& nodeId) const;
    // The number of the registered unique IDs.
    size_t size() const { return m_idTable.size();}
    // The func generates a new ID by the pair `(parent, subItem)` or returns an already registered one.        
    MxTreeNodeId Query(const MxTreeNodeId& parentId, MxTreeLocalId lacalId);

private:
   MxTreeNodeId AlternativeId_(const MxTreeNodeId& parent, MxTreeLocalId subItem) const;

private:   
    std::unordered_map<key,id_record,MxTreeNodeIdHasher> m_idTable; // All registered identifiers of the model.
    std::unordered_map<id_record,key,MxTreeNodeIdHasher> m_idAlter; // Registering alternative hashes to avoid collisions (reversed pair `key-value`).
};

//-----------------------------------------------------------------------------
// The root node implementation.
//---
class MxTreeRootImpl final: public MxTreeRoot
{
public:    
    MxTreeRootImpl()
        : MxTreeRoot()
    {
        PresetId_(MxTreeNodeId::rootNode);
    }

    MxTreeNodeIdTable& MutableIdTable() const { return const_cast<MxTreeNodeIdTable&>(m_idTable); }

private:
    const MbItem * MathItem() const final { return nullptr; }
    MxTreeNodeIdTable m_idTable;
};

const MxTreeNodeIdTable::id_record  MxTreeNodeIdTable::nullRec;

//---------------------------------------------------------------------------------------
// 
//---
inline const MxTreeNodeIdTable::id_record& MxTreeNodeIdTable::operator[] (const MxTreeNodeId& nodeId) const
{
    auto nodeIter = m_idTable.find(nodeId);
    return (nodeIter == m_idTable.end()) ? nullRec : nodeIter->second;        
}

//---------------------------------------------------------------------------------------
// Generated hash of a node id avoiding collisions (based on parenId and local id).
//---
MxTreeNodeId MxTreeNodeIdTable::AlternativeId_(const MxTreeNodeId& parentId, MxTreeLocalId subItemId) const
{ 
    const MxTreeNodeIdPair tabRec = {parentId, subItemId};
    auto nodeIter = m_idAlter.find(tabRec);
    return (nodeIter == m_idAlter.end()) ? MxTreeNodeId::null : nodeIter->second;
}

//---------------------------------------------------------------------------------------
// TODO: Extract the id table from the root node and assign the `m_nodeId`.
//       The field `m_nodeId` is a cach data member.
// MxTreeNodeIdTable is stored in an attribute of the main `MbAssembly`.
//---
MxTreeNodeIdTable& IdTable(const MxTreeRootConstPtr& rootNode)
{ 
    const MxTreeRootImpl* rootImpl = static_cast<const MxTreeRootImpl*>(rootNode.get());     
    return rootImpl->MutableIdTable();
}

//---------------------------------------------------------------------------------------
// This class is intended to calculate Jenkins hash for an arbitrary sequence of 32-bit IDs.
//---
struct SequenceHasher
{
    uint32 abc[3] = {c3d::INIT_HASH32_VAL, c3d::GOLDENRATIO, c3d::GOLDENRATIO};
    uint32 count = 0;
    inline SequenceHasher & Init(uint32 initVal) 
    {
        count = 0;
        abc[0] = initVal;
        abc[1] = abc[2] = c3d::GOLDENRATIO;
        return *this;
    }
    inline void Add(uint32 id)
    {
        abc[count%3] += id;
        ++count;
        if (0 == count%3)
        {
          c3d::mix(abc[0], abc[1], abc[2]);
        }
    }
    inline uint32 Hash() const
    {
        uint32 a = abc[0];
        uint32 b = abc[1];
        uint32 c = abc[2];
        if (0 != count%3)
        {
          c3d::mix(a, b, c);
        }

        c += count*4;
        c3d::mix(a, b, c);
        return c;
    }    
};

//---------------------------------------------------------------------------------------
// extNode - Expanded model tree node.
//---
inline uint64 TreePathHash(        uint32 uWord
                           , const MxTreeNodeConstPtr & rootNode
                           , const MxTreeNodeConstPtr & subNode )
{
    uint32 hashIndex = uWord & 0x00ffffff;

    SequenceHasher hasher;
    hasher.Init(hashIndex);
    for (MxTreeNodeConstPtr node = subNode; node != rootNode; node = node.get()->Parent())
    {
        hasher.Add(node->LocalId());
    }
    
    uint64 key = uWord;
    key <<= 32;
    key |= hasher.Hash();
    return key;
}

//---------------------------------------------------------------------------------------
// parentId - already known the parent node id.
// initVal - the previous hash, or an arbitrary value (used to avoid collisions).
// Also initVal contains the tag 0xTT in the upper 8 bites (0xTTNNNNNN).
//---
inline MxTreeNodeId TreeNodeHash(MxTreeNodeId parentId, const MxTreeLocalId subNodeId, uint32 initVal)
{   
    uint64 id = initVal;
    id <<= 32;
    SequenceHasher hasher;
    hasher.Init(initVal);
    hasher.Add(HiUint32(parentId.Descriptor()));
    hasher.Add(LoUint32(parentId.Descriptor()));
    hasher.Add(subNodeId);
    
    return MxTreeNodeId(id | hasher.Hash());
}

//---------------------------------------------------------------------------------------
// The func generates a new ID by the pair `(parent, subItem)` or returns an already registered one.
// Generated hash of a node id avoiding collisions (based on parenId and local id)
//---
MxTreeNodeId MxTreeNodeIdTable::Query(const MxTreeNodeId& parentId, MxTreeLocalId localId)
{
    const MxTreeNodeIdTable::id_record requestedRec = {parentId, localId};
    uint32 hashTag = MxTreeNodeId::hashPacked; // (0xTT000000)
    hashTag <<= 24;
    uint32 hashNum = 0x00df5e76;    // initial hash number (0x00NNNNNN).
    const auto nodeId = TreeNodeHash(parentId, localId, hashTag|hashNum);
    
    auto tabRec = (*this)[nodeId]; // It is a registered pair (parentId localId).
    
    if (tabRec == MxTreeNodeIdTable::nullRec) // registering a new ID.
    {
        C3D_ASSERT(AlternativeId_(parentId, localId) == MxTreeNodeId::null);
        m_idTable.emplace(nodeId.Descriptor(), requestedRec); 
        return MxTreeNodeId(nodeId);
    }

    if (tabRec == requestedRec) // existing ID found with no collisions.
    { 
        return nodeId;
    }

    // a hash collision detected.
    auto altNodeId = AlternativeId_(parentId, localId);
    if (altNodeId != MxTreeNodeId::null) // existing avoiding ID found with no collisions.
    {
        C3D_ASSERT((*this)[altNodeId] == requestedRec);
        return altNodeId; 
    }    
    
    size_t limitOfPicks = this->size()/4 + 16;
    // Pick the key to avoid collisions.
    for( ;limitOfPicks != 0; ++hashNum, --limitOfPicks)
    {          
        altNodeId = TreeNodeHash(parentId, localId, hashTag|(hashNum & 0x00ffffff));
        if ((*this)[altNodeId] == MxTreeNodeIdTable::nullRec) // a free id found.
        {
            // a new uniqu ID.
            m_idTable.emplace(altNodeId.Descriptor(), requestedRec);  
            m_idAlter.emplace(requestedRec, altNodeId); 
            return MxTreeNodeId(altNodeId);
        }
    }
    return MxTreeNodeId::null;
}


//---------------------------------------------------------------------------------------
// Generate unique id for the `subNode`.
// TODO: Check the code.
// Parameters:  subNode -  a node of the expanded model tree.
//              rootNode - the root node of the expanded model tree.
// Hexidemical format of the generated code: 0xTTNNNNNN:HHHHHHHH.
//---
MxTreeNodeId QueryObjectId( MxTreeNodeIdTable& idTable, const MxTreeNodeBase* subNode,
                            const MxTreeNodeConstPtr& rootNode)
{    
    C3D_ASSERT(rootNode->ObjectId().Tag() == MxTreeNodeId::rootNode);
    const auto parentNode = subNode->Parent();

    if (rootNode == parentNode && AssemblyItem(subNode)!=nullptr)
    {
        // `subNode` is a main assembly.
        return MxTreeNodeId(MxTreeNodeId::mainAssmId); // Simple name case (uniqueness is guaranteed).
    }
    const auto localId = subNode->LocalId();
    if (rootNode == parentNode->Parent())
    {
        // `parentNode` is a main assembly.
        return MxTreeNodeId(localId); // Simple name case (uniqueness is guaranteed).
    }    
    return idTable.Query(parentNode->ObjectId(), localId);
}


// //---------------------------------------------------------------------------------------
// // extNode - Expanded model tree node.
// //---
// template<class ObjectItTable>
// inline MxObjectId QueryObjectId( ObjectItTable & idTable
//                                , const MxTreeNodeConstPtr & rootNode
//                                , const MxTreeNodeConstPtr & subNode )
// {  
//     if (IsEqual(rootNode,subNode.Parent()))
//     {
//         return {node->GetItemName()}; // Simple name case.
//     }
//     std::vector<uint32> path;    
//     for (MxTreeNodeConstPtr node = subNode; !IsEqual(node, rootNode); node = node->Parent())
//     {
//         path.push_back(node->GetItemName());
//     }
//     std::reverse(path);
//     SequenceHasher hasher;
//     for (uint32 id : path)
//     {
//         hasher.Add(id);
//     }
//     hasher.Hash();
// 
//     MxObjectId objectId();
//     
//     return objectId;
// }


//---------------------------------------------------------------------------------------
//
//---
MxTreeNodeBase::MxTreeNodeBase(const TreeNodeConstPtr& parent) 
    : m_parent(parent), 
      m_nodeId() 
{}

//---------------------------------------------------------------------------------------
//
//---
MxTreeNodeBase::MxTreeNodeBase(TreeNodeConstPtr&& parent) 
    : m_parent(std::move(parent))
    , m_nodeId() 
{}

//---------------------------------------------------------------------------------------
// 
//---
void MxTreeNodeBase::PresetId_(MxTreeNodeId id)
{
    if (m_nodeId == MxTreeNodeId::null)
    {
        m_nodeId = id;
    }
}

//---------------------------------------------------------------------------------------
// 
//---
MxTreeNodeId MxTreeNodeBase::ObjectId() const
{ 
    if (m_nodeId == MxTreeNodeId::null)
    {
        const auto rootNode = RootNode(*this);
        C3D_ASSERT(rootNode != nullptr); 
        m_nodeId = QueryObjectId(IdTable(rootNode), this, rootNode);
    }
    return m_nodeId;
}

//---------------------------------------------------------------------------------------
// Get a simple item name, a local id.
//---
SimpleName MxTreeNodeBase::GetItemName() const
{
    if ( const MbItem* mbItem = MathItem() )
      return mbItem->GetItemName();
    return c3d::UNDEFINED_SNAME;
}

//-----------------------------------------------------------------------------
// 
//---
MxModelTree::MxModelTree() 
    : m_rootNode(std::make_shared<MxTreeRootImpl>())
    , m_assmNode()
{}

//-----------------------------------------------------------------------------
// The root node is always an assembly, namely Main Assembly containing entire model.
//---
const MbAssembly* MxModelTree::MainAssembly() const
{
    if (m_assmNode == nullptr)
    {
        return nullptr;
    }
    if (const MbAssembly* assm = isa_cast<const MbAssembly*>(m_assmNode->MathItem()))
    {
        return assm;
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------
// Call this before writing the model to the *.c3d file.
//---
MxResultCode MxModelTree::Prepare2Write() const
{
    // TODO: Save an ID table into the c3d model attributes.
    return MxResultCode::Ok;
}

//---------------------------------------------------------------------------------------
// Get to the root of the tree using the `Parent()` function.
// Return `nullptr` if `node` is already a root.
//---
MxTreeRootConstPtr RootNode(const MxTreeNodeBase& node)
{     
    auto parent = node.Parent();
    auto res = parent;

    while (parent != nullptr)
    {
        res = parent;
        parent = res->Parent();
    }
    C3D_ASSERT(res->ObjectId().Tag() == MxTreeNodeId::rootNode);
    if (res->ObjectId().Tag() == MxTreeNodeId::rootNode)
    {
        return {res, static_cast<const MxTreeRoot*>(res.get())};
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------
// Local coordinate system of the item positioning one in parental LCS.
//---
const MbPlacement3D& LocalPlacement(const MxTreeNodeBase& node)
{
  if (const MbInstance * inst = isa_cast<const MbInstance*>(node.RefItem()))
  {
    return inst->GetPlacement();
  }

  return MbPlacement3D::global;
}


// eof
