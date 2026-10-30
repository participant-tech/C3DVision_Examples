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

#ifndef __QT_COMMANDPRIVATE_H
#define __QT_COMMANDPRIVATE_H

#include <qt_command.h>
#include <qt_icontext.h>
#include <qt_proxyaction.h>
#include <qt_id.h>

#include <QList>
#include <QMultiMap>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QKeySequence>

#include <memory>

namespace VSN {
namespace QtVision {


/* CommandPrivate */
class CommandPrivate : public QObject
{
    Q_OBJECT
public:
    CommandPrivate(Command* parent);
public:
    void setCurrentContext(const Context& context);

    void addOverrideAction(QAction* action, const Context& context, bool scriptable);
    void removeOverrideAction(QAction *action);
    bool isEmpty() const;

    void updateActiveState();
    void setActive(bool state);

    Command* m_q = nullptr;
    Context m_context;
    Command::CommandAttributes m_attributes;
    Id m_id;
    QList<QKeySequence> m_defaultKeys;
    QString m_defaultText;
    QString m_touchBarText;
    QIcon m_touchBarIcon;
    bool m_isKeyInitialized = false;

    ProxyAction* m_action = nullptr;
    mutable std::unique_ptr<ProxyAction> m_touchBarAction;
    QString m_toolTip;

    QMap<Id, QPointer<QAction> > m_contextActionMap;
    QMap<QAction*, bool> m_scriptableMap;
    bool m_active = false;
    bool m_contextInitialized = false;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_COMMANDPRIVATE_H */
