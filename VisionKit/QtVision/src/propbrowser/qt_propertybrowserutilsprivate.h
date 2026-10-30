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

#ifndef __VSN_PROPERTYBROWSERUTILS_H
#define __VSN_PROPERTYBROWSERUTILS_H

#include <QtCore/QMap>
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>
#include <QtCore/QStringList>
#include <vsn_global.h>

class QMouseEvent;
class QCheckBox;
class QLineEdit;

namespace VSN {
namespace QtVision {

/* CursorDatabase */
class CursorDatabase
{
public:
    CursorDatabase();
public:
    void clear();
    QStringList cursorShapeNames() const;
    QMap<int, QIcon> cursorShapeIcons() const;
    QString cursorToShapeName(const QCursor& cursor) const;
    QIcon cursorToShapeIcon(const QCursor& cursor) const;
    int cursorToValue(const QCursor& cursor) const;
#ifndef QT_NO_CURSOR
    QCursor valueToCursor(int value) const;
#endif
private:
    void appendCursor(Qt::CursorShape shape, const QString& name, const QIcon& icon);
    QStringList m_cursorNames;
    QMap<int, QIcon> m_cursorIcons;
    QMap<int, Qt::CursorShape> m_valueToCursorShape;
    QMap<Qt::CursorShape, int> m_cursorShapeToValue;
};

/* PropBrowserUtils */
class PropBrowserUtils
{
public:
    static QPixmap brushValuePixmap(const QBrush& b);
    static QIcon brushValueIcon(const QBrush& b);
    static QString colorValueText(const QColor& c);
    static QPixmap fontValuePixmap(const QFont& f);
    static QIcon fontValueIcon(const QFont& f);
    static QString fontValueText(const QFont& f);
    static QString dateFormat();
    static QString timeFormat();
    static QString dateTimeFormat();
};

/* BoolEdit */
class BoolEdit : public QWidget 
{
    Q_OBJECT
public:
    BoolEdit(QWidget* parent = nullptr);
public:
    bool textVisible() const { return m_textVisible; }
    void setTextVisible(bool textVisible);

    Qt::CheckState checkState() const;
    void setCheckState(Qt::CheckState state);

    bool isChecked() const;
    void setChecked(bool c);

    bool blockCheckBoxSignals(bool block);
Q_SIGNALS:
    void toggled(bool);
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
private:
    QCheckBox* m_checkBox;
    bool m_textVisible;
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_PROPERTYBROWSERUTILS_H */
