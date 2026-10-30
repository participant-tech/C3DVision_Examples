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

///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_MODELDOCUMENT_H
#define __QT_MODELDOCUMENT_H

#include <QObject>
#include <QFile>
#include <mx_model_extension.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* ModelDocument */
class QT_CLASS ModelDocument : public QObject
{
    Q_OBJECT
public:
    ModelDocument(QObject* parent = nullptr);
    ~ModelDocument();
public:
    bool isModified() const;
    MbAttributeContainer* attributes() const;
    MxModelExtension* model() const;

    bool openFile(QFile& file);
    bool openFiles(const QStringList& filesName);
    bool save(const QString& fileName, bool& bSave);
public Q_SLOTS:
    void setModified(bool isModified = true);
Q_SIGNALS:
    void contentsChanged(MxModelExtension* pModelEx);
    void modelLoaded(bool);
    void numReadFileChanged(int numFile);
    void modificationChanged(bool m);
private:
    MbAttributeContainer* m_modelAttrs;
    MxModelExtension* m_modelEx;
    bool m_isModified = false;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MODELDOCUMENT_H */
