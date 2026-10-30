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

#ifndef __QT_OSSPECIFICASPECTS_H
#define __QT_OSSPECIFICASPECTS_H

#include <QString>

#include <algorithm>

#define QTC_WIN_EXE_SUFFIX ".exe"

namespace VSN {
namespace QtVision {

// Add more as needed.
enum OsType { OsTypeWindows, OsTypeLinux, OsTypeMac, OsTypeOtherUnix, OsTypeOther };


inline QString withExecutableSuffix(OsType osType, const QString &executable)
{
    QString finalName = executable;
    if (osType == OsTypeWindows && !finalName.endsWith(QTC_WIN_EXE_SUFFIX))
        finalName += QLatin1String(QTC_WIN_EXE_SUFFIX);
    return finalName;
}

inline Qt::CaseSensitivity fileNameCaseSensitivity(OsType osType)
{
    return osType == OsTypeWindows || osType == OsTypeMac ? Qt::CaseInsensitive : Qt::CaseSensitive;
}

inline Qt::CaseSensitivity envVarCaseSensitivity(OsType osType)
{
    return fileNameCaseSensitivity(osType);
}

inline QChar pathListSeparator(OsType osType)
{
    return QLatin1Char(osType == OsTypeWindows ? ';' : ':');
}

inline Qt::KeyboardModifier controlModifier(OsType osType)
{
    return osType == OsTypeMac ? Qt::MetaModifier : Qt::ControlModifier;
}

inline QString pathWithNativeSeparators(OsType osType, const QString &pathName)
{
    if (osType == OsTypeWindows) {
        const int pos = pathName.indexOf('/');
        if (pos >= 0) {
            QString n = pathName;
            std::replace(std::begin(n) + pos, std::end(n), '/', '\\');
            return n;
        }
    } else {
        const int pos = pathName.indexOf('\\');
        if (pos >= 0) {
            QString n = pathName;
            std::replace(std::begin(n) + pos, std::end(n), '\\', '/');
            return n;
        }
    }
    return pathName;
}

} // namespace OsSpecificAspects
} // namespace Utils

#endif /* __QT_OSSPECIFICASPECTS_H */
