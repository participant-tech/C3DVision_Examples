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

#include <readwritelic.h>
#include <tool_enabler.h>

#include <fstream>
#include <list>
#include <stdlib.h>
#include <vsn_last.h>

const std::string ReadWriteLic::m_keyFile = "c3d.lic";
#ifdef VSN_OS_WIN
const std::string ReadWriteLic::m_path = "\\";
#else
const std::string ReadWriteLic::m_path = "//";
#endif

//-----------------------------------------------------------------------------
// 
// ---
#ifdef VSN_OS_WIN
#else
void /*errno_t*/ vsn_getenv_s(size_t* requiredCount, char* buffer, size_t const bufferCount, char const* varName)
{
    const char* env = getenv(varName);
    if (env)
    {
        *(requiredCount) = strlen(env) + 1;
        if (bufferCount > *(requiredCount))
        {
            memcpy(buffer, env, *(requiredCount));
            return;
        }
    }

    *(requiredCount) = 0;
    memcpy(buffer, "\0", 1);
}
#endif

//-----------------------------------------------------------------------------
// 
// ---
std::string ReadWriteLic::LicenseFilePath()
{
    const size_t bufferSize = 255;
    char buffer[bufferSize];
    std::string strEmpty = "";

    size_t sizes = bufferSize;
#ifdef VSN_OS_WIN
    getenv_s(&sizes, buffer, bufferSize, "HOMEDRIVE");
#else
    vsn_getenv_s(&sizes, buffer, bufferSize, "HOME");
#endif
    if (sizes == 0) return strEmpty;
    std::string res(buffer, sizes - 1);

    sizes = bufferSize;
#ifdef VSN_OS_WIN
    getenv_s(&sizes, buffer, bufferSize, "HOMEPATH");
    if (sizes == 0) return strEmpty;
    res = res + std::string(buffer, sizes - 1);
#endif

    return res + m_path + m_keyFile;
}

//-----------------------------------------------------------------------------
// 
// ---
bool ReadWriteLic::ApplyKey(const std::string& key, const std::string& signature)
{
    ::EnableMathModules(key.c_str(), static_cast<int>(key.length()), signature.c_str(), static_cast<int>(signature.length()));
    return IsMathVisionEnable();
}

//-----------------------------------------------------------------------------
// 
// ---
bool ReadWriteLic::SaveKey(const std::string& key, const std::string& signature)
{
    bool isLicenseEnable = false;
    std::fstream licenseFile;
    std::list<std::string> dataList;

    dataList.push_back(key.data());
    dataList.push_back(signature.data());
    licenseFile.open(LicenseFilePath(), std::fstream::out | std::fstream::in);
    isLicenseEnable = licenseFile.is_open();
    if (isLicenseEnable)
    {
        licenseFile.seekg(0, std::ios_base::end);
        std::streampos sizeFile = licenseFile.tellg();
        licenseFile.seekg(0, std::ios_base::beg);

        if (sizeFile != std::streampos(0))
        {
            std::string buffer;
            while (std::getline(licenseFile, buffer))
            {
                dataList.push_back(buffer);
                buffer = std::string();
            }
        }

        licenseFile.close();
    }

    licenseFile.open(LicenseFilePath(), std::fstream::out | std::fstream::trunc);
    isLicenseEnable = licenseFile.is_open();
    if (isLicenseEnable)
    {
        for (auto iter = dataList.begin(); iter != dataList.end(); iter++)
        {
            licenseFile << *(iter);
            if (iter != (--dataList.cend())) licenseFile << std::endl;
        }
    }

    return isLicenseEnable;
}

//-----------------------------------------------------------------------------
// 
// ---
bool ReadWriteLic::LoadKey(std::string& key, std::string& signature)
{
    bool isLicenseEnable = false;
    std::string buffer;
    std::ifstream licenseFile;

    licenseFile.open(LicenseFilePath(), std::ios::in);
    if (licenseFile.is_open())
    {
        do
        {
            std::getline(licenseFile, buffer);
            key = buffer;
            buffer = std::string();

            std::getline(licenseFile, buffer);
            signature = buffer;
            buffer = std::string();

            isLicenseEnable = ApplyKey(key, signature);
        } while (!isLicenseEnable && !licenseFile.fail());
        licenseFile.close();
    }

    return isLicenseEnable;
}
