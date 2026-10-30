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

///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_MATERIALPROPS_H
#define __QT_MATERIALPROPS_H

#include <QObject>
#include <vsn_material.h>
#include <qt_variantproperty.h>
#include <qt_propertymanager.h>
#include <qt_propbrowserwidget.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

const char ID_PRIMARYCOLOR[] = "Material.PrimaryColor";
const char ID_AMBIENT[]      = "Material.Ambient";
const char ID_DIFFUSE[]      = "Material.Diffuse";
const char ID_SPECULARITY[]  = "Material.Specularity";
const char ID_SHININESS[]    = "Material.Shininess";
const char ID_TRANSPARENCY[] = "Material.Transparency";
const char ID_EMISSION[]     = "Material.Emission";


/* 
    MaterialPropManager: FontPropertyManager: A mixin for projects-examples that 
    manages material properties. Adds an material subproperty and set color 
    handling for the other subproperties.
*/
class QT_CLASS MaterialPropManager : public QObject
{
    Q_OBJECT
public:
    MaterialPropManager(QObject* parent = nullptr);
    ~MaterialPropManager();
public Q_SLOTS:
    // Set new material for editing
    void setMaterial(const Material* material);
    void setModified(bool isModified = true);
Q_SIGNALS:
    void applyMaterial(const Material& material);
    void materialChanged(const Material* material);
    void modificationChanged(bool m);
public:
    const Material* material() const { return &m_material; }
    // fill the material group with basic properties. PreviewWidget can be nullptr
    void createProperties(QtPropBrowserWidget* browserWidget);
protected:
    // update original components from the material sent
    void updateSourceComponents();
    // update parameter values ​​for source components
    void updateParamsValue();
protected Q_SLOTS:
    void slotPropertyChanged(QtVision::Property* property);
    void slotApplyMaterial();
private:
    QAction* m_actionApply;
    Color m_ambientColor;
    Color m_diffuseColor;
    Color m_specularColor;
    Color m_emissionColor;
    float m_shininess;
    float m_opacity;

    VarProperty* m_groupPropMaterial;
    VarProperty* m_propDiffuseColor;
    VarProperty* m_propAmbient;
    VarProperty* m_propDiffuse;
    VarProperty* m_propSpecular;
    VarProperty* m_propEmission;
    VarProperty* m_propShininess;
    VarProperty* m_propTransparency;

    Material m_material;
    bool m_bAvailable;
    bool m_isModified;
    bool m_update;
private:
    Q_DISABLE_COPY(MaterialPropManager);
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MATERIALPROPS_H */
