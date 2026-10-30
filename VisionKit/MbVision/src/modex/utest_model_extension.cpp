//
// Created by al-maks on 03.09.23.
//
#include <generic_utility.h>
#include <mb_class_traits.h>
#include <mx_model_extension.h>
#include <action_solid.h>
#include <gtest/gtest.h>
#include <iostream>

#include <vsn_last.h>

//------------------------------------------------------------------------------
//
// ---
template< class PointsArray >
static void Get4BoxVertices( PointsArray & points )
{
  const double d1 = 100;
  const double d2 = 40;
  const double d3 = 0.62*(d1+d2);
  points.clear();
  MbPlacement3D place;
  MbCartPoint3D origin( -0.5 * d1, -0.5 * d2, - 0.5 * d3 );
  place.GetPointFrom( origin );
  points.push_back( origin );

  MbCartPoint3D pnt;
  pnt.Init( 0.5 * d1, -0.5 * d2, -0.5 * d3 );
  place.GetPointFrom( pnt );
  points.push_back( pnt );
  pnt.Init( -0.5 * d1, 0.5 * d2, -0.5 * d3 );
  place.GetPointFrom( pnt );
  points.push_back( pnt );
  pnt.Init( -0.5 * d1, -0.5 * d2, 0.5 * d3 );
  place.GetPointFrom( pnt );
  points.push_back( pnt );
}

//----------------------------------------------------------------------------------------
// Create a box for testing purposes.
// ---
static SPtr<MbSolid> CreateBox()
{
    c3d::SpacePointsVector points;  
    MbSNameMaker names1( 1, MbSNameMaker::i_SideNone, 0 );
    Get4BoxVertices( points );
    MbElementarySolidResults res;
    ElementarySolid( MbElementarySolidParams(et_Block, points, names1), res );

    return res.GetResultSolid();
}

//---------------------------------------------------------------------------------------
// Create testing model tree.
// The routine creates the model hierarchy based on reused assembly 'A4'.
// See a figure of page: https://wiki.c3d.ascon.ru/doku.php?id=development:c3d_model:expanded_tree
//---
std::unique_ptr<MxModelExtension> CreateA1I2I3A4I5I6S7()
{
  std::unique_ptr<MxModelExtension> modelExt = std::make_unique<MxModelExtension>();
  SPtr<MbSolid> s7 = CreateBox();
  const MbVector3D trans = s7->GetCube().GetDiagonal()*MbVector3D::xAxis;
  MbPlacement3D lcs;
  MxGrAssembly itemA1 = modelExt->MainAssembly();
  SPtr<MbAssembly> itemA4 = c3d::make_sptr<MbAssembly>(); // Assembly 'A4' is reused twice.
  auto itemI2 = itemA1.AddInstance( itemA4, lcs );
  auto itemI3 = itemA1.AddInstance( itemA4, lcs.Move(trans) );
  EXPECT_NE(itemI2, itemI3);
  EXPECT_TRUE( ok(itemI2) && ok(itemI3) );

  MbItem * inst5 = itemA4->AddInstance( *s7, lcs.Move(trans) );
  MbItem * inst6 = itemA4->AddInstance( *s7, lcs.Move(trans) );
  EXPECT_NE(inst5, nullptr);
  EXPECT_NE(inst6, nullptr);

  return modelExt;
}

//---------------------------------------------------------------------------------------
// Test access to sub-assembly interface and traversing its sub components.
//---
TEST(ModexSample, SubAssemblyItems)
{
    std::unique_ptr<MxModelExtension> modelExt = CreateA1I2I3A4I5I6S7();
    MxGrAssembly assembly = modelExt->MainAssembly();
    // Компонентом называется все из чего состоит сборка "физически".
    // A component is everything that makes up any assembly phisically.
    for (MxGrComponentItem comp: assembly.Components())
    {
        EXPECT_EQ(assembly, comp.ParentAssembly());
        // Component 'comp' may be a solid, an instance or a sub-assembly.
        MxGrAssembly subAssembly = modelExt->SubAssembly(comp);      
        auto subAssmMat = subAssembly.Placement().GetMatrixFrom();
        for (MxGrComponentItem subComp : subAssembly.Components())
        {
            EXPECT_TRUE(subAssembly == subComp.ParentAssembly());
            const MbItem * mbItem = subComp.MathItem();
            EXPECT_NE(mbItem, nullptr);
            EXPECT_TRUE(mbItem != nullptr && isa_cast<const MbInstance*>(mbItem) != nullptr);
            if (const MbInstance * mbInst = isa_cast<const MbInstance*>(mbItem))
            {
                // The key difference is mbInst->GetPlacement() denots LCS in the subassembly's CS and
                // subComp.Placement() is denoted in The World. So both LCSs can be not equal.
                EXPECT_TRUE( mbInst->GetPlacement()*subAssmMat == subComp.Placement() );
            }
        }
    }
}

//---------------------------------------------------------------------------------------
// 
//---
TEST(ModexSample, UniqueIDs)
{
    std::unique_ptr<MxModelExtension> modelExt = CreateA1I2I3A4I5I6S7();

    std::queue<MxGrItem> Q;
    std::set<uint64> nodeIDs;
    Q.push(modelExt->MainAssembly());
    std::cout << std::hex << std::showbase << modelExt->MainAssembly().ObjectId().Descriptor() << '\n';
    for (; !Q.empty(); Q.pop())
    {
        const MxGrItem currItem = Q.front();
        MxObjectId currId = currItem.ObjectId();
        EXPECT_TRUE(nodeIDs.insert(currId.Descriptor()).second);
        
        for (const MxGrItem& subItem : currItem.SubItems())
        {
            EXPECT_EQ(currItem.ObjectId(), subItem.ParentId());
            Q.push(subItem);
            std::cout << std::hex << std::showbase << subItem.ObjectId().Descriptor() << '\n';
        }
    }
    // Count of unique identifiers must be seven.
    EXPECT_EQ(nodeIDs.size(), 7);
}


//---------------------------------------------------------------------------------------
// 
//---
TEST(ModexSample, AssemblyComponents)
{
    MxModelExtension modelExt;
  
    // Интерфейс MxGrAssembly с доступом на редактирование предоставляется только через MxModelExtension.
    MxGrAssembly assembly = modelExt.MainAssembly(); // Get an interface of the root assembly.
    // Создать тестовое тело.
    SPtr<MbSolid> box = CreateBox();
    // Добавить Экземпляр тела в сборку.
    auto inst1 = assembly.AddInstance(box, MbPlacement3D::global);
    auto inst2 = assembly.AddInstance(box, MbPlacement3D::global);
    assembly.AddInstance(CreateBox(), MbPlacement3D().Move(MbVector3D::zAxis*100.0));
    EXPECT_NE(inst1, inst2);
    EXPECT_TRUE( ok(inst1) && ok(inst2) );
    EXPECT_FALSE(assembly.Components().empty());
    size_t itemsCount = 0;
    for ( const MxGrComponentItem comp: assembly.Components() )
    {
        EXPECT_TRUE(assembly == comp.ParentAssembly());
        ++itemsCount;
    }
    EXPECT_EQ(itemsCount, 3);
}
