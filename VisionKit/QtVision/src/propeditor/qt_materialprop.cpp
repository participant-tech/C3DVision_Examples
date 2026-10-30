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

#include <qt_materialprop.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

// ---
static Color convertToColor(const Color& color, float value)
{
    if (value < 0.f || value > 1.f)
        return Color(0.f, 0.f, 0.f);

    Color clr = color;
    int h1, s1, v1;
    clr.GetHsv(&h1, &s1, &v1);

    int valHsv = (255 * static_cast<int>(value * 100.f)) / 100;
    clr.SetHsv(h1, s1, valHsv);

    return clr;
}

// ---
static float convertToFloat(const Color& color)
{
    if (!color.IsValid())
        return 0.f;
    int h1, s1, v1;
    color.GetHsv(&h1, &s1, &v1);
    return ((float(v1) * 100.f) / 255) / 100.f;
}


/* MaterialPropManager */
MaterialPropManager::MaterialPropManager(QObject* parent)
    : QObject(parent)
    , m_actionApply(nullptr)
    , m_groupPropMaterial(nullptr)
    , m_propAmbient(nullptr)
    , m_propDiffuse(nullptr)
    , m_propSpecular(nullptr)
    , m_propEmission(nullptr)
    , m_propShininess(nullptr)
    , m_propTransparency(nullptr)
    , m_material(Material::GetDefaultMaterial())
    , m_bAvailable(false)
    , m_isModified(false)
    , m_update(false)
{
    const QIcon openIcon = QIcon::fromTheme("materialEditor-Apply", QIcon(":/res/apply_48.png"));
    m_actionApply = new QAction(openIcon, tr("Apply..."), this);
    m_actionApply->setToolTip(tr("Apply selected material..."));
    m_actionApply->setEnabled(m_isModified);
    QObject::connect(this, &MaterialPropManager::modificationChanged, m_actionApply, &QAction::setEnabled);
    QObject::connect(m_actionApply, &QAction::triggered, this, &MaterialPropManager::slotApplyMaterial);
}

// --------------------------------------------------------------------------------------
// 
// ---
MaterialPropManager::~MaterialPropManager()
{
}

// --------------------------------------------------------------------------------------
// Set new material for editing
// ---
void MaterialPropManager::setMaterial(const Material* material)
{
    m_bAvailable = material != nullptr;
    if (m_bAvailable)
        m_material.CopyFrom(*material);

    m_update = false;
    updateSourceComponents();
    updateParamsValue();
    m_update = true;

    setModified(false);
    emit materialChanged(m_bAvailable ? &m_material : nullptr);
}

// --------------------------------------------------------------------------------------
//
// ---
void MaterialPropManager::setModified(bool isModified)
{
    if (isModified == m_isModified)
        return;
    m_isModified = isModified;
    emit modificationChanged(m_isModified);
}

// --------------------------------------------------------------------------------------
// fill the material group with basic properties
// ---
void MaterialPropManager::createProperties(QtPropBrowserWidget* browserWidget)
{
    QList<QAction*> list = browserWidget->toolBar()->actions();
    // TODO For now we'll add actions, so in the next version 
    // we'll come up with a better algorithm
    QAction* actionSeparator = new QAction(this);
    actionSeparator->setSeparator(true);
    list.insert(0, m_actionApply);
    list.insert(1, actionSeparator);
    browserWidget->toolBar()->clear();
    browserWidget->toolBar()->addActions(list);

    QObject::connect(this, SIGNAL(materialChanged(const Material*)),
        browserWidget->previewWidget(), SLOT(setMaterial(const Material*)));

    VarPropManager* propManager = browserWidget->propertyManager();
    Q_ASSERT(propManager != nullptr);
    m_groupPropMaterial = propManager->addProperty(VarPropManager::groupTypeId(), QObject::tr("Material"));
    // color
    m_propDiffuseColor = propManager->addProperty(QVariant::Color, QObject::tr("Primary color"), ID_PRIMARYCOLOR);
    m_propDiffuseColor->removeSubProperty(ID_COLOR_ALPHA);
    m_groupPropMaterial->addSubProperty(m_propDiffuseColor);
    // 1
    m_propAmbient = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Ambient:"), ID_AMBIENT);
    m_propAmbient->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propAmbient->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propAmbient->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propAmbient);
    // 2
    m_propDiffuse = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Diffuse:"), ID_DIFFUSE);
    m_propDiffuse->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propDiffuse->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propDiffuse->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propDiffuse);
    // 3
    m_propSpecular = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Specularity:"), ID_SPECULARITY);
    m_propSpecular->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propSpecular->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propSpecular->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propSpecular);
    // 4
    m_propEmission = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Emission:"), ID_EMISSION);
    m_propEmission->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propEmission->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propEmission->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propEmission);
    // 5
    m_propShininess = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Shininess:"), ID_SHININESS);
    m_propShininess->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propShininess->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propShininess->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propShininess);
    // 6
    m_propTransparency = propManager->addProperty(VarPropManager::sliderTypeId(), QObject::tr("Transparency:"), ID_TRANSPARENCY);
    m_propTransparency->setAttribute(QLatin1String("minimum"), QVariant(0));
    m_propTransparency->setAttribute(QLatin1String("maximum"), QVariant(100));
    m_propTransparency->setAttribute(QLatin1String("singleStep"), QVariant(1));
    m_groupPropMaterial->addSubProperty(m_propTransparency);

    browserWidget->addProperty(m_groupPropMaterial);
    updateParamsValue();

    if (browserWidget->previewWidget() != nullptr)
        QObject::connect(this, SIGNAL(materialChanged(const Material*)), 
            browserWidget->previewWidget(), SLOT(setMaterial(const Material*)));

    QObject::connect(browserWidget, &QtPropBrowserWidget::propChanged, this, &MaterialPropManager::slotPropertyChanged);
    emit materialChanged(m_bAvailable ? &m_material : nullptr);
}

