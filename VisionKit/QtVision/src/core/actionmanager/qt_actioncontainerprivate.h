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

#ifndef __QT_ACTIONCONTAINERPRIVATE_H
#define __QT_ACTIONCONTAINERPRIVATE_H

#include <qt_actionmanagerprivate.h>

#include <qt_actioncontainer.h>
#include <qt_command.h>


namespace VSN {
namespace QtVision {

/* Group */
struct Group
{
    Group(Id id) : id(id) {}
    Id id;
    QList<QObject *> items; // Command * or ActionContainer *
};

/* ActionContainerPrivate */
class ActionContainerPrivate : public ActionContainer
{
    Q_OBJECT
public:
    ActionContainerPrivate(Id id);
    ~ActionContainerPrivate() override = default;
public:
    void setOnAllDisabledBehavior(OnAllDisabledBehavior behavior) override;
    ActionContainer::OnAllDisabledBehavior onAllDisabledBehavior() const override;

    QAction *insertLocation(Id groupId) const override;
    void appendGroup(Id id) override;
    void insertGroup(Id before, Id groupId) override;
    void addAction(Command *action, Id group = {}) override;
    void addMenu(ActionContainer *menu, Id group = {}) override;
    void addMenu(ActionContainer *before, ActionContainer *menu) override;
    Command *addSeparator(const Context &context, Id group = {}, QAction **outSeparator = nullptr) override;
    void clear() override;

    Id id() const override;

    QMenu *menu() const override;
    QMenuBar* menuBar() const override;
//    Utils::TouchBar *touchBar() const override;

    virtual QAction *containerAction() const = 0;
    virtual QAction *actionForItem(QObject *item) const;

    virtual void insertAction(QAction *before, Command *command) = 0;
    virtual void insertMenu(QAction *before, ActionContainer *container) = 0;

    virtual void removeAction(Command *command) = 0;
    virtual void removeMenu(ActionContainer *container) = 0;

    virtual bool updateInternal() = 0;

protected:
    static bool canAddAction(Command *action);
    bool canAddMenu(ActionContainer *menu) const;
    virtual bool canBeAddedToContainer(ActionContainerPrivate *container) const = 0;

    // groupId --> list of Command* and ActionContainer*
    QList<Group> m_groups;

private:
    void scheduleUpdate();
    void update();
    void itemDestroyed();

    QList<Group>::const_iterator findGroup(Id groupId) const;
    QAction *insertLocation(QList<Group>::const_iterator group) const;

    OnAllDisabledBehavior m_onAllDisabledBehavior;
    Id m_id;
    bool m_updateRequested;
};

/* MenuActionContainer */
class MenuActionContainer : public ActionContainerPrivate
{
    Q_OBJECT
public:
    explicit MenuActionContainer(Id id);
    ~MenuActionContainer() override;
public:
    QMenu *menu() const override;

    QAction *containerAction() const override;

    void insertAction(QAction *before, Command *command) override;
    void insertMenu(QAction *before, ActionContainer *container) override;

    void removeAction(Command *command) override;
    void removeMenu(ActionContainer *container) override;
protected:
    bool canBeAddedToContainer(ActionContainerPrivate *container) const override;
    bool updateInternal() override;

private:
    QPointer<QMenu> m_menu;
};

/* MenuBarActionContainer */
class MenuBarActionContainer : public ActionContainerPrivate
{
    Q_OBJECT
public:
    explicit MenuBarActionContainer(Id id);
    ~MenuBarActionContainer() override;
public:
    void setMenuBar(QMenuBar *menuBar);
    QMenuBar *menuBar() const override;

    QAction *containerAction() const override;

    void insertAction(QAction *before, Command *command) override;
    void insertMenu(QAction *before, ActionContainer *container) override;

    void removeAction(Command *command) override;
    void removeMenu(ActionContainer *container) override;
protected:
    bool canBeAddedToContainer(ActionContainerPrivate *container) const override;
    bool updateInternal() override;
private:
    QMenuBar *m_menuBar;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ACTIONCONTAINERPRIVATE_H */
