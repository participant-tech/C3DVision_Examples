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

#ifndef __QT_SAVEFILE_H
#define __QT_SAVEFILE_H

#include <QFile>

QT_BEGIN_NAMESPACE
class QTemporaryFile;
QT_END_NAMESPACE

#include <memory>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* SaveFile */
class SaveFile : public QFile
{
    Q_OBJECT
public:
    explicit SaveFile(const QString &filename);
    ~SaveFile() override;

    bool open(OpenMode flags = QIODevice::WriteOnly) override;

    void rollback();
    bool commit();

    static void initializeUmask();
private:
    const QString m_finalFileName;
    std::unique_ptr<QTemporaryFile> m_tempFile;
    bool m_finalized = true;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_SAVEFILE_H */
