#include "stdafx.h"
#include "cubeview.h"
#include <mfc_scenerenderer.h>
#include <vsn_last.h>

using namespace VSN;

BEGIN_MESSAGE_MAP(CubeView, COpenGLWnd)
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

/* CubeView */
CubeView::CubeView()
    : COpenGLWnd()
{
    SceneSegment* pCubeSegment = new SceneSegment(GeometryFactory::Instance()->CreateBox(2.0, 2.0, 2.0));
    GetSceneContent()->GetRootSegment()->AddSegment(pCubeSegment);
}

//-----------------------------------------------------------------------------
//
// ---
CubeView::~CubeView()
{
}

//-----------------------------------------------------------------------------
//
// ---
void CubeView::InitializeOpenGL()
{
    GetViewport()->GetCamera()->SetViewOrientation(Orientation::IsoXYZ);
    GetViewport()->SetGradientBackgroundColour(Color(171, 171, 171), Color(71, 71, 71));
    GetViewport()->ZoomToFit(GetSceneContent()->GetBoundingBox());
    MfcVision::CreateProcessesCameraControls(GetSceneRenderer());
    if (OrientationMarker* pMarker = GetGraphicsView()->GetOrientationMarker())
    {
        uint nFactor = 2;
        uint a, b, c, d, e, f, h;
        pMarker->GetRepOptionTriad(a, b, c, d, e, f, h);
        pMarker->SetRepOptionTriad(nFactor * a, nFactor * b, nFactor * c, nFactor * d, nFactor * e, nFactor * f, nFactor * h);
//        pMarker->SetEnabled(false);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void CubeView::OnSetFocus(CWnd* pOldWnd)
{
    COpenGLWnd::OnSetFocus(pOldWnd);
    GetSceneRenderer()->DoSetFocus(pOldWnd);
}

//-----------------------------------------------------------------------------
//
// ---
void CubeView::OnKillFocus(CWnd* pNewWnd)
{
    COpenGLWnd::OnKillFocus(pNewWnd);
    GetSceneRenderer()->DoKillFocus(pNewWnd);
}
