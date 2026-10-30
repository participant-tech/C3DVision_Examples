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
#ifndef __QT_STYLEHELPER_H
#define __QT_STYLEHELPER_H

#include <QStyle>
#include <qt_global.h>

class QPalette;
class QPainter;
class QRect;

// Эта функция экспортируется в частном заголовке, поскольку от этого зависит qtOpengl.
// Следует рассмотреть возможность добавления этой функции в качестве общедоступной вспомогательной функции.
void qt_blurImage(QPainter* p, QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);



namespace VSN {
namespace QtVision {

/** \brief \ru Вспомогательный класс, который содержит все пользовательские значения цвета.
           \en Helper class containing all custom color values.\~
    \ingroup Vision_OpenGL
*/
class QT_CLASS StyleHelper
{
public:
    static const unsigned int DEFAULT_BASE_COLOR = 0x666666;
    static const int progressFadeAnimationDuration = 600;

    static qreal dpi(const QStyleOption* option);
    static qreal dpiScaled(qreal value, qreal dpi);
    static qreal dpiScaled(qreal value, const QPaintDevice* device);
    static qreal dpiScaled(qreal value, const QStyleOption* option);

    /// \ru Высота панели навигации проводника проекта. \en Height of the project explorer navigation bar. \~
    static int navigationWidgetHeight() { return 24; }
    static qreal sidebarFontSize();
    static QPalette sidebarFontPalette(const QPalette &original);

    /// \ru Таблица всех цветов, унаследованная от baseColor. \en Table of all colors inherited from baseColor. \~
    static QColor requestedBaseColor() { return m_requestedBaseColor; }
    static QColor baseColor(bool lightColored = false);
    static QColor panelTextColor(bool lightColored = false);
    static QColor highlightColor(bool lightColored = false);
    static QColor shadowColor(bool lightColored = false);
    static QColor borderColor(bool lightColored = false);
    static QColor toolBarBorderColor();
    static QColor buttonTextColor() { return QColor(0x4c4c4c); }
    static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50);
    static QColor alphaBlendedColors(const QColor &colorA, const QColor &colorB);

    static QColor sidebarHighlight() { return QColor(255, 255, 255, 40); }
    static QColor sidebarShadow() { return QColor(0, 0, 0, 40); }

    static QColor toolBarDropShadowColor() { return QColor(0, 0, 0, 70); }

    static QColor notTooBrightHighlightColor();

    /// \ru Устанавливает базовый цвет для обеспечения всех виджетов верхнего уровня. \en Sets the base color for all top-level widgets. \~
    static void setBaseColor(const QColor& color);

    /// \ru Рисует затененную сглаженную стрелку. \en Draws a shaded smooth arrow. \~
    static void drawArrow(QStyle::PrimitiveElement element, QPainter *painter, const QStyleOption *option);

    /// \ru Использование градиентов для панелей. \en Using gradients for panels. \~
    static void horizontalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect, bool lightColored = false);
    static void verticalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect, bool lightColored = false);
    static void menuGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect);
    static bool usePixmapCache() { return true; }

    static QPixmap disabledSideBarIcon(const QPixmap &enabledicon);
    static void drawIconWithShadow(const QIcon &icon, const QRect &rect, QPainter *p, QIcon::Mode iconMode,
                                   int dipRadius = 3, const QColor &color = QColor(0, 0, 0, 130),
                                   const QPoint &dipOffset = QPoint(1, -2));
    static void drawCornerImage(const QImage &img, QPainter *painter, const QRect &rect,
                         int left = 0, int top = 0, int right = 0, int bottom = 0);

    static void tintImage(QImage &img, const QColor &tintColor);
    static QLinearGradient statusBarGradient(const QRect &statusBarRect);

    class IconFontHelper
    {
        public:
            IconFontHelper(const QString &iconSymbol,
                           const QColor &color,
                           const QSize &size,
                           QIcon::Mode mode = QIcon::Normal,
                           QIcon::State state = QIcon::Off)
                : m_iconSymbol(iconSymbol)
                , m_color(color)
                , m_size(size)
                , m_mode(mode)
                , m_state(state)
            {}

            QString iconSymbol() const { return m_iconSymbol; }
            QColor color() const { return m_color; }
            QSize size() const { return m_size; }
            QIcon::Mode mode() const { return m_mode; }
            QIcon::State state() const { return m_state; }

        private:
            QString m_iconSymbol;
            QColor m_color;
            QSize m_size;
            QIcon::Mode m_mode;
            QIcon::State m_state;
    };

    static QIcon getIconFromIconFont(const QString &fontName, const QList<IconFontHelper> &parameters);
    static QIcon getIconFromIconFont(const QString &fontName, const QString &iconSymbol, int fontSize, int iconSize, QColor color);
    static QIcon getIconFromIconFont(const QString &fontName, const QString &iconSymbol, int fontSize, int iconSize);
    static QIcon getCursorFromIconFont(const QString &fontname, const QString &cursorFill, const QString &cursorOutline,
                                       int fontSize, int iconSize);

    static QString dpiSpecificImageFile(const QString &fileName);
    static QString imageFileWithResolution(const QString &fileName, int dpr);
    static QList<int> availableImageResolutions(const QString &fileName);

    static double luminance(const QColor &color);
    static bool isReadableOn(const QColor &background, const QColor &foreground);
    /// \ru Возвращает цвет переднего плана, например, для desiredForeground. \en Return the foreground color for example for the desired Foreground. \~
    static QColor ensureReadableOn(const QColor& background, const QColor& desiredForeground);
private:
    static QColor m_baseColor;
    static QColor m_requestedBaseColor;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_STYLEHELPER_H */
