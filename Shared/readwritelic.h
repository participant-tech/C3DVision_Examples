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
  \file Класс ReadWriteLic представляет статические методы для загрузки, сохранения и
        применения ключа из файла c3d.lic, который располагается в папке пользователя.
  \brief \ru
         \en NO TRANSLATION \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_READWRITELIC_H
#define __VSN_READWRITELIC_H

#include <string>
#include <vsn_global.h>

class ReadWriteLic
{
public:
    /// \ru Применить ключ. \en NO TRANSLATION
    bool static ApplyKey(const std::string& key, const std::string& signature);
    /// \ru Загрузить ключ. \en NO TRANSLATION
    bool static LoadKey(std::string& key, std::string& signature);
    /// \ru Сохранить ключ. \en NO TRANSLATION
    bool static SaveKey(const std::string& key, const std::string& signature);

private:
    /// \ru NO TRANSLATION \en NO TRANSLATION
    std::string  static LicenseFilePath();
private:
    static const std::string m_keyFile;
    static const std::string m_path;
};

#endif /* __VSN_READWRITELIC_H */
