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

///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_ID_H
#define __QT_ID_H

#include <QList>
#include <QMetaType>
#include <QString>

#include <qt_global.h>

namespace VSN {
namespace QtVision {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using QHashValueType = uint;
#else
using QHashValueType = size_t;
#endif

class QT_CLASS Id
{
public:
    Id() = default;
    Id(const char* name); // Good to use.
    Id(const QLatin1String&) = delete;
public:

    Id withSuffix(int suffix) const;
    Id withSuffix(const char* suffix) const;
    Id withSuffix(const QString& suffix) const;
    Id withPrefix(const char* prefix) const;

    QByteArray name() const;
    QString toString() const; // Avoid.
    QVariant toSetting() const; // Good to use.
    QString suffixAfter(Id baseId) const;
    bool isValid() const { return m_id; }

    quintptr uniqueIdentifier() const { return m_id; } // Avoid.
    static Id fromSetting(const QVariant& variant); // Good to use.

    bool operator == (Id id) const { return m_id == id.m_id; }
    bool operator == (const char* name) const;
    bool operator != (Id id) const { return m_id != id.m_id; }
    bool operator != (const char* name) const { return !operator==(name); }
    bool operator < (Id id) const { return m_id < id.m_id; }
    bool operator > (Id id) const { return m_id > id.m_id; }
    bool alphabeticallyBefore(Id other) const;

    friend QHashValueType qHash(Id id) { return static_cast<QHashValueType>(id.uniqueIdentifier()); }
private:
    explicit Id(quintptr uid) : m_id(uid) {}
    quintptr m_id = 0;
};


} // namespace QtVision
} // namespace VSN

#endif /* __QT_ID_H */

