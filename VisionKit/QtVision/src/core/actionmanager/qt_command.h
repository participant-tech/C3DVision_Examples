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

#ifndef __QT_COMMAND_H
#define __QT_COMMAND_H

#include <QObject>
#include <qt_id.h>
#include <qt_hostosinfo.h>

QT_BEGIN_NAMESPACE
class QAction;
class QKeySequence;
class QToolButton;
QT_END_NAMESPACE


namespace VSN {
namespace QtVision {

class ActionManager;
class Context;
class CommandPrivate;

constexpr bool useMacShortcuts = HostOsInfo::isMacHost();

/* Command */
class Command : public QObject
{
    Q_OBJECT
public:
    enum CommandAttribute {
        CA_Hide = 1,
        CA_UpdateText = 2,
        CA_UpdateIcon = 4,
        CA_NonConfigurable = 8
    };
    Q_DECLARE_FLAGS(CommandAttributes, CommandAttribute)
    ~Command();
public:
    void setDefaultKeySequence(const QKeySequence& key);
    void setDefaultKeySequences(const QList<QKeySequence> &keys);
    QList<QKeySequence> defaultKeySequences() const;
    QList<QKeySequence> keySequences() const;
    QKeySequence keySequence() const;
    // explicitly set the description (used e.g. in shortcut settings)
    // default is to use the action text for actions, or the whatsThis for shortcuts,
    // or, as a last fall back if these are empty, the command ID string
    // override the default e.g. if the text is context dependent and contains file names etc
    void setDescription(const QString &text);
    QString description() const;

    Id id() const;

    QAction* action() const;
    Context context() const;

    void setAttribute(CommandAttribute attr);
    void removeAttribute(CommandAttribute attr);
    bool hasAttribute(CommandAttribute attr) const;

    bool isActive() const;

    void setKeySequences(const QList<QKeySequence> &keys);
    QString stringWithAppendedShortcut(const QString &str) const;
    void augmentActionWithShortcutToolTip(QAction *action) const;
    static QToolButton* toolButtonWithAppendedShortcut(QAction* action, Command* cmd);

    bool isScriptable() const;
    bool isScriptable(const Context &) const;

    void setTouchBarText(const QString &text);
    QString touchBarText() const;
    void setTouchBarIcon(const QIcon &icon);
    QIcon touchBarIcon() const;
    QAction* touchBarAction() const;
signals:
    void keySequenceChanged();
    void activeStateChanged();
private:
    friend class ActionManager;
    friend class ActionManagerPrivate;

    Command(Id id);

    CommandPrivate *d;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_COMMAND_H */

//Q_DECLARE_OPERATORS_FOR_FLAGS(Command::CommandAttributes)
