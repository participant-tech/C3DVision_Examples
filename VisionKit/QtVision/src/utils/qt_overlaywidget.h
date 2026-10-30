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
#ifndef __QT_OVERLAYWIDGET_H
#define __QT_OVERLAYWIDGET_H

#include <QWidget>
#include <functional>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* OverlayWidget */
class OverlayWidget : public QWidget
{
//    Q_OBJECT
public:
    using PaintFunction = std::function<void(QWidget *, QPainter &, QPaintEvent *)>;

    explicit OverlayWidget(QWidget *parent = nullptr);

    void attachToWidget(QWidget *parent);
    void setPaintFunction(const PaintFunction &paint);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *ev) override;
private:
    void resizeToParent();
    PaintFunction m_paint;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_OVERLAYWIDGET_H */
