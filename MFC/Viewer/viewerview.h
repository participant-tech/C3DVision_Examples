
// viewerview.h : interface of the ViewerView class
//

#pragma once
#include "openglview.h"
#include <vsn_vision.h>
#include <vsn_global.h>

class ViewerView : public MfcVision::COpenGLView, public Object
{
    VSN_OBJECT(ViewerView)
        DECLARE_DYNCREATE(ViewerView)
protected: // create from serialization only
    ViewerView();
    // Attributes
public:
    ViewerDocument* GetDocument() const;
    void UpdateSceneForModel(SPtr<MbModel> pModel);
public:
    void SlotFinishBuildRep();
    void ValueModified(int val);
    // Operations
public:
    /// \ru Функция вызывается после инициализации Vision. \en NO TRANSLATION. \~
    virtual void InitializeOpenGL();
    // Overrides
public:
    VSN_SIGNAL(Public, CancelBuild, void CancelBuild())
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    // Implementation
public:
    virtual ~ViewerView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    SceneSegment* m_pModelSegment;
    SceneGenerator* m_pSceneGenerator;
    // Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCApplication1View.cpp
inline ViewerDocument* ViewerView::GetDocument() const
{
    return reinterpret_cast<ViewerDocument*>(m_pDocument);
}
#endif

