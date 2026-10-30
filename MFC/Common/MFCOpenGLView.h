#ifndef __MFC_OPENGLVIEW_H
#define __MFC_OPENGLVIEW_H

#include <afxwin.h>
#include <vsn_graphicssceneview.h>

// W A R N I N G 
//
// This file is not part of the C3D Vision API. It exists only as the implementation of certain tasks. 
// This header file may change from version to version without notice, or even be removed.
//

class ProcessManagerEx;
class BaseProcess;
class ProcessDefault;

////////////////////////////////////////////////////////////////////////////////
// CMFCOpenGLView view

class CMFCOpenGLView : public CView
{
  DECLARE_DYNCREATE(CMFCOpenGLView)
protected:
  CMFCOpenGLView();  // protected constructor used by dynamic creation

// Attributes
public:
  virtual GraphicsSceneView* CreateGraphicsSceneView() = 0;

// Operations
protected:
//  MbCube GetTotalBoundingBox() const;

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMFCOpenGLView)
public:
    /// \ru Прегрузка метода необходима для модификации стиля CWnd это необходимо для поддержки OpenGL. \en Overloading the Create method to modify the CWnd window style, necessary for OpenGL support. 
#ifdef _UNICODE
    virtual BOOL Create(__wchar_t const * lpszClassName, __wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
    virtual BOOL Create(unsigned short const * lpszClassName, unsigned short const *  lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#else
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#endif
  /// \ru Прегрузка метода необходима для некоторй инициализации Vision'а. \en Method overloading is necessary for some initialization Vision. 
  virtual void OnInitialUpdate();
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

protected:
  virtual void OnDraw(CDC* pDC);  //!< overridden but currently does nothing
  virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
  /// \ru Прегрузка метода необходима для модификации класса CWnd это необходимо для поддержки OpenGL. \en Overloading the PreCreateWindow method to modify the CWnd necessary for OpenGL support. 
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //}}AFX_VIRTUAL

// Implementation
protected:
  virtual ~CMFCOpenGLView();

protected:
  GraphicsSceneView* m_pSceneView; ///< \ru NO TRANSLATION. \en Pointer to GraphicsScene MVP object associated with this CView object.

protected:
  /// \ru NO TRANSLATION. \en Maps the MFC button and Shift/Control state to abstracted Vision/MVP values.
  unsigned long InitMapFlags( unsigned long state );

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  // Generated message map functions
protected:
  //{{AFX_MSG(CMFCOpenGLView)
  //  Overloaded CView method. Instructs Vision to traverse the scene-graph and update the display
  afx_msg void OnPaint();
  /// \ru NO TRANSLATION. \en Dispatches the OnLButtonDown event to all event listeners that are registered for the OnLButtonDown event type.The GUI specific flags are mapped to Vision/MVP abstracted flags use the CMFCOpenGLView::MapFlags method.
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  /// \ru NO TRANSLATION. \en Dispatches the OnMouseMove event to all event listeners that are registered for the OnMouseMove event type. The GUI specific flags are mapped to Vision/MVP abstracted flags use the CMFCOpenGLView::MapFlags method.
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  /// \ru NO TRANSLATION. \en Dispatches the OnLButtonUp event to all event listeners that are registered for the OnLButtonUp event type. The GUI specific flags are mapped to Vision/MVP abstracted flags use the CHoopsView::MapFlags method.
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  /// \ru NO TRANSLATION. \en Dispatches the OnMouseWheel event to all event listeners that are registered for the OnMouseWheel event type. The GUI specific flags are mapped to Vision/MVP abstracted flags use the CMFCOpenGLView::MapFlags method.
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnDestroy();
  afx_msg void OnFileSaveAs();
  afx_msg void OnRunMyCode();
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif // __MFC_OPENGLVIEW_H
