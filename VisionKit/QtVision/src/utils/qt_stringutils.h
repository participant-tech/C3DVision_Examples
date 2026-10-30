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

#ifndef __QT_STRINGUTILS_H
#define __QT_STRINGUTILS_H

#include <QList>
#include <QString>

#include <functional>

QT_BEGIN_NAMESPACE
class QJsonValue;
QT_END_NAMESPACE

namespace VSN {
namespace QtVision {

// Create a usable settings key from a category,
// for example Editor|C++ -> Editor_C__
QString settingsKey(const QString &category);

// Return the common prefix part of a string list:
// "C:\foo\bar1" "C:\foo\bar2"  -> "C:\foo\bar"
QString commonPrefix(const QStringList &strings);

// Return the common path of a list of files:
// "C:\foo\bar1" "C:\foo\bar2"  -> "C:\foo"
//QString commonPath(const QStringList &files);

// On Linux/Mac replace user's home path with ~
// Uses cleaned path and tries to use absolute path of "path" if possible
// If path is not sub of home path, or when running on Windows, returns the input
QString withTildeHomePath(const QString &path);

// Removes first unescaped ampersand in text
QString stripAccelerator(const QString &text);
// Quotes all ampersands
QString quoteAmpersands(const QString &text);

bool readMultiLineString(const QJsonValue &value, QString *out);

// Compare case insensitive and use case sensitive comparison in case of that being equal.
int caseFriendlyCompare(const QString &a, const QString &b);

class AbstractMacroExpander
{
public:
    virtual ~AbstractMacroExpander() {}
    // Not const, as it may change the state of the expander.
    //! Find an expando to replace and provide a replacement string.
    //! \param str The string to scan
    //! \param pos Position to start scan on input, found position on output
    //! \param ret Replacement string on output
    //! \return Length of string part to replace, zero if no (further) matches found
    virtual int findMacro(const QString &str, int *pos, QString *ret);
    //! Provide a replacement string for an expando
    //! \param name The name of the expando
    //! \param ret Replacement string on output
    //! \return True if the expando was found
    virtual bool resolveMacro(const QString &name, QString *ret, QSet<AbstractMacroExpander *> &seen) = 0;
private:
    bool expandNestedMacros(const QString &str, int *pos, QString *ret);
};

void expandMacros(QString *str, AbstractMacroExpander *mx);
QString expandMacros(const QString &str, AbstractMacroExpander *mx);

int parseUsedPortFromNetstatOutput(const QByteArray &line);

template<typename T>
T makeUniquelyNumbered(const T &preferred, const std::function<bool(const T &)> &isOk)
{
    if (isOk(preferred))
        return preferred;
    int i = 2;
    T tryName = preferred + QString::number(i);
    while (!isOk(tryName))
        tryName = preferred + QString::number(++i);
    return tryName;
}

template<typename T, typename Container>
T makeUniquelyNumbered(const T &preferred, const Container &reserved)
{
    const std::function<bool(const T &)> isOk
            = [&reserved](const T &v) { return !reserved.contains(v); };
    return makeUniquelyNumbered(preferred, isOk);
}

QString formatElapsedTime(qint64 elapsed);

/* This function is only necessary if you need to match the wildcard expression against a
 * string that might contain path separators - otherwise
 * QRegularExpression::wildcardToRegularExpression() can be used.
 * Working around QRegularExpression::wildcardToRegularExpression() taking native separators
 * into account and handling them to disallow matching a wildcard characters.
 */
QString wildcardToRegularExpression(const QString &original);

QString languageNameFromLanguageCode(const QString &languageCode);


#ifdef QT_WIDGETS_LIB

// Feeds the global clipboard and, when present, the primary selection
void setClipboardAndSelection(const QString &text);

#endif

} // namespace QtVision
} // namespace VSN

#endif /* __QT_COMMAND_H */
