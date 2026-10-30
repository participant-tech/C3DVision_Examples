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
#ifndef __VSN_SCENEGENERATOR_H
#define __VSN_SCENEGENERATOR_H

#include <mx_model_extension.h>

#include <vsn_objectmap.h>
#include <vsn_object.h>
#include <vsn_geometry.h>
#include <vsn_geometryrep.h>
#include <vsn_scsegmentdata.h>
#include <vsn_scenesegment.h>
#include <mb_progressbuild.h>
#include <mb_visiondef.h>


using namespace VSN;

class MxGrItem;
class MxModelExtension;
class SampleGeometryMap;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneGenerator представляет фабрику представлений геометрических
               объектов, а также генерацию готовой сцены для последующей отрисовки.
           \en SceneGenerator class presents a factory of geometric object representations and
               also generates the prepared scene for the next rendering. \~
  \details \ru SceneGenerator имеет две группы функций. Первая группа работает непосредственно с математическими
               объектами и тем самым обеспечивает глубокую интеграцию с математическим ядром. Вторая группа
               генерирует представления простых объектов, таких как куб, цилиндр, сфера и др., т.е. где 
               полигональная модель рассчитывается не с помощью математического ядра, а самими визуальными
               объектами. \n.
           \en SceneGenerator class has two function groups. The first one directly operates with math objects
               providing a deep integration with the math kernel. The second one generates representations
               of such simple objects as cube, cylinder, sphere, etc., i.e. a polygonal model is computed
               with not a math kernel, but with visual objects themselves. \n \~
    \ingroup Vision_Node
*/
// ---
class SceneGenerator : public Object
{
    VSN_OBJECT(SceneGenerator);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit SceneGenerator(Object* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    ~SceneGenerator() override;
public:
    /// \ru Загрузить модель из памяти. \en Loads the model from memory. \~
    static SPtr<MbModel> LoadModel(const char* pMemory, size_t length);
    /// \en Returns an array group of geometric objects for building a default scene. \~ 
    static const std::vector<MbeSpaceType>& DefaultSpaceTypes();
    /// \en Set the default array of geometric objects to build the scene with.
    /// \en \param[in] addition - addition to existing types
    static void SetDefaultSpaceTypes(const std::vector<MbeSpaceType>& spaceTypes, bool addition = false);
    /// \en Correction of rendering accuracy in accordance with the overall cube
    /// \en drawPrecisionFactor - this is not the accuracy and not the deflection arrow and not the 
    /// \en                       deviationStep - this is a multiplier that roughens both the accuracy 
    /// \en                       and the deflection arrow and the deviationStep
    static double CorrectDrawPrecision(double drawPrecisionFactor, const MbCube& gabarit);
public: /// \ru Группа функций, работающая с математическим ядром. \en Group functions operating with the math kernel. \~
    /// \ru Создать прогресс построения геометрии. \en Creates the progress of the rebuilding geometry. \~
    ProgressBuild* CreateProgressBuild();
    /// \ru Создать граф сцены из MbModel. \en Creates a scene graph from MbModel. \~
    SceneSegment* CreateSceneSegment(SPtr<MbModel> pModel, SceneSegment* pParent = nullptr);
    // Creates a scene graph from `MxModelExtension` 
    SceneSegment* CreateSceneSegment(MxModelExtension* modExt, SceneSegment* pParent = nullptr);
    /// \ru Построение полигонального представления для отрисовки сцены. \en Building a polygon representation for scene rendering. \~
    void StartBuildGeometry(CommandType buildType = CommandType::Threaded);
    /// \en Set the precision for polygon calculation. \~
    void SetVisualSag(double visualSag);
public:
    /// \ru Сигнал об окончании перестроения конкретной геометрии. \en The signal about finishing rebuilding of a certain geometry. \~
    VSN_SIGNAL(Public, CreateSegment, void CreateSegment(SceneSegment* newSeg, SceneSegment* parentSeg), newSeg, parentSeg)
    /// \ru Сигнал об окончании перестроения конкретной геометрии. \en The signal about finishing rebuilding of a certain geometry. \~
    VSN_SIGNAL(Public, CreateSegmentItem, void CreateSegmentItem(SceneSegment* newSeg, SceneSegment* parentSeg, 
        const MbModel* model, const MbItem* item, const MbItem* parentItem), newSeg, parentSeg, model, item, parentItem)
    VSN_SIGNAL(Public, SetupIDMapping, void SetupIDMapping(const NodeKey& key, const NodeKey& keyItem, const MxObjectId& id), key, keyItem, id);
protected:
    VSN_SLOT(Protected, OnBuildCompleted, void OnBuildCompleted(Geometry* pGeometry))
protected:
    // Build a segment scene based on the Model Extension.
    void BuildSceneEx(const MxModelExtension& modExt, const MxGrItem & pItem, SceneSegment* pParent, uint& countGeom );
    // Add a final element, a body, to the scene.
    void BuildFinalSegment(const MxGrItem & pItem, SceneSegment* pParent, uint& countGeom );
    void LoadSceneFromModel(SPtr<MbModel> pModel, SceneSegment* pParent);
    void ClearProgressBuild();
    // Create reference geometry if any
    SegmentInstance* CreateSegmentInstance(const MxGrItem& grItem);

    Material* CreateMaterialFromItem(const MxGrItem& grItem);
    void ClearMaterials();
private:
    uint m_countBuilt;
    ProgressBuild* m_pProgressBuild;
    SceneSegment* m_pHeadSegment;
    std::shared_ptr<SampleGeometryMap> m_pGeometryHash;
    std::shared_ptr<MaterialCache> m_ptrMaterialCache;
    std::vector<SPtr<MbItem>> m_items;
    ObjectMap<const MbItem*, Material*> m_actualMaterials;
    double m_visualSag;
private:
    // Group of geometric objects for building a default scene
    static std::vector<MbeSpaceType> m_geomSpaceTypes;
private:
    VSN_DISABLE_COPY(SceneGenerator);
    friend class ProgressBuild;
};

#endif /* __VSN_SCENEGENERATOR_H */
