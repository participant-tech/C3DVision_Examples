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

#include <qt_progressindicator.h>

#include <qt_theme.h>
#include <qt_icon.h>

#include <QPainter>
#include <vsn_last.h>

// The ProgressIndicator class shows an circular, endlessly animated progress indicator.

// Use it if you want to indicate that some work is being done, but you do not have the detailed
// progress information needed for a progress bar. You can either create the widget on demand,
// or create the widget once and only show it on demand. The animation only runs while the widget
// is visible.


// The ProgressIndicatorPainter class is the painting backend for the ProgressIndicator
// class.

// You can use it to paint a circular, endlessly animated progress indicator directly onto a
// QPaintDevice, for example, if you want to show a progress indicator where you cannot use
// a QWidget.


//-----------------------------------------------------------------------------
// Size of a progress indicator.

// Small
//      Small icon size. Useful for tool bars, status bars, rows in tree views,
//      and so on.
// Medium
//      Larger progress indicator useful for covering whole medium sized widgets.
// Large
//      Very large progress indicator that can be used to cover large parts of a UI.

namespace VSN {
namespace QtVision {

static FilePath imageFileNameForIndicatorSize(ProgressIndicatorSize size)
{
    switch (size) 
    {
        case ProgressIndicatorSize::Large:
            return ":/res/progressindicator_big_2x.png";
        case ProgressIndicatorSize::Medium:
            return ":/res/progressindicator_medium.png";
        case ProgressIndicatorSize::Small:
        default:
            return ":/res/progressindicator_small.png";
    }
}


// Constructs a progress indicator painter for the indicator size.
ProgressIndicatorPainter::ProgressIndicatorPainter(ProgressIndicatorSize size)
{
    m_timer.setSingleShot(false);
    QObject::connect(&m_timer, &QTimer::timeout, [this]() {
        nextAnimationStep();
        if (m_callback)
            m_callback();
    });

    setIndicatorSize(size);
}

// Changes the size of the progress indicator to size. Users of the class need
// to adapt their painting or layouting code to the change in resulting pixel size.
void ProgressIndicatorPainter::setIndicatorSize(ProgressIndicatorSize size)
{
    m_size = size;
    m_rotationStep = size == ProgressIndicatorSize::Small ? 45 : 30;
    m_timer.setInterval(size == ProgressIndicatorSize::Small ? 100 : 80);
    m_pixmap = Icon({{imageFileNameForIndicatorSize(size), Theme::PanelTextColorMid}}, Icon::Tint).pixmap();
    if (m_pixmap.isNull())
        Q_ASSERT(false);
}

// Returns the current indicator size. Use size to get the resulting
// pixel size.
ProgressIndicatorSize ProgressIndicatorPainter::indicatorSize() const
{
    return m_size;
}

// Sets the callback cb that is called whenever the progress indicator needs a repaint, because
// its animation progressed. The callback is a void function taking no parameters, and should
// usually trigger a QWidget::update on the widget that does the actual painting.
void ProgressIndicatorPainter::setUpdateCallback(const UpdateCallback &cb)
{
    m_callback = cb;
}

// Returns the size of the progress indicator in device independent pixels.
QSize ProgressIndicatorPainter::size() const
{
    return m_pixmap.size() / m_pixmap.devicePixelRatio();
}

// Paints the progress indicator centered in the rect on the given painter.
void ProgressIndicatorPainter::paint(QPainter& painter, const QRect& rect) const
{
/*
    QPen pen(Qt::red);
    painter.drawRect(rect);
    painter.fillRect(rect, Qt::red);
*/

    painter.save();
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPoint translate(rect.x() + rect.width() / 2, rect.y() + rect.height() / 2);
    QTransform t;
    t.translate(translate.x(), translate.y());
    t.rotate(m_rotation);
    t.translate(-translate.x(), -translate.y());
    painter.setTransform(t);
    QSize pixmapUserSize(m_pixmap.size() / m_pixmap.devicePixelRatio());
    painter.drawPixmap(QPoint(rect.x() + ((rect.width() - pixmapUserSize.width()) / 2),
                              rect.y() + ((rect.height() - pixmapUserSize.height()) / 2)),
                 m_pixmap);
    painter.restore();

}

// Starts the progress indicator animation.
void ProgressIndicatorPainter::startAnimation()
{
    QTV_ASSERT(m_callback, return);
    m_timer.start();
}

// Stops the progress indicator animation.
void ProgressIndicatorPainter::stopAnimation()
{
    m_timer.stop();
}

void ProgressIndicatorPainter::nextAnimationStep()
{
    m_rotation = (m_rotation + m_rotationStep + 360) % 360;
}

// Constructs a ProgressIndicator of the size size and with the parent parent.

// Use  attachToWidget to make the progress indicator automatically resize and center on the
// parent widget.
ProgressIndicator::ProgressIndicator(ProgressIndicatorSize size, QWidget *parent)
    : OverlayWidget(parent)
    , m_paint(size)
{
    setPaintFunction(
        [this](QWidget *w, QPainter &p, QPaintEvent *) { m_paint.paint(p, w->rect()); });
    m_paint.setUpdateCallback([this]() { update(); });
    updateGeometry();
}

// Changes the size of the progress indicator to size.
void ProgressIndicator::setIndicatorSize(ProgressIndicatorSize size)
{
    m_paint.setIndicatorSize(size);
    updateGeometry();
}

// Returns the size of the indicator in device independent pixels.
QSize ProgressIndicator::sizeHint() const
{
    return m_paint.size();
}

void ProgressIndicator::showEvent(QShowEvent *)
{
    m_paint.startAnimation();
}

void ProgressIndicator::hideEvent(QHideEvent *)
{
    m_paint.stopAnimation();
}

} // namespace QtVision
} // namespace VSN
