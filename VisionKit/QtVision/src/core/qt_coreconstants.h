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

#ifndef __QT_CORECONSTANTS_H
#define __QT_CORECONSTANTS_H


namespace VSN {
namespace QtVision {
namespace Constants {

// Modes
const char MODE_WELCOME[]          = "Welcome";
const char MODE_EDIT[]             = "Edit";
const char MODE_DESIGN[]           = "Design";
const int  P_MODE_WELCOME          = 100;
const int  P_MODE_EDIT             = 90;
const int  P_MODE_DESIGN           = 89;

// TouchBar
const char TOUCH_BAR[]             = "C3DVision.TouchBar";

// Menubar
const char MENU_BAR[]              = "C3DVision.MenuBar";

// Menus
const char M_FILE[]                = "C3DVision.Menu.File";
const char M_FILE_RECENTFILES[]    = "C3DVision.Menu.File.RecentFiles";
const char M_EDIT[]                = "C3DVision.Menu.Edit";
const char M_EDIT_ADVANCED[]       = "C3DVision.Menu.Edit.Advanced";
const char M_VIEW[]                = "C3DVision.Menu.View";
const char M_VIEW_MODESTYLES[]     = "C3DVision.Menu.View.ModeStyles";
const char M_VIEW_VIEWS[]          = "C3DVision.Menu.View.Views";
const char M_VIEW_PANES[]          = "C3DVision.Menu.View.Panes";
const char M_TOOLS[]               = "C3DVision.Menu.Tools";
const char M_TOOLS_EXTERNAL[]      = "C3DVision.Menu.Tools.External";
const char M_TOOLS_DEBUG[]         = "C3DVision.Menu.Tools.Debug";
const char M_WINDOW[]              = "C3DVision.Menu.Window";
const char M_HELP[]                = "C3DVision.Menu.Help";

// Contexts
const char C_GLOBAL[]              = "Global Context";
const char C_WELCOME_MODE[]        = "Core.WelcomeMode";
const char C_EDIT_MODE[]           = "Core.EditMode";
const char C_DESIGN_MODE[]         = "Core.DesignMode";
const char C_EDITORMANAGER[]       = "Core.EditorManager";
const char C_NAVIGATION_PANE[]     = "Core.NavigationPane";
const char C_PROBLEM_PANE[]        = "Core.ProblemPane";
const char C_GENERAL_OUTPUT_PANE[] = "Core.GeneralOutputPane";

// Default editor kind
//const char K_DEFAULT_TEXT_EDITOR_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("OpenWith::Editors", "Plain Text Editor");
const char K_DEFAULT_TEXT_EDITOR_ID[] = "Core.PlainTextEditor";
const char K_DEFAULT_BINARY_EDITOR_ID[] = "Core.BinaryEditor";

//actions
const char UNDO[]                  = "C3DVision.Undo";
const char REDO[]                  = "C3DVision.Redo";
const char COPY[]                  = "C3DVision.Copy";
const char PASTE[]                 = "C3DVision.Paste";
const char CUT[]                   = "C3DVision.Cut";
const char SELECTALL[]             = "C3DVision.SelectAll";

const char GOTO[]                  = "C3DVision.Goto";
const char ZOOM_IN[]               = "C3DVision.ZoomIn";
const char ZOOM_OUT[]              = "C3DVision.ZoomOut";
const char ZOOM_RESET[]            = "C3DVision.ZoomReset";

const char NEW[]                   = "C3DVision.New";
const char NEW_FILE[]              = "C3DVision.NewFile";
const char OPEN[]                  = "C3DVision.Open";
const char OPEN_WITH[]             = "C3DVision.OpenWith";
const char REVERTTOSAVED[]         = "C3DVision.RevertToSaved";
const char SAVE[]                  = "C3DVision.Save";
const char SAVEAS[]                = "C3DVision.SaveAs";
const char SAVEALL[]               = "C3DVision.SaveAll";
const char PRINT[]                 = "C3DVision.Print";
const char EXIT[]                  = "C3DVision.Exit";

const char OPTIONS[]               = "C3DVision.Options";
const char LOGGER[]                = "C3DVision.Logger";

const char TOGGLE_PROPS_PANEL[]    = "C3DVision.TogglePropertiesPanel";
const char TOGGLE_MODEL_PANEL[]    = "C3DVision.ToggleModelPanel";
const char TOGGLE_OUTPUT_PANEL[]   = "C3DVision.ToggleOutputPanel";

const char TOGGLE_LEFT_SIDEBAR[]   = "C3DVision.ToggleLeftSidebar";
const char TOGGLE_RIGHT_SIDEBAR[]  = "C3DVision.ToggleRightSidebar";
const char CYCLE_MODE_SELECTOR_STYLE[] =
                                     "C3DVision.CycleModeSelectorStyle";
const char TOGGLE_FULLSCREEN[]     = "C3DVision.ToggleFullScreen";
const char THEMEOPTIONS[]          = "C3DVision.ThemeOptions";

//const char TR_SHOW_LEFT_SIDEBAR[]  = QT_TRANSLATE_NOOP("Core", "Show Left Sidebar");
//const char TR_HIDE_LEFT_SIDEBAR[]  = QT_TRANSLATE_NOOP("Core", "Hide Left Sidebar");

//const char TR_SHOW_RIGHT_SIDEBAR[] = QT_TRANSLATE_NOOP("Core", "Show Right Sidebar");
//const char TR_HIDE_RIGHT_SIDEBAR[] = QT_TRANSLATE_NOOP("Core", "Hide Right Sidebar");

const char MINIMIZE_WINDOW[]       = "C3DVision.MinimizeWindow";
const char ZOOM_WINDOW[]           = "C3DVision.ZoomWindow";
const char CLOSE_WINDOW[]          = "C3DVision.CloseWindow";

const char SPLIT[]                 = "C3DVision.Split";
const char SPLIT_SIDE_BY_SIDE[]    = "C3DVision.SplitSideBySide";
const char SPLIT_NEW_WINDOW[]      = "C3DVision.SplitNewWindow";
const char REMOVE_CURRENT_SPLIT[]  = "C3DVision.RemoveCurrentSplit";
const char REMOVE_ALL_SPLITS[]     = "C3DVision.RemoveAllSplits";
const char GOTO_PREV_SPLIT[]       = "C3DVision.GoToPreviousSplit";
const char GOTO_NEXT_SPLIT[]       = "C3DVision.GoToNextSplit";
const char CLOSE[]                 = "C3DVision.Close";
const char CLOSE_ALTERNATIVE[]     = "C3DVision.Close_Alternative";
const char CLOSEALL[]              = "C3DVision.CloseAll";
const char CLOSEOTHERS[]           = "C3DVision.CloseOthers";
const char CLOSEALLEXCEPTVISIBLE[] = "C3DVision.CloseAllExceptVisible";
const char GOTONEXTINHISTORY[]     = "C3DVision.GotoNextInHistory";
const char GOTOPREVINHISTORY[]     = "C3DVision.GotoPreviousInHistory";
const char GO_BACK[]               = "C3DVision.GoBack";
const char GO_FORWARD[]            = "C3DVision.GoForward";
const char GOTOLASTEDIT[]          = "C3DVision.GotoLastEdit";
const char ABOUT_C3DVISION[]       = "C3DVision.AboutC3DVision";
const char ABOUT_PLUGINS[]         = "C3DVision.AboutPlugins";
const char S_RETURNTOEDITOR[]      = "C3DVision.ReturnToEditor";
const char SHOWINGRAPHICALSHELL[]  = "C3DVision.ShowInGraphicalShell";
const char SHOWINFILESYSTEMVIEW[]  = "C3DVision.ShowInFileSystemView";

const char OUTPUTPANE_CLEAR[] = "Coreplugin.OutputPane.clear";

// Default groups
const char G_DEFAULT_ONE[]         = "C3DVision.Group.Default.One";
const char G_DEFAULT_TWO[]         = "C3DVision.Group.Default.Two";
const char G_DEFAULT_THREE[]       = "C3DVision.Group.Default.Three";

// Main menu bar groups
const char G_FILE[]                = "C3DVision.Group.File";
const char G_EDIT[]                = "C3DVision.Group.Edit";
const char G_VIEW[]                = "C3DVision.Group.View";
const char G_TOOLS[]               = "C3DVision.Group.Tools";
const char G_WINDOW[]              = "C3DVision.Group.Window";
const char G_HELP[]                = "C3DVision.Group.Help";

// File menu groups
const char G_FILE_NEW[]            = "C3DVision.Group.File.New";
const char G_FILE_OPEN[]           = "C3DVision.Group.File.Open";
const char G_FILE_PROJECT[]        = "C3DVision.Group.File.Project";
const char G_FILE_SAVE[]           = "C3DVision.Group.File.Save";
const char G_FILE_EXPORT[]         = "C3DVision.Group.File.Export";
const char G_FILE_CLOSE[]          = "C3DVision.Group.File.Close";
const char G_FILE_PRINT[]          = "C3DVision.Group.File.Print";
const char G_FILE_OTHER[]          = "C3DVision.Group.File.Other";

// Edit menu groups
const char G_EDIT_UNDOREDO[]       = "C3DVision.Group.Edit.UndoRedo";
const char G_EDIT_COPYPASTE[]      = "C3DVision.Group.Edit.CopyPaste";
const char G_EDIT_SELECTALL[]      = "C3DVision.Group.Edit.SelectAll";
const char G_EDIT_ADVANCED[]       = "C3DVision.Group.Edit.Advanced";

const char G_EDIT_FIND[]           = "C3DVision.Group.Edit.Find";
const char G_EDIT_OTHER[]          = "C3DVision.Group.Edit.Other";

// Advanced edit menu groups
const char G_EDIT_FORMAT[]         = "C3DVision.Group.Edit.Format";
const char G_EDIT_COLLAPSING[]     = "C3DVision.Group.Edit.Collapsing";
const char G_EDIT_TEXT[]           = "C3DVision.Group.Edit.Text";
const char G_EDIT_BLOCKS[]         = "C3DVision.Group.Edit.Blocks";
const char G_EDIT_FONT[]           = "C3DVision.Group.Edit.Font";
const char G_EDIT_EDITOR[]         = "C3DVision.Group.Edit.Editor";

// View menu groups
const char G_VIEW_VIEWS[]          = "C3DVision.Group.View.Views";
const char G_VIEW_PANES[]          = "C3DVision.Group.View.Panes";

// Tools menu groups
const char G_TOOLS_DEBUG[]         = "C3DVision.Group.Tools.Debug";
const char G_EDIT_PREFERENCES[]    = "C3DVision.Group.Edit.Preferences";

// Window menu groups
const char G_WINDOW_SIZE[]         = "C3DVision.Group.Window.Size";
const char G_WINDOW_SPLIT[]        = "C3DVision.Group.Window.Split";
const char G_WINDOW_NAVIGATE[]     = "C3DVision.Group.Window.Navigate";
const char G_WINDOW_LIST[]         = "C3DVision.Group.Window.List";
const char G_WINDOW_OTHER[]        = "C3DVision.Group.Window.Other";

// Help groups (global)
const char G_HELP_HELP[]           = "C3DVision.Group.Help.Help";
const char G_HELP_SUPPORT[]        = "C3DVision.Group.Help.Supprt";
const char G_HELP_ABOUT[]          = "C3DVision.Group.Help.About";
const char G_HELP_UPDATES[]        = "C3DVision.Group.Help.Updates";

// Touchbar groups
const char G_TOUCHBAR_HELP[]       = "C3DVision.Group.TouchBar.Help";
const char G_TOUCHBAR_EDITOR[]     = "C3DVision.Group.TouchBar.Editor";
const char G_TOUCHBAR_NAVIGATION[] = "C3DVision.Group.TouchBar.Navigation";
const char G_TOUCHBAR_OTHER[]      = "C3DVision.Group.TouchBar.Other";

const char WIZARD_CATEGORY_QT[] = "R.Qt";
//const char WIZARD_TR_CATEGORY_QT[] = QT_TRANSLATE_NOOP("Core", "Qt");
const char WIZARD_KIND_UNKNOWN[] = "unknown";
const char WIZARD_KIND_PROJECT[] = "project";
const char WIZARD_KIND_FILE[]    = "file";

const char SETTINGS_CATEGORY_CORE[] = "B.Core";
const char SETTINGS_ID_INTERFACE[]  = "A.Interface";
const char SETTINGS_ID_SYSTEM[]     = "B.Core.System";
const char SETTINGS_ID_SHORTCUTS[]  = "C.Keyboard";
const char SETTINGS_ID_TOOLS[]      = "D.ExternalTools";
const char SETTINGS_ID_MIMETYPES[]  = "E.MimeTypes";

const char SETTINGS_DEFAULTTEXTENCODING[]     = "General/DefaultFileEncoding";
const char SETTINGS_DEFAULT_LINE_TERMINATOR[] = "General/DefaultLineTerminator";

const char SETTINGS_THEME[]     = "Core/CreatorTheme";
const char DEFAULT_THEME[]      = "flat";
const char DEFAULT_DARK_THEME[] = "flat-dark";

//const char TR_CLEAR_MENU[]         = QT_TRANSLATE_NOOP("Core", "Clear Menu");

const int MODEBAR_ICON_SIZE = 34;
const int MODEBAR_ICONSONLY_BUTTON_SIZE = MODEBAR_ICON_SIZE + 4;
const int DEFAULT_MAX_CHAR_COUNT = 10000000;

} // namespace Constants
} // namespace QtVision
} // namespace VSN

#endif /* __QT_CORECONSTANTS_H */
