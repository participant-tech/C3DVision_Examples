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

#ifndef __QT_INFOLABEL_H
#define __QT_INFOLABEL_H

#include <qt_elidinglabel.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* InfoLabel */
class QT_CLASS InfoLabel : public ElidingLabel
{
public:
    enum InfoType {
        Information,
        Warning,
        Error,
        Ok,
        NotOk,
        None
    };

    explicit InfoLabel(QWidget *parent);
    explicit InfoLabel(const QString &text = {}, InfoType type = Information,
                       QWidget *parent = nullptr);

    InfoType type() const;
    void setType(InfoType type);
    bool filled() const;
    void setFilled(bool filled);
    QSize minimumSizeHint() const override;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    InfoType m_type = Information;
    bool m_filled = false;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_INFOLABEL_H */
