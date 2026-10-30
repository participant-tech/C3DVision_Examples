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

#ifndef __MFC_LICENSEWND_H
#define __MFC_LICENSEWND_H
#ifdef ENABLE_VLD
  #include <vld.h>
#endif
#include <afxwin.h>
#include <mfc_visiondef.h>

namespace VSN {

namespace MfcVision {

//------------------------------------------------------------------------------
/** \brief \ru Класс окна для активации лицензии.
           \en License activation window class. \~
*/
// ---
class MFC_CLASS LicenseWnd : public CDialog
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    LicenseWnd();
    /// \ru Деструктор. \en Destructor.
    ~LicenseWnd();
public:
    /// \ru NO TRANSLATION \en NO TRANSLATION
    bool Activate();
protected:
    DECLARE_MESSAGE_MAP()
private:
    enum
    {
        IDC_BUTTON_ACTIVATE = 1004,
        IDC_BUTTON_CONTINUE = 1005,
    };
private:
    /// \ru NO TRANSLATION \en NO TRANSLATION
    BOOL OnInitDialog() override;
    /// \ru NO TRANSLATION \en NO TRANSLATION
    afx_msg void OnActivateClick();
    /// \ru NO TRANSLATION \en NO TRANSLATION
    afx_msg void OnContinueClick();
private:
    std::unique_ptr<CFont> m_GuiFont;
    std::unique_ptr<CStatic> m_staticInfo;
    std::unique_ptr<CStatic> m_staticKey;
    std::unique_ptr<CStatic> m_staticSignature;

    std::unique_ptr<CEdit> m_editKey;
    std::unique_ptr<CEdit> m_editSignature;

    std::unique_ptr<CButton> m_checkSaveKey;

    std::unique_ptr<CButton> m_buttonActivate;
    std::unique_ptr<CButton> m_buttonContinue;
};

} // namespace MfcVision

} // namespace VSN

#endif /* __MFC_LICENSEWND_H */
