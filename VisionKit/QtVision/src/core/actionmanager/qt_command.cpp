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

#include <qt_command.h>
#include <qt_commandprivate.h>
#include <qt_coreconstants.h>
#include <qt_stringutils.h>

#include <QAction>
#include <QToolButton>
#include <QTextStream>
#include <vsn_last.h>

using namespace Utils;

namespace VSN {
namespace QtVision {

Command::Command(Id id)
    : d(new CommandPrivate(this))
{
    d->m_id = id;
}

Command::~Command()
{
    delete d;
}

CommandPrivate::CommandPrivate(Command* parent)
    : m_q(parent)
    , m_attributes({})
    , m_action(new ProxyAction(this))
{
    m_action->setShortcutVisibleInToolTip(true);
    connect(m_action, &QAction::changed, this, &CommandPrivate::updateActiveState);
}

Id Command::id() const
{
    return d->m_id;
}

void Command::setDefaultKeySequence(const QKeySequence& key)
{
    if (!d->m_isKeyInitialized)
        setKeySequences({key});
    d->m_defaultKeys = {key};
}

void Command::setDefaultKeySequences(const QList<QKeySequence>& keys)
{
    if (!d->m_isKeyInitialized)
        setKeySequences(keys);
    d->m_defaultKeys = keys;
}

// ---
QList<QKeySequence> Command::defaultKeySequences() const
{
    return d->m_defaultKeys;
}

// ---
QAction* Command::action() const
{
    return d->m_action;
}

// ---
QString Command::stringWithAppendedShortcut(const QString& str) const
{
    return ProxyAction::stringWithAppendedShortcut(str, keySequence());
}

// ---
Context Command::context() const
{
    return d->m_context;
}

// ---
void Command::setKeySequences(const QList<QKeySequence>& keys)
{
    d->m_isKeyInitialized = true;
    d->m_action->setShortcuts(keys);
    emit keySequenceChanged();
}

// ---
QList<QKeySequence> Command::keySequences() const
{
    return d->m_action->shortcuts();
}

// ---
QKeySequence Command::keySequence() const
{
    return d->m_action->shortcut();
}

// ---
void Command::setDescription(const QString &text)
{
    d->m_defaultText = text;
}

// ---
QString Command::description() const
{
    if (!d->m_defaultText.isEmpty())
        return d->m_defaultText;
    if (QAction* act = action()) 
    {
        const QString text = stripAccelerator(act->text());
        if (!text.isEmpty())
            return text;
    }
    return id().toString();
}

// ---
void CommandPrivate::setCurrentContext(const Context& context)
{
    m_context = context;
    QAction* currentAction = nullptr;
    for (int i = 0; i < m_context.size(); ++i) 
    {
        if (QAction* a = m_contextActionMap.value(m_context.at(i), nullptr)) 
        {
            currentAction = a;
            break;
        }
    }

    m_action->setAction(currentAction);
    updateActiveState();
}

// ---
void CommandPrivate::updateActiveState()
{
    setActive(m_action->isEnabled() && m_action->isVisible() && !m_action->isSeparator());
}

static QString msgActionWarning(QAction *newAction, Id id, QAction *oldAction)
{
    QString msg;
    QTextStream str(&msg);
    str << "addOverrideAction " << newAction->objectName() << '/' << newAction->text()
         << ": Action ";
    if (oldAction)
        str << oldAction->objectName() << '/' << oldAction->text();
    str << " is already registered for context " << id.toString() << '.';
    return msg;
}

void CommandPrivate::addOverrideAction(QAction* action, const Context& context, bool scriptable)
{
    // disallow TextHeuristic menu role, because it doesn't work with translations
    if (action->menuRole() == QAction::TextHeuristicRole)
        action->setMenuRole(QAction::NoRole);
    if (isEmpty())
        m_action->initialize(action);
    if (context.isEmpty()) 
    {
        m_contextActionMap.insert(Constants::C_GLOBAL, action);
    } 
    else 
    {
        for (const Id& id : context) 
        {
            if (m_contextActionMap.contains(id))
                qWarning("%s", qPrintable(msgActionWarning(action, id, m_contextActionMap.value(id, nullptr))));
            m_contextActionMap.insert(id, action);
        }
    }
    m_scriptableMap[action] = scriptable;
    setCurrentContext(m_context);
}

void CommandPrivate::removeOverrideAction(QAction* action)
{
    QList<Id> toRemove;
    for (auto it = m_contextActionMap.cbegin(), end = m_contextActionMap.cend(); it != end; ++it) 
    {
        if (it.value() == nullptr || it.value() == action)
            toRemove.append(it.key());
    }
    for (Id id : toRemove)
        m_contextActionMap.remove(id);
    setCurrentContext(m_context);
}

bool Command::isActive() const
{
    return d->m_active;
}

void CommandPrivate::setActive(bool state)
{
    if (state != m_active) 
    {
        m_active = state;
        emit m_q->activeStateChanged();
    }
}

bool CommandPrivate::isEmpty() const
{
    return m_contextActionMap.isEmpty();
}

bool Command::isScriptable() const
{
    return std::find(d->m_scriptableMap.cbegin(), d->m_scriptableMap.cend(), true)
           != d->m_scriptableMap.cend();
}

bool Command::isScriptable(const Context& context) const
{
    if (context == d->m_context && d->m_scriptableMap.contains(d->m_action->action()))
        return d->m_scriptableMap.value(d->m_action->action());

    for (int i = 0; i < context.size(); ++i) 
    {
        if (QAction *a = d->m_contextActionMap.value(context.at(i), nullptr)) 
        {
            if (d->m_scriptableMap.contains(a) && d->m_scriptableMap.value(a))
                return true;
        }
    }
    return false;
}

void Command::setAttribute(CommandAttribute attr)
{
    d->m_attributes |= attr;
    switch (attr) 
    {
        case Command::CA_Hide:
            d->m_action->setAttribute(ProxyAction::Hide);
            break;
        case Command::CA_UpdateText:
            d->m_action->setAttribute(ProxyAction::UpdateText);
            break;
        case Command::CA_UpdateIcon:
            d->m_action->setAttribute(ProxyAction::UpdateIcon);
            break;
        case Command::CA_NonConfigurable:
            break;
    }
}

void Command::removeAttribute(CommandAttribute attr)
{
    d->m_attributes &= ~attr;
    switch (attr) {
    case Command::CA_Hide:
        d->m_action->removeAttribute(ProxyAction::Hide);
        break;
    case Command::CA_UpdateText:
        d->m_action->removeAttribute(ProxyAction::UpdateText);
        break;
    case Command::CA_UpdateIcon:
        d->m_action->removeAttribute(ProxyAction::UpdateIcon);
        break;
    case Command::CA_NonConfigurable:
        break;
    }
}

bool Command::hasAttribute(CommandAttribute attr) const
{
    return (d->m_attributes & attr);
}

void Command::setTouchBarText(const QString &text)
{
    d->m_touchBarText = text;
}

QString Command::touchBarText() const
{
    return d->m_touchBarText;
}

void Command::setTouchBarIcon(const QIcon &icon)
{
    d->m_touchBarIcon = icon;
}

QIcon Command::touchBarIcon() const
{
    return d->m_touchBarIcon;
}

QAction *Command::touchBarAction() const
{
    if (!d->m_touchBarAction) 
    {
        d->m_touchBarAction = std::make_unique<ProxyAction>();
        d->m_touchBarAction->initialize(d->m_action);
        d->m_touchBarAction->setIcon(d->m_touchBarIcon);
        d->m_touchBarAction->setText(d->m_touchBarText);
        // the touch bar action should be hidden if the command is not valid for the context
        d->m_touchBarAction->setAttribute(ProxyAction::Hide);
        d->m_touchBarAction->setAction(d->m_action->action());
        connect(d->m_action,
                &ProxyAction::currentActionChanged,
                d->m_touchBarAction.get(),
                &ProxyAction::setAction);
    }
    return d->m_touchBarAction.get();
}

/*!
    Appends the main keyboard shortcut that is currently assigned to the action
    a to its tool tip.
*/
void Command::augmentActionWithShortcutToolTip(QAction* a) const
{
    a->setToolTip(stringWithAppendedShortcut(a->text()));
    QObject::connect(this, &Command::keySequenceChanged, a, [this, a]() 
        {
            a->setToolTip(stringWithAppendedShortcut(a->text()));
        });
    QObject::connect(a, &QAction::changed, this, [this, a]() 
        {
            a->setToolTip(stringWithAppendedShortcut(a->text()));
        });
}

/*!
    Returns a tool button for action.
    Appends the main keyboard shortcut cmd to the tool tip of the action.
*/
QToolButton* Command::toolButtonWithAppendedShortcut(QAction* action, Command* cmd)
{
    auto button = new QToolButton;
    button->setDefaultAction(action);
    if (cmd)
        cmd->augmentActionWithShortcutToolTip(action);
    return button;
}

} // namespace QtVision
} // namespace VSN
