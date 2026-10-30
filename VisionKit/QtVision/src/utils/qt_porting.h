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

#ifndef __QT_PORTING_H
#define __QT_PORTING_H

#ifdef QT_GUI_LIB
#include <QEnterEvent>
#endif
#include <QString>

namespace VSN {
namespace QtVision {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using QHashValueType = uint;
#else
using QHashValueType = size_t;
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using QtSizeType = int;
#else
using QtSizeType = qsizetype;
#endif

// StringView - either QStringRef or QStringView
// Can be used where it is not possible to completely switch to QStringView
// For example where QString::splitRef / QStringView::split is essential.
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using StringView = QStringRef;
#else
using StringView = QStringView;
#endif

inline StringView make_stringview(const QString &s)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return QStringRef(&s);
#else
    return QStringView(s);
#endif
}

// QStringView::mid in Qt5 does not do bounds checking, in Qt6 it does
inline QStringView midView(const QString &s, int offset, int length = -1)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    const int size = s.size();
    if (offset > size)
        return {};
    if (offset < 0) {
        if (length < 0 || length + offset >= size)
            return QStringView(s);
        if (length + offset <= 0)
            return {};
        return QStringView(s).left(length + offset);
    } else if (length < 0 || length > size - offset)
        return QStringView(s).mid(offset);
    return QStringView(s).mid(offset, length);
#else
    return QStringView(s).mid(offset, length);
#endif
}

#ifdef QT_GUI_LIB
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using EnterEvent = QEvent;
#else
using EnterEvent = QEnterEvent;
#endif
#endif

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PORTING_H */
