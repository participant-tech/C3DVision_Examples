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

#ifndef __QT_MACROEXPANDER_H
#define __QT_MACROEXPANDER_H

#include <QCoreApplication>
#include <QList>
#include <QVector>

#include <functional>

namespace VSN {
namespace QtVision {

class MacroExpanderPrivate;

class FilePath;
class MacroExpander;
using MacroExpanderProvider = std::function<MacroExpander *()>;
using MacroExpanderProviders = QVector<MacroExpanderProvider>;

class MacroExpander
{
    Q_DECLARE_TR_FUNCTIONS(Utils::MacroExpander)
    Q_DISABLE_COPY(MacroExpander)
public:
    explicit MacroExpander();
    ~MacroExpander();
public:
    bool resolveMacro(const QString &name, QString *ret) const;

    QString value(const QByteArray &variable, bool *found = nullptr) const;

    QString expand(const QString &stringWithVariables) const;
    FilePath expand(const FilePath &fileNameWithVariables) const;
    QByteArray expand(const QByteArray &stringWithVariables) const;
    QVariant expandVariant(const QVariant &v) const;

    QString expandProcessArgs(const QString &argsWithVariables) const;

    using PrefixFunction = std::function<QString(QString)>;
    using ResolverFunction = std::function<bool(QString, QString *)>;
    using StringFunction = std::function<QString()>;
    using FileFunction = std::function<FilePath()>;
    using IntFunction = std::function<int()>;

    void registerPrefix(const QByteArray &prefix,
        const QString &description, const PrefixFunction &value, bool visible = true);

    void registerVariable(const QByteArray &variable,
        const QString &description, const StringFunction &value,
        bool visibleInChooser = true);

    void registerIntVariable(const QByteArray &variable,
        const QString &description, const IntFunction &value);

    void registerFileVariables(const QByteArray &prefix,
        const QString &heading, const FileFunction &value,
        bool visibleInChooser = true);

    void registerExtraResolver(const ResolverFunction &value);

    QList<QByteArray> visibleVariables() const;
    QString variableDescription(const QByteArray &variable) const;
    bool isPrefixVariable(const QByteArray &variable) const;

    MacroExpanderProviders subProviders() const;

    QString displayName() const;
    void setDisplayName(const QString &displayName);

    void registerSubProvider(const MacroExpanderProvider &provider);

    bool isAccumulating() const;
    void setAccumulating(bool on);

private:
    friend class MacroExpanderPrivate;
    MacroExpanderPrivate *d;
};

MacroExpander* globalMacroExpander();

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MACROEXPANDER_H */
