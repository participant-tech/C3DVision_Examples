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

#include <qt_createprjnodes.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* MathModelNode */
MathModelNode::MathModelNode(const QString& displayName)
    : ProjectNode(displayName)
    , m_modelExt(nullptr)
{
}

// ----------------------------------------------------------------------------
// 
// ---
MathModelNode::~MathModelNode()
{
}

// ---
MxModelExtension* MathModelNode::mathModel() const { return m_modelExt; }
// ---
void MathModelNode::setMathModel(MxModelExtension* modelExt)
{
    m_modelExt = modelExt;
}

/* CheckableNode*/
CheckableNode::CheckableNode(const QString& displayName)
    : FolderNode(displayName)
{
    setCheckable(true);
}

// ----------------------------------------------------------------------------
// 
// ---
CheckableNode::~CheckableNode()
{
}

// ----------------------------------------------------------------------------
// 
// ---
bool CheckableNode::supportsAction(ProjectAction action, const Node* node) const
{
    if (node != this || !isCheckable())
        return false;
    return action == Check || action == Rename;
}

// ----------------------------------------------------------------------------
// 
// ---
void CheckableNode::setCheck(Qt::CheckState state)
{
    m_state = state;
}

/* MxGrItemNode */
MxGrItemNode::MxGrItemNode(const QString& displayName, const MxGrItem& mxGrItem)
    : CheckableNode(displayName)
    , m_mxGrItem(mxGrItem)
{
}

// ---
MxGrItem MxGrItemNode::mxItem() const { return m_mxGrItem; }

/* AssemblyNode */
AssemblyNode::AssemblyNode(const QString& displayName, const MxGrItem& mxGrItem)
    : MxGrItemNode(displayName, mxGrItem)
{
    m_icon = QIcon(":/res/assemb.ico"); // only safe from UI thread
}

/* BodyNode */
BodyNode::BodyNode(const QString& displayName, const MxGrItem& mxGrItem)
    : MxGrItemNode(displayName, mxGrItem)
{
    m_icon = QIcon(":/res/detail.ico"); // only safe from UI thread
}

} // namespace QtVision
} // namespace VSN
