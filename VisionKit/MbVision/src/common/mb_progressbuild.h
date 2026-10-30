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


////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneGenerator представляет фабрику представлений геометрических
             объектов, а также генерацию готовой сцены для последующей отрисовки.
         \en SceneGenerator class presents a factory of geometric object representations,
             and also generates the prepared scene for the next rendering. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PROGRESSBUILD_H
#define __VSN_PROGRESSBUILD_H

#include <vsn_object.h>
#include <vsn_geometry.h>
#include <vsn_geometryrep.h>
#include <mb_visiondef.h>

using namespace VSN;

class SceneGenerator;
//------------------------------------------------------------------------------
/** \brief \ru Класс ProgressBuild служит для определения конца и шага генерации полигональной модели.
           \en ProgressBuild class serves to define an end and a step for generating a polygonal model. \~
    \details \ru Класс ProgressBuild имеет ряд функций, а также сигналов, с помощью которых пользователь 
                 может узнать состояние генерации тел и примитивов, а также ее окончание. Важно знать, что
                 ProgressBuild применяется только при генерации математических объектов. \n.
             \en ProgressBuild class has a set of functions, and also signals that the user
                 can use to know a state of the solid and the primitive generation and also when generation ends.
                 It's important to know that ProgressBuild class is used only when generating math objects. \n \~
    \ingroup Vision_Node
*/
// ---
class ProgressBuild : public Object
{
    VSN_OBJECT(ProgressBuild);
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ProgressBuild(SceneGenerator* pGenerator);
    /// \ru Деструктор. \en Destructor. \~ 
    ~ProgressBuild() override;
public:
    /// \ru Вернуть текущее значение перестраиваемой геометрии. \en Returns the current value of the rebuilding geometry. \~
    int GetValue() const;
    /// \ru Вернуть минимальное значение перестраиваемой геометрии. \en Returns the minimum value of the rebuilding geometry. \~
    int GetMinimum() const;
    /// \ru Вернуть максимальное значение количества перестраиваемой геометрии. \en Returns the maximum quantity value of the rebuilding geometry. \~
    int GetMaximum() const;
    void RegisterGeometryRep(const GeometryRep* pGeometryRep);
    void RegisterGeometry(const Geometry* pGeometry);
    void UnregisterGeometry(const Geometry* pGeometry);
public:
    /// \ru Сигнал об окончании перестроения конкретной геометрии. \en The signal about finishing rebuilding of a certain geometry. \~
    VSN_SIGNAL(Public, ValueModified, void ValueModified(int val), val)
public:
    VSN_SLOT(Public, slotFinishBuildRep, void slotFinishBuildRep())
    VSN_SLOT(Public, slotFinishBuildGeometry, void slotFinishBuildGeometry(Geometry* pGeometry))
    /// \ru Сигнал об окончании перестроения всей геометрии. \en The signal about finishing rebuilding of all geometry. \~
    VSN_SIGNAL(Public, BuildAllCompleted, void BuildAllCompleted())
protected:
    int m_currentGeometry;
    int m_countGeometry;
    SceneGenerator* m_pGenerator;
    ObjectList<const Geometry*> m_geometries;
private:
    VSN_DISABLE_COPY(ProgressBuild)
    friend class SceneGenerator;
};

// Returns the current value of the rebuilding geometry
inline int ProgressBuild::GetValue() const { return m_currentGeometry; }
// Returns the minimum value of the rebuilding geometry.
inline int ProgressBuild::GetMinimum() const { return 0; }
// Returns the maximum quantity value of the rebuilding geometry.
inline int ProgressBuild::GetMaximum() const { return m_countGeometry; }

#endif /* __VSN_PROGRESSBUILD_H */
