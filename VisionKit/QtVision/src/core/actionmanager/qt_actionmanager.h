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

#ifndef __QT_ACTIONMANAGER_H
#define __QT_ACTIONMANAGER_H

#include <qt_coreconstants.h>
#include <qt_icontext.h>
#include <qt_command.h>
//#include <qt_id.h>

#include <QObject>
#include <QList>

QT_BEGIN_NAMESPACE
class QAction;
class QString;
QT_END_NAMESPACE

namespace VSN {
namespace QtVision {

class ActionContainer;
class Command;
class Context;

namespace Internal {
class CorePlugin;
class MainWindow;
} // Internal


/* ActionManager */
class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* instance();
    static ActionContainer* createMenu(Id id);
    static ActionContainer* createMenuBar(Id id);

//    static ActionContainer *createTouchBar(Id id,
//                                           const QIcon &icon,
//                                           const QString &text = QString());

    static Command* registerAction(QAction* action, Id id,
                                   const Context& context = Context(Constants::C_GLOBAL),
                                   bool scriptable = false);

    static Command* command(Id id);
    static ActionContainer* actionContainer(Id id);

    static QList<Command*> commands();

    static void unregisterAction(QAction* action, Id id);

    static void setPresentationModeEnabled(bool enabled);
    static bool isPresentationModeEnabled();

    static QString withNumberAccelerator(const QString &text, const int number);
signals:
    void commandListChanged();
    void commandAdded(Id id);
private:
    ActionManager(QObject* parent = nullptr);
    ~ActionManager() override;
//    static void saveSettings();
    static void setContext(const Context& context);

    friend class Internal::CorePlugin; // initialization
    friend class Internal::MainWindow; // saving settings and setting context
    friend class QtMainWindow;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ACTIONCONTAINER_H */
