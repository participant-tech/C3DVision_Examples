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

#ifndef __QT_NAMEVALUEDICTIONARY_H
#define __QT_NAMEVALUEDICTIONARY_H

#include <qt_hostosinfo.h>
#include <qt_namevalueitem.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class DictKey
{
public:
    DictKey(const QString &name, Qt::CaseSensitivity cs) : name(name), caseSensitivity(cs) {}

    friend bool operator==(const DictKey &k1, const DictKey &k2)
    {
        return k1.name.compare(k2.name, k1.caseSensitivity) == 0;
    }

    QString name;
    Qt::CaseSensitivity caseSensitivity;
};
inline bool operator<(const DictKey &k1, const DictKey &k2)
{
    return k1.name.compare(k2.name, k1.caseSensitivity) < 0;
}
inline bool operator>(const DictKey &k1, const DictKey &k2) { return k2 < k1; }

using NameValuePair = std::pair<QString, QString>;
using NameValuePairs = QVector<NameValuePair>;
using NameValueMap = QMap<DictKey, QPair<QString, bool>>;

class NameValueDictionary
{
public:
    using const_iterator = NameValueMap::const_iterator;

    explicit NameValueDictionary(OsType osType = HostOsInfo::hostOs())
        : m_osType(osType)
    {}
    explicit NameValueDictionary(const QStringList &env, OsType osType = HostOsInfo::hostOs());
    explicit NameValueDictionary(const NameValuePairs &nameValues);

    QStringList toStringList() const;
    QString value(const QString &key) const;
    void set(const QString &key, const QString &value, bool enabled = true);
    void unset(const QString &key);
    void modify(const NameValueItems &items);
    /// Return the KeyValueDictionary changes necessary to modify this into the other environment.
    NameValueItems diff(const NameValueDictionary &other, bool checkAppendPrepend = false) const;
    bool hasKey(const QString &key) const;
    OsType osType() const;
    Qt::CaseSensitivity nameCaseSensitivity() const;

    QString userName() const;

    void clear();
    int size() const;

    QString key(const_iterator it) const { return it.key().name; }
    QString value(const_iterator it) const { return it.value().first; }
    bool isEnabled(const_iterator it) const { return it.value().second; }

    const_iterator constBegin() const { return m_values.constBegin(); }
    const_iterator constEnd() const { return m_values.constEnd(); }
    const_iterator constFind(const QString &name) const;

    friend bool operator!=(const NameValueDictionary &first, const NameValueDictionary &second)
    {
        return !(first == second);
    }

    friend bool operator==(const NameValueDictionary &first, const NameValueDictionary &second)
    {
        return first.m_osType == second.m_osType && first.m_values == second.m_values;
    }

protected:
    friend class Environment;
    NameValueMap::iterator findKey(const QString &key);
    const_iterator findKey(const QString &key) const;

    NameValueMap m_values;
    OsType m_osType;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_NAMEVALUEDICTIONARY_H */
