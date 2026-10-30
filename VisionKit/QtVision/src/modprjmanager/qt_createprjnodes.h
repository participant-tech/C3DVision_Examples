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
#ifndef __QT_CREATEPRJNODES_H
#define __QT_CREATEPRJNODES_H

#include <QObject>
#include <mx_model_extension.h>
#include <qt_modelnodes.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* MathModelNode */
class MathModelNode : public ProjectNode
{
public:
    explicit MathModelNode(const QString& displayName);
    ~MathModelNode();
public:
    MxModelExtension* mathModel() const;
    void setMathModel(MxModelExtension* modelExt);
private:
    MxModelExtension* m_modelExt;
};

/* CheckableNode */
class CheckableNode : public FolderNode
{
public:
    explicit CheckableNode(const QString& displayName);
    ~CheckableNode();
public:
    bool supportsAction(ProjectAction action, const Node* node) const override;
    Qt::CheckState checked() const override { return m_state; }
    void setCheck(Qt::CheckState state) override;
private:
    Qt::CheckState m_state  = Qt::Checked;
};

/* MxGrItemNode */
class MxGrItemNode : public CheckableNode
{
public:
    explicit MxGrItemNode(const QString& displayName, const MxGrItem& mxGrItem);
public:
    MxGrItem mxItem() const;
protected:
    MxGrItem m_mxGrItem;
};

/* AssemblyNode */
class AssemblyNode : public MxGrItemNode
{
public:
    explicit AssemblyNode(const QString& displayName, const MxGrItem& mxGrItem);
};

/* BodyNode */
class BodyNode : public MxGrItemNode
{
public:
    explicit BodyNode(const QString& displayName, const MxGrItem& mxGrItem);
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_CREATEPRJNODES_H */