//-----------------------------------------------------------------------------
// update original components from the material sent
// ---
void MaterialPropManager::updateSourceComponents()
{
    if (m_bAvailable)
    {
        m_ambientColor  = m_material.GetAmbient();
        m_diffuseColor  = m_material.GetDiffuse();
        m_specularColor = m_material.GetSpecular();
        m_emissionColor = m_material.GetEmission();
        m_shininess     = m_material.GetShininess();
        m_opacity       = m_material.GetOpacity();
    }
    else
    {
        m_ambientColor  = Color();
        m_diffuseColor  = Color();
        m_specularColor = Color();
        m_emissionColor = Color();
        m_shininess     = 0.f;
        m_opacity       = 1.f;
    }
}

//-----------------------------------------------------------------------------
// update parameter values ​​for source components
// ---
void MaterialPropManager::updateParamsValue()
{
    if (m_bAvailable)
    {
        m_propDiffuseColor->setValue(QColor(m_diffuseColor.GetRed(), m_diffuseColor.GetGreen(),
            m_diffuseColor.GetBlue(), m_diffuseColor.GetAlpha()));
        m_propAmbient->setValue(convertToFloat(m_ambientColor) * 100.f);
        m_propDiffuse->setValue(convertToFloat(m_diffuseColor) * 100.f);
        m_propSpecular->setValue(convertToFloat(m_specularColor) * 100.f);
        m_propEmission->setValue(convertToFloat(m_emissionColor) * 100.f);
        m_propShininess->setValue(m_shininess);
        m_propTransparency->setValue(100.f - (m_opacity * 100.f));
    }
    else
    {
        m_propDiffuseColor->setValue(QColor());
        m_propAmbient->setValue(0);
        m_propDiffuse->setValue(0);
        m_propSpecular->setValue(0);
        m_propEmission->setValue(0);
        m_propShininess->setValue(0);
        m_propTransparency->setValue(0);
    }
    m_groupPropMaterial->setEnabled(m_bAvailable);
}

//-----------------------------------------------------------------------------
//
// ---
void MaterialPropManager::slotPropertyChanged(QtVision::Property* property)
{
    if (property == nullptr || !m_update)
        return;

    Material material = m_material;

    QtVision::VarProperty* vProperty = ((QtVision::VarProperty*)property);

    if (property->propertyId() == ID_PRIMARYCOLOR)
    {
        QColor color = vProperty->value().value<QColor>();
        if (color.isValid())
        {
            material.SetDiffuse({ color.red(), color.green(), color.blue(), color.alpha() });
            m_diffuseColor = material.GetDiffuse();

            m_update = false;
            m_propDiffuse->setValue(convertToFloat(m_diffuseColor) * 100.f);
            m_update = true;
        }
    }
    else if (property->propertyId() == ID_AMBIENT)
    {
        int val = vProperty->value().toInt();
        material.SetAmbient(convertToColor(m_ambientColor, static_cast<float>(val) / 100.0f));
    }
    else if (property->propertyId() == ID_DIFFUSE)
    {
        int val = vProperty->value().toInt();
        material.SetDiffuse(convertToColor(m_diffuseColor, static_cast<float>(val) / 100.0f));

        m_update = false;
        Color diffuseColor = material.GetDiffuse();
        m_propDiffuseColor->setValue(QColor(diffuseColor.GetRed(), diffuseColor.GetGreen(),
            diffuseColor.GetBlue(), diffuseColor.GetAlpha()));
        m_update = true;
    }
    else if (property->propertyId() == ID_SPECULARITY)
    {
        int val = vProperty->value().toInt();
        material.SetSpecular(convertToColor(m_specularColor, static_cast<float>(val) / 100.0f));
    }
    else if (property->propertyId() == ID_EMISSION)
    {
        int val = vProperty->value().toInt();
        material.SetEmission(convertToColor(m_emissionColor, static_cast<float>(val) / 100.0f));
    }
    else if (property->propertyId() == ID_SHININESS)
    {
        int val = vProperty->value().toInt();
        material.SetShininess((static_cast<float>(val) * 128.0f) / 100.0f);
    }
    else if (property->propertyId() == ID_TRANSPARENCY)
    {
        int val = vProperty->value().toInt();
        material.SetOpacity(((1.0f - (static_cast<float>(val)) / 100.0f)));
    }

    if (!(material == m_material) && m_bAvailable)
    {
        m_material.CopyFrom(material);
        setModified(true);
        emit materialChanged(&m_material);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void MaterialPropManager::slotApplyMaterial()
{ emit applyMaterial(m_material); }

} // namespace QtVision
} // namespace VSN
