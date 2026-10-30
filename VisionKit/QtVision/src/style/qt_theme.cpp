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

#include <qt_theme.h>
#include <qt_hostosinfo.h>

#include <QApplication>
#include <QMetaEnum>
#include <QPalette>
#include <QSettings>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

static Theme* m_pVisionTheme = nullptr;

class ThemePrivate
{
public:
    ThemePrivate();

    QString id;
    QString fileName;
    QString displayName;
    QStringList preferredStyles;
    QString defaultTextEditorColorScheme;
    QString enforceAccentColorOnMacOS;
    QVector<QPair<QColor, QString> > colors;
    QVector<QString> imageFiles;
    QVector<bool> flags;
    QMap<QString, QColor> palette;
};

ThemePrivate::ThemePrivate()
{
    const QMetaObject& m = Theme::staticMetaObject;
    colors.resize        (m.enumerator(m.indexOfEnumerator("Color")).keyCount());
    imageFiles.resize    (m.enumerator(m.indexOfEnumerator("ImageFile")).keyCount());
    flags.resize         (m.enumerator(m.indexOfEnumerator("Flag")).keyCount());
}

QT_FUNC(Theme*) visionTheme()
{
    return m_pVisionTheme;
}

QT_FUNC(Theme*) proxyTheme()
{
    return new Theme(m_pVisionTheme);
}

void setThemeApplicationPalette()
{
    if (m_pVisionTheme && m_pVisionTheme->flag(Theme::ApplyThemePaletteGlobally))
        QApplication::setPalette(m_pVisionTheme->palette());
}

static void setMacAppearance(Theme *theme)
{
#ifdef Q_OS_MACOS
    // Сопоставить собственную тему и палитру UI с создателем.Тема
    //  задает светло-голубой цвет для тем Light Vision и
    //  цвет морской волны для темных тем.
    if (theme)
        Internal::forceMacAppearance(theme->flag(Theme::DarkUserInterface));
#else
    Q_UNUSED(theme)
#endif
}

static bool macOSSystemIsDark()
{
#ifdef Q_OS_MACOS
    static bool systemIsDark = Internal::currentAppearanceIsDark();
    return systemIsDark;
#else
    return false;
#endif
}

QT_FUNC(void) setVisionTheme(Theme* theme)
{
    if (m_pVisionTheme == theme)
        return;
    delete m_pVisionTheme;
    m_pVisionTheme = theme;

    setMacAppearance(theme);
    setThemeApplicationPalette();
}

QT_FUNC(void) clearVisionTheme()
{
    VSN_DELETE_AND_NULL(m_pVisionTheme);
}

/* Theme */
Theme::Theme(const QString& id, QObject* parent)
  : QObject(parent)
  , d(new ThemePrivate)
{
    d->id = id;
}

/* Theme */
Theme::Theme(Theme* originTheme, QObject* parent)
    : QObject(parent)
    , d(new ThemePrivate(*(originTheme->d)))
{
}

Theme::~Theme()
{
    delete d;
}

QStringList Theme::preferredStyles() const
{
    // Применить стиль Fusion, если темная тема в Windows или Linux,
    // потому что QStyle по умолчанию может не подойти для нее.
    if (!HostOsInfo::isMacHost() && d->preferredStyles.isEmpty() && flag(DarkUserInterface))
        return {"Fusion"};
    return d->preferredStyles;
}

QString Theme::defaultTextEditorColorScheme() const
{
    return d->defaultTextEditorColorScheme;
}

QString Theme::id() const
{
    return d->id;
}

bool Theme::flag(Theme::Flag f) const
{
    return d->flags[f];
}

QColor Theme::color(Theme::Color role) const
{
    const auto color = d->colors[role];
    if (HostOsInfo::isMacHost() && !d->enforceAccentColorOnMacOS.isEmpty()
        && color.second == d->enforceAccentColorOnMacOS)
        return initialPalette().color(QPalette::Highlight);
    return d->colors[role].first;
}

QString Theme::imageFile(Theme::ImageFile imageFile, const QString &fallBack) const
{
    const QString &file = d->imageFiles.at(imageFile);
    return file.isEmpty() ? fallBack : file;
}

QPair<QColor, QString> Theme::readNamedColor(const QString &color) const
{
    const auto it = d->palette.constFind(color);
    if (it != d->palette.constEnd())
        return {it.value(), color};
    if (color == QLatin1String("style"))
        return {};

    const QColor col('#' + color);
    if (!col.isValid())
    {
        qWarning("Color \"%s\" is neither a named color nor a valid color", qPrintable(color));
        return {Qt::black, {}};
    }
    return {col, {}};
}

