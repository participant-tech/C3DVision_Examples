
// viewerview.cpp : implementation of the ViewerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "viewerapplication.h"
#endif

#include "viewerdoc.h"
#include "viewerview.h"
#include <mfc_scenerenderer.h>
#include <vsn_last.h>


// ViewerView

IMPLEMENT_DYNCREATE(ViewerView, COpenGLView)
BEGIN_MESSAGE_MAP(ViewerView, COpenGLView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &COpenGLView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &COpenGLView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ViewerView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//
// ---
ViewerView::ViewerView()
    : m_pModelSegment(nullptr)
    , m_pSceneGenerator(new SceneGenerator())
{
}

//-----------------------------------------------------------------------------
//
// ---
ViewerView::~ViewerView()
{
    VSN_DELETE_AND_NULL(m_pSceneGenerator);
}

//-----------------------------------------------------------------------------
// Функция вызывается после инициализации Vision.
// ---
void ViewerView::InitializeOpenGL()
{
    COpenGLView::InitializeOpenGL();
    GetViewport()->SetGradientBackgroundColour(Color(171, 171, 171), Color(71, 71, 71));
    GetViewport()->GetCamera()->SetViewOrientation(Orientation::IsoXYZ);
    GetViewport()->GetCamera()->SetDefaultUpVector(MbVector3D::yAxis);
    GetViewport()->SetPixelCullingSize(25);

    GetMainLight()->SetPosition(100.0, 100.0, 100.0);
    Light* pLight = GetGraphicsScene()->CreateExtraLight();
    pLight->SetType(Light::DirectionLight);
    pLight->SetPosition(-100.0, -1.0, -1.0);
    pLight->SetDiffuseColor(Color(0.2f, 0.2f, 0.2f, 1.0f));
    MfcVision::CreateProcessesCameraControls(GetSceneRenderer());
}

//-----------------------------------------------------------------------------
//
// ---
void ViewerView::UpdateSceneForModel(SPtr<MbModel> pModel)
{
    if (pModel == nullptr)
        return;
    SceneSegment* pSceneSegment = GetSceneContent()->GetRootSegment();
    ASSERT(pSceneSegment != nullptr);
    m_pModelSegment = new SceneSegment(pSceneSegment);
    ProgressBuild* pProgressBuild = m_pSceneGenerator->CreateProgressBuild();
    m_pSceneGenerator->CreateSceneSegment(pModel, m_pModelSegment);
    Object::Connect(pProgressBuild, &ProgressBuild::ValueModified, this, &ViewerView::ValueModified);
    Object::Connect(pProgressBuild, &ProgressBuild::BuildAllCompleted, this, &ViewerView::SlotFinishBuildRep);
    m_pSceneGenerator->StartBuildGeometry();
}

//-----------------------------------------------------------------------------
//
// ---
void ViewerView::SlotFinishBuildRep()
{
    GetViewport()->ZoomToFit(GetSceneContent()->GetBoundingBox(), 2.0);
    Invalidate();
}

void ViewerView::ValueModified(int /*val*/)
{
}

//-----------------------------------------------------------------------------
//
// ---
BOOL ViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    return COpenGLView::PreCreateWindow(cs);
}

//-----------------------------------------------------------------------------
// ViewerView drawing
// ---
void ViewerView::OnDraw(CDC* /*pDC*/)
{
    ViewerDocument* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
}

//-----------------------------------------------------------------------------
// ViewerView printing
// ---
void ViewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL ViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void ViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void ViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void ViewerView::OnRButtonUp(UINT /* nFlags */, CPoint /*/point*/)
{
    // ClientToScreen(&point);
    // OnContextMenu(this, point);
}

void ViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint /*point*/)
{
#ifndef SHARED_HANDLERS
    // theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ViewerView diagnostics
#ifdef _DEBUG
void ViewerView::AssertValid() const
{
    COpenGLView::AssertValid();
}

void ViewerView::Dump(CDumpContext& dc) const
{
    COpenGLView::Dump(dc);
}

ViewerDocument* ViewerView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ViewerDocument)));
    return (ViewerDocument*)m_pDocument;
}
#endif //_DEBUG

