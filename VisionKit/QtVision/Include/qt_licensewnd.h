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

#ifndef __QT_LICENSEWND_H
#define __QT_LICENSEWND_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <qt_global.h>

namespace VSN {

namespace QtVision {

//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n.
             \en NO TRANSLATION. \n \~
*/
// ---
class QT_CLASS LicenseWnd : public QDialog
{
    Q_OBJECT
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    LicenseWnd();
    /// \ru Деструктор. \en Destructor.
    virtual ~LicenseWnd();
public:
    /// \ru NO TRANSLATION \en NO TRANSLATION
    bool Activate();
private slots:
    /// \ru NO TRANSLATION \en NO TRANSLATION
    void OnActivateClicked();
    /// \ru NO TRANSLATION \en NO TRANSLATION
    void OnContinueClicked();
private:
    QLineEdit* m_editKey = nullptr;
    QPlainTextEdit* m_editSignature = nullptr;
    QCheckBox* m_checkSaveKey = nullptr;
private:
    Q_DISABLE_COPY(LicenseWnd)
};

} // namespace QtVision

} // namespace VSN

#endif /* __QT_LICENSEWND_H */
