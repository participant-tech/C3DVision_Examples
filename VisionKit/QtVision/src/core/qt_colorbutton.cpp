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

#include <qt_colorbutton.h>
#include <QPainter>
#include <QColorDialog>
#include <QStyleOptionButton>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* ColorButton */
ColorButton::ColorButton(QWidget* pParent, QColor color)
    : QPushButton(pParent)
    , m_selectColor(color)
{
    connect(this, SIGNAL(released()), this, SLOT(chooseOtherColor()));
}

//-----------------------------------------------------------------------------
// 
// ---
ColorButton::~ColorButton()
{
}

//-----------------------------------------------------------------------------
// 
// ---
QColor ColorButton::GetColor() const
{ return m_selectColor; }

//-----------------------------------------------------------------------------
// 
// ---
void ColorButton::SetColor(const QColor& color)
{
    if (!color.isValid() || m_selectColor == color)
        return;
    m_selectColor = color;
    emit chooseColor(m_selectColor);
}

//-----------------------------------------------------------------------------
// 
// ---
void ColorButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QStyleOptionButton option;
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    option.init(this);
#else
    option.initFrom(this);
#endif
    option.rect = this->rect();
    this->style()->drawControl(QStyle::CE_PushButton, &option, &p, this);
    QColor clr = m_selectColor;
    if (!(option.state & QStyle::State_Enabled))
        clr = option.palette.color(QPalette::Disabled, QPalette::Button);
    p.fillRect(option.rect.adjusted(8, 8, -8, -8), clr);
    p.drawRect(option.rect.adjusted(8, 8, -8, -8));
}

//-----------------------------------------------------------------------------
// 
// ---
void ColorButton::chooseOtherColor()
{ SetColor(QColorDialog::getColor(m_selectColor, this)); }

} // namespace QtVision
} // namespace VSN
