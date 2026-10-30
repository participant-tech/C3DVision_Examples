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
#ifndef __QT_THEME_H
#define __QT_THEME_H

#include <QBrush>
#include <QObject>
#include <qt_global.h>

class QMenu;
class QPalette;
class QSettings;

namespace VSN {
namespace QtVision {

class ThemePrivate;
/* Theme */
class QT_CLASS Theme : public QObject
{
    Q_OBJECT
public:
    Theme(const QString& id, QObject* parent = nullptr);
    ~Theme() override;
public:
    enum Color
    {
        BackgroundColorDisabled,
        ComboBoxTextColor,
        DockWidgetResizeHandleColor,
        FancyToolBarSeparatorColor,
        FancyToolButtonHoverColor,
        FancyToolButtonSelectedColor,
        MenuBarItemTextColorDisabled,
        MenuBarItemTextColorNormal,
        MenuItemTextColorDisabled,
        MenuItemTextColorNormal,
        PanelStatusBarBackgroundColor,
        PanelTextColorDark,
        PanelTextColorMid,
        PanelTextColorLight,
        ProgressBarTitleColor,

        /* Palette for QPalette */
        PaletteWindow,
        PaletteWindowText,
        PaletteBase,
        PaletteAlternateBase,
        PaletteToolTipBase,
        PaletteToolTipText,
        PaletteText,
        PaletteButton,
        PaletteButtonText,
        PaletteBrightText,
        PaletteHighlight,
        PaletteHighlightedText,
        PaletteLink,
        PaletteLinkVisited,

        PaletteLight,
        PaletteMidlight,
        PaletteDark,
        PaletteMid,
        PaletteShadow,

        PaletteWindowDisabled,
        PaletteWindowTextDisabled,
        PaletteBaseDisabled,
        PaletteAlternateBaseDisabled,
        PaletteToolTipBaseDisabled,
        PaletteToolTipTextDisabled,
        PaletteTextDisabled,
        PaletteButtonDisabled,
        PaletteButtonTextDisabled,
        PaletteBrightTextDisabled,
        PaletteHighlightDisabled,
        PaletteHighlightedTextDisabled,
        PaletteLinkDisabled,
        PaletteLinkVisitedDisabled,

        PaletteLightDisabled,
        PaletteMidlightDisabled,
        PaletteDarkDisabled,
        PaletteMidDisabled,
        PaletteShadowDisabled,

        PalettePlaceholderText,
        PalettePlaceholderTextDisabled,

        /* Icons */
        IconsBaseColor,
        IconsDisabledColor,
        IconsInfoToolBarColor,
        IconsWarningColor,
        IconsWarningToolBarColor,
    };

    enum ImageFile {
    };

    enum Flag {
        DrawTargetSelectorBottom,
        DrawSearchResultWidgetFrame,
        DrawIndicatorBranch,
        DrawToolBarHighlights,
        DrawToolBarBorders,
        ComboBoxDrawTextShadow,
        DerivePaletteFromTheme,
        ApplyThemePaletteGlobally,
        FlatToolBars,
        FlatSideBarIcons,
        FlatProjectsMode,
        FlatMenuBar,
        ToolBarIconShadow,
        WindowColorAsBase,
        DarkUserInterface
    };

    Q_ENUM(Color)
    Q_ENUM(ImageFile)
    Q_ENUM(Flag)

    Q_INVOKABLE bool flag(Theme::Flag f) const;
    Q_INVOKABLE QColor color(Theme::Color role) const;
    QString imageFile(ImageFile imageFile, const QString &fallBack) const;
    QPalette palette() const;
    QStringList preferredStyles() const;
    QString defaultTextEditorColorScheme() const;

    QString id() const;
    QString filePath() const;
    QString displayName() const;
    void setDisplayName(const QString& displayName);

    void readSettings(QSettings& settings);

    static bool systemUsesDarkMode();
    static QPalette initialPalette();

    static void setInitialPalette(Theme *initTheme);

    static void setHelpMenu(QMenu* menu);
protected:
    Theme(Theme* originTheme, QObject* parent = nullptr);
    ThemePrivate* d;
private:
    friend QT_FUNC(Theme*) visionTheme();
    friend QT_FUNC(Theme*) proxyTheme();
    QPair<QColor, QString> readNamedColor(const QString& color) const;
};

QT_FUNC(Theme*) visionTheme();
QT_FUNC(Theme*) proxyTheme();
QT_FUNC(void) setVisionTheme(Theme* theme);
QT_FUNC(void) clearVisionTheme();

} // namespace QtVision

} // namespace VSN


#endif /* __QT_THEME_H */
