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

#include <qt_overlaywidget.h>

#include <QEvent>
#include <QPainter>
#include <vsn_last.h>


namespace VSN {
namespace QtVision {

OverlayWidget::OverlayWidget(QWidget *parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    if (parent)
        attachToWidget(parent);
}

void OverlayWidget::setPaintFunction(const OverlayWidget::PaintFunction &paint)
{
    m_paint = paint;
}

bool OverlayWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == parent() && ev->type() == QEvent::Resize)
        resizeToParent();
    return QWidget::eventFilter(obj, ev);
}

void OverlayWidget::paintEvent(QPaintEvent* ev)
{
    if (m_paint) 
    {
        QPainter p(this);
        m_paint(this, p, ev);
    }
}

void OverlayWidget::attachToWidget(QWidget *parent)
{
    if (parentWidget())
        parentWidget()->removeEventFilter(this);
    setParent(parent);
    if (parent) 
    {
        parent->installEventFilter(this);
        resizeToParent();
        raise();
    }
}

void OverlayWidget::resizeToParent()
{
    QTV_ASSERT(parentWidget(), return );
    setGeometry(QRect(QPoint(0, 0), parentWidget()->size()));
}

} // namespace QtVision
} // namespace VSN
