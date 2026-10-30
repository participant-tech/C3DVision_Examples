#include "mb_pointcloud.h"

#include <mesh.h>
#include <point_frame.h>
#include <vector>

#include <vsn_point3d.h>
#include <vsn_pointcloudgeometry.h>

#include <vsn_last.h>

using namespace VSN;

class PointCloudFromFrame : public PointCloudBuilder
{
public:
    explicit PointCloudFromFrame(const SPtr<MbPointFrame>& pointFrame);
public:
    void Build(PointCloudGeometry&) override;
private:
    SPtr<MbPointFrame> m_pointFrame;
};

class PointCloudFromMesh : public PointCloudBuilder
{
public:
    explicit PointCloudFromMesh(const SPtr<MbMesh>& mesh);
public:
    void Build(PointCloudGeometry&) override;
private:
    SPtr<MbMesh> m_mesh;
};

//-----------------------------------------------------------------------------
//
// ---
void MathPointCloudGeometry::SetMesh(const SPtr<MbMesh>& mesh) { m_builder = std::make_unique<PointCloudFromMesh>(mesh); }

//-----------------------------------------------------------------------------
//
// ---
void MathPointCloudGeometry::SetPointFrame(const SPtr<MbPointFrame>& pointFrame)
{
    m_builder = std::make_unique<PointCloudFromFrame>(pointFrame);
}

//-----------------------------------------------------------------------------
//
// ---
void MathPointCloudGeometry::RebuildGeometry()
{
    Clear();
    if (m_builder)
        m_builder->Build(*this);
}

//-----------------------------------------------------------------------------
//
// ---
uint MathPointCloudGeometry::AddPoints(const std::vector<MbCartPoint3D>& points)
{
    std::vector<Point3DF> visionPoints;
    visionPoints.insert(visionPoints.end(), points.begin(), points.end());
    return PointCloudGeometry::AddPoints(visionPoints, defaultColor, defaultSize);
}

//-----------------------------------------------------------------------------
//
// ---
uint MathPointCloudGeometry::AddPoints(const std::vector<MbFloatPoint3D>& points)
{
    std::vector<Point3DF> visionPoints;
    visionPoints.insert(visionPoints.end(), points.begin(), points.end());
    return PointCloudGeometry::AddPoints(visionPoints, defaultColor, defaultSize);
}

//---------------------------------------------------------------------------
//
// ---
PointCloudFromFrame::PointCloudFromFrame(const SPtr<MbPointFrame>& pointFrame)
    : m_pointFrame(pointFrame)
{
}

//---------------------------------------------------------------------------
//
// ---
void PointCloudFromFrame::Build(PointCloudGeometry& res)
{
    std::vector<Point3DFColored> points;
    points.reserve(m_pointFrame->GetVerticesCount());
    for (size_t i = 0; i < m_pointFrame->GetVerticesCount(); ++i)
    {
        const auto* vertex = m_pointFrame->GetVertex(i);
        points.push_back({vertex->GetCartPoint(), vertex->GetColor()});
    }
    res.AddPoints(points, 4.0f);
}

//---------------------------------------------------------------------------
//
// ---
PointCloudFromMesh::PointCloudFromMesh(const SPtr<MbMesh>& mesh)
    : m_mesh(mesh)
{
}

//---------------------------------------------------------------------------
//
// ---
void PointCloudFromMesh::Build(PointCloudGeometry& res)
{
    for (size_t i = 0; i < m_mesh->GridsCount(); ++i)
    {
        auto* grid = m_mesh->GetGrid(i);
        std::vector<Point3DF> gridPoints;
        grid->GetPoints<MbCartPoint3D>(gridPoints);
        res.AddPoints(gridPoints, Color(100, 100, 100), 4);
    }
}
