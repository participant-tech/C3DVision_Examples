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

#include <qt_orientationbar.h>
#include <QStylePainter>
#include <QCoreApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QGridLayout>
#include <QWidgetAction>
#include <QStyleOptionToolButton>
#include <qt_mainwindow.h>
#include <qt_icore.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

    /* QtOrientationPopupMenu */
class QtOrientationPopupMenu : public QMenu
{
public:
    explicit QtOrientationPopupMenu(QWidget* parent = nullptr);
    ~QtOrientationPopupMenu() override;
public:
    QtOrientationWidget* orientationWidget() { return m_orientationWidget; }
protected:
#if 0
    void paintEvent(QPaintEvent* event) override;
#endif
private:
    QtOrientationWidget* m_orientationWidget;
    friend class QtOrientationWidget;
};

/* QtOrientationPopupMenu */
QtOrientationPopupMenu::QtOrientationPopupMenu(QWidget* parent)
    : QMenu(parent)
    , m_orientationWidget(new QtOrientationWidget(this))
{
    setProperty("panelwidget", true);
    QWidgetAction* orientationWidgetAction = new QWidgetAction(this);
    orientationWidgetAction->setDefaultWidget(m_orientationWidget);
    addAction(orientationWidgetAction);
    addSeparator();
//    QAction* actionViewFront = new QAction(QIcon(":/res/view_front_48.png"), QObject::tr("Front"), this);
//    addAction(actionViewFront);
}

//-----------------------------------------------------------------------------
//
// ---
QtOrientationPopupMenu::~QtOrientationPopupMenu() {}
#if 0
// ---
void QtOrientationPopupMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStylePainter p(this);
    QStyleOption opt;
    QPalette pal = opt.palette;
    opt.initFrom(this);
    p.fillRect(opt.rect, pal.color(QPalette::Light));
}
#endif
/* QtOrientationWidget */
QtOrientationWidget::QtOrientationWidget(QtOrientationPopupMenu* menu, QWidget* parent)
    : QWidget(parent)
    , m_menu(menu)
    , m_gridLayout(new QGridLayout(this))
{
    setMouseTracking(true);
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(4, 4, 4, 4); // setMargin(4);
}

QtOrientationWidget::~QtOrientationWidget()
{
}

// ---
void QtOrientationWidget::addAction(int row, int column, QAction* action)
{ 
    QToolButton* button = new QToolButton(); 
    QStyleOption option; option.initFrom(this);
    int iconExtent = style()->proxy()->pixelMetric(QStyle::PM_SmallIconSize, &option);
    button->setIconSize(QSize(iconExtent, iconExtent));
    button->setDefaultAction(action);
    m_gridLayout->addWidget(button, row, column, Qt::AlignCenter);
    button->installEventFilter(this);
}

// ---
bool QtOrientationWidget::event(QEvent* event)
{ 
    if (event->type() == QEvent::StatusTip)
    {
        QtMainWindow* mainWindow = ICore::mainWindow();
        if (mainWindow != nullptr)
            QCoreApplication::sendEvent(mainWindow, event);
    }
    return QWidget::event(event);
}

// ---
bool QtOrientationWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
        this->mousePressEvent(static_cast<QMouseEvent*>(event));
    else if (event->type() == QEvent::MouseMove)
        this->mouseMoveEvent(static_cast<QMouseEvent*>(event));
    else if (event->type() == QEvent::MouseButtonRelease)
        this->mouseReleaseEvent(static_cast<QMouseEvent*>(event));
    return QWidget::eventFilter(watched, event);
}

// ---
void QtOrientationWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint pnt = event->pos();
    pnt = this->mapTo(m_menu, pnt);
    QMouseEvent ev(event->type(), pnt, event->button(), event->buttons(), event->modifiers());
    m_menu->mousePressEvent(&ev);
}

// ---
void QtOrientationWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint pnt = event->pos();
    pnt = this->mapTo(m_menu, pnt);
    QMouseEvent ev(event->type(), pnt, event->button(), event->buttons(), event->modifiers());
    m_menu->mouseReleaseEvent(&ev);
}

// ---
void QtOrientationWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pnt = event->pos();
    pnt = this->mapTo(m_menu, pnt);
    QMouseEvent ev(event->type(), pnt, event->button(), event->buttons(), event->modifiers());
    m_menu->mouseMoveEvent(&ev);
}

// ---
void QtOrientationWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStylePainter p(this);
    QStyleOption opt;
    QPalette pal = opt.palette;
    opt.initFrom(this);
    p.drawControl(QStyle::CE_ToolBar, opt);
}

/* QtOrientationToolButton */
QtOrientationToolButton::QtOrientationToolButton(QWidget* pParent)
    : QToolButton(pParent)
    , m_pMenu(new QtOrientationPopupMenu(this))
{
    setMenu(m_pMenu);
    setProperty("noArrow", true);
    setPopupMode(QToolButton::InstantPopup);
}

//-----------------------------------------------------------------------------
// 
// ---
QtOrientationToolButton::~QtOrientationToolButton()
{
}

//-----------------------------------------------------------------------------
// add additional orientation types
// ---
void QtOrientationToolButton::addActionToMenu(QAction* action) 
{ m_pMenu->addAction(action); }

//-----------------------------------------------------------------------------
// add standard orientation types
// ---
void QtOrientationToolButton::addActionToWidget(int row, int column, QAction* action)
{ ((QtOrientationPopupMenu*)m_pMenu)->orientationWidget()->addAction(row, column, action); }

//-----------------------------------------------------------------------------
// 
// ---
bool QtOrientationToolButton::event(QEvent* event)
{
    return QToolButton::event(event);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtOrientationToolButton::paintEvent(QPaintEvent* event)
{
    QToolButton::paintEvent(event);
}

} // namespace QtVision
} // namespace VSN
