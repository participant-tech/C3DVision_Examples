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

#ifndef __EXAMPLEVIEW_H
#define __EXAMPLEVIEW_H
#ifdef ENABLE_VLD
  #include <vld.h>
#endif
#include <afxwin.h>
#include <mfc_visiondef.h>
#include <vsn_vision.h>
#include <mfc_openglwnd.h>

namespace VSN {

namespace MfcVision {

class MFC_CLASS ExampleView : public COpenGLWnd
{
public:
    ExampleView();
    virtual ~ExampleView();
protected:
    virtual void InitializeOpenGL();
public:
    //{{AFX_MSG(MFCContext
    afx_msg void OnDestroy();
protected:
    DECLARE_MESSAGE_MAP()
};

} // namespace MfcVision

} // namespace VSN
#endif /* __EXAMPLEVIEW_H */