//---------------------------------------------------------------------------------------
//
// ---
QString Theme::filePath() const { return d->fileName; }

QString Theme::displayName() const
{
    return d->displayName;
}

//---------------------------------------------------------------------------------------
//
// ---
void Theme::setDisplayName(const QString& name) { d->displayName = name;}

//---------------------------------------------------------------------------------------
//
// ---
void Theme::readSettings(QSettings& settings)
{
    d->fileName = settings.fileName();
    const QMetaObject& m = *metaObject();

    {
        d->displayName = settings.value(QLatin1String("ThemeName"), QLatin1String("unnamed")).toString();
        d->preferredStyles = settings.value(QLatin1String("PreferredStyles")).toStringList();
        d->preferredStyles.removeAll(QString());
        d->defaultTextEditorColorScheme =
                settings.value(QLatin1String("DefaultTextEditorColorScheme")).toString();
        d->enforceAccentColorOnMacOS = settings.value("EnforceAccentColorOnMacOS").toString();
    }
    {
        settings.beginGroup(QLatin1String("Palette"));
        const QStringList allKeys = settings.allKeys();
        for (const QString &key : allKeys)
            d->palette[key] = readNamedColor(settings.value(key).toString()).first;
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("Colors"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("Color"));
        for (int i = 0, total = e.keyCount(); i < total; ++i)
        {
            const QString key = QLatin1String(e.key(i));
            if (!settings.contains(key))
            {
                if (i < PaletteWindow || i > PalettePlaceholderTextDisabled)
                    qWarning("Theme \"%s\" misses color setting for key \"%s\".",
                             qPrintable(d->fileName), qPrintable(key));
                continue;
            }
            d->colors[i] = readNamedColor(settings.value(key).toString());
        }
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("ImageFiles"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("ImageFile"));
        for (int i = 0, total = e.keyCount(); i < total; ++i)
        {
            const QString key = QLatin1String(e.key(i));
            d->imageFiles[i] = settings.value(key).toString();
        }
        settings.endGroup();
    }
    {
        settings.beginGroup(QLatin1String("Flags"));
        QMetaEnum e = m.enumerator(m.indexOfEnumerator("Flag"));
        for (int i = 0, total = e.keyCount(); i < total; ++i)
        {
            const QString key = QLatin1String(e.key(i));
            QTV_ASSERT(settings.contains(key), return);;
            d->flags[i] = settings.value(key).toBool();
        }
        settings.endGroup();
    }
}

//---------------------------------------------------------------------------------------
//
// ---
bool Theme::systemUsesDarkMode()
{
    if (HostOsInfo::isWindowsHost())
    {
        constexpr char regkey[]
            = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
        bool ok;
        const int setting = QSettings(regkey, QSettings::NativeFormat).value("AppsUseLightTheme").toInt(&ok);
        return ok && setting == 0;
    }

    if (HostOsInfo::isMacHost())
        return macOSSystemIsDark();

    return false;
}

//---------------------------------------------------------------------------------------
// Если копируется QPalette, то значения по умолчанию остаются такими же,
// даже если эти значения по умолчанию различаются в контексте разных виджетов.
// Создать полную копию.
// ---
static QPalette copyPalette(const QPalette &p)
{
    QPalette res;
    for (int group = 0; group < QPalette::NColorGroups; ++group)
    {
        for (int role = 0; role < QPalette::NColorRoles; ++role)
        {
            res.setBrush(QPalette::ColorGroup(group),
                         QPalette::ColorRole(role),
                         p.brush(QPalette::ColorGroup(group), QPalette::ColorRole(role)));
        }
    }
    return res;
}

//---------------------------------------------------------------------------------------
//
// ---
void Theme::setInitialPalette(Theme* initTheme)
{
    macOSSystemIsDark(); // инициализировать значение для системного режима
    setMacAppearance(initTheme);
    initialPalette();
}

//---------------------------------------------------------------------------------------
//
// ---
void Theme::setHelpMenu(QMenu* menu)
{
#ifdef Q_OS_MACOS
    Internal::setMacOSHelpMenu(menu);
#else
    Q_UNUSED(menu)
#endif
}

//---------------------------------------------------------------------------------------
//
// ---
QPalette Theme::initialPalette()
{
    static QPalette palette = copyPalette(QApplication::palette());
    return palette;
}

