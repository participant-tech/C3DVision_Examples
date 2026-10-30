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

#ifndef __QT_ENVIRONMENT_H
#define __QT_ENVIRONMENT_H

#include <qt_environmentfwd.h>
#include <qt_filepath.h>
#include <qt_hostosinfo.h>
#include <qt_namevaluedictionary.h>
#include <qt_optional.h>

#include <functional>

QT_BEGIN_NAMESPACE
class QProcessEnvironment;
QT_END_NAMESPACE

namespace VSN {
namespace QtVision {

class Environment final
{
public:
    Environment() : m_dict(HostOsInfo::hostOs()) {}
    explicit Environment(OsType osType) : m_dict(osType) {}
    explicit Environment(const QStringList &env, OsType osType = HostOsInfo::hostOs())
        : m_dict(env, osType) {}
    explicit Environment(const NameValuePairs &nameValues) : m_dict(nameValues) {}
    explicit Environment(const NameValueDictionary &dict) : m_dict(dict) {}

    QString value(const QString &key) const { return m_dict.value(key); }
    bool hasKey(const QString &key) const { return m_dict.hasKey(key); }

    void set(const QString &key, const QString &value, bool enabled = true) { m_dict.set(key, value, enabled); }
    void unset(const QString &key) { m_dict.unset(key); }
    void modify(const NameValueItems &items) { m_dict.modify(items); }

    int isValid() const;
    void clear() { return m_dict.clear(); }

    QStringList toStringList() const { return m_dict.toStringList(); }
    QProcessEnvironment toProcessEnvironment() const;

    void appendOrSet(const QString &key, const QString &value, const QString &sep = QString());
    void prependOrSet(const QString &key, const QString &value, const QString &sep = QString());

    void appendOrSetPath(const FilePath &value);
    void prependOrSetPath(const FilePath &value);

    void prependOrSetLibrarySearchPath(const FilePath &value);
    void prependOrSetLibrarySearchPaths(const FilePaths &values);

    void setupEnglishOutput();

    using PathFilter = std::function<bool(const FilePath &)>;
    FilePath searchInPath(const QString &executable,
                          const FilePaths &additionalDirs = FilePaths(),
                          const PathFilter &func = PathFilter()) const;
    FilePath searchInDirectories(const QString &executable,
                                 const FilePaths &dirs) const;
    FilePaths findAllInPath(const QString &executable,
                               const FilePaths &additionalDirs = FilePaths(),
                               const PathFilter &func = PathFilter()) const;

    FilePaths path() const;
    FilePaths pathListValue(const QString &varName) const;
    QStringList appendExeExtensions(const QString &executable) const;

    bool isSameExecutable(const QString &exe1, const QString &exe2) const;

    QString expandedValueForKey(const QString &key) const;
    QString expandVariables(const QString &input) const;
    FilePath expandVariables(const FilePath &input) const;
    QStringList expandVariables(const QStringList &input) const;

    OsType osType() const { return m_dict.osType(); }
    QString userName() const;

    using const_iterator = NameValueMap::const_iterator; // FIXME: avoid
    NameValueDictionary toDictionary() const { return m_dict; } // FIXME: avoid
    NameValueItems diff(const Environment &other, bool checkAppendPrepend = false) const; // FIXME: avoid

    QString key(const_iterator it) const { return m_dict.key(it); } // FIXME: avoid
    QString value(const_iterator it) const { return m_dict.value(it); } // FIXME: avoid
    bool isEnabled(const_iterator it) const { return m_dict.isEnabled(it); } // FIXME: avoid

    const_iterator constBegin() const { return m_dict.constBegin(); } // FIXME: avoid
    const_iterator constEnd() const { return m_dict.constEnd(); } // FIXME: avoid
    const_iterator constFind(const QString &name) const { return m_dict.constFind(name); } // FIXME: avoid

    friend bool operator!=(const Environment &first, const Environment &second)
    {
        return first.m_dict != second.m_dict;
    }

    friend bool operator==(const Environment &first, const Environment &second)
    {
        return first.m_dict == second.m_dict;
    }

    static Environment systemEnvironment();

    static void modifySystemEnvironment(const EnvironmentItems &list); // use with care!!!
    static void setSystemEnvironment(const Environment &environment);  // don't use at all!!!

private:
    NameValueDictionary m_dict;
};

class EnvironmentChange final
{
public:
    EnvironmentChange() = default;

    class Item final
    {
    public:
        enum Type {
            SetSystemEnvironment,
            SetFixedEnvironment,
            SetValue,
            UnsetValue,
            PrependToPath,
            AppendToPath,
        };

        Type type;
        QVariant data;
    };

    static EnvironmentChange fromFixedEnvironment(const Environment &fixedEnv);

    void applyToEnvironment(Environment &) const;

    void addSetValue(const QString &key, const QString &value);
    void addUnsetValue(const QString &key);
    void addPrependToPath(const FilePaths &values);
    void addAppendToPath(const FilePaths &values);

private:
    QList<Item> m_changeItems;
};

class EnvironmentProvider
{
public:
    QByteArray id;
    QString displayName;
    std::function<Environment()> environment;

    static void addProvider(EnvironmentProvider &&provider);
    static const QVector<EnvironmentProvider> providers();
    static optional<EnvironmentProvider> provider(const QByteArray &id);
};

} // namespace QtVision
} // namespace VSN

Q_DECLARE_METATYPE(VSN::QtVision::Environment)

#endif /* __QT_ENVIRONMENT_H */
