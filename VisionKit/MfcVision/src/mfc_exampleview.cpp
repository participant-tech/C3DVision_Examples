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

#include <mfc_exampleview.h>
#include <mfc_scenerenderer.h>
#include <vsn_last.h>

namespace VSN {

namespace MfcVision {

BEGIN_MESSAGE_MAP(ExampleView, COpenGLWnd)
END_MESSAGE_MAP()

ExampleView::ExampleView()
    : COpenGLWnd()
{
    MfcVision::CreateProcessesCameraControls(GetSceneRenderer());
}

//-----------------------------------------------------------------------------
//
// ---
ExampleView::~ExampleView()
{
}

//-----------------------------------------------------------------------------
//
// ---
void ExampleView::InitializeOpenGL()
{
    GetViewport()->GetCamera()->SetViewOrientation(Orientation::IsoXYZ);
    GetViewport()->SetBackgroundColour(VSN::Color(0xFF, 0xFF, 0xFF));
    GetViewport()->ZoomToFit(GetSceneContent()->GetBoundingBox());
}


} // namespace MfcVision
} // namespace VSN
