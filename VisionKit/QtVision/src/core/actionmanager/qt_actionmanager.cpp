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

#include <qt_actionmanager.h>
#include <qt_actionmanagerprivate.h>
#include <qt_actioncontainerprivate.h>
#include <qt_commandprivate.h>

#include <qt_icore.h>
#include <qt_mainwindow.h>

//#include <utils/algorithm.h>
//#include <utils/fadingindicator.h>

#include <QHash>
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

namespace {
    enum { warnAboutFindFailures = 0 };
}

static const char kKeyboardSettingsKeyV2[] = "KeyboardShortcutsV2";

static ActionManager *m_instance = nullptr;
static ActionManagerPrivate *d;

ActionManager::ActionManager(QObject *parent)
    : QObject(parent)
{
    m_instance = this;
    d = new ActionManagerPrivate;
    if (HostOsInfo::isMacHost())
        QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
}

ActionManager::~ActionManager()
{
    delete d;
}

// Returns the pointer to the instance. Only use for connecting to signals.
ActionManager* ActionManager::instance()
{
    return m_instance;
}

// ---
ActionContainer* ActionManager::createMenu(Id id)
{
    const ActionManagerPrivate::IdContainerMap::const_iterator it = d->m_idContainerMap.constFind(id);
    if (it !=  d->m_idContainerMap.constEnd())
        return it.value();
    auto mc = new MenuActionContainer(id);
    d->m_idContainerMap.insert(id, mc);
    connect(mc, &QObject::destroyed, d, &ActionManagerPrivate::containerDestroyed);
    return mc;
}

// ---
ActionContainer* ActionManager::createMenuBar(Id id)
{
    const ActionManagerPrivate::IdContainerMap::const_iterator it = d->m_idContainerMap.constFind(id);
    if (it !=  d->m_idContainerMap.constEnd())
        return it.value();
    QMenuBar* mb = nullptr;
    mb = new QMenuBar; // No parent (System menu bar on macOS)
    mb->setObjectName(id.toString());

    auto mbc = new MenuBarActionContainer(id);
    mbc->setMenuBar(mb);

    d->m_idContainerMap.insert(id, mbc);
    connect(mbc, &QObject::destroyed, d, &ActionManagerPrivate::containerDestroyed);

    return mbc;
}

// ---
/*
ActionContainer *ActionManager::createTouchBar(Id id, const QIcon &icon, const QString &text)
{
    QTV_CHECK(!icon.isNull() || !text.isEmpty());
    ActionContainer * const c = d->m_idContainerMap.value(id);
    if (c)
        return c;
    auto ac = new TouchBarActionContainer(id, icon, text);
    d->m_idContainerMap.insert(id, ac);
    connect(ac, &QObject::destroyed, d, &ActionManagerPrivate::containerDestroyed);
    return ac;
}
*/

Command* ActionManager::registerAction(QAction* action, Id id, const Context& context, bool scriptable)
{
    Command* cmd = d->overridableAction(id);
    if (cmd) 
    {
        cmd->d->addOverrideAction(action, context, scriptable);
        emit m_instance->commandListChanged();
        emit m_instance->commandAdded(id);
    }
    return cmd;
}

// ---
Command* ActionManager::command(Id id)
{
    const ActionManagerPrivate::IdCmdMap::const_iterator it = d->m_idCmdMap.constFind(id);
    if (it == d->m_idCmdMap.constEnd()) 
    {
        if (/*warnAboutFindFailures*/ false)
            qWarning() << "ActionManagerPrivate::command(): failed to find :"
                       << id.name();
        return nullptr;
    }
    return it.value();
}

// ---
ActionContainer* ActionManager::actionContainer(Id id)
{
    const ActionManagerPrivate::IdContainerMap::const_iterator it = d->m_idContainerMap.constFind(id);
    if (it == d->m_idContainerMap.constEnd()) 
    {
        if (/*warnAboutFindFailures*/ false)
            qWarning() << "ActionManagerPrivate::actionContainer(): failed to find :"
                       << id.name();
        return nullptr;
    }
    return it.value();
}

QList<Command*> ActionManager::commands()
{ return d->m_idCmdMap.values(); }

void ActionManager::unregisterAction(QAction* action, Id id)
{
    Command *cmd = d->m_idCmdMap.value(id, nullptr);
    if (!cmd) 
    {
        qWarning() << "unregisterAction: id" << id.name()
                   << "is registered with a different command type.";
        return;
    }
    cmd->d->removeOverrideAction(action);
    if (cmd->d->isEmpty()) 
    {
        // clean up
//        ActionManagerPrivate::saveSettings(cmd);
        Q_ASSERT(false);
        ICore::mainWindow()->removeAction(cmd->action());
        // ActionContainers listen to the commands' destroyed signals
        delete cmd->action();
        d->m_idCmdMap.remove(id);
        delete cmd;
    }
    emit m_instance->commandListChanged();
}

// internal
void ActionManager::setPresentationModeEnabled(bool enabled)
{
    if (enabled == isPresentationModeEnabled())
        return;
    // Signal/slots to commands:
    const QList<Command *> commandList = commands();
    for (Command *c : commandList) 
    {
        if (c->action()) 
        {
            if (enabled)
                connect(c->action(), &QAction::triggered, d, &ActionManagerPrivate::actionTriggered);
            else
                disconnect(c->action(), &QAction::triggered, d, &ActionManagerPrivate::actionTriggered);
        }
    }

    d->m_presentationModeEnabled = enabled;
}

