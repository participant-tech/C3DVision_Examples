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

#ifndef MATH_POINTCLOUD_H
#define MATH_POINTCLOUD_H
#include <vsn_pointcloudgeometry.h>

class MbPointFrame;
class MbMesh;

namespace VSN
{
    class PointCloudGeometry;
}

//------------------------------------------------------------------------------
/** \brief \ru Класс PointCloudBuilder определяет алгоритм перестроения облака точек.
           \en The PointCloudBuilder class defines an algorithm for rebuilding a point cloud. \~
*/
// ---
class PointCloudBuilder
{
public:
    virtual ~PointCloudBuilder() = default;
public:
    virtual void Build(VSN::PointCloudGeometry&) = 0;
};

//------------------------------------------------------------------------------
/** \brief \ru Класс MathPointCloudGeometry демонстрирует вариант интеграции облака точек с объектами ядра c3d.
           \en The MathPointCloudGeometry class demonstrates a variant of integrating a point cloud with c3d kernel objects. \~
*/
// ---
class MathPointCloudGeometry : public VSN::PointCloudGeometry
{
public:
    /// \ru Установить сетку для построения геометрии. \en Set up a grid to build geometry. \~
    void SetMesh(const SPtr<MbMesh>& mesh);
    /// \ru Установить point frame для построения геометрии. \en Set up a point frame to build geometry. \~
    void SetPointFrame(const SPtr<MbPointFrame>& pointFrame);
    /// \ru Перестроить геометрию по измененным математическим данным. \en Rebuild geometry based on modified mathematical data. \~
    void RebuildGeometry();
    /// \ru Добавить массив точек для построения облака точек и вернуть идентификатор этой группы точек. \en Add an array of points to build a point cloud and return the ID of this point group.
    uint AddPoints(const std::vector<MbCartPoint3D>& points);
    /// \ru Добавить массив точек для построения облака точек и вернуть идентификатор этой группы точек. \en Add an array of points to build a point cloud and return the ID of this point group.
    uint AddPoints(const std::vector<MbFloatPoint3D>& points);
private:
    std::unique_ptr<PointCloudBuilder> m_builder;
};

#endif //MATH_POINTCLOUD_H
