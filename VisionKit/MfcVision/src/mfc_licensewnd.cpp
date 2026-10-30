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

#include <mfc_licensewnd.h>
#include <readwritelic.h>
#include <vsn_last.h>

namespace VSN {

namespace MfcVision {

//-----------------------------------------------------------------------------
// 
// ---
static inline std::string GetEditText(const CEdit& edit)
{
    CString value;
    edit.GetWindowText(value);
    return std::string(CStringA(value).Trim());
}

// LicenseWnd

BEGIN_MESSAGE_MAP(LicenseWnd, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ACTIVATE, &LicenseWnd::OnActivateClick)
    ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &LicenseWnd::OnContinueClick)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
// 
// ---
LicenseWnd::LicenseWnd()
{
    static DLGTEMPLATE dlgTemplate;

    dlgTemplate.style = WS_BORDER | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU | DS_3DLOOK | DS_CENTER;

    dlgTemplate.dwExtendedStyle = 0;

    dlgTemplate.cdit = 0;
    dlgTemplate.x = 0;
    dlgTemplate.y = 0;

    dlgTemplate.cx = 350;
    dlgTemplate.cy = 230;

    BOOL ret = InitModalIndirect(&dlgTemplate);
    VSN_UNUSED(ret);
}

//-----------------------------------------------------------------------------
// 
// ---
LicenseWnd::~LicenseWnd()
{
}

//-----------------------------------------------------------------------------
// 
// ---
bool LicenseWnd::Activate()
{
    std::string key;
    std::string signature;
    if (ReadWriteLic::LoadKey(key, signature)) return true;

    return (DoModal() == IDOK);
}

//-----------------------------------------------------------------------------
// 
// ---
BOOL LicenseWnd::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetWindowText(AfxGetApp()->m_pszAppName);

    NONCLIENTMETRICS metrics;
    metrics.cbSize = sizeof(NONCLIENTMETRICS);
    ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &metrics, 0);

    m_GuiFont = std::make_unique<CFont>();
    m_GuiFont->CreateFontIndirect(&metrics.lfMessageFont);

    RECT rctClient;
    GetClientRect(&rctClient);

    const int clientWidth = rctClient.right;

    TEXTMETRIC textMetrics;

    CDC* dc = GetDC();
    dc->GetTextMetrics(&textMetrics);
    ReleaseDC(dc);

    const int textHeight = textMetrics.tmHeight + textMetrics.tmExternalLeading + 5;

    m_staticInfo = std::make_unique<CStatic>();
    m_staticInfo->Create(_TEXT("The current license key is missing or wrong. Please enter your license key to activate."),
        WS_CHILD | WS_VISIBLE | SS_CENTER, {10, 10, clientWidth - 10, 10 + textHeight}, this);
    m_staticInfo->SetFont(m_GuiFont.get());

    m_staticKey = std::make_unique<CStatic>();
    m_staticKey->Create(_TEXT("License key"), WS_CHILD | WS_VISIBLE | SS_RIGHT, {10, 50, 100, 50 + textHeight}, this);
    m_staticKey->SetFont(m_GuiFont.get());

    m_staticSignature = std::make_unique<CStatic>();
    m_staticSignature->Create(_TEXT("Signature"), WS_CHILD | WS_VISIBLE | SS_RIGHT, {10, 80, 100, 80 + textHeight}, this);
    m_staticSignature->SetFont(m_GuiFont.get());

    m_editKey = std::make_unique<CEdit>();
    m_editKey->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL, {110, 50, clientWidth - 10, 50 + textHeight}, this, 0);
    m_editKey->SetFont(m_GuiFont.get());

    const int editBottom = rctClient.bottom - 90;

    m_editSignature = std::make_unique<CEdit>();
    m_editSignature->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_TABSTOP, {110, 80, clientWidth - 10, editBottom}, this, 0);
    m_editSignature->SetFont(m_GuiFont.get());

    m_checkSaveKey = std::make_unique<CButton>();
    m_checkSaveKey->Create(_TEXT("Save this license key"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP,
        {10, editBottom + 10, clientWidth / 2, editBottom + 10 + textHeight}, this, 0);
    m_checkSaveKey->SetFont(m_GuiFont.get());

    const int buttonWidth = 170;
    const int quarterWindowWidth = clientWidth / 4;

    m_buttonActivate = std::make_unique<CButton>();
    m_buttonActivate->Create(_TEXT("Activate"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
        {quarterWindowWidth - buttonWidth / 2, editBottom + 50, quarterWindowWidth + buttonWidth / 2, editBottom + 50 + 27}, this, IDC_BUTTON_ACTIVATE);
    m_buttonActivate->SetFont(m_GuiFont.get());

    m_buttonContinue = std::make_unique<CButton>();
    m_buttonContinue->Create(_TEXT("Continue without key"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
        {quarterWindowWidth * 3 - buttonWidth / 2, editBottom + 50, quarterWindowWidth * 3 + buttonWidth / 2, editBottom + 50 + 27}, this, IDC_BUTTON_CONTINUE);
    m_buttonContinue->SetFont(m_GuiFont.get());

    return TRUE;
}

//-----------------------------------------------------------------------------
// 
// ---
void LicenseWnd::OnActivateClick()
{
    VSN_ASSERT(m_editKey);
    VSN_ASSERT(m_editSignature);
    VSN_ASSERT(m_checkSaveKey);

    const std::string key = GetEditText(*m_editKey);
    const std::string signature = GetEditText(*m_editSignature);
    if (ReadWriteLic::ApplyKey(key, signature))
    {
        const bool saveKeyFlag = (m_checkSaveKey->GetCheck() == BST_CHECKED);
        if (saveKeyFlag)
            ReadWriteLic::SaveKey(key, signature);

        EndDialog(IDOK);
    }
    else
        AfxMessageBox(_T("Invalid license key. For a new license, please contact C3D Labs."), MB_OK | MB_ICONWARNING);
}

//-----------------------------------------------------------------------------
// 
// ---
void LicenseWnd::OnContinueClick()
{
    EndDialog(IDOK);
}

} // namespace MfcVision

} // namespace VSN
