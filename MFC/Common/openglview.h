#ifndef __VSN_OPENGLVIEW_H
#define __VSN_OPENGLVIEW_H

#include <afxwin.h>
#include "mfc_openglview.h"
#include <vsn_global.h>

class ProcessManagerEx;
class BaseProcess;
class ProcessDefault;
class OpenGLViewPrivate;

////////////////////////////////////////////////////////////////////////////////
// OpenGLView view

class OpenGLView : public MfcVision::COpenGLView, public Object
{
    VSN_OBJECT(OpenGLView)
    DECLARE_DYNCREATE(OpenGLView)
protected:
    OpenGLView();  // protected constructor used by dynamic creation
private:
    /*! Maps the MFC button and Shift/Control state to abstracted Vision values */
    unsigned long MapFlags(unsigned long state);
    // Attributes
public:
    void UpdateSceneForModel(MbModel* pModel);
public:
    void SlotFinishBuildRep();
    // Operations
protected:
    /// \ru Функция вызывается после инициализации Vision. \en NO TRANSLATION. \~
    virtual void InitializeOpenGL();
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(OpenGLView)
public:
    //!< We overload the Create method to modify the CWnd window style; necessary for OpenGL support
#ifdef _UNICODE
    virtual BOOL Create(__wchar_t const * lpszClassName, __wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
    virtual BOOL Create(unsigned short const * lpszClassName, unsigned short const *  lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#else
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#endif
    virtual void OnInitialUpdate();
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
protected:
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    //!< We overload the PreCreateWindow method to modify the CWnd window class; necessary for OpenGL support
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

    // Implementation
protected:
    virtual ~OpenGLView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(OpenGLView)
    //  Overloaded CView method. Instructs Vision to traverse the scene-graph and update the display
    /*!
    Dispatches the OnMouseMove event to all event receivers that are registered for the OnMouseMove event type.
    */
    afx_msg void OnFileSaveAs();
    afx_msg void OnGouraudShaded();
    afx_msg void OnWireframe();
    afx_msg void OnHiddenline();
    afx_msg void OnZoom();
    afx_msg void OnZoomToExtents();
    afx_msg void OnZoomToWindow();
    afx_msg void OnOrbit();
    afx_msg void OnUpdateOrbit(CCmdUI* pCmdUI);
    afx_msg void OnPan();
    afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
    afx_msg void OnWindowSelect();
    afx_msg void OnUpdateWindowSelect(CCmdUI* pCmdUI);
    afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
    afx_msg void OnUpdateZoomToWindow(CCmdUI* pCmdUI);
    afx_msg void OnRunMyCode();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    VSN_DECLARE_PRIVATE(OpenGLView)
};

#endif // __VSN_OPENGLVIEW_H
