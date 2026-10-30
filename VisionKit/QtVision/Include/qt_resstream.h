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

////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поток для загрузки Qt ресурсов.
         \en Stream for loading Qt resources. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __QT_RESSTREAM_H
#define __QT_RESSTREAM_H

#include <QResource>
#include <vsn_resourcestream.h>

namespace VSN {
namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtResStream служит для загрузки Qt ресурсов.
           \en Class QtResStream is needed to load Qt resources. \~
    \ingroup Vision_OpenGL
*/
// ---
class QtResStream : public ResourceStream
{
public:
    QtResStream(const QString & res)
        : ResourceStream()
        , m_resource(res)
    {
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
        if (m_resource.isCompressed())
#else
        if (m_resource.compressionAlgorithm() != QResource::NoCompression)
#endif
        {
            m_pUncompressData = qUncompress(m_resource.data(), m_resource.size());
            size_t length = m_pUncompressData.size();
            Init(m_pUncompressData.data(), length);
        }
        else
        {
            size_t length = m_resource.size();
            Init(m_resource.data(), length);
        }
    }
private:
    QResource  m_resource;
    QByteArray m_pUncompressData;
};

} // namespace QtVision

} // namespace VSN

#endif //__QT_RESSTREAM_H

