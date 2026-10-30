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
#ifndef __QT_ICORE_H
#define __QT_ICORE_H

#include <QObject>
#include <QSettings>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class QtMainWindow;
class PrManagerContainer;

/* ICore */
class QT_CLASS ICore : public QObject
{
    Q_OBJECT
public:
    explicit ICore(QtMainWindow* mainWindow);
    ~ICore() override;
public:
    static ICore* instance();
    static QtMainWindow* mainWindow();
    static PrManagerContainer* processContainer();
    static QWidget* dialogParent();
    static QSettings* settings(QSettings::Scope scope = QSettings::UserScope);
public:
//    static void saveSettings(SaveSettingsReason reason);
private:
    Q_DISABLE_COPY(ICore)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ICORE_H */
