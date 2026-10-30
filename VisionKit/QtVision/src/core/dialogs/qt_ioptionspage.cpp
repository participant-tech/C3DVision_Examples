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

#include <qt_ioptionspage.h>

#include <qt_icore.h>

#include <qt_aspects.h>
#include <qt_stringutils.h>

#include <QCheckBox>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QRegularExpression>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/*
    The IOptionsPage class is an interface for providing pages for the
    uicontrol Options dialog (called uicontrol Preferences on macos).

    Id Core::IOptionsPage::id() const
    Returns a unique identifier for referencing the options page.

    QString Core::IOptionsPage::displayName() const
    Returns the translated display name of the options page.

    Id Core::IOptionsPage::category() const

    Returns the unique id for the category that the options page should be displayed in. This id is
    used for sorting the list on the left side of the \uicontrol Options dialog.

    QString Core::IOptionsPage::displayCategory() const

    Returns the translated category name of the options page. This name is displayed in the list on
    the left side of the uicontrol Options dialog.
*/

// --------------------------------------------------------------------------------------
// Returns the category icon of the options page.This icon is displayed in the list on the left
// side of the \uicontrol Options dialog.
// ---
QIcon IOptionsPage::categoryIcon() const
{
    return m_categoryIcon.icon();
}

// --------------------------------------------------------------------------------------
// Sets the widgetCreator callback to create page widgets on demand.The
// widget will be destroyed on finish().
// ---
void IOptionsPage::setWidgetCreator(const WidgetCreator &widgetCreator)
{
    m_widgetCreator = widgetCreator;
}

// --------------------------------------------------------------------------------------
// Returns the widget to show in the uicontrol Options dialog.You should create a widget lazily here,
// and delete it again in the finish() method. This method can be called multiple times, so you
// should only create a new widget if the old one was deleted.

// Alternatively, use setWidgetCreator() to set a callback function that is used to
// lazily create a widget in time.

// Either override this function in a derived class, or set a widget creator.
// ---
QWidget* IOptionsPage::widget()
{
    if (!m_widget) 
    {
        if (m_widgetCreator) 
        {
            m_widget = m_widgetCreator();
        } 
        else if (m_layouter) 
        {
            m_widget = new QWidget;
            m_layouter(m_widget);
        } 
        else 
        {
            QTV_CHECK(false);
        }
    }
    return m_widget;
}

// --------------------------------------------------------------------------------------
// Called when selecting the uicontrol Apply button on the options page dialog.
// Should detect whether any changes were made and store those.
// Either override this function in a derived class, or set a widget creator.
// ---
void IOptionsPage::apply()
{
    if (auto widget = qobject_cast<IOptionsPageWidget *>(m_widget)) 
    {
        widget->apply();
    } 
    else if (m_settings) 
    {
        if (m_settings->isDirty()) 
        {
            m_settings->apply();
            m_settings->writeSettings(ICore::settings());
         }
    }
}

// --------------------------------------------------------------------------------------
// Called directly before the uicontrol Options dialog closes. Here you should
// delete the widget that was created in widget() to free resources.
// Either override this function in a derived class, or set a widget creator.
// ---
void IOptionsPage::finish()
{
    if (auto widget = qobject_cast<IOptionsPageWidget *>(m_widget))
        widget->finish();
    else if (m_settings)
        m_settings->finish();

    delete m_widget;
}

// --------------------------------------------------------------------------------------
// Sets categoryIconPath as the path to the category icon of the options page.
// ---
void IOptionsPage::setCategoryIconPath(const FilePath& categoryIconPath)
{
    m_categoryIcon = Icon({{categoryIconPath, Theme::PanelTextColorDark}}, Icon::Tint);
}

void IOptionsPage::setSettings(AspectContainer *settings)
{
    m_settings = settings;
}

void IOptionsPage::setLayouter(const std::function<void(QWidget *w)> &layouter)
{
    m_layouter = layouter;
}

/*
    Sets the id of the options page.

    void Core::IOptionsPage::setDisplayName(const QString& displayName)
    Sets displayName as the display name of the options page.

    void Core::IOptionsPage::setCategory(Id category)
    Uses category to sort the options pages.

    void Core::IOptionsPage::setDisplayCategory(const QString& displayCategory)
    Sets displayCategory as the display category of the options page.
*/

// --------------------------------------------------------------------------------------
// void Core::IOptionsPage::setCategoryIcon(const Icon& categoryIcon)
// Sets categoryIcon as the category icon of the options page.
// ---
static QList<IOptionsPage*> g_optionsPages;

// --------------------------------------------------------------------------------------
// Constructs an options page with the given parent and registers it
// at the global options page pool if registerGlobally is true.
// ---
IOptionsPage::IOptionsPage(QObject *parent, bool registerGlobally)
    : QObject(parent)
{
    if (registerGlobally)
        g_optionsPages.append(this);
}

IOptionsPage::~IOptionsPage()
{
    g_optionsPages.removeOne(this);
}

// --------------------------------------------------------------------------------------
// Returns a list of all options pages.
// ---
const QList<IOptionsPage*> IOptionsPage::allOptionsPages()
{
    return g_optionsPages;
}

// --------------------------------------------------------------------------------------
// Is used by the uicontrol Options dialog search filter to match regexp to this options
// page. This defaults to take the widget and then looks for all child labels, check boxes, push
// buttons, and group boxes. Should return true when a match is found.
// ---
bool IOptionsPage::matches(const QRegularExpression& regexp) const
{
    if (!m_keywordsInitialized) 
    {
        auto that = const_cast<IOptionsPage *>(this);
        QWidget *widget = that->widget();
        if (!widget)
            return false;
        // find common subwidgets
        for (const QLabel *label : widget->findChildren<QLabel *>())
            m_keywords << VSN::QtVision::stripAccelerator(label->text());
        for (const QCheckBox *checkbox : widget->findChildren<QCheckBox *>())
            m_keywords << VSN::QtVision::stripAccelerator(checkbox->text());
        for (const QPushButton *pushButton : widget->findChildren<QPushButton *>())
            m_keywords << VSN::QtVision::stripAccelerator(pushButton->text());
        for (const QGroupBox *groupBox : widget->findChildren<QGroupBox *>())
            m_keywords << VSN::QtVision::stripAccelerator(groupBox->title());

        m_keywordsInitialized = true;
    }
    for (const QString &keyword : qAsConst(m_keywords))
        if (keyword.contains(regexp))
            return true;
    return false;
}

static QList<IOptionsPageProvider *> g_optionsPagesProviders;

/* IOptionsPageProvider */
IOptionsPageProvider::IOptionsPageProvider(QObject *parent)
    : QObject(parent)
{
    g_optionsPagesProviders.append(this);
}

IOptionsPageProvider::~IOptionsPageProvider()
{
    g_optionsPagesProviders.removeOne(this);
}

const QList<IOptionsPageProvider *> IOptionsPageProvider::allOptionsPagesProviders()
{
    return g_optionsPagesProviders;
}

QIcon IOptionsPageProvider::categoryIcon() const
{
    return m_categoryIcon.icon();
}

} // namespace QtVision
} // namespace VSN
