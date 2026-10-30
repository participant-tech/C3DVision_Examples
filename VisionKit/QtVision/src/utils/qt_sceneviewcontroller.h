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
#ifndef __QT_SCENEVIEWCONTROLLER_H
#define __QT_SCENEVIEWCONTROLLER_H

#include <QObject>
#include <qt_modelview.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* SceneViewController */
class QT_CLASS SceneViewController : public QObject
{
    Q_OBJECT
public:
    SceneViewController(QObject* parent);
public:
    enum class HeadsUpToolType
    {
        ZoomToFit = 1 << 1,
        ZoomToBox = 1 << 2,
        Orientation = 1 << 3,
        Isometry = 1 << 4,
        Perspective = 1 << 5,
        RenderMode = 1 << 6
    };
    Q_DECLARE_FLAGS(HeadsUpToolTypes, HeadsUpToolType)
    // Create a toolbar in each viewport that contains all 
    // the common tools needed to control the view.
    void createHeadsUpViewToolbar(bool createMode);
    void createHeadsUpViewToolbar(HeadsUpToolTypes types);
    void createCameraControlToolbar();
    void setSceneWidget(ModelView* sceneWidget);
public Q_SLOTS:
    void viewPortCommands();
    void viewPortRenderMode();
    void updateActions();
private:
    ModelView* m_sceneWidget;
    QtAutoHideWindow* m_autoHideWindow;

    QAction* m_actionZoomBox;
private:
    Q_DISABLE_COPY(SceneViewController)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_SCENEVIEWCONTROLLER_H */

