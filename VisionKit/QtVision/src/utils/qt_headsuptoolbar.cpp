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

#include <qt_headsuptoolbar.h>

#include <QApplication>
#include <QStylePainter>
#include <QStyleOption>
#include <QWidgetAction>
#include <QActionEvent>
#include <QPainter>
#include <QEvent>
#include <QStyle>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* _qt_connect_iconsize */
static void _qt_connect_iconsize(QObject* parent, QtToolButton* button)
{
    if (QToolBar* tb = qobject_cast<QToolBar*>(parent))
        QObject::connect(tb, SIGNAL(iconSizeChanged(QSize)), button, SLOT(setIconSize(QSize)));
}

/* QtToolButton */
QtToolButton::QtToolButton(QWidget* pParent)
    : QToolButton(pParent)
    , m_pCurrentAction(nullptr)
    , m_pMenu(new QMenu(this))
{
    setMenu(m_pMenu);
    setPopupMode(QToolButton::MenuButtonPopup);
    _qt_connect_iconsize(pParent, this);
}

//-----------------------------------------------------------------------------
// 
// ---
QtToolButton::~QtToolButton()
{
}

//-----------------------------------------------------------------------------
// 
// ---
void QtToolButton::setCurrentAction(QAction* pCurrentAction)
{
    if (m_pCurrentAction != pCurrentAction)
    {
        m_pCurrentAction = pCurrentAction;
        setDefaultAction(m_pCurrentAction);
        setIcon(m_pCurrentAction->icon());
        update();
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void QtToolButton::currentAction(bool current)
{
    Q_UNUSED(current);
    if (QAction* pAction = qobject_cast<QAction*>(sender()))
        setCurrentAction(pAction);
}

//-----------------------------------------------------------------------------
// 
// ---
bool QtToolButton::event(QEvent* event)
{
    if (event->type() == QEvent::ParentChange)
        _qt_connect_iconsize(parent(), this);
    return QToolButton::event(event);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtToolButton::actionEvent(QActionEvent* event)
{
    QToolButton::actionEvent(event);

    QAction* action = event->action();
    if (action == m_pMenu->menuAction())
        return;

    QWidgetAction* widgetAction = qobject_cast<QWidgetAction*>(action);
    Q_ASSERT(widgetAction == nullptr);

    switch (event->type()) 
    {
        case QEvent::ActionAdded:
        {
            m_pMenu->addAction(action);
            QObject::connect(action, SIGNAL(triggered(bool)), this, SLOT(currentAction(bool)));
            break;
        }
        case QEvent::ActionRemoved:
        {
            QObject::disconnect(action, SIGNAL(triggered(bool)), this, SLOT(currentAction(bool)));
            m_pMenu->removeAction(action);
            break;
        }
        default:
//            Q_ASSERT_X(false, "QtToolBar::actionEvent", "internal error");
            break;
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void QtToolButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStylePainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    opt.icon = m_pCurrentAction->icon();
    p.drawComplexControl(QStyle::CC_ToolButton, opt);
}


/* QtAutoHideWindow */
QtAutoHideWindow::QtAutoHideWindow(QWidget* pParent)
    : QWidget(pParent)
    , m_pToolBar(nullptr)
{
    pParent->installEventFilter(this);
}

//-----------------------------------------------------------------------------
// 
// ---
QtAutoHideWindow::~QtAutoHideWindow()
{
    parent()->removeEventFilter(this);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::setToolBar(QToolBar* pToolBar) 
{
    if (pToolBar == nullptr)
        return;
    if (m_pToolBar != pToolBar)
        delete m_pToolBar;

    m_pToolBar = pToolBar;
    m_pToolBar->setParent(this);
    m_pToolBar->setAllowedAreas(Qt::TopToolBarArea);

    QObject::connect(m_pToolBar, &QToolBar::allowedAreasChanged, 
        this, &QtAutoHideWindow::allowedAreasChanged);
    QObject::connect(m_pToolBar, &QToolBar::iconSizeChanged, 
        this, &QtAutoHideWindow::iconSizeChanged);
}

//-----------------------------------------------------------------------------
// 
// ---
bool QtAutoHideWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == parent())
    {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Show)
            reposition();
    }
    return QWidget::eventFilter(watched, event);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::reposition()
{
    if (m_pToolBar == nullptr)
        return;
    if (QWidget* pParent = qobject_cast<QWidget*>(parent()))
    {
        QRect rc = m_pToolBar->rect();
        QRect rcParent = pParent->rect();
        if (m_pToolBar->allowedAreas() == Qt::TopToolBarArea)
        {
            m_pToolBar->setOrientation(Qt::Horizontal);
            int val = style()->pixelMetric(QStyle::PM_LayoutTopMargin);
            move((rcParent.width() / 2) - (rc.width() / 2) - rc.x(), rc.y() + val);
        }
        else if (m_pToolBar->allowedAreas() == Qt::BottomToolBarArea)
        {
            m_pToolBar->setOrientation(Qt::Horizontal);
            int val = style()->pixelMetric(QStyle::PM_LayoutBottomMargin);
            move((rcParent.width() / 2) - (rc.width() / 2) - rc.x(), (rcParent.height() - rc.height()) - val);
        }
        else if (m_pToolBar->allowedAreas() == Qt::RightToolBarArea)
        {
            m_pToolBar->setOrientation(Qt::Vertical);
            int val = style()->pixelMetric(QStyle::PM_LayoutRightMargin);
            move((rcParent.width() - rc.width()) - val, (rcParent.height() / 2) - (rc.height() / 2) - rc.y());
        }
        else if (m_pToolBar->allowedAreas() == Qt::LeftToolBarArea)
        {
            m_pToolBar->setOrientation(Qt::Vertical);
            int val = style()->pixelMetric(QStyle::PM_LayoutLeftMargin);
            move(rc.left() + val, (rcParent.height() / 2) - (rc.height() / 2) - rc.y());
        }
        resize(rc.size());
    }
}

//-----------------------------------------------------------------------------
// 
// ---
bool QtAutoHideWindow::event(QEvent* event)
{
    if (event->type() == QEvent::StyleChange && toolBar() != nullptr)
    {
        toolBar()->adjustSize();
        updateGeometry();
    }
    return QWidget::event(event);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
#if 0
    QPainter p(this);
    p.setPen(QPen(QColor(255, 0, 0)));
    QRect rc = rect();
    p.drawRect(rc.adjusted(0, 0, -1, -1));
#endif
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    reposition();
}

//-----------------------------------------------------------------------------
// 
// ---
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
void QtAutoHideWindow::enterEvent(QEvent* event)
#else
void QtAutoHideWindow::enterEvent(QEnterEvent* event)
#endif
{
    QWidget::enterEvent(event);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    QApplication::restoreOverrideCursor();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::allowedAreasChanged(Qt::ToolBarAreas allowedAreas)
{
    Q_UNUSED(allowedAreas);
    reposition();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtAutoHideWindow::iconSizeChanged(const QSize& iconSize)
{
    Q_UNUSED(iconSize);
    if (m_pToolBar != nullptr)
    {
        m_pToolBar->adjustSize();
        reposition();
    }
}

} // namespace QtVision

} // namespace VSN
