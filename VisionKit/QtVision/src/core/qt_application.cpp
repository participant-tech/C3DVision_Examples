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

#include <qt_application.h>
#include <qt_openglwidget.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* QtMainWindow */
QtApplication::QtApplication(int& argc, char** argv, int flags)
    : QApplication(argc, argv, flags)
{
    setOrganizationName("C3DLabs");
}

//-----------------------------------------------------------------------------
// 
// ---
QtApplication::~QtApplication()
{
}

//-----------------------------------------------------------------------------
// 
// ---
QSharedPointer<QApplication> QtApplication::createApplication(int& argc, char** argv, const QString& appName)
{
#if defined(WIN32) /*&& defined(HUNT_FOR_MEM_LEAKS)*/
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QSharedPointer<QApplication> app(new QtApplication(argc, argv));
    app->setApplicationName(appName);
    if (!QtVision::activateLicense())
        return nullptr;

//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    app->setAttribute(Qt::AA_UseHighDpiPixmaps);
//    app->setAttribute(Qt::AA_DisableWindowContextHelpButton);
//#endif
    return app;
}

} // namespace QtVision
} // namespace VSN
