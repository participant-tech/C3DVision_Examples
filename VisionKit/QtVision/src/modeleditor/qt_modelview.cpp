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

#include <qt_modelview.h>
#include <vsn_last.h>


namespace VSN {
namespace QtVision {

/* ModelView */
ModelView::ModelView(QWidget* parent)
    : QtOpenGLSceneWidget(parent)
    , m_modelEditor(nullptr)
{
}

// ----------------------------------------------------------------------------
//
// ---
ModelView::~ModelView()
{
}

// ---
void ModelView::newFile() {}
bool ModelView::loadFiles(const QStringList& files) { Q_UNUSED(files); return false; }
void ModelView::activationView() {}
void ModelView::deactivationView() {}

#ifdef KOMPAS_STYLE
namespace {
enum class colorScheme
{
    One,
    Two,
    Three
};

Point3DF makeLatLon(float latDeg, float lonDeg)
{
    Vector3DF v(Vector3DF::zAxis);
    v.Rotate(Vector3DF::xAxis, -latDeg / 57.3);
    v.Rotate(Vector3DF::yAxis, lonDeg / 57.3);
    return {v.x, v.y, v.z};
}

void initKompasStyleLights(GraphicsScene& scene, colorScheme scheme)
{
    if (scheme == colorScheme::One)
    {
        scene.GetMainLight()->SetType(Light::DirectionLight);
        scene.GetMainLight()->SetPosition({-1.0f, 1.0f, 1.0f});
        scene.GetMainLight()->SetDiffuseColor(Color::DEFINE_WHITE);
        scene.GetMainLight()->SetSpecularColor(Color::DEFINE_WHITE);
    }
    else if (scheme == colorScheme::Two)
    {
        scene.GetMainLight()->SetType(Light::DirectionLight);
        scene.GetMainLight()->SetPosition(makeLatLon(21.6f, 25.2f));
        scene.GetMainLight()->SetAmbientColor({0.00f, 0.00f, 0.00f, 1.0f});
        scene.GetMainLight()->SetDiffuseColor({0.90f, 0.90f, 0.90f, 0.0f});
        scene.GetMainLight()->SetSpecularColor({0.70f, 0.70f, 0.70f, 1.0f});
        
        Light* pLight = scene.CreateExtraLight();
        pLight->SetType(Light::DirectionLight);
        pLight->SetPosition(makeLatLon(-57.6f, -176.5f));
        pLight->SetAmbientColor({0.00f, 0.00f, 0.00f, 0.f});
        pLight->SetDiffuseColor({0.40f, 0.40f, 0.40f, 0.f});
        pLight->SetSpecularColor({0.26f, 0.26f, 0.26f, 1.f});
    }
    else if (scheme == colorScheme::Three)
    {
        scene.GetMainLight()->SetType(Light::DirectionLight);
        scene.GetMainLight()->SetPosition(makeLatLon(27.0f, -136.8f));
        scene.GetMainLight()->SetAmbientColor({0.00f, 0.00f, 0.00f, 1.0f});
        scene.GetMainLight()->SetDiffuseColor({0.80f, 0.80f, 0.80f, 0.0f});
        scene.GetMainLight()->SetSpecularColor({0.16f, 0.16f, 0.16f, 1.0f});
        
        Light* pLight1 = scene.CreateExtraLight();
        pLight1->SetType(Light::DirectionLight);
        pLight1->SetPosition(makeLatLon(25.2f, -176.4f));
        pLight1->SetAmbientColor({0.00f, 0.00f, 0.00f, 0.f});
        pLight1->SetDiffuseColor({0.65f, 0.65f, 0.65f, 0.f});
        pLight1->SetSpecularColor({0.44f, 0.44f, 0.44f, 1.f});
        
        Light* pLight2 = scene.CreateExtraLight();
        pLight2->SetType(Light::DirectionLight);
        pLight2->SetPosition(makeLatLon(1.8f, 36.f));
        pLight2->SetAmbientColor({0.00f, 0.00f, 0.00f, 0.f});
        pLight2->SetDiffuseColor({0.90f, 0.90f, 0.90f, 0.f});
        pLight2->SetSpecularColor({0.46f, 0.46f, 0.46f, 1.f});
    }
}
} // namespace
#endif // KOMPAS_STYLE

// ----------------------------------------------------------------------------
// Initialises OpenGL resources.
// ---
void ModelView::initializeGL() 
{ 
    QtOpenGLSceneWidget::initializeGL();
    GlobalFlags::SetFaceCulling(CullFaces::Back);
    GlobalFlags::SetPixelCullingEnabled(true);

#ifdef KOMPAS_STYLE
    initKompasStyleLights(*graphicsScene(), colorScheme::Three);
#else
    mainLight()->SetDoubleSided(false);
    mainLight()->SetPosition(1000.0, 1000.0, 1000.0);
    mainLight()->SetType(Light::DirectionLight);
    mainLight()->SetSpecularColor(Color(0.2f, 0.2f, 0.2f));

    Light* pLight = graphicsScene()->CreateExtraLight();
    pLight->SetDoubleSided(false);
    pLight->SetType(Light::DirectionLight);
    pLight->SetPosition(Point3DF(-1000, -1, -1));
    pLight->SetDiffuseColor(Color(0.2f, 0.2f, 0.2f, 1.0f));
    pLight->SetSpecularColor(Color(0.2f, 0.2f, 0.2f));
#endif // KOMPAS_STYLE

    graphicsView()->SetSmoothTransition(true);
    viewport()->SetPixelCullingSize(25);
//    m_modelView->viewport()->GetCamera()->SetUpVector(Vector3DF::yAxis);
//    m_modelView->viewport()->GetCamera()->SetDefaultUpVector(Vector3DF::yAxis);
    viewport()->GetCamera()->SetViewOrientation(Orientation::IsoXYZ);

    if (OrientationMarker* pMarker = graphicsView()->GetOrientationMarker())
    {
        uint nFactor = 1;
        uint a, b, c, d, e, f, h;
        pMarker->GetRepOptionTriad(a, b, c, d, e, f, h);
        pMarker->SetRepOptionTriad(nFactor * a, nFactor * b, nFactor * c, nFactor * d, nFactor * e, nFactor * f, nFactor * h);
    }
    emit afterInitializeModelView();
}

} // namespace QtVision
} // namespace VSN
