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

#include <qt_cursors.h>

#include <QPainter>
#include <QBitmap>
#include <QColor>
#include <qstyleoption.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

// ---
static QPixmap paintPixmap(int size, const QColor& c)
{
    QPixmap result(size, size);
    result.fill(c);
    QPainter p(&result);
    int factor = 4;

    QPen pen(QColor(255, 255, 255, 180), 3);
    p.setPen(pen);
    // cross
    p.drawLine(size / 2, size - size / factor, size / 2, size / factor);
    p.drawLine(size / factor, size / 2, size - size / factor, size / 2);
    // top-left
    p.drawLine(0, 0, size / factor, 0);
    p.drawLine(0, 0, 0, size / factor);
    // top-right
    p.drawLine(size, 0, size - size / factor, 0);
    p.drawLine(size - 1, 0, size - 1, size / factor);
    // botton-left
    p.drawLine(0, size - 1, size / factor, size - 1);
    p.drawLine(0, size, 0, size - size / factor);
    // botton-right
    p.drawLine(size, size - 1, size - size / factor, size - 1);
    p.drawLine(size, size - 1, size - 1, size - size / factor);


    QPen penBlack(Qt::black, 1);
    p.setPen(penBlack);
    // cross
    p.drawLine(size / 2, size - size / factor, size / 2, size / factor);
    p.drawLine(size / factor, size / 2, size - size / factor, size / 2);
    // top-left
    p.drawLine(0, 0, size / factor, 0);
    p.drawLine(0, 0, 0, size / factor);
    // top-right
    p.drawLine(size, 0, size - size / factor, 0);
    p.drawLine(size - 1, 0, size - 1, size / factor);
    // botton-left
    p.drawLine(0, size - 1, size / factor, size - 1);
    p.drawLine(0, size, 0, size - size / factor);
    // botton-right
    p.drawLine(size, size - 1, size - size / factor, size - 1);
    p.drawLine(size, size - 1, size - 1, size - size / factor);
    return result;
}

// ---
QT_FUNC(QCursor) findCursor(const QWidget* pWidget)
{
    QStyleOption opt;
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    opt.init(pWidget);
#else
    opt.initFrom(pWidget);
#endif
//    QRect rect = opt.fontMetrics.boundingRect("X");
    int size = 32; // rect.width() + rect.height();
    QPixmap px = paintPixmap(size, Qt::transparent);
    QCursor result(px, size / 2, size / 2);
    return result;
}

} // namespace QtVision

} // namespace VSN
