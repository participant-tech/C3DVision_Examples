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

#include <mb_scenegenerator.h>

#include <assembly.h>
#include <mb_class_traits.h>
#include <mb_variables.h>
#include <mx_model_extension.h>
#include <mx_model_routines.h>
#include <attr_product.h>
#include <action_mesh.h>
#include <op_mesh_parameter.h>
#include <conv_model_exchange.h>
#include <conv_exchange_settings.h>
#include <vsn_renderstatistics.h>
#include <vsn_mathgeometry.h>
#include <vsn_mathrepresentation.h>

#include <vsn_last.h>


using namespace c3d;

//-----------------------------------------------------------------------------
// The class implements associative container to store geometry representation of the samples.
// (sample is a solid or mesh reused by instancies).
//---
class SampleGeometryMap
{
    using samples_map = std::unordered_map<const MbItem*, std::pair<SegmentInstance*, Geometry*>>;
    using samples_range = c3d::range<samples_map::const_iterator>;

public:    
     SampleGeometryMap() = default;
    ~SampleGeometryMap() { ClearGeometries(); }
public:
    samples_range SampleGeometry() const
    { 
        return c3d::make_range(m_gSamplesMap.begin(), m_gSamplesMap.end());
    }
    void AppendInstance(const MxGrItem& grItem, SegmentInstance* pInstance, Geometry* pGeometry)
    {
        auto it1 = m_gSamplesMap.find(grItem.SourceItem());
        if (it1 == m_gSamplesMap.end())
            m_gSamplesMap.insert({ grItem.SourceItem(), std::make_pair(pInstance, pGeometry) });
    }
    void RemoveGeometry(const MxGrItem& grItem)
    {
        auto it1 = m_gSamplesMap.find(grItem.SourceItem());
        if (it1 != m_gSamplesMap.end())
            m_gSamplesMap.erase(it1);
    }
    void ClearGeometries()
    {
        m_gSamplesMap.clear();
    }
public:
    SegmentInstance* FindInstanceByItem(const MxGrItem& grItem) const
    {
        auto it1 = m_gSamplesMap.find(grItem.SourceItem());
        if (it1 != m_gSamplesMap.end())
            return it1->second.first;
        return nullptr;
    }
private:
    std::unordered_map<const MbItem*, std::pair<SegmentInstance*, Geometry*>> m_gSamplesMap;
    VSN_DISABLE_COPY(SampleGeometryMap);
};

// Group of geometric objects for building a default scene
std::vector<MbeSpaceType> SceneGenerator::m_geomSpaceTypes = { st_Assembly, st_Instance,
    st_Solid, st_Mesh, st_WireFrame };

Material* kompasMaterialConverter(const MbVisual& visual)
{
    Material* pMaterial = new Material();

    const MbRGBA baseColor = visual.GetColor();
    float ambientCoeff = 0.5f;
    float diffuseCoeff = 0.6f;
    float specularCoeff = 0.8f;
    float emissionCoeff = 0.5f;

    pMaterial->SetAmbient(Color(baseColor.GetRedFloat() * ambientCoeff, baseColor.GetGreenFloat() * ambientCoeff, baseColor.GetBlueFloat() * ambientCoeff, 1.0f));
    pMaterial->SetDiffuse(
        Color(baseColor.GetRedFloat() * diffuseCoeff, baseColor.GetGreenFloat() * diffuseCoeff, baseColor.GetBlueFloat() * diffuseCoeff, baseColor.GetAlphaFloat()));
    pMaterial->SetSpecular(
        Color(baseColor.GetRedFloat() * specularCoeff, baseColor.GetGreenFloat() * specularCoeff, baseColor.GetBlueFloat() * specularCoeff, 1.0f));
    pMaterial->SetEmission(Color(baseColor.GetRedFloat() * emissionCoeff, baseColor.GetGreenFloat() * emissionCoeff, baseColor.GetBlueFloat() * emissionCoeff, 1.0f));

    float shininess = visual.Shininess();
    if (shininess < 1.0)
        shininess = 128.f;

    pMaterial->SetShininess(shininess);
    const float opacity = visual.Opacity();
    pMaterial->SetOpacity(opacity);

    return pMaterial;
}

