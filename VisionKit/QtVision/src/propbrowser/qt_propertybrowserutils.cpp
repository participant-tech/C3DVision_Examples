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

#include <qt_propertybrowserutilsprivate.h>
#include <QtWidgets/QApplication>
#include <QtGui/QPainter>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenu>
#include <QtCore/QLocale>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

CursorDatabase::CursorDatabase()
{
    appendCursor(Qt::ArrowCursor, QCoreApplication::translate("CursorDatabase", "Arrow"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-arrow.png")));
    appendCursor(Qt::UpArrowCursor, QCoreApplication::translate("CursorDatabase", "Up Arrow"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-uparrow.png")));
    appendCursor(Qt::CrossCursor, QCoreApplication::translate("CursorDatabase", "Cross"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-cross.png")));
    appendCursor(Qt::WaitCursor, QCoreApplication::translate("CursorDatabase", "Wait"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-wait.png")));
    appendCursor(Qt::IBeamCursor, QCoreApplication::translate("CursorDatabase", "IBeam"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-ibeam.png")));
    appendCursor(Qt::SizeVerCursor, QCoreApplication::translate("CursorDatabase", "Size Vertical"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizev.png")));
    appendCursor(Qt::SizeHorCursor, QCoreApplication::translate("CursorDatabase", "Size Horizontal"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeh.png")));
    appendCursor(Qt::SizeFDiagCursor, QCoreApplication::translate("CursorDatabase", "Size Backslash"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizef.png")));
    appendCursor(Qt::SizeBDiagCursor, QCoreApplication::translate("CursorDatabase", "Size Slash"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeb.png")));
    appendCursor(Qt::SizeAllCursor, QCoreApplication::translate("CursorDatabase", "Size All"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeall.png")));
    appendCursor(Qt::BlankCursor, QCoreApplication::translate("CursorDatabase", "Blank"),
                 QIcon());
    appendCursor(Qt::SplitVCursor, QCoreApplication::translate("CursorDatabase", "Split Vertical"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-vsplit.png")));
    appendCursor(Qt::SplitHCursor, QCoreApplication::translate("CursorDatabase", "Split Horizontal"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hsplit.png")));
    appendCursor(Qt::PointingHandCursor, QCoreApplication::translate("CursorDatabase", "Pointing Hand"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hand.png")));
    appendCursor(Qt::ForbiddenCursor, QCoreApplication::translate("CursorDatabase", "Forbidden"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-forbidden.png")));
    appendCursor(Qt::OpenHandCursor, QCoreApplication::translate("CursorDatabase", "Open Hand"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-openhand.png")));
    appendCursor(Qt::ClosedHandCursor, QCoreApplication::translate("CursorDatabase", "Closed Hand"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-closedhand.png")));
    appendCursor(Qt::WhatsThisCursor, QCoreApplication::translate("CursorDatabase", "What's This"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-whatsthis.png")));
    appendCursor(Qt::BusyCursor, QCoreApplication::translate("CursorDatabase", "Busy"),
                 QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-busy.png")));
}

void CursorDatabase::clear()
{
    m_cursorNames.clear();
    m_cursorIcons.clear();
    m_valueToCursorShape.clear();
    m_cursorShapeToValue.clear();
}

void CursorDatabase::appendCursor(Qt::CursorShape shape, const QString &name, const QIcon& icon)
{
    if (m_cursorShapeToValue.contains(shape))
        return;
    const int value = m_cursorNames.count();
    m_cursorNames.append(name);
    m_cursorIcons.insert(value, icon);
    m_valueToCursorShape.insert(value, shape);
    m_cursorShapeToValue.insert(shape, value);
}

QStringList CursorDatabase::cursorShapeNames() const
{
    return m_cursorNames;
}

QMap<int, QIcon> CursorDatabase::cursorShapeIcons() const
{
    return m_cursorIcons;
}

QString CursorDatabase::cursorToShapeName(const QCursor& cursor) const
{
    int val = cursorToValue(cursor);
    if (val >= 0)
        return m_cursorNames.at(val);
    return QString();
}

QIcon CursorDatabase::cursorToShapeIcon(const QCursor& cursor) const
{
    int val = cursorToValue(cursor);
    return m_cursorIcons.value(val);
}

int CursorDatabase::cursorToValue(const QCursor& cursor) const
{
#ifndef QT_NO_CURSOR
    Qt::CursorShape shape = cursor.shape();
    if (m_cursorShapeToValue.contains(shape))
        return m_cursorShapeToValue[shape];
#endif
    return -1;
}

#ifndef QT_NO_CURSOR
QCursor CursorDatabase::valueToCursor(int value) const
{
    if (m_valueToCursorShape.contains(value))
        return QCursor(m_valueToCursorShape[value]);
    return QCursor();
}
#endif
// ---
QPixmap PropBrowserUtils::brushValuePixmap(const QBrush& b)
{
    QImage img(24, 24, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QPainter painter(&img);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0, 0, img.width(), img.height(), b);
    QColor color = b.color();
    if (color.alpha() != 255) 
    {
        QBrush  opaqueBrush = b;
        color.setAlpha(255);
        opaqueBrush.setColor(color);
        painter.fillRect(img.width() / 4, img.height() / 4,
                         img.width() / 2, img.height() / 2, opaqueBrush);
    }
    painter.end();
    return QPixmap::fromImage(img);
}

QIcon PropBrowserUtils::brushValueIcon(const QBrush& b)
{
    return QIcon(brushValuePixmap(b));
}

QString PropBrowserUtils::colorValueText(const QColor& c)
{
    return QCoreApplication::translate("PropBrowserUtils", "[%1, %2, %3] (%4)")
           .arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}

QPixmap PropBrowserUtils::fontValuePixmap(const QFont& font)
{
    QFont f = font;
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter p(&img);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::Antialiasing, true);
    f.setPointSize(13);
    p.setFont(f);
    QTextOption t;
    t.setAlignment(Qt::AlignCenter);
    p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
    return QPixmap::fromImage(img);
}

QIcon PropBrowserUtils::fontValueIcon(const QFont &f)
{
    return QIcon(fontValuePixmap(f));
}

QString PropBrowserUtils::fontValueText(const QFont &f)
{
    return QCoreApplication::translate("PropBrowserUtils", "[%1, %2]")
           .arg(f.family()).arg(f.pointSize());
}

QString PropBrowserUtils::dateFormat()
{
    QLocale loc;
    QString format = loc.dateFormat(QLocale::ShortFormat);
    if (format.count(QLatin1Char('y')) == 2)
        format.insert(format.indexOf(QLatin1Char('y')), QLatin1String("yy"));
    return format;
}

QString PropBrowserUtils::timeFormat()
{
    QLocale loc;
    return loc.timeFormat(QLocale::LongFormat);
}

QString PropBrowserUtils::dateTimeFormat()
{
    QString format = dateFormat();
    format += QLatin1Char(' ');
    format += timeFormat();
    return format;
}

BoolEdit::BoolEdit(QWidget *parent) 
    : QWidget(parent)
    , m_checkBox(new QCheckBox(this))
    , m_textVisible(true)
{
    QHBoxLayout *lt = new QHBoxLayout;
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        lt->setContentsMargins(4, 0, 0, 0);
    else
        lt->setContentsMargins(0, 0, 4, 0);
    lt->addWidget(m_checkBox);
    setLayout(lt);
    connect(m_checkBox, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
    setFocusProxy(m_checkBox);
    m_checkBox->setText(tr("True"));
}

void BoolEdit::setTextVisible(bool textVisible)
{
    if (m_textVisible == textVisible)
        return;

    m_textVisible = textVisible;
    if (m_textVisible)
        m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
    else
        m_checkBox->setText(QString());
}

Qt::CheckState BoolEdit::checkState() const
{
    return m_checkBox->checkState();
}

void BoolEdit::setCheckState(Qt::CheckState state)
{
    m_checkBox->setCheckState(state);
}

bool BoolEdit::isChecked() const
{
    return m_checkBox->isChecked();
}

void BoolEdit::setChecked(bool c)
{
    m_checkBox->setChecked(c);
    if (!m_textVisible)
        return;
    m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
}

bool BoolEdit::blockCheckBoxSignals(bool block)
{
    return m_checkBox->blockSignals(block);
}

void BoolEdit::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) 
    {
        m_checkBox->click();
        event->accept();
    } 
    else 
    {
        QWidget::mousePressEvent(event);
    }
}

} // namespace QtVision
} // namespace VSN
