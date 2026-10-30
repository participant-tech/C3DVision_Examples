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

#include <qt_icore.h>
#include <qt_mainwindow.h>
#include <qt_processmanager.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

// The Core Singleton
static ICore*        m_instance   = nullptr;
static QtMainWindow* m_mainwindow = nullptr;
static PrManagerContainer* m_processContainer = nullptr;

/* ICore */
ICore::ICore(QtMainWindow* mainWindow)
{
    m_instance = this;
    m_mainwindow = mainWindow;
    m_processContainer = new PrManagerContainer();
}

//-----------------------------------------------------------------------------
// 
// ---
ICore::~ICore()
{
    m_instance = nullptr;
    m_mainwindow = nullptr;
    delete m_processContainer;
    m_processContainer = nullptr;
}

//-----------------------------------------------------------------------------
// Returns the pointer to the instance. Only use for connecting to signals.
// ---
ICore* ICore::instance() { return m_instance; }

//-----------------------------------------------------------------------------
// Returns the main window of the application.
// For dialog parents use dialogParent().
// Also needed for other purposes
// ---
QtMainWindow* ICore::mainWindow() { return m_mainwindow; }
PrManagerContainer* ICore::processContainer() { return m_processContainer; }

//-----------------------------------------------------------------------------
// Returns a widget pointer suitable to use as parent for QDialogs.
// ---
QWidget* ICore::dialogParent() 
{
    QWidget* active = QApplication::activeModalWidget();
    if (active == nullptr)
        active = QApplication::activeWindow();
    if (active == nullptr || (active && active->windowFlags().testFlag(Qt::SplashScreen)))
        active = m_mainwindow;
    return active;
}

static QSettings* set = nullptr;

QSettings* ICore::settings(QSettings::Scope /*scope*/)
{
    if (set == nullptr)
        set = new QSettings;

    Q_ASSERT(false);
    return set;
    /*
    if (scope == QSettings::UserScope)
        return PluginManager::settings();
    else
        return PluginManager::globalSettings();
*/
}


} // namespace QtVision
} // namespace VSN
