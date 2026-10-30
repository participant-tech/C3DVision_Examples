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
#ifndef __QT_PROGRESSINDICATOR_H
#define __QT_PROGRESSINDICATOR_H

#include <qt_overlaywidget.h>

#include <QTimer>

#include <functional>
#include <memory>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

namespace Internal { class ProgressIndicatorPrivate; }

enum class ProgressIndicatorSize
{
    Small,
    Medium,
    Large
};

/* ProgressIndicatorPainter*/
class ProgressIndicatorPainter
{
public:
    using UpdateCallback = std::function<void()>;

    ProgressIndicatorPainter(ProgressIndicatorSize size);
    virtual ~ProgressIndicatorPainter() = default;

    void setIndicatorSize(ProgressIndicatorSize size);
    ProgressIndicatorSize indicatorSize() const;

    void setUpdateCallback(const UpdateCallback &cb);

    QSize size() const;

    void paint(QPainter &painter, const QRect &rect) const;

    void startAnimation();
    void stopAnimation();

protected:
    void nextAnimationStep();

private:
    ProgressIndicatorSize m_size = ProgressIndicatorSize::Small;
    int m_rotationStep = 45;
    int m_rotation = 0;
    QTimer m_timer;
    QPixmap m_pixmap;
    UpdateCallback m_callback;
};

/* ProgressIndicator */
class ProgressIndicator : public OverlayWidget
{
//    Q_OBJECT
public:
    explicit ProgressIndicator(ProgressIndicatorSize size, QWidget *parent = nullptr);

    void setIndicatorSize(ProgressIndicatorSize size);
    QSize sizeHint() const final;
protected:
    void showEvent(QShowEvent *) final;
    void hideEvent(QHideEvent *) final;
private:
    ProgressIndicatorPainter m_paint;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROGRESSINDICATOR_H */
