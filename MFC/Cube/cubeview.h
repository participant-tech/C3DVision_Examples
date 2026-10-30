#ifndef __CUBEVIEW_H
#define __CUBEVIEW_H

#include <afxwin.h>
#include <vsn_vision.h>
#include <mfc_openglwnd.h>

/* CubeView */
class CubeView : public MfcVision::COpenGLWnd
{
public:
    CubeView();
    virtual ~CubeView();
protected:
    virtual void InitializeOpenGL();
public:
    //{{AFX_MSG(MFCContext
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnDestroy();
protected:
    DECLARE_MESSAGE_MAP()
};

#endif /* __CUBEVIEW_H */