//-----------------------------------------------------------------------------
// Default constructor
// ---
SceneGenerator::SceneGenerator(Object* parent)
    : Object(parent)
    , m_countBuilt(0)
    , m_pHeadSegment(nullptr)
    , m_pProgressBuild(nullptr)
    , m_pGeometryHash(nullptr)
    , m_visualSag(Math::visualSag)
{
#ifdef KOMPAS_STYLE
    MathGeometry::SetMaterialConverter(kompasMaterialConverter);
#endif
}

//-----------------------------------------------------------------------------
// Destructor
// ---
SceneGenerator::~SceneGenerator()
{
    VSN_ASSERT(m_pProgressBuild == nullptr);
    ClearMaterials();
}

//-----------------------------------------------------------------------------
// Loads the model from memory
// ---
SPtr<MbModel> SceneGenerator::LoadModel(const char* pMemory, size_t length)
{
    MbModel* pModel = nullptr;
    if (pMemory == nullptr)
        return SPtr<MbModel>(pModel);
    C3DExchangeBuffer buffer;
    buffer.Init(pMemory, length);
    ConvConvertorProperty3D convProperties;
    SPtr<MbModel> pLoadMathModel(new MbModel);
    MbeConvResType readRes = ImportFromBuffer(*pLoadMathModel, buffer, mxf_C3D, &convProperties, nullptr);
    if (readRes == cnv_Error)
        pLoadMathModel.reset();
    return pLoadMathModel;
}

// ---
const std::vector<MbeSpaceType>& SceneGenerator::DefaultSpaceTypes() { return m_geomSpaceTypes; }
//
void SceneGenerator::SetDefaultSpaceTypes(const std::vector<MbeSpaceType>& spaceTypes, bool addition)
{
    if (!addition)
        m_geomSpaceTypes.clear();
    m_geomSpaceTypes.insert(m_geomSpaceTypes.end(), spaceTypes.begin(), spaceTypes.end());
}

// Returns 1 if 0, decreasing the power
static double isnt0(double val, double& degree, const double eps = Math::metricRegion)
{
    return val > -eps ? val : (--degree, 1.0);
}

// --------------------------------------------------------------------------------------
// Correction of rendering accuracy in accordance with the overall cube
// drawPrecisionFactor - this is not the accuracy and not the deflection arrow and not the
// deviationStep - this is a multiplier that roughens both the accuracy
// and the deflection arrow and the deviationStep
// ---
double SceneGenerator::CorrectDrawPrecision(double drawPrecisionFactor, const MbCube& gabarit)
{
    // static const double st_minRatio = 0.0002598; // minimum pitch to diameter ratio (5330 triangles)
    // static const double st_minRatio = 0.000209;  // minimum pitch to diameter ratio (6642 triangles)
    // The new value is selected empirically to satisfy a tenfold increase in accuracy compared 
    // to the previous coefficient, there may be problems
    static const double st_minRatio = 0.000020968; // minimum pitch to diameter ratio (???? triangles)

    // VSN_ASSERT( !gabarit.IsEmpty() ); // degree == 0
    //  "take not the diagonal of the overall parallelepiped, but the cube root of the product of its sides"
    double degree = 3.0;
    const double vol =
        ::isnt0(gabarit.GetLengthX(), degree) * ::isnt0(gabarit.GetLengthY(), degree) * ::isnt0(gabarit.GetLengthZ(), degree);
    degree = 1.0 / ::isnt0(degree, degree);
    double p = ::pow(vol, degree);
    double d = gabarit.GetDiagonal();
    double diagonal = 20 * p < d ? p : d; // piecewise function
    if (diagonal < Math::metricRegion)
        diagonal = 50.0;

    double sag = drawPrecisionFactor * diagonal * 0.023;

    if (sag / diagonal < st_minRatio)
        sag = st_minRatio * diagonal;

    return sag;
}

//-----------------------------------------------------------------------------
// Создать прогресс построения геометрии.
// ---
ProgressBuild* SceneGenerator::CreateProgressBuild()
{
    if (m_pProgressBuild != nullptr)
        VSN_DELETE_AND_NULL(m_pProgressBuild);
    m_pProgressBuild = new ProgressBuild(this);
    return m_pProgressBuild;
}

