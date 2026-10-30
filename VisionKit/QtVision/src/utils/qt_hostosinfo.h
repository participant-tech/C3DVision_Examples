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
#ifndef __QT_HOSTOSINFO_H
#define __QT_HOSTOSINFO_H

#include <qnamespace.h>
#include <qt_osspecificaspects.h>

#include <optional>
#include <qt_global.h>

class QString;

#ifdef Q_OS_WIN
#define QTC_HOST_EXE_SUFFIX QTC_WIN_EXE_SUFFIX
#else
#define QTC_HOST_EXE_SUFFIX ""
#endif // Q_OS_WIN

namespace VSN {
namespace QtVision {

/* HostOsInfo */
class QT_CLASS HostOsInfo
{
public:
    static constexpr OsType hostOs()
    {
#if defined(Q_OS_WIN)
        return OsTypeWindows;
#elif defined(Q_OS_LINUX)
        return OsTypeLinux;
#elif defined(Q_OS_MAC)
        return OsTypeMac;
#elif defined(Q_OS_UNIX)
        return OsTypeOtherUnix;
#else
        return OsTypeOther;
#endif
    }

    enum HostArchitecture { HostArchitectureX86, HostArchitectureAMD64, HostArchitectureItanium,
                            HostArchitectureArm, HostArchitectureArm64, HostArchitectureUnknown };
    static HostArchitecture hostArchitecture();

    static constexpr bool isWindowsHost() { return hostOs() == OsTypeWindows; }
    static constexpr bool isLinuxHost() { return hostOs() == OsTypeLinux; }
    static constexpr bool isMacHost() { return hostOs() == OsTypeMac; }
    static constexpr bool isAnyUnixHost()
    {
#ifdef Q_OS_UNIX
        return true;
#else
        return false;
#endif
    }

    static bool isRunningUnderRosetta();

    static QString withExecutableSuffix(const QString &executable)
    {
        return OsSpecificAspects::withExecutableSuffix(hostOs(), executable);
    }

    static void setOverrideFileNameCaseSensitivity(Qt::CaseSensitivity sensitivity);
    static void unsetOverrideFileNameCaseSensitivity();

    static Qt::CaseSensitivity fileNameCaseSensitivity()
    {
        return m_useOverrideFileNameCaseSensitivity
                ? m_overrideFileNameCaseSensitivity
                : OsSpecificAspects::fileNameCaseSensitivity(hostOs());
    }

    static constexpr QChar pathListSeparator()
    {
        return OsSpecificAspects::pathListSeparator(hostOs());
    }

    static constexpr Qt::KeyboardModifier controlModifier()
    {
        return OsSpecificAspects::controlModifier(hostOs());
    }

    static bool canCreateOpenGLContext(QString *errorMessage);

    static std::optional<vuint64> totalMemoryInstalledInBytes();

private:
    static Qt::CaseSensitivity m_overrideFileNameCaseSensitivity;
    static bool m_useOverrideFileNameCaseSensitivity;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_HOSTOSINFO_H */