//---------------------------------------------------------------------------------------
//
// ---
QPalette Theme::palette() const
{
    QPalette pal = initialPalette();
    if (!flag(DerivePaletteFromTheme))
        return pal;

    const static struct 
    {
        Color themeColor;
        QPalette::ColorRole paletteColorRole;
        QPalette::ColorGroup paletteColorGroup;
        bool setColorRoleAsBrush;
    } mapping[] = {
        {PaletteWindow,                    QPalette::Window,           QPalette::All,      false},
        {PaletteWindowDisabled,            QPalette::Window,           QPalette::Disabled, false},
        {PaletteWindowText,                QPalette::WindowText,       QPalette::All,      true},
        {PaletteWindowTextDisabled,        QPalette::WindowText,       QPalette::Disabled, true},
        {PaletteBase,                      QPalette::Base,             QPalette::All,      false},
        {PaletteBaseDisabled,              QPalette::Base,             QPalette::Disabled, false},
        {PaletteAlternateBase,             QPalette::AlternateBase,    QPalette::All,      false},
        {PaletteAlternateBaseDisabled,     QPalette::AlternateBase,    QPalette::Disabled, false},
        {PaletteToolTipBase,               QPalette::ToolTipBase,      QPalette::All,      true},
        {PaletteToolTipBaseDisabled,       QPalette::ToolTipBase,      QPalette::Disabled, true},
        {PaletteToolTipText,               QPalette::ToolTipText,      QPalette::All,      false},
        {PaletteToolTipTextDisabled,       QPalette::ToolTipText,      QPalette::Disabled, false},
        {PaletteText,                      QPalette::Text,             QPalette::All,      true},
        {PaletteTextDisabled,              QPalette::Text,             QPalette::Disabled, true},
        {PaletteButton,                    QPalette::Button,           QPalette::All,      false},
        {PaletteButtonDisabled,            QPalette::Button,           QPalette::Disabled, false},
        {PaletteButtonText,                QPalette::ButtonText,       QPalette::All,      true},
        {PaletteButtonTextDisabled,        QPalette::ButtonText,       QPalette::Disabled, true},
        {PaletteBrightText,                QPalette::BrightText,       QPalette::All,      false},
        {PaletteBrightTextDisabled,        QPalette::BrightText,       QPalette::Disabled, false},
        {PaletteHighlight,                 QPalette::Highlight,        QPalette::All,      true},
        {PaletteHighlightDisabled,         QPalette::Highlight,        QPalette::Disabled, true},
        {PaletteHighlightedText,           QPalette::HighlightedText,  QPalette::All,      true},
        {PaletteHighlightedTextDisabled,   QPalette::HighlightedText,  QPalette::Disabled, true},
        {PaletteLink,                      QPalette::Link,             QPalette::All,      false},
        {PaletteLinkDisabled,              QPalette::Link,             QPalette::Disabled, false},
        {PaletteLinkVisited,               QPalette::LinkVisited,      QPalette::All,      false},
        {PaletteLinkVisitedDisabled,       QPalette::LinkVisited,      QPalette::Disabled, false},
        {PaletteLight,                     QPalette::Light,            QPalette::All,      false},
        {PaletteLightDisabled,             QPalette::Light,            QPalette::Disabled, false},
        {PaletteMidlight,                  QPalette::Midlight,         QPalette::All,      false},
        {PaletteMidlightDisabled,          QPalette::Midlight,         QPalette::Disabled, false},
        {PaletteDark,                      QPalette::Dark,             QPalette::All,      false},
        {PaletteDarkDisabled,              QPalette::Dark,             QPalette::Disabled, false},
        {PaletteMid,                       QPalette::Mid,              QPalette::All,      false},
        {PaletteMidDisabled,               QPalette::Mid,              QPalette::Disabled, false},
        {PaletteShadow,                    QPalette::Shadow,           QPalette::All,      false},
        {PaletteShadowDisabled,            QPalette::Shadow,           QPalette::Disabled, false},
// Qt6        {PalettePlaceholderText,           QPalette::PlaceholderText,  QPalette::All,      false},
// Qt6        {PalettePlaceholderTextDisabled,   QPalette::PlaceholderText,  QPalette::Disabled, false},
    };

    for (auto entry: mapping) 
    {
        const QColor themeColor = color(entry.themeColor);
        // Использовать исходный цвет, если цвет не определен в теме.
        if (themeColor.isValid()) 
        {
            if (entry.setColorRoleAsBrush)
                // TODO: выяснить, почему иногда используется setBrush
                pal.setBrush(entry.paletteColorGroup, entry.paletteColorRole, themeColor);
            else
                pal.setColor(entry.paletteColorGroup, entry.paletteColorRole, themeColor);
        }
    }

    return pal;
}

} // namespace QtVision
} // namespace VSN