//-----------------------------------------------------------------------------
// Создать граф сцены с MbModel
// ---
SceneSegment* SceneGenerator::CreateSceneSegment(SPtr<MbModel> pModel, SceneSegment* pParent)
{
    m_items.clear();
    m_pGeometryHash = nullptr;

    ClearMaterials();
    VSN_ASSERT(m_actualMaterials.size() == 0);

    RenderStatistics::ResetLoadedBodies();
    if (pModel == nullptr)
    {
        vsnWarning("GeometryFactory::CreateMathRep: MbModel cannot be null.");
        return nullptr;
    }
    pParent = new SceneSegment(pParent);

    std::vector<MbAttribute*> attrib;
    pModel->GetAttributes(attrib, at_ProductAttribute, at_ProductInfo);
    if (!attrib.empty())
    {
        MbProductInfo* prod = static_cast<MbProductInfo*>(attrib[0]);
        c3d::string_t sId, sName, sDescr;
        prod->GetData(sId, sName, sDescr);
        if (!sName.empty())
            pParent->SetObjectName(String(sName.c_str()));
    }
    else
        pParent->SetObjectName(String("Model"));

    emit CreateSegment(pParent, nullptr);
    emit CreateSegmentItem(pParent, nullptr, pModel, nullptr, nullptr);
    LoadSceneFromModel(pModel, pParent);

    return pParent;
}

//-----------------------------------------------------------------------------
// Creates a scene graph from `MxModelExtension`. 
// ---
SceneSegment* SceneGenerator::CreateSceneSegment(MxModelExtension* modExt, SceneSegment* pParent)
{
    uint countGeom = 0;
    m_items.clear();
    m_pGeometryHash = nullptr;

    ClearMaterials();
    VSN_ASSERT(m_actualMaterials.size() == 0);

    RenderStatistics::ResetLoadedBodies();
    if (modExt == nullptr)
    {
        vsnWarning("GeometryFactory::CreateMathRep: MbModel cannot be null.");
        return nullptr;
    }
    m_pHeadSegment = new SceneSegment(pParent);
    m_pHeadSegment->SetVisible(false);

    VSN_ASSERT(m_pGeometryHash == nullptr);
    m_pGeometryHash = std::make_shared<SampleGeometryMap>();
    BuildSceneEx(*modExt, modExt->MainAssembly(), m_pHeadSegment, countGeom);

    if (countGeom == 0)
        ClearProgressBuild();
    return m_pHeadSegment;
}

