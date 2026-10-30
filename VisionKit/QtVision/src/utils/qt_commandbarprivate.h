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
#ifndef __QT_COMMANDPRIVATE_H
#define __QT_COMMANDPRIVATE_H

#include <QToolBar>
#include <QToolButton>
#include <QWidget>

namespace VSN {
namespace QtVision {

//----------------------------------------------------------------------------------------
// The separator in the QtCommandBar.
// ---
class SeparatorArea : public QWidget
{
public:
    SeparatorArea(QWidget* parent = nullptr, QToolBar* parentToolBar_ = nullptr)
    : QWidget(parent)
    , m_parentToolBar(parentToolBar_)
    {}
    ~SeparatorArea() override;
    QSize sizeHint() const override;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QToolBar* m_parentToolBar;
};

//----------------------------------------------------------------------------------------
// The button in the QtCommandPage.
// ---
class CommandButton : public QToolButton
{
public:
    CommandButton(QWidget* parent = nullptr);
    ~CommandButton() override;
protected:
    void paintEvent(QPaintEvent* event) override;
};

//----------------------------------------------------------------------------------------
// The page switching button in the QtCommandBar.
// ---
class SwitchCommandButton : public QToolButton
{
public:
    SwitchCommandButton(QWidget* parentToolBar = nullptr);
    ~SwitchCommandButton() override;
protected:
    void paintEvent(QPaintEvent* event) override;
};

} // namespace QtVision
} // namespace VSN

#endif
