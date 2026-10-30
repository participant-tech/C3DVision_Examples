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

#ifndef __QT_ELIDINGLABEL_H
#define __QT_ELIDINGLABEL_H

#include <QLabel>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class QT_CLASS ElidingLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode DESIGNABLE true)
    Q_PROPERTY(QString additionalToolTip READ additionalToolTip WRITE setAdditionalToolTip DESIGNABLE true)
    Q_PROPERTY(QString additionalToolTipSeparator READ additionalToolTipSeparator WRITE setAdditionalToolTipSeparator DESIGNABLE true)
public:
    explicit ElidingLabel(QWidget *parent = nullptr);
    explicit ElidingLabel(const QString &text, QWidget *parent = nullptr);

    Qt::TextElideMode elideMode() const;
    void setElideMode(const Qt::TextElideMode &elideMode);

    QString additionalToolTip();
    void setAdditionalToolTip(const QString& additionalToolTip);

    QString additionalToolTipSeparator() const;
    void setAdditionalToolTipSeparator(const QString &newAdditionalToolTipSeparator);
protected:
    void paintEvent(QPaintEvent *event) override;
    void updateToolTip(const QString& elidedText);
private:
    Qt::TextElideMode m_elideMode;
    QString m_additionalToolTip;
    QString m_additionalToolTipSeparator{"\n\n"};
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_ELIDINGLABEL_H */
