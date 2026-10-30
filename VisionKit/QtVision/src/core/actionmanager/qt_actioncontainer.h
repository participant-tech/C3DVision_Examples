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

#ifndef __QT_ACTIONCONTAINER_H
#define __QT_ACTIONCONTAINER_H

#include <qt_icontext.h>
#include <QObject>

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
class QAction;
QT_END_NAMESPACE


namespace VSN {
namespace QtVision {

class Command;

class ActionContainer : public QObject
{
    Q_OBJECT
public:
    enum OnAllDisabledBehavior {
        Disable,
        Hide,
        Show
    };

    virtual void setOnAllDisabledBehavior(OnAllDisabledBehavior behavior) = 0;
    virtual ActionContainer::OnAllDisabledBehavior onAllDisabledBehavior() const = 0;

    virtual Id id() const = 0;

    virtual QMenu* menu() const = 0;
    virtual QMenuBar* menuBar() const = 0;
//    virtual Utils::TouchBar *touchBar() const = 0;
    virtual QAction* insertLocation(Id group) const = 0;
    virtual void appendGroup(Id group) = 0;
    virtual void insertGroup(Id before, Id group) = 0;
    virtual void addAction(Command *action, Id group = {}) = 0;
    virtual void addMenu(ActionContainer *menu, Id group = {}) = 0;
    virtual void addMenu(ActionContainer *before, ActionContainer *menu) = 0;
    Command *addSeparator(Id group = {});
    virtual Command *addSeparator(const Context &context, Id group = {}, QAction **outSeparator = nullptr) = 0;
    // This clears this menu and submenus from all actions and submenus.
    // It does not destroy the submenus and commands, just removes them from their parents.
    virtual void clear() = 0;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ACTIONCONTAINER_H */
