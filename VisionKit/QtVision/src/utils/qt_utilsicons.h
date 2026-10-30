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

#ifndef __QT_UTILSICONS_H
#define __QT_UTILSICONS_H


#include <qt_icon.h>
#include <qt_theme.h>
#include <qt_global.h>


namespace VSN {
namespace QtVision {

namespace Icons {

extern const Icon HOME;
extern const Icon HOME_TOOLBAR;
extern const Icon EDIT_CLEAR;
extern const Icon EDIT_CLEAR_TOOLBAR;
extern const Icon LOCKED_TOOLBAR;
extern const Icon LOCKED;
extern const Icon UNLOCKED_TOOLBAR;
extern const Icon UNLOCKED;
extern const Icon PINNED;
extern const Icon NEXT;
extern const Icon NEXT_TOOLBAR;
extern const Icon PREV;
extern const Icon PREV_TOOLBAR;
extern const Icon PROJECT;
extern const Icon ZOOM;
extern const Icon ZOOM_TOOLBAR;
extern const Icon ZOOMIN_TOOLBAR;
extern const Icon ZOOMOUT_TOOLBAR;
extern const Icon FITTOVIEW_TOOLBAR;
extern const Icon OK;
extern const Icon NOTLOADED;
extern const Icon BROKEN;
extern const Icon BOOKMARK;
extern const Icon BOOKMARK_TOOLBAR;
extern const Icon BOOKMARK_TEXTEDITOR;
extern const Icon SNAPSHOT_TOOLBAR;
extern const Icon NEWSEARCH_TOOLBAR;
extern const Icon SETTINGS_TOOLBAR;

extern const Icon NEWFILE;
extern const Icon OPENFILE;
extern const Icon OPENFILE_TOOLBAR;
extern const Icon SAVEFILE;
extern const Icon SAVEFILE_TOOLBAR;

extern const Icon EXPORTFILE_TOOLBAR;
extern const Icon MULTIEXPORTFILE_TOOLBAR;

extern const Icon DIR;
extern const Icon HELP;
extern const Icon UNKNOWN_FILE;

extern const Icon UNDO;
extern const Icon UNDO_TOOLBAR;
extern const Icon REDO;
extern const Icon REDO_TOOLBAR;
extern const Icon COPY;
extern const Icon COPY_TOOLBAR;
extern const Icon PASTE;
extern const Icon PASTE_TOOLBAR;
extern const Icon CUT;
extern const Icon CUT_TOOLBAR;
extern const Icon RESET;
extern const Icon RESET_TOOLBAR;

extern const Icon ARROW_UP;
extern const Icon ARROW_UP_TOOLBAR;
extern const Icon ARROW_DOWN;
extern const Icon ARROW_DOWN_TOOLBAR;
extern const Icon MINUS;
extern const Icon PLUS_TOOLBAR;
extern const Icon PLUS;
extern const Icon MAGNIFIER;
extern const Icon CLEAN;
extern const Icon CLEAN_TOOLBAR;
extern const Icon RELOAD;
extern const Icon RELOAD_TOOLBAR;
extern const Icon TOGGLE_LEFT_SIDEBAR;
extern const Icon TOGGLE_LEFT_SIDEBAR_TOOLBAR;
extern const Icon TOGGLE_RIGHT_SIDEBAR;
extern const Icon TOGGLE_RIGHT_SIDEBAR_TOOLBAR;
extern const Icon CLOSE_TOOLBAR;
extern const Icon CLOSE_FOREGROUND;
extern const Icon CLOSE_BACKGROUND;
extern const Icon SPLIT_HORIZONTAL;
extern const Icon SPLIT_HORIZONTAL_TOOLBAR;
extern const Icon SPLIT_VERTICAL;
extern const Icon SPLIT_VERTICAL_TOOLBAR;
extern const Icon CLOSE_SPLIT_TOP;
extern const Icon CLOSE_SPLIT_BOTTOM;
extern const Icon CLOSE_SPLIT_LEFT;
extern const Icon CLOSE_SPLIT_RIGHT;
extern const Icon FILTER;
extern const Icon LINK;
extern const Icon LINK_TOOLBAR;
extern const Icon SORT_ALPHABETICALLY_TOOLBAR;
extern const Icon TOGGLE_PROGRESSDETAILS_TOOLBAR;
extern const Icon ONLINE;
extern const Icon ONLINE_TOOLBAR;
extern const Icon DOWNLOAD;

extern const Icon INFO;
extern const Icon INFO_TOOLBAR;
extern const Icon WARNING;
extern const Icon WARNING_TOOLBAR;
extern const Icon CRITICAL;
extern const Icon CRITICAL_TOOLBAR;

extern const Icon ERROR_TASKBAR;
extern const Icon EXPAND_ALL_TOOLBAR;
extern const Icon TOOLBAR_EXTENSION;
extern const Icon RUN_SMALL;
extern const Icon RUN_SMALL_TOOLBAR;
extern const Icon STOP_SMALL;
extern const Icon STOP_SMALL_TOOLBAR;
extern const Icon INTERRUPT_SMALL;
extern const Icon INTERRUPT_SMALL_TOOLBAR;
extern const Icon BOUNDING_RECT;
extern const Icon EYE_OPEN_TOOLBAR;
extern const Icon EYE_CLOSED_TOOLBAR;
extern const Icon REPLACE;
extern const Icon EXPAND;
extern const Icon EXPAND_TOOLBAR;
extern const Icon COLLAPSE;
extern const Icon COLLAPSE_TOOLBAR;
extern const Icon PAN_TOOLBAR;
extern const Icon EMPTY14;
extern const Icon EMPTY16;
extern const Icon OVERLAY_ADD;
extern const Icon OVERLAY_WARNING;
extern const Icon OVERLAY_ERROR;
extern const Icon RUN_FILE;
extern const Icon RUN_FILE_TOOLBAR;
extern const Icon RUN_SELECTED;
extern const Icon RUN_SELECTED_TOOLBAR;

extern const Icon CODEMODEL_ERROR;
extern const Icon CODEMODEL_WARNING;
extern const Icon CODEMODEL_DISABLED_ERROR;
extern const Icon CODEMODEL_DISABLED_WARNING;
extern const Icon CODEMODEL_FIXIT;

extern const Icon MACOS_TOUCHBAR_BOOKMARK;
extern const Icon MACOS_TOUCHBAR_CLEAR;
} // namespace Icons

namespace CodeModelIcon {

enum Type {
    Class = 0,
    Struct,
    Enum,
    Enumerator,
    FuncPublic,
    FuncProtected,
    FuncPrivate,
    FuncPublicStatic,
    FuncProtectedStatic,
    FuncPrivateStatic,
    Namespace,
    VarPublic,
    VarProtected,
    VarPrivate,
    VarPublicStatic,
    VarProtectedStatic,
    VarPrivateStatic,
    Signal,
    SlotPublic,
    SlotProtected,
    SlotPrivate,
    Keyword,
    Macro,
    Property,
    Unknown
};

QIcon iconForType(Type type);

} // namespace CodeModelIcon

} // namespace QtVision
} // namespace VSN

#endif /* __QT_UTILSICONS_H */
