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
#ifndef __QT_COMMANDBAR_H
#define __QT_COMMANDBAR_H

#include <QGridLayout>
#include <QStackedWidget>
#include <QToolBar>
#include <QWidget>

#include <qt_commandbarprivate.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class QtCommandBar;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtCommandPage - это виджет, представляющий собой страницу с действиями
               на панели инструментов QtCommandBar.
           \en QtCommandPage class is a widget that represents a page with actions on the QtCommandBar. \~
*/
// ---
class QT_CLASS QtCommandPage : public QWidget
{
    Q_OBJECT
public:
    QtCommandPage(QWidget* parent = nullptr, QtCommandBar* parentToolBar_ = nullptr);
    ~QtCommandPage() override;
    QSize sizeHint() const override;
public:
    void addAction(QAction* action);
    // void removeAction(QAction* action); //TODO

    int rowsNumber() const;
    int columnsNumber() const;
    void setColumnsNumber(const int columnsNumber_);

    QSize buttonSize() const;
    void setButtonSize(const QSize&);
protected:
    void paintEvent(QPaintEvent* event) override;
private slots:
    void updateButtonsSize();
    void updatePage();
private:
    QSize buttonSizeWithoutStyle() const;
    QToolButton* createCommandButton(QAction* action);

    void clearGridLayout();
    void addWidgetsIntoGridLayout();
    void setSpacerItems();
private:
    QtCommandBar* m_parentToolBar;
    QGridLayout* m_gridLayout;
    QList<QToolButton*> m_commandButtons;
    int m_columnsNumber;
    QSize m_buttonSize;
};

class SeparatorArea;
class SwitchCommandButton;

//------------------------------------------------------------------------------
/** \brief \ru Класс QtCommandBar - панель инструментов с управляющими кнопками и
               соответствующими им страницами с действиями.
           \en QtCommandBar class is a toolbar with switch buttons and their corresponding pages with actions. \~
*/
// ---
class QT_CLASS QtCommandBar : public QToolBar
{
    Q_OBJECT
public:
    QtCommandBar(QWidget* parent = nullptr);
    ~QtCommandBar() override;
    QSize sizeHint() const override;
    QSize switchButtonSizeHint() const;
public:
    QtCommandPage* addPage(const QIcon& icon, QtCommandPage* commandPage = nullptr);
    void removePage(QtCommandPage* commandPage); //TODO

    int switchCommandsColumnsNumber() const;
    void setSwitchCommandsColumnsNumber(const int columnsNumber_);

    int switchCommandsRowsNumber() const;

    int commandPageColumnsNumber() const;
    void setCommandPageColumnsNumber(const int columnsNumber_);

    int switchButtonToCommandButtonRatio() const;
    void setSwitchButtonToCommandButtonRatio(const int ratio_);
private slots:
    void updateContent();
    void updateSwitchArea();
    void onOrientationChanged();
private:
    enum class DimType {Width = 0, Height = 1};
private:
    void membersInitialization();
    void clearGridLayout(QGridLayout* gridLayout_);
    void addWidgetsIntoGridLayout(std::vector<int>::iterator rIt, std::vector<int>::iterator cIt);

    void addSwitchCommand(const QIcon& icon);
    void addCommandPage(QtCommandPage* commandPage);

    int calcCommandPageColumnsNumber() const;

    int calcDimension(const DimType&) const;
    QRect calcGripRect() const;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QWidget* m_baseWidget;
    QGridLayout* m_gridLayout;
    SeparatorArea* m_separator;

    QWidget* m_switchCommandsWidget;
    QGridLayout* m_switchCommandsLayout;
    QButtonGroup* m_buttonGroup;
    QList<SwitchCommandButton*> m_switchCommands;

    QStackedWidget* m_stackedWidget;
    QList<QtCommandPage*> m_commandPages;

    int m_switchCommandsColumnsNumber;
    int m_commandPageColumnsNumber;
    double m_switchButtonToCommandButtonRatio;
};

} // namespace QtVision
} // namespace VSN

#endif
