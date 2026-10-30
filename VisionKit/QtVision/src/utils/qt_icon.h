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
#ifndef __QT_ICON_H
#define __QT_ICON_H

#include <qt_theme.h>
#include <qt_filepath.h>

#include <QIcon>
#include <QPair>
#include <QVector>
#include <qt_global.h>

QT_BEGIN_NAMESPACE
class QColor;
class QPixmap;
class QString;
QT_END_NAMESPACE

namespace VSN {
namespace QtVision {


using IconMaskAndColor = QPair<FilePath, Theme::Color>;

// Returns a recolored icon with shadow and custom disabled state for a
// series of grayscalemask|Theme::Color mask pairs
class Icon
{
public:
    enum IconStyleOption {
        None = 0,
        Tint = 1,
        DropShadow = 2,
        PunchEdges = 4,

        ToolBarStyle = Tint | DropShadow | PunchEdges,
        MenuTintedStyle = Tint | PunchEdges
    };
    Q_DECLARE_FLAGS(IconStyleOptions, IconStyleOption)

    Icon();
    Icon(std::initializer_list<IconMaskAndColor> args, IconStyleOptions style = ToolBarStyle);
    Icon(const FilePath& imageFileName);
    Icon(const Icon &other) = default;

    QIcon icon() const;
    // Same as icon() but without disabled state.
    QPixmap pixmap(QIcon::Mode iconMode = QIcon::Normal) const;

    // Try to avoid it. it is just there for special API cases in Qt Vision
    // where icons are still defined as filename.
    QString imageFilePath() const;

    // Returns either the classic or a themed icon depending on
    // the current Theme::FlatModeIcons flag.
    static QIcon sideBarIcon(const Icon &classic, const Icon &flat);
    // Like sideBarIcon plus added action mode for the flat icon
    static QIcon modeIcon(const Icon &classic, const Icon &flat, const Icon &flatActive);

    // Combined icon pixmaps in Normal and Disabled states from several Icons
    static QIcon combinedIcon(const QList<QIcon> &icons);
    static QIcon combinedIcon(const QList<Icon> &icons);
private:
    QVector<IconMaskAndColor> m_iconSourceList;
    IconStyleOptions m_style = None;
    mutable int m_lastDevicePixelRatio = -1;
    mutable QIcon m_lastIcon;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROJECT_H */

