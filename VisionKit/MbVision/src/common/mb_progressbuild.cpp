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

#include <mb_progressbuild.h>
#include <mb_scenegenerator.h>
#include <vsn_last.h>

using namespace c3d;

//-----------------------------------------------------------------------------
// Конструктор по умолчанию
// ---
ProgressBuild::ProgressBuild(SceneGenerator* pGenerator)
    : Object(nullptr)
    , m_currentGeometry(0)
    , m_countGeometry(0)
    , m_pGenerator(pGenerator)
{
}

//-----------------------------------------------------------------------------
// Деструктор
// ---
ProgressBuild::~ProgressBuild() { emit BuildAllCompleted(); }

//-----------------------------------------------------------------------------
//
// ---
void ProgressBuild::slotFinishBuildRep()
{
    if (GeometryRep* pRepresentation = vobject_cast<GeometryRep*>(GetSender()))
    {
        const ObjectList<Geometry*>& list = pRepresentation->GetGeomList();
        for (auto it : list)
            UnregisterGeometry(it);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void ProgressBuild::slotFinishBuildGeometry(Geometry* pGeometry) { UnregisterGeometry(pGeometry); }

//-----------------------------------------------------------------------------
//
// ---
void ProgressBuild::RegisterGeometryRep(const GeometryRep* pGeometryRep)
{
    auto& list = pGeometryRep->GetGeomList();
    for (auto it : list)
        RegisterGeometry(it);
}

//-----------------------------------------------------------------------------
//
// ---
void ProgressBuild::RegisterGeometry(const Geometry* pGeometry)
{
    if (!m_geometries.contains(pGeometry))
    {
        m_countGeometry++;
        m_geometries << pGeometry;
        Object::Connect(pGeometry, &Geometry::OnBuildCompleted, 
            this, &ProgressBuild::slotFinishBuildGeometry);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void ProgressBuild::UnregisterGeometry(const Geometry* pGeometry)
{
    auto index = m_geometries.indexOf(pGeometry);
    if (index != -1)
    {
        m_geometries.removeAt(index);
        m_currentGeometry++;
        Object::Disconnect(pGeometry, &Geometry::OnBuildCompleted, 
            this, &ProgressBuild::slotFinishBuildGeometry);
        emit ValueModified(m_currentGeometry);
    }
    if (m_geometries.size() == 0)
    {
        if (m_pGenerator != nullptr)
            m_pGenerator->ClearProgressBuild();
    }
}


