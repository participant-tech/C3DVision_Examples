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

#ifndef __SCENERENDERER_H
#define __SCENERENDERER_H

#include <afxwin.h>
#include <vsn_object.h>
#include <vsn_vision.h>
#include <vsn_global.h>
#include "mfc_visiondef.h"

namespace VSN {
namespace MfcVision {

class CSceneRendererPrivate;
/* CSceneRenderer */
class MFC_CLASS CSceneRenderer : public Object
{
    VSN_OBJECT(CSceneRenderer)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    CSceneRenderer();
    /// \ru Деструктор OpenGLWnd освобождает созданные ресурсы. \en NO TRANSLATION.
    virtual ~CSceneRenderer();
public:
    /**
    \brief \ru Подготовка OpenGL для рендеринга в этом виджете(установить текущий OpenGL контекст.
           \en NO TRANSLATION.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, потому что она вызывается автоматически перед вызовом paintGL().
                 \en NO TRANSLATION.
    */
    void MakeCurrent();
    /**
    \brief \ru Освободить OpenGL контекст.
           \en NO TRANSLATION.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, поскольку
                     в функции paintGL() контекст будет назначен и освобожден.
                 \en NO TRANSLATION.
    */
    void DoneCurrent();
public:
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* GetMainLight() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en Returns a pointer to Viewport for displaying the scene. \~
    Viewport* GetViewport() const;
    /// \ru Вернуть указатель на графическую сцену. \en Returns a pointer to the graphic scene. \~
    GraphicsScene* GetGraphicsScene() const;
    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to the scene content. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns a pointer to GraphicsView. \~
    GraphicsViewPtr GetGraphicsView() const;
    /// \ru Вернуть указатель на GraphicsSceneEngine. \en Returns a pointer to GraphicsSceneEngine. \~
    GraphicsSceneEnginePtr GetGraphicsEngine() const;
    /// \ru Нарисовать сцену и сохранить в картинку. \en Draw a scene and save it as a picture. \~
    Image GrabFrameImage(const SnapshotSettings& settings);
public:
    /// \ru Создать CSceneRenderer и захватить все необходимые рисурсы. \en NO TRANSLATION. \~
    void DoCreate(HWND hWnd);
    /// \ru Разрушить и освободить ресурсы Vision. \en NO TRANSLATION. \~
    void DoDestroy();
    /// \ru Подготовка Vision для отрисовки сцены. \en NO TRANSLATION. \~
    void DoPreparingToDisplay();
    /// \ru Отрисовать сцену. \en NO TRANSLATION. \~
    void DoDraw();
    /// \ru Изменить размер Viewport. \en NO TRANSLATION. \~
    void DoResize(int w, int h);
    //
    void DoSetFocus(CWnd* pOldWnd);
    void DoKillFocus(CWnd* pNewWnd);

    /// \ru Перегрузка для внутренних работ. \en Overload for internal workings.
    virtual bool OnWinEvent(MSG* pMsg);
public:
    VSN_SLOT(Public, RepaintWindow, void RepaintWindow())
protected:
    virtual void InitializeOpenGL();
    virtual void PaintOpenGL();
private:
    VSN_DECLARE_PRIVATE(CSceneRenderer)
};

enum ProcessType
{
    pt_Pan = 0x01,      ///< \ru Инициализация процесса параномирования. \en Initializes the pan process. \~
    pt_Orbit = 0x02,    ///< \ru Инициализация процесса вращения вокруг орбиты. \en Initializes the process of rotation about the orbit. \~
    pt_Rotate = 0x04,   ///< \ru Инициализация процесса вращения вокруг центра габарита. \en Initialization the process of rotation about the center of the boundbox. \~
    pt_Zoom = 0x08,     ///< \ru Инициализация процесса масштабирования. \en Initializes the zoom process. \~
    pt_AllProcess = pt_Orbit | pt_Zoom | pt_Pan,
};
VSN_DECLARE_FLAGS(ProcessTypes, ProcessType)


/// \ru Создание процессов для управления камерой. \en Creating processes to control the camera. \~
MFC_FUNC(void) CreateProcessesCameraControls(CSceneRenderer* pGLWidget, ProcessTypes prType = pt_AllProcess);

} // namespace MfcVision

} // namespace VSN

#endif /* __OPENGLWINDOW_H */
