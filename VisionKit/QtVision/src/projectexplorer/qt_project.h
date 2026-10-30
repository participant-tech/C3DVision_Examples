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
#ifndef __QT_PROJECT_H
#define __QT_PROJECT_H

#include <QObject>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class FolderNode;
class ProjectNode;
class ContainerNode;
/* Project */
class Project : public QObject
{
public:
    explicit Project(QObject* parent = nullptr);
    ~Project() override;
public:
    QString displayName() const;

    ContainerNode* containerNode() const;
    virtual ProjectNode* rootProjectNode() const;
    void setRootProjectNode(std::unique_ptr<ProjectNode>&& root);
private:
    void handleSubTreeChanged(FolderNode* node);
private:
    std::unique_ptr<ProjectNode> m_rootProjectNode;
    std::unique_ptr<ContainerNode> m_containerNode;
    QString m_displayName;
private:
    Q_DISABLE_COPY(Project);
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROJECT_H */