bool ActionManager::isPresentationModeEnabled()
{
    return d->m_presentationModeEnabled;
}

QString ActionManager::withNumberAccelerator(const QString &text, const int number)
{
    if (HostOsInfo::isMacHost() || number > 9)
        return text;
    return QString("&%1 | %2").arg(number).arg(text);
}
/*
void ActionManager::saveSettings()
{
    d->saveSettings();
}
*/
void ActionManager::setContext(const Context &context)
{
    d->setContext(context);
}

// ---
ActionManagerPrivate::~ActionManagerPrivate()
{
    // first delete containers to avoid them reacting to command deletion
    for (const ActionContainerPrivate *container : qAsConst(m_idContainerMap))
        disconnect(container, &QObject::destroyed, this, &ActionManagerPrivate::containerDestroyed);
    qDeleteAll(m_idContainerMap);
    qDeleteAll(m_idCmdMap);
}

// ---
void ActionManagerPrivate::setContext(const Context& context)
{
    // here are possibilities for speed optimization if necessary:
    // let commands (de-)register themselves for contexts
    // and only update commands that are either in old or new contexts
    m_context = context;
    const IdCmdMap::const_iterator cmdcend = m_idCmdMap.constEnd();
    for (IdCmdMap::const_iterator it = m_idCmdMap.constBegin(); it != cmdcend; ++it)
        it.value()->d->setCurrentContext(m_context);
}

bool ActionManagerPrivate::hasContext(const Context& context) const
{
    for (int i = 0; i < m_context.size(); ++i) 
    {
        if (context.contains(m_context.at(i)))
            return true;
    }
    return false;
}

void ActionManagerPrivate::containerDestroyed()
{
    auto container = static_cast<ActionContainerPrivate*>(sender());
    m_idContainerMap.remove(m_idContainerMap.key(container));
}

void ActionManagerPrivate::actionTriggered()
{
    auto action = qobject_cast<QAction *>(QObject::sender());
    if (action)
        showShortcutPopup(action->shortcut().toString());
}

void ActionManagerPrivate::showShortcutPopup(const QString& shortcut)
{
    if (shortcut.isEmpty() || !ActionManager::isPresentationModeEnabled())
        return;

    QWidget* window = QApplication::activeWindow();
    if (!window) 
    {
        if (!QApplication::topLevelWidgets().isEmpty())
            window = QApplication::topLevelWidgets().first();
        else
            window = ICore::mainWindow();
    }
    Q_ASSERT(false);
//    Utils::FadingIndicator::showText(window, shortcut);
}

Command* ActionManagerPrivate::overridableAction(Id id)
{
    Command* cmd = m_idCmdMap.value(id, nullptr);
    if (!cmd) 
    {
        cmd = new Command(id);
        m_idCmdMap.insert(id, cmd);
//        readUserSettings(id, cmd);
        ICore::mainWindow()->addAction(cmd->action());
        cmd->action()->setObjectName(id.toString());
        cmd->action()->setShortcutContext(Qt::ApplicationShortcut);
        cmd->d->setCurrentContext(m_context);

        if (ActionManager::isPresentationModeEnabled())
            connect(cmd->action(), &QAction::triggered, this, &ActionManagerPrivate::actionTriggered);
    }
    return cmd;
}

/*
void ActionManagerPrivate::readUserSettings(Id id, Command*  cmd)
{
    QSettings *settings = ICore::settings();
    settings->beginGroup(kKeyboardSettingsKeyV2);
    if (settings->contains(id.toString())) {
        const QVariant v = settings->value(id.toString());
        if (QMetaType::Type(v.type()) == QMetaType::QStringList) {
            cmd->setKeySequences(Utils::transform<QList>(v.toStringList(), [](const QString &s) {
                return QKeySequence::fromString(s);
            }));
        } else {
            cmd->setKeySequences({QKeySequence::fromString(v.toString())});
        }
    }
    settings->endGroup();
}
*/
/*
void ActionManagerPrivate::saveSettings(Command* cmd)
{
    const QString id = cmd->id().toString();
    const QString settingsKey = QLatin1String(kKeyboardSettingsKeyV2) + '/' + id;
    const QList<QKeySequence> keys = cmd->keySequences();
    const QList<QKeySequence> defaultKeys = cmd->defaultKeySequences();
    if (keys != defaultKeys) {
        if (keys.isEmpty()) {
            ICore::settings()->setValue(settingsKey, QString());
        } else if (keys.size() == 1) {
            ICore::settings()->setValue(settingsKey, keys.first().toString());
        } else {
            ICore::settings()->setValue(settingsKey,
                                        Utils::transform<QStringList>(keys,
                                                                      [](const QKeySequence &k) {
                                                                          return k.toString();
                                                                      }));
        }
    } else {
        ICore::settings()->remove(settingsKey);
    }
}
*/
/*
void ActionManagerPrivate::saveSettings()
{
    const IdCmdMap::const_iterator cmdcend = m_idCmdMap.constEnd();
    for (IdCmdMap::const_iterator j = m_idCmdMap.constBegin(); j != cmdcend; ++j)
        saveSettings(j.value());
}
*/
} // namespace QtVision
} // namespace VSN
