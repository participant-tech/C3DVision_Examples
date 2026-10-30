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
#ifndef __QT_ORIENTATIONBAR_H
#define __QT_ORIENTATIONBAR_H

#include <QMenu>
#include <QLayout>
#include <QToolButton>

#include <qt_global.h>

namespace VSN {
namespace QtVision {

class QtOrientationPopupMenu;
/* QtOrientationPopupMenu */
class QT_CLASS QtOrientationWidget : public QWidget
{
public:
    explicit QtOrientationWidget(QtOrientationPopupMenu* menu, QWidget* parent = nullptr);
    ~QtOrientationWidget() override;
public:
    void addAction(int row, int column, QAction* action);
protected:
    bool event(QEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    QtOrientationPopupMenu* m_menu;
    QGridLayout* m_gridLayout;
};

/* QtToolButton */
class QT_CLASS QtOrientationToolButton : public QToolButton
{
    Q_OBJECT
public:
    QtOrientationToolButton(QWidget* pParent = nullptr);
    ~QtOrientationToolButton() override;
public:
    void addActionToMenu(QAction* action);
    void addActionToWidget(int row, int column, QAction* action);
protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    QMenu* m_pMenu;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ORIENTATIONBAR_H */
