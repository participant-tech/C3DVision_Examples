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

#include <qt_modeldocument.h>
#include <conv_predefined.h>
#include <conv_model_exchange.h>
#include <conv_exchange_settings.h>
#include <attribute_container.h>
#include <QMessageBox>
#include <vsn_last.h>

//#pragma optimize("", off)

using namespace c3d;

namespace VSN {
namespace QtVision {

/* ModelDocument */
ModelDocument::ModelDocument(QObject* parent)
    : QObject(parent)
    , m_modelAttrs(nullptr)
    , m_modelEx(nullptr)
    , m_isModified(false)
{
}

// ----------------------------------------------------------------------------
//
// ---
ModelDocument::~ModelDocument()
{
    VSN_DELETE_AND_NULL(m_modelEx);
    VSN_DELETE_AND_NULL(m_modelAttrs);
}

// ---
MbAttributeContainer* ModelDocument::attributes() const { return m_modelAttrs; }
// ---
MxModelExtension* ModelDocument::model() const { return m_modelEx; }
// ---
bool ModelDocument::isModified() const { return m_modelEx != nullptr && m_isModified; }
// ---
void ModelDocument::setModified(bool isModified)
{
    if (isModified == m_isModified)
        return;
    m_isModified = isModified;
    emit modificationChanged(m_isModified);
}

// ----------------------------------------------------------------------------
//
// ---
bool ModelDocument::openFile(QFile& file)
{
    // you need to delete the old model before creating a new one
    VSN_DELETE_AND_NULL(m_modelEx);
    emit modelLoaded(false);

    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray byteData = file.readAll();

    C3DExchangeBuffer buffer;
    buffer.Init(byteData.constData(), byteData.length());
    ConvConvertorProperty3D convProperties;
    SPtr<MbModel> ptrModel(new MbModel);
    MbeConvResType readRes = ImportFromBuffer(*ptrModel, buffer, mxf_C3D, &convProperties, nullptr);
    if (readRes == cnv_Error)
    {
        ptrModel.reset();
        return false;
    }

    VSN_DELETE_AND_NULL(m_modelEx);
    m_modelEx = new MxModelExtension();
    m_isModified = false;

    // initialize the extended model
    MxResultCode result = m_modelEx->ImportFromC3DModel(*ptrModel);
    if (result == MxResultCode::Error) // model creation error
        return false;

    emit modelLoaded(true);
    emit contentsChanged(m_modelEx);
    return true;
}

// ----------------------------------------------------------------------------
// Open all selected files and merge them into one model(MbModel)
// ---
bool ModelDocument::openFiles(const QStringList& filesName)
{
    // you need to delete the old model before creating a new one
    VSN_DELETE_AND_NULL(m_modelEx);
    emit modelLoaded(false);

    SPtr<MbModel> ptrModel = c3d::make_sptr<MbModel>();
    for (int i = 0, count = filesName.count(); i < count; ++i)
    {
        QString fileName = filesName.at(i);
        if (fileName.isEmpty())
            continue;

        MbModel model;
        ConvConvertorProperty3D convProperties;
        convProperties.enableAutostitch = true;
        convProperties.autostitchPrecision = Math::visualSag;
        convProperties.fileName = c3d::WToPathstring(fileName.toStdWString());
        auto result = c3d::ImportFromFile(model, c3d::WToPathstring(fileName.toStdWString()), &convProperties, nullptr);
        //if (c3d::ImportFromFile(model, c3d::WToPathstring(fileName.toStdWString()), &convProperties, nullptr) == cnv_Success)
        if (cnv_Success == result)
        {
            for (auto iter = model.Begin(), last = model.End(); iter != last; ++iter)
                ptrModel->AddItem(*(*iter));
        }
        else
        {
            QMessageBox msgBox;
            QString strMessage("Error of processing file: " + fileName);
            msgBox.setText(strMessage);
            msgBox.exec();
            // return false;
            continue;
        }
        if (count == 1)
            ptrModel->AttributesAssign(model);
        emit numReadFileChanged(i);
    }

    if (ptrModel->AttributesCount() > 0)
    {
        if (m_modelAttrs == nullptr)
            m_modelAttrs = new MbAttributeContainer;
        m_modelAttrs->RemoveAttributes();
        m_modelAttrs->AttributesAssign(*ptrModel);
    }

    VSN_DELETE_AND_NULL(m_modelEx);
    m_modelEx = new MxModelExtension();
    setModified(m_isModified);

    // initialize the extended model
    MxResultCode result = m_modelEx->ImportFromC3DModel(*ptrModel);
    if (result == MxResultCode::Error) // model creation error
    {
        VSN_DELETE_AND_NULL(m_modelEx);
        return false;
    }

    emit modelLoaded(true);
    emit contentsChanged(m_modelEx);
    return true;
}

// ----------------------------------------------------------------------------
//
// ---
bool ModelDocument::save(const QString& fileName, bool& bSave)
{
    if (m_modelEx == nullptr)
        return false;

    auto readRes = m_modelEx->ExportToC3DModel();
    if (readRes.second == MxResultCode::Ok)
    {
        MbeConvResType readConvRes = c3d::ExportIntoFile(*readRes.first, c3d::WToPathstring(fileName.toStdWString()));
        if (readConvRes == cnv_Success)
        {
            bSave = true;
            return true;
        }
    }
    else
        Q_ASSERT(false);
    return false;
}


} // namespace QtVision
} // namespace VSN