//-----------------------------------------------------------------------------
// Построение полигонального представления для отрисовки сцены.
// ---
void SceneGenerator::StartBuildGeometry(CommandType buildType)
{
    m_countBuilt = 0;
    for (const auto& sample: m_pGeometryHash->SampleGeometry())
    {
        m_countBuilt++;
        Geometry* pMathGeometry = sample.second.second;
        if (MathRepresentation* pMathRepresentation = vobject_cast<MathRepresentation*>(pMathGeometry->GetParent()))
        {
#ifdef VSN_OS_UNIX
            buildType = CommandType::Synchronous;
#endif
            pMathRepresentation->SetBuildType(buildType);
            if (pMathRepresentation->GetMathItem() == nullptr)
            {
// TODO:                pMathRepresentation->SetMathItem(m_pGeometryHash->FindItemById(it->first), m_visualSag);
            }
            else
                pMathRepresentation->RebuildGeometry();
        }
        if (buildType == CommandType::Synchronous)
            SceneGenerator::OnBuildCompleted(pMathGeometry);
        else
            Object::Connect(pMathGeometry, &Geometry::OnBuildCompleted, this,
                &SceneGenerator::OnBuildCompleted);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void SceneGenerator::OnBuildCompleted(Geometry* pGeometry)
{
    if (MathGeometry* pMathGeom = vobject_cast<MathGeometry*>(pGeometry))
    {
        if (Material* hMaterial = pMathGeom->GetHeadMaterial())
        {
            if (Material* pMaterial = m_actualMaterials.take(pMathGeom->GetMathItem()))
            {
                hMaterial->CopyFrom(*pMaterial);
                delete pMaterial;
            }
        }
    }
    m_countBuilt--;
    if (m_countBuilt == 0 && m_pHeadSegment != nullptr)
        m_pHeadSegment->SetVisible(true);
}

//-----------------------------------------------------------------------------
//
// ---
void SceneGenerator::SetVisualSag(double visualSag)
{ m_visualSag = visualSag; }

static String GetItemName(const String& _name, const MbItem* pItem)
{
    VSN_ASSERT(pItem != nullptr);
    String name = _name;
    std::vector<MbAttribute*> attrib;
    pItem->GetAttributes(attrib, at_ProductAttribute, at_ProductInfo);
    if (!attrib.empty())
    {
        MbProductInfo* prod = static_cast<MbProductInfo*>(attrib.front());
        c3d::string_t sId, sName, sDescr;
        prod->GetData(sId, sName, sDescr);
        name = sName.c_str() + String("-(") + _name + String(')');
    }
    return name;
}

//-----------------------------------------------------------------------------
//
// ---
Material* SceneGenerator::CreateMaterialFromItem(const MxGrItem& grItem)
{
    Material* pMaterial = nullptr;
    const MbItem* pItem = grItem.MathItem();   // It may by `MbInstance`.

    if (pItem == nullptr)
        return pMaterial;

    auto it = m_actualMaterials.find(pItem);
    if (it != m_actualMaterials.cend())
        return pMaterial;

    if (const MbVisual* visual = MaterialPropertiesRecursively(grItem))
        pMaterial = MaterialCache::CreateMaterialFromAttribute(*pItem, false, nullptr, visual);

    if (pMaterial != nullptr)
        m_actualMaterials.insert(pItem, pMaterial);
    return pMaterial;
}

//-----------------------------------------------------------------------------
//
// ---
void SceneGenerator::ClearMaterials()
{
    std::set<Material*> sMaterials;
    for (auto* pMaterial : m_actualMaterials)
        sMaterials.insert(pMaterial);
    for (auto* pMaterial : sMaterials)
        delete pMaterial;
    m_actualMaterials.clear();
}

//-----------------------------------------------------------------------------
// Установка свойства для восставновления `MbPath` из иерархии сегментов в последствии.
// ---
inline void SetPathItemProperty(SceneSegment* pSegment, const MbItem* pItem)
{
    VSN_ASSERT(pItem != nullptr);
    // Set a local ID of assembly or assembly subitem. It's unique only to the local assembly and not to the entire model..
    // Задать ID-шник сборки или объекта сборки. Уникальный только на уровне этой сборки, но не для всей модели.
    pSegment->SetProperty(C3D_PATHITEM_ID, pItem->GetItemName());
    if (const MbInstance * pInst = isa_cast<const MbInstance*>(pItem))
    {
        // Set an additional ID of the instance source.
        // Задать дополнительный ID-шник источника вставки. Нужен для сборки полной последовательности `MbPath`.
        pSegment->SetProperty(C3D_PATHITEM_SUB_ID, pInst->GetItem()->GetItemName());
    }
}

//-----------------------------------------------------------------------------
// Построить сцену сегментов на основе Расширения Модели (Новый вариант).
/*
  modEx - Расширение модели, предоставляющее Дерево модели.
  grItem - Графический узел Дерева модели.
  
  Для сведения:
   - Установка свойств `C3D_PATHITEM_ID` применяется только в проекте мастеркласса N60,
     а также всюду где есть `ObjectPickSelectionPrivate::FindMathObject`.
   - Сигнал `CreateSegmentItem` применяется только в 50-м примере (Workshop).
*/
// ---
void SceneGenerator::BuildSceneEx(const MxModelExtension& modExt, const MxGrItem& grItem,
                                  SceneSegment* pParent, uint& countGeom)
{
    const MbItem * pItem = grItem.MathItem();   // It may by `MbInstance`.
    const MbItem * sItem = grItem.SourceItem(); // It is a source geometry, not `MbInstance`.
    if (sItem == nullptr || pItem == nullptr)
        return;
    
    const MbeSpaceType sType = sItem->IsA(); // Характеристический тип геометрии (никогда не бывает типом `MbInstance`).
    const std::vector<MbeSpaceType>& spaceTypes = SceneGenerator::DefaultSpaceTypes();
    if (std::find(spaceTypes.cbegin(), spaceTypes.cend(), sType) == spaceTypes.cend())
        return; // Reject geometry type that out of enabling list `spaceTypes`.

    // Пока оставляем старые "правила игры" - на всякий `MbInstance` заводится соотвествующий `SceneSegment`.
    switch (sItem->IsA()) // Тип узла по его оранизации (может быть типом `MbInstance`).
    {        
        case st_Assembly:
        {
            SceneSegment* pNewSegment = new SceneSegment(pParent);
            pNewSegment->SetObjectName(GetItemName(String("Assembly"), pItem));
            pNewSegment->SetVisible(IsVisible(grItem));
            SetPathItemProperty(pNewSegment, pItem);

            emit SetupIDMapping(pNewSegment->GetUniqueKey(), NodeKey::ZERO, grItem.ObjectId());
            emit CreateSegment(pNewSegment, pParent);
            emit CreateSegmentItem(pNewSegment, pParent, nullptr, pItem, grItem.ParentItem());

            if (m_pProgressBuild != nullptr)
            {
              if (MathRepresentation* pRepresentation = vobject_cast<MathRepresentation*>(pNewSegment->GetRepresentation()))
                 m_pProgressBuild->RegisterGeometryRep( pRepresentation );
            }
            pNewSegment->GetTransform().SetMatrix(grItem.LocalPlacement().GetMatrixFrom());

            for (MxGrItem subItem: grItem.SubItems()) // Пока итератор предоставляет `subItem` "по значению".
              BuildSceneEx(modExt, subItem, pNewSegment, countGeom);
            return;
        }    

        default:
            // Call this to build a final node of the scene.
            return BuildFinalSegment(grItem, pParent, countGeom);
    }
}

//-----------------------------------------------------------------------------
// Добавить в сцену конечный элемент, тело.
/*
  modEx - Расширение модели, предоставляющее Дерево модели.
  grItem - Графический узел Дерева модели, который .
  
  Для сведения:
   - Установка свойств `C3D_PATHITEM_ID` пока применяется только в проекте мастеркласса N60.
   - Сигнал `CreateSegmentItem` пока применяется только в 50-м примере (Workshop).
*/
// ---
void SceneGenerator::BuildFinalSegment(const MxGrItem& grItem, SceneSegment* pParent, uint& countGeom)
{
    const MbItem * pItem = grItem.MathItem();   // It may by `MbInstance`.
    const MbItem * sItem = grItem.SourceItem(); // It is a source geometry, not `MbInstance`.
    if (sItem == nullptr || pItem == nullptr)
        return;

//    const MbeSpaceType sType = sItem->IsA(); // Характеристический тип геометрии (никогда не бывает типом `MbInstance`).
//    if (std::find(spaceTypes.cbegin(), spaceTypes.cend(), sType ) == spaceTypes.cend())
//        return; // Reject geometry type that out of enabling list `spaceTypes`.
//    if (sType == st_Solid || sType == st_Mesh || sType == st_PointFrame || sType == st_Curve3D
//        sType == st_WireFrame || sType == st_SpaceInstance)
    {
#if 0
        const MbFormNote note(GlobalFlags::IsBuildQuadGrid(), true, false);
        MbMesh* mesh = new MbMesh(note.DoExact());
        mesh->AttributesAssign(*pItem);
        pItem->AttributesConvert(*mesh);
        mesh->CopyItemName(*pItem);
        mesh->SetRefItem(pItem);
        MbRegDuplicate* iReg = nullptr;
        pItem->CalculateMesh(MbStepData(ist_SpaceStep, /*Math::visualSag*/0.02), note, *mesh);
        SegmentInstance* pInstance = CreateSegmentInstance(mesh);
#else
        SegmentInstance* pInstance = CreateSegmentInstance(grItem);
#endif
        CreateMaterialFromItem(grItem);

        SceneSegment* pNewSegment = new SceneSegment(pInstance, pParent);
        pNewSegment->SetObjectName(GetItemName(String("Body"), sItem));
        pNewSegment->SetVisible(IsVisible(grItem));
        SetPathItemProperty(pNewSegment, pItem);

        emit SetupIDMapping(pNewSegment->GetUniqueKey(), NodeKey::ZERO, grItem.ObjectId());
        emit CreateSegment(pNewSegment, pParent);
        emit CreateSegmentItem(pNewSegment, pParent, nullptr, pItem, grItem.ParentItem()); // received in 50-th example only.

        if (m_pProgressBuild)
        {
          if (MathRepresentation* pRepresentation = vobject_cast<MathRepresentation*>(pNewSegment->GetRepresentation()))
            m_pProgressBuild->RegisterGeometryRep(pRepresentation);
        }
        MbMatrix3D matrix = grItem.LocalPlacement().GetMatrixFrom();
        pNewSegment->GetTransform().SetMatrix(matrix);

        ++countGeom;
    }
}

//---------------------------------------------------------------------------------------
//
//---
static void GatherSameItemsFromModel(const MbItem* pItem, const std::vector<MbeSpaceType>& spaceTypes, std::vector<SPtr<MbItem>>& items)
{
    if (pItem == nullptr)
        return;

    MbeSpaceType type = pItem->IsA();
    bool bEnabled = std::find(spaceTypes.cbegin(), spaceTypes.cend(), type) != spaceTypes.cend();
    if (bEnabled && (type == st_Solid || type == st_Mesh || type == st_PointFrame ||
        type == st_WireFrame || type == st_SpaceInstance))
    {
        items.emplace_back(const_cast<MbItem*>(pItem));
    }
    else if (bEnabled && type == st_Instance)
    {
        const MbInstance* pInstance = (const MbInstance*)pItem;
        GatherSameItemsFromModel(pInstance->GetItem(), spaceTypes, items);
    }
    else if (bEnabled && type == st_Assembly)
    {
        const MbAssembly* pAssembly = (const MbAssembly*)pItem;
        for (size_t i = 0, iCount = pAssembly->ItemsCount(); i < iCount; i++)
            GatherSameItemsFromModel(pAssembly->GetItem(i), spaceTypes, items);
    }
}

//---------------------------------------------------------------------------------------
//
// --
void SceneGenerator::LoadSceneFromModel(SPtr<MbModel> pModel, SceneSegment* pParent)
{
    VSN_ASSERT(pModel != nullptr);
    uint countGeom = 0;
    m_ptrMaterialCache = std::make_shared<MaterialCache>();
    MxModelExtension modExt;
    modExt.ImportFromC3DModel( *pModel );
    VSN_ASSERT(m_pGeometryHash == nullptr);
    m_pGeometryHash = std::make_shared<SampleGeometryMap>();
    BuildSceneEx(modExt, modExt.MainAssembly(), pParent, countGeom);
    if (countGeom == 0)
        ClearProgressBuild();
}

// ---
void SceneGenerator::ClearProgressBuild()
{
    ProgressBuild* pProgressBuild = m_pProgressBuild;
    if (pProgressBuild != nullptr)
    {
        pProgressBuild->DeferredDelete();
        m_pProgressBuild = nullptr;
    }
    m_ptrMaterialCache.reset();
}

//-----------------------------------------------------------------------------
//
// --
SegmentInstance* SceneGenerator::CreateSegmentInstance(const MxGrItem& grItem)
{
    SegmentInstance* pInstance = nullptr;
    if (m_pGeometryHash != nullptr)
        pInstance = m_pGeometryHash->FindInstanceByItem(grItem);

    if (pInstance == nullptr)
    {
        MathRepresentation* pMathRep = new MathRepresentation();
#ifdef VSN_OS_UNIX
        pMathRep->SetBuildType(CommandType::Synchronous);
#endif
        pInstance = new SegmentInstance(pMathRep);
        MathGeometry* pMathGeometry = vobject_cast<MathGeometry*>(pMathRep->GetGeomList().front());

        const MbItem* sItem = grItem.SourceItem(); // It is a source geometry, not `MbInstance`.
        double mathSag = m_visualSag;
        const MbeSpaceType sType = sItem->IsA(); // The characteristic type of the geometry (never of type `MbInstance`).
        if (sType == st_Solid)
        {
            MbCube gabarit;
            sItem->AddYourGabaritTo(gabarit);
            mathSag = SceneGenerator::CorrectDrawPrecision(0.05, gabarit);
        }
        pMathGeometry->SetMathItem(sItem, mathSag);
        pMathGeometry->SetMaterialCache(m_ptrMaterialCache);
        // register a new model element 
        if (m_pGeometryHash != nullptr)
            m_pGeometryHash->AppendInstance(grItem, pInstance, pMathGeometry);
        return pInstance;
    }
    else
        return pInstance;
}

