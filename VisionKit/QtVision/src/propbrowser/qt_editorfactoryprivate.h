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

#ifndef __VSN_EDITORFACTORYPRIVATE_H
#define __VSN_EDITORFACTORYPRIVATE_H

#include <QWidget>
#include <QColor>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QToolButton>
#include <vsn_global.h>

namespace VSN {
namespace QtVision {

/* ColorEditWidget */
class ColorEditWidget : public QWidget
{
    Q_OBJECT
public:
    ColorEditWidget(QWidget* parent);
public:
    bool eventFilter(QObject* obj, QEvent* ev);
public Q_SLOTS:
    void setValue(const QColor& value);
private Q_SLOTS:
    void buttonClicked();
Q_SIGNALS:
    void valueChanged(const QColor& value);
private:
    QColor m_color;
    QLabel* m_pixmapLabel;
    QLabel* m_label;
    QToolButton* m_button;
};

/* QtCharEdit */
class QtCharEdit : public QWidget
{
    Q_OBJECT
public:
    QtCharEdit(QWidget* parent = 0);

    QChar value() const;
    bool eventFilter(QObject* o, QEvent* e);
public Q_SLOTS:
    void setValue(const QChar& value);
Q_SIGNALS:
    void valueChanged(const QChar& value);
protected:
    void focusInEvent(QFocusEvent* e);
    void focusOutEvent(QFocusEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    bool event(QEvent* e);
private slots:
    void slotClearChar();
private:
    void handleKeyEvent(QKeyEvent* e);
private:
    QChar m_value;
    QLineEdit* m_lineEdit;
};

/* FontEditWidget */
class FontEditWidget : public QWidget
{
    Q_OBJECT
public:
    FontEditWidget(QWidget* parent);
public:
    bool eventFilter(QObject* obj, QEvent* ev);
public Q_SLOTS:
    void setValue(const QFont& value);
private Q_SLOTS:
    void buttonClicked();
Q_SIGNALS:
    void valueChanged(const QFont& value);
private:
    QFont m_font;
    QLabel* m_pixmapLabel;
    QLabel* m_label;
    QToolButton* m_button;
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_EDITORFACTORYPRIVATE_H */
