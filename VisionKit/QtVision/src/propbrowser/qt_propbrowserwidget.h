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
#ifndef __QT_PROPBROWSERWIDGET_H
#define __QT_PROPBROWSERWIDGET_H

#include <QSettings>
#include <QSplitter>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>


#include <qt_global.h>
#include <qt_variantproperty.h>

namespace VSN {
namespace QtVision {

class AbsPropBrowser;
class VarPropManager;

/* QtPropBrowserWidget */
class QT_CLASS QtPropBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    QtPropBrowserWidget(QWidget* parent = nullptr);
    ~QtPropBrowserWidget() override;
public:
    // Returns pointer to toolbar
    QToolBar* toolBar() const { return m_toolBar; }

    // Returns a pointer to the property manager
    VarPropManager* propertyManager() const { return m_propertyManager; }

    // Add new property
    void addProperty(VarProperty* prop);
    // Add new user action before existing actions
    void addUserAction(QAction*);

    // Returns true if DropBox view is enabled
    bool isGropBoxProp() const { return m_bGroupBox; }

    // Returns a pointer to preview
    QWidget* previewWidget() const;
    // Initialize preview widget
    void setPreviewWidget(QWidget* widget);
public Q_SLOTS:
    void setRresentationProps(bool checked = false);
Q_SIGNALS:
    void propChanged(Property* property);
    void propRepChanged(bool check);
public:
    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
private:
    void createActions();
    void createPropertiesBrowser();
    void createPreviewHolder();
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QVBoxLayout* m_vMainLayout;
    QVBoxLayout* m_vLayout;
    QWidget* m_mainHolderWidget;
    QWidget* m_holderWidget;
    QToolBar* m_toolBar;
    QSplitter* m_splitter;
    AbsPropBrowser* m_propsBrowser;
    VarPropManager* m_propertyManager;
    VariantEditorFactory* m_propertyEditorFactory;
    QAction* m_actionRepSwitcher;
    bool m_bGroupBox;
private:
    Q_DISABLE_COPY(QtPropBrowserWidget)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROPBROWSERWIDGET_H */
