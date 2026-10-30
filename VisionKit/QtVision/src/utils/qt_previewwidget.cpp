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

#include <qt_previewwidget.h>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QIcon>
#include <QStyleOption>
#include <qt_mainwindow.h>
#include <qt_icore.h>
#include <qt_theme.h>
#include <QResizeEvent>
#include <vsn_last.h>


namespace VSN {
namespace QtVision {

/// create vision image from Qimage
static Image convertToImage(QImage&& image)
{
    /// convert to vision image
    Image::Format format = Image::Format::UINT32;
    image = image.convertToFormat(QImage::Format_RGBA8888);
    image = image.mirrored();
    image = image.rgbSwapped();

    Image result;
    result.Init(image.width(), image.height(), format, (const unsigned char*)image.bits());
    return result;
}

/* MaterialPreviewWidget */
MaterialPreviewWidget::MaterialPreviewWidget(QWidget* parent)
    : QtOpenGLSceneWidget(parent)
    , m_material(Material::GetDefaultMaterial())
    , m_segment(new SceneSegment(GeometryFactory::Instance()->CreateSphere(1.5f, 15.0f)))
{
}

// --------------------------------------------------------------------------------------
// 
// ---
void MaterialPreviewWidget::initializeGL()
{
    QtOpenGLSceneWidget::initializeGL();
    graphicsView()->GetOrientationMarker()->SetVisible(false);

    updateBackground();
/*
    viewport()->GetCamera()->SetPosition({ 0.0f, 0.0f, 500.0f });
    mainLight()->SetPosition(100.0f, 100.0f, 100.0f);
    mainLight()->SetDoubleSided(false);
*/
    mainLight()->SetDoubleSided(false);

    Light* pLight = graphicsScene()->CreateExtraLight();
    pLight->SetType(Light::DirectionLight);
    pLight->SetPosition(-8.0f, -2.0f, -4.0f);
    pLight->SetDiffuseColor(Color(0.2f, 0.2f, 0.2f, 1.0f));
    pLight->SetDoubleSided(false);

    SceneSegment* pTopSegment = sceneContent()->GetRootSegment();
    Q_ASSERT(pTopSegment != nullptr);
    pTopSegment->AddSegment(m_segment);
    viewport()->ZoomToFit(sceneContent()->GetBoundingBox(),1.8f);
    updateMaterial();
}

// --------------------------------------------------------------------------------------
// 
// ---
void MaterialPreviewWidget::updateMaterial()
{
    if (m_segment == nullptr)
        return;
    for (auto it : m_segment->GetRepresentation()->GetGeomList())
    {
        MeshGeometry* pGeometry = static_cast<MeshGeometry*>(it);
        VSN_ASSERT(pGeometry != nullptr);
        if (Material* pMaterialGeom = pGeometry->GetHeadMaterial())
        {
            pMaterialGeom->CopyFrom(m_material);
            update();
            break;
        }
    }
}

// --------------------------------------------------------------------------------------
// 
// ---
void MaterialPreviewWidget::setMaterial(const Material* material)
{
    setEnabled(material);

    if (material == nullptr)
        return;
    if (m_material == *material)
        return;
    m_material.CopyFrom(*material);
    updateMaterial();
    viewport()->ZoomToFit(sceneContent()->GetBoundingBox(), 1.8f);

    emit materialChanged(m_material);
}

// ---
void MaterialPreviewWidget::updateBackground()
{
    ThemeId id = ICore::mainWindow()->idStyleTeme();
    viewport()->LoadBackgroundImage(convertToImage(id == Default ? 
        QImage(":/res/dummy_light.png") : QImage(":/res/dummy_dark.png")));
}

// ---
bool MaterialPreviewWidget::event(QEvent* event)
{
    if (event->type() == QEvent::StyleChange)
    {
        updateBackground();
    }
    else if (event->type() == QEvent::EnabledChange)
    {
        bool bIsEnabled = isEnabled();
        m_segment->SetVisible(bIsEnabled);
    }
    return QWidget::event(event);
}

} // namespace QtVision
} // namespace VSN
