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

#include <qt_licensewnd.h>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>
#include <readwritelic.h>
#include <vsn_last.h>


using namespace VSN;
using namespace QtVision;

///////////////////////////////////////////////////////////////////////////////
//
// класс LicenseWnd
//
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// конструктор по умолчанию
// ---
LicenseWnd::LicenseWnd()
{
}

//-----------------------------------------------------------------------------
// деструктор
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

    auto labelLicense = new QLabel;
    labelLicense->setText(QObject::tr("The current license key is missing or wrong. Please enter your license key to activate."));
    labelLicense->setAlignment(Qt::AlignCenter);

    auto formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight);

    m_editKey = new QLineEdit();
    m_editSignature = new QPlainTextEdit();

    formLayout->addRow(QObject::tr("License key"), m_editKey);
    formLayout->addRow(QObject::tr("Signature"), m_editSignature);

    m_checkSaveKey = new QCheckBox;
    m_checkSaveKey->setText(QObject::tr("Save this license key"));

    auto buttonActivate = new QPushButton;
    auto buttonContinue = new QPushButton;

    buttonActivate->setFixedWidth(170);
    buttonContinue->setFixedWidth(170);

    buttonActivate->setText(QObject::tr("Activate"));
    buttonContinue->setText(QObject::tr("Continue without key"));

    buttonContinue->setDefault(true);

    auto buttons = new QHBoxLayout();
    buttons->addWidget(buttonActivate);
    buttons->addWidget(buttonContinue);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowIcon(QIcon(":/res/crystal.ico"));

    auto vLayout = new QVBoxLayout(this);
    vLayout->setSizeConstraint(QLayout::SetFixedSize);

    vLayout->addWidget(labelLicense);
    vLayout->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vLayout->addLayout(formLayout);
    vLayout->addWidget(m_checkSaveKey);
    vLayout->addLayout(buttons);

    QObject::connect(buttonActivate, SIGNAL(clicked()), this, SLOT(OnActivateClicked()));
    QObject::connect(buttonContinue, SIGNAL(clicked()), this, SLOT(OnContinueClicked()));
    return (exec() == Accepted);
}

//-----------------------------------------------------------------------------
// 
// ---
void LicenseWnd::OnActivateClicked()
{
    VSN_ASSERT(m_editKey);
    VSN_ASSERT(m_editSignature);
    VSN_ASSERT(m_checkSaveKey);

    const std::string key = m_editKey->text().trimmed().toStdString();
    const std::string signature = m_editSignature->toPlainText().trimmed().toStdString();

    if (ReadWriteLic::ApplyKey(key, signature))
    {
        const bool saveKeyFlag = (m_checkSaveKey->checkState() == Qt::CheckState::Checked);
        if (saveKeyFlag)
            ReadWriteLic::SaveKey(key, signature);
        accept();
    }
    else
        QMessageBox::warning(nullptr, QObject::tr("Warning"), QObject::tr("Invalid license key. For a new license, please contact C3D Labs."));
}

//-----------------------------------------------------------------------------
// 
// ---
void LicenseWnd::OnContinueClicked()
{
    accept();
}
