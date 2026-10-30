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

#include <qt_propbrowserwidget.h>

#include <QPainter>
#include <QScrollBar>
#include <QStyleOption>


#include <qt_groupboxpropertybrowser.h>
#include <qt_treepropertybrowser.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

#define TEST_PREVIEW 0

class HolderPreviewWidget : public QWidget
{
public:
    HolderPreviewWidget(QWidget* parent = nullptr)
        : QWidget(parent)
        , m_vMainLayout(new QVBoxLayout(this))
        , m_widget(nullptr)
    {
        m_vMainLayout->setContentsMargins(16, 16, 16, 16); // setMargin(16);
    }

    QWidget* widget() { return m_widget; }

    void setWidget(QWidget* widget)
    {
        if (widget || m_widget != widget)
            VSN_DELETE_AND_NULL(m_widget);

        m_widget = widget;

        if (m_widget)
            m_vMainLayout->addWidget(m_widget);
        setVisible(m_widget);
    }
protected:
#if TEST_PREVIEW > 0
    void paintEvent(QPaintEvent* event) override
    {
        Q_UNUSED(event);
        QPainter p(this);
        QStyleOption opt;
        opt.initFrom(this);
        p.fillRect(opt.rect, QColor(255, 0, 0));
    }
#endif // TEST_PREVIEW
private:
    QVBoxLayout* m_vMainLayout;
    QWidget* m_widget;
};

/* QtPropBrowserWidget */
QtPropBrowserWidget::QtPropBrowserWidget(QWidget* parent)
    : QWidget(parent)
    , m_vMainLayout(nullptr)
    , m_vLayout(nullptr)
    , m_mainHolderWidget(new QWidget())
    , m_holderWidget(new HolderPreviewWidget)
    , m_toolBar(new QToolBar())
    , m_splitter(new QSplitter(this))
    , m_propsBrowser(nullptr)
    , m_propertyManager(nullptr)
    , m_propertyEditorFactory(nullptr)
    , m_bGroupBox(true)
{
    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0); // setMargin(0);


    m_vLayout = new QVBoxLayout(m_mainHolderWidget);
    m_vLayout->setContentsMargins(2, 2, 2, 2); // setMargin(2);
    m_vMainLayout->addWidget(m_mainHolderWidget);

    createActions();
    //    m_toolBar->setIconSize(QSize(32, 32));
    m_toolBar->addAction(m_actionRepSwitcher);
    m_vLayout->addWidget(m_toolBar);
    createPropertiesBrowser();
    createPreviewHolder();
}

// ---
QtPropBrowserWidget::~QtPropBrowserWidget() {}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::addProperty(VarProperty* prop)
{
    if (m_propsBrowser != nullptr)
        m_propsBrowser->addProperty(prop);
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::addUserAction(QAction* action)
{
    toolBar()->insertAction(m_actionRepSwitcher, action);
}

// Returns a pointer to preview
QWidget* QtPropBrowserWidget::previewWidget() const { return ((HolderPreviewWidget*)m_holderWidget)->widget(); }

// Initialize preview widget
void QtPropBrowserWidget::setPreviewWidget(QWidget* widget) { ((HolderPreviewWidget*)m_holderWidget)->setWidget(widget); }

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::setRresentationProps(bool checked)
{
    if (m_bGroupBox == checked)
        return;

    m_bGroupBox = checked;
    QList<Property*> lstProp = m_propsBrowser->properties();
    if (m_bGroupBox)
    {
        m_vLayout->removeWidget(m_propsBrowser);
        delete m_propsBrowser;
        m_propsBrowser = new GroupBoxPropBrowser(this);
    }
    else
    {
        m_vLayout->removeWidget(m_propsBrowser);
        delete m_propsBrowser;
        m_propsBrowser = new TreePropBrowser(this);
        ((TreePropBrowser*)m_propsBrowser)->setRootIsDecorated(false);
        ((TreePropBrowser*)m_propsBrowser)->setPropertiesWithoutValueMarked(true);
        ((TreePropBrowser*)m_propsBrowser)->setResizeMode(TreePropBrowser::Interactive);
    }
    m_propsBrowser->unsetFactoryForManager(m_propertyManager);
    m_propsBrowser->setFactoryForManager(m_propertyManager, m_propertyEditorFactory);
    QObject::connect(m_propertyManager, &AbsPropertyManager::propertyChanged, this, &QtPropBrowserWidget::propChanged);
    setFocusProxy(m_propsBrowser);

    for (Property* prop : lstProp)
        m_propsBrowser->addProperty(prop);
    m_vLayout->addWidget(m_propsBrowser);
    emit propRepChanged(m_bGroupBox);
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::readSettings(QSettings& settings)
{
    bool bGroupBox = settings.value("property", m_bGroupBox).toBool();
    setRresentationProps(bGroupBox);
    if (m_splitter != nullptr)
    {
        QByteArray splitter_data = settings.value("splitter", QByteArray()).toByteArray();
        m_splitter->restoreState(splitter_data);
    }
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::writeSettings(QSettings& settings)
{
    settings.setValue("property", m_bGroupBox);
    if (m_splitter != nullptr)
    {
        QByteArray layout_data = m_splitter->saveState();
        settings.setValue("splitter", layout_data);
    }
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::createActions()
{
    m_actionRepSwitcher = new QAction(QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/propgroup_48x.png")),
        QString("Group display mode"), this);
    m_actionRepSwitcher->setCheckable(true);
    m_actionRepSwitcher->setChecked(m_bGroupBox);
    QObject::connect(m_actionRepSwitcher, &QAction::triggered, this, &QtPropBrowserWidget::setRresentationProps);
    QObject::connect(this, &QtPropBrowserWidget::propRepChanged, m_actionRepSwitcher, &QAction::setChecked);
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::createPropertiesBrowser()
{
    m_propsBrowser = new GroupBoxPropBrowser();
    setFocusProxy(m_propsBrowser);

    m_vLayout->addWidget(m_propsBrowser);
    m_propertyManager = new VarPropManager(this);
    m_propertyEditorFactory = new VariantEditorFactory(this);
    m_propsBrowser->setFactoryForManager(m_propertyManager, m_propertyEditorFactory);
    QObject::connect(m_propertyManager, &AbsPropertyManager::propertyChanged, this, &QtPropBrowserWidget::propChanged);
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::createPreviewHolder()
{
    m_vMainLayout->addWidget(m_splitter);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_mainHolderWidget);
    m_splitter->addWidget(m_holderWidget);
    // set the size of the panels. 30% is the default for preview,
    // the rest will be taken by the properties panel
    QList<int> splitterSizes;
    int height = size().height();
    int placeSize = height - (height * 30) / 100;
    splitterSizes.append(placeSize);
    splitterSizes.append((height - placeSize));
    m_splitter->setSizes(splitterSizes);
    m_holderWidget->setVisible(false);
}

// ----------------------------------------------------------------------------
//
// ---
void QtPropBrowserWidget::resizeEvent(QResizeEvent* event) { QWidget::resizeEvent(event); }


} // namespace QtVision
} // namespace VSN
