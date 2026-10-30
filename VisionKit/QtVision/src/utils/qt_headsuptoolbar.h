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
#ifndef __QT_HEADSUPTOOLBAR_H
#define __QT_HEADSUPTOOLBAR_H

#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <qt_global.h>


namespace VSN {
namespace QtVision {

/* QtToolButton */
class QT_CLASS QtToolButton : public QToolButton
{
    Q_OBJECT
public:
    QtToolButton(QWidget* pParent = nullptr);
    ~QtToolButton() override;
public:
    void setCurrentAction(QAction* pCurrentAction);
protected Q_SLOTS:
    void currentAction(bool);
protected:
    bool event(QEvent* event) override;
    void actionEvent(QActionEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    QAction* m_pCurrentAction;
    QMenu* m_pMenu;
};

/* QtAutoHideWindow */
class QT_CLASS QtAutoHideWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QtAutoHideWindow(QWidget* pParent = nullptr);
    ~QtAutoHideWindow() override;
public:
    QToolBar* toolBar() const { return m_pToolBar; }
    void setToolBar(QToolBar* pToolBar);
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
protected:
    void reposition();
protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    void enterEvent(QEvent* event) override;
#else
    void enterEvent(QEnterEvent* event) override;
#endif
    void leaveEvent(QEvent* event);
protected Q_SLOTS:
    void allowedAreasChanged(Qt::ToolBarAreas allowedAreas);
    void iconSizeChanged(const QSize& iconSize);
private:
    QToolBar* m_pToolBar;
private:
    Q_DISABLE_COPY(QtAutoHideWindow);
};

} // namespace QtVision

} // namespace VSN

#endif /* __QT_HEADSUPTOOLBAR_H */
