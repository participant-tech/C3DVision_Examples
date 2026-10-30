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

#include <qt_infolabel.h>

#include <qt_icon.h>
#include <qt_utilsicons.h>

#include <QPainter>
#include <QPaintEvent>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

constexpr int iconSize = 16;

InfoLabel::InfoLabel(QWidget *parent)
    : InfoLabel({}, Information, parent)
{
}

InfoLabel::InfoLabel(const QString &text, InfoType type, QWidget *parent)
    : ElidingLabel(text, parent)
{
    setType(type);
}

InfoLabel::InfoType InfoLabel::type() const
{
    return m_type;
}

void InfoLabel::setType(InfoType type)
{
    m_type = type;
    setContentsMargins(m_type == None ? 0 : iconSize + 2, 0, 0, 0);
    update();
}

bool InfoLabel::filled() const
{
    return m_filled;
}

void InfoLabel::setFilled(bool filled)
{
    m_filled = filled;
}

QSize InfoLabel::minimumSizeHint() const
{
    QSize baseHint = ElidingLabel::minimumSizeHint();
    baseHint.setHeight(qMax(baseHint.height(), iconSize));
    return baseHint;
}

static Theme::Color fillColorForType(InfoLabel::InfoType type)
{
    using namespace Utils;
    switch (type) {
    case InfoLabel::Warning:
        return Theme::IconsWarningColor;
    /*
    case InfoLabel::Ok:
        return Theme::IconsRunColor;
    case InfoLabel::Error:
    case InfoLabel::NotOk:
        return Theme::IconsErrorColor;
    case InfoLabel::Information:
    default:
        return Theme::IconsInfoColor;
    */
    default:
        return Theme::IconsWarningColor;
    }
}

static const QIcon& iconForType(InfoLabel::InfoType /*type*/)
{
    /*
    switch (type) 
    {
        case InfoLabel::Information: 
        {
            static const QIcon icon = Icons::INFO.icon();
            return icon;
        }
        case InfoLabel::Warning: 
        {
            static const QIcon icon = Icons::WARNING.icon();
            return icon;
        }
        case InfoLabel::Error: 
        {
            static const QIcon icon = Icons::CRITICAL.icon();
            return icon;
        }
        case InfoLabel::Ok: 
        {
            static const QIcon icon = Icons::OK.icon();
            return icon;
        }
        case InfoLabel::NotOk: 
        {
            static const QIcon icon = Icons::BROKEN.icon();
            return icon;
        }
        default: 
        {
            static const QIcon undefined;
            return undefined;
        }
    }
    */
    Q_ASSERT(false);
    return QIcon();
}

void InfoLabel::paintEvent(QPaintEvent *event)
{
    if (m_type == None)
        return ElidingLabel::paintEvent(event);

    const bool centerIconVertically = wordWrap() || elideMode() == Qt::ElideNone;
    const QRect iconRect(0, centerIconVertically ? 0 : ((height() - iconSize) / 2),
                         iconSize, iconSize);

    QPainter p(this);
    if (m_filled && isEnabled()) 
    {
        p.save();
        p.setOpacity(0.175);
        Q_ASSERT(false);
        //        p.fillRect(rect(), creatorTheme()->color(fillColorForType(m_type)));
        p.restore();
    }
    const QIcon &icon = iconForType(m_type);
    QWindow *window = this->window()->windowHandle();
    const QIcon::Mode mode = !this->isEnabled() ? QIcon::Disabled : QIcon::Normal;
    const QPixmap iconPx =
            icon.pixmap(window, QSize(iconSize, iconSize) * devicePixelRatio(), mode);
    p.drawPixmap(iconRect, iconPx);
    ElidingLabel::paintEvent(event);
}

} // namespace QtVision
} // namespace VSN
