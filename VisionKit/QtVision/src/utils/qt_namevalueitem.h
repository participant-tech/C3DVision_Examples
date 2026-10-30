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

#ifndef __QT_NAMEVALUEITEM_H
#define __QT_NAMEVALUEITEM_H

#include <qt_environmentfwd.h>

#include <QStringList>
#include <QVariantList>
#include <QVector>

namespace VSN {
namespace QtVision {

class NameValueItem
{
public:
    enum Operation : char { SetEnabled, Unset, Prepend, Append, SetDisabled };
    NameValueItem() = default;
    NameValueItem(const QString &key, const QString &value, Operation operation = SetEnabled)
        : name(key)
        , value(value)
        , operation(operation)
    {}

    void apply(NameValueDictionary *dictionary) const { apply(dictionary, operation); }

    static void sort(NameValueItems *list);
    static NameValueItems fromStringList(const QStringList &list);
    static QStringList toStringList(const NameValueItems &list);
    static NameValueItems itemsFromVariantList(const QVariantList &list);
    static QVariantList toVariantList(const NameValueItems &list);
    static NameValueItem itemFromVariantList(const QVariantList &list);
    static QVariantList toVariantList(const NameValueItem &item);

    friend bool operator==(const NameValueItem &first, const NameValueItem &second)
    {
        return first.operation == second.operation && first.name == second.name
               && first.value == second.value;
    }
    friend bool operator!=(const NameValueItem &first, const NameValueItem &second)
    {
        return !(first == second);
    }

    friend QDebug operator<<(QDebug debug, const NameValueItem &i);

public:
    QString name;
    QString value;
    Operation operation = Unset;

private:
    void apply(NameValueDictionary *dictionary, Operation op) const;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_NAMEVALUEITEM_H */
