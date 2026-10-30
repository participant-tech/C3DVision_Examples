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

#include <qt_commandbar.h>
#include <qt_commandbarprivate.h>

#include <QButtonGroup>
#include <QMainWindow>
#include <QPainter>
#include <QStyleOption>

#include <vsn_last.h>

// #define DEBUG_LAYOUT_TURN_ON


//------------------------------------------------------------------------------
/** QtCommandBar consists of a switch buttons area and corresponding pages with actions.
    In the case of a single page, the switch buttons area is not displayed.

    Example of using a QtCommandBar:

    QtCommandBar* commandBar = new QtCommandBar(this);

    QtCommandPage* commandPage1 = commandBar->addPage(icon1);
    commandPage1->addAction(action11);
    commandPage1->addAction(action12);
    commandPage1->addAction(action13);
    commandPage1->addAction(action14);

    QtCommandPage* commandPage2 = commandBar->addPage(icon2);
    commandPage2->addAction(action21);
    commandPage2->addAction(action22);
    commandPage2->addAction(action23);

    QtCommandPage* commandPage3 = commandBar->addPage(icon3);
    commandPage3->addAction(action31);

    QtCommandPage* commandPageUser = new QtCommandPage(commandBar, commandBar);
    commandBar->addPage(icon4, commandPageUser);
    commandPageUser->setColumnsNumber(3);
    commandPageUser->addAction(action41);
    commandPageUser->addAction(action42);
    commandPageUser->addAction(action43);

    auto qsize = commandBar->iconSize();
    qsize.scale(30, 30, Qt::KeepAspectRatio);
    commandBar->setIconSize(qsize);

    addToolBar(Qt::LeftToolBarArea, commandBar);
*/
// ---

namespace VSN {
namespace QtVision {

//-----------------------------------------------------------------------------
// 
// ---
SeparatorArea::~SeparatorArea()
{}

//-----------------------------------------------------------------------------
// 
// ---
QSize SeparatorArea::sizeHint() const
{
    QStyleOption opt;
    opt.initFrom(this);
    if (m_parentToolBar->orientation() == Qt::Horizontal)
        opt.state |= QStyle::State_Horizontal;

    const int extent = style()->pixelMetric(QStyle::PM_ToolBarSeparatorExtent, &opt, parentWidget());
    return QSize(extent, extent);
}

//-----------------------------------------------------------------------------
// 
// ---
void SeparatorArea::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QStyleOption opt;
    opt.initFrom(this);
    if (m_parentToolBar->orientation() == Qt::Horizontal)
        opt.state |= QStyle::State_Horizontal;

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_IndicatorToolBarSeparator, &opt, &p, parentWidget());
}

//-----------------------------------------------------------------------------
// 
// ---
QtCommandPage::QtCommandPage(QWidget* parent, QtCommandBar* parentToolBar_)
: QWidget(parent)
, m_parentToolBar(parentToolBar_)
, m_gridLayout(nullptr)
, m_commandButtons()
, m_columnsNumber(2)
, m_buttonSize(QSize(50, 50))
{
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    setSpacerItems();
    setLayout(m_gridLayout);

    connect(m_parentToolBar, SIGNAL(iconSizeChanged(QSize)), this, SLOT(updateButtonsSize()));
    connect(m_parentToolBar, SIGNAL(orientationChanged(Qt::Orientation)), this, SLOT(updatePage()));
}

//-----------------------------------------------------------------------------
// 
// ---
QSize QtCommandPage::sizeHint() const
{
    const auto size = QSize(m_buttonSize.width()  * columnsNumber(),
                            m_buttonSize.height() * rowsNumber());

    const_cast<QtCommandPage*>(this)->setMinimumSize(size);
    const_cast<QtCommandPage*>(this)->setMaximumSize(size);
    return size;
}

//-----------------------------------------------------------------------------
// Updates the size of command buttons depending on the switching area of the command bar.
// ---
void QtCommandPage::updateButtonsSize()
{
    const bool vertical = m_parentToolBar->orientation() == Qt::Vertical;
    const int switchAreaDim = (vertical ? m_parentToolBar->switchButtonSizeHint().width() *
                                          m_parentToolBar->switchCommandsColumnsNumber()
                                        :
                                          m_parentToolBar->switchButtonSizeHint().height() *
                                          m_parentToolBar->switchCommandsRowsNumber());

    const int buttonsNum = vertical ? columnsNumber() : rowsNumber();
    const auto buttonDim = switchAreaDim / buttonsNum;
    m_buttonSize = QSize(buttonDim, buttonDim);

    std::for_each(m_commandButtons.begin(), m_commandButtons.end(), [this, buttonsNum](QToolButton* button) {
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setMinimumSize(QSize(0, 0));
        button->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

        button->setIconSize(buttonSizeWithoutStyle());
        // if the column/row is not completely filled with buttons, get rid of their stretching.
        m_commandButtons.size() < buttonsNum ? button->setFixedSize(m_buttonSize) :
                                               button->setMinimumSize(m_buttonSize);
        button->updateGeometry();
    });
}

//-----------------------------------------------------------------------------
// 
// ---
QSize QtCommandPage::buttonSizeWithoutStyle() const
{
    QSize styleSize {0, 0};
    if (!m_commandButtons.empty())
    {
        const auto buttonStyle = m_commandButtons.front()->style();
        const int margin = buttonStyle->pixelMetric(QStyle::PM_ButtonMargin, nullptr, m_commandButtons.front());
        const int frameWidth = buttonStyle->pixelMetric(QStyle::PM_ButtonDefaultIndicator, nullptr, m_commandButtons.front());
        const int styleMetric = 2 * (margin + frameWidth);
        styleSize = styleMetric > 0.5*m_buttonSize.width() ? styleSize : QSize(styleMetric, styleMetric);
    }
    return m_buttonSize - styleSize;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::updatePage()
{
    clearGridLayout();
    updateButtonsSize();
    addWidgetsIntoGridLayout(); // fill the grid after cleaning
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::addWidgetsIntoGridLayout()
{
    const bool vertical = m_parentToolBar->orientation() == Qt::Vertical;
    auto i = [this, vertical]() { return vertical ? m_gridLayout->count() / m_columnsNumber :
                                                    m_gridLayout->count() % m_columnsNumber; };
    auto j = [this, vertical]() { return vertical ? m_gridLayout->count() % m_columnsNumber :
                                                    m_gridLayout->count() / m_columnsNumber; };
    for(QToolButton* button : m_commandButtons)
        m_gridLayout->addWidget(button, i(), j(), vertical ? Qt::AlignTop : Qt::AlignLeft);
    setSpacerItems();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::setSpacerItems()
{
    const bool vertical = m_parentToolBar->orientation() == Qt::Vertical;
    if (m_commandButtons.size() < (vertical ? columnsNumber() : rowsNumber()))
    {
        // if the column/row is not completely filled with buttons, get rid of their stretching.
        QSpacerItem* spacer = vertical ? new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum) :
                                         new QSpacerItem(0, 0, QSizePolicy::Minimum,   QSizePolicy::Expanding);
        m_gridLayout->addItem(spacer, vertical ? 0 : m_commandButtons.size(), vertical ? m_commandButtons.size() : 0);
    }
    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_gridLayout->addItem(spacer, vertical ? rowsNumber() : 0, vertical ? 0 : rowsNumber(),
                          -1, -1, vertical ? Qt::AlignBottom : Qt::AlignRight);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::clearGridLayout()
{
    if (m_gridLayout != 0)
    {
        QLayoutItem* child;
        while ((child = m_gridLayout->takeAt(0)) != 0)
        {
            delete child;
        }
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::setColumnsNumber(const int columnsNumber_)
{
    m_columnsNumber = columnsNumber_ > 0 ? columnsNumber_ : 2;
    updatePage();
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandPage::columnsNumber() const
{
    return m_parentToolBar->orientation() == Qt::Vertical ?
                m_columnsNumber :
                (int)(ceil(double(m_commandButtons.size()) / double(m_columnsNumber)));
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandPage::rowsNumber() const
{
    return m_parentToolBar->orientation() == Qt::Vertical ?
                (int)(ceil(double(m_commandButtons.size()) / double(m_columnsNumber))) :
                m_columnsNumber;
}

//-----------------------------------------------------------------------------
// 
// ---
QSize QtCommandPage::buttonSize() const
{
    return m_commandButtons.empty() ? QSize(0, 0) : m_commandButtons.front()->sizeHint();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::setButtonSize(const QSize& buttonSize_)
{
    m_buttonSize = buttonSize_;
}

//-----------------------------------------------------------------------------
// 
// ---
QToolButton* QtCommandPage::createCommandButton(QAction* action)
{
    QToolButton* button = new CommandButton(m_parentToolBar);
    button->setDefaultAction(action);
    return button;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::addAction(QAction* action)
{
    QToolButton* button = createCommandButton(action);
    m_commandButtons.append(button);
    updatePage();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandPage::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
#ifdef DEBUG_LAYOUT_TURN_ON
    QPainter p(this);
    QRect rc = rect();
    p.setPen(QColor(0, 0, 255));
    p.drawRect(rc.adjusted(0, 0, -1, -1));
#endif
}

//-----------------------------------------------------------------------------
// 
// ---
QtCommandPage::~QtCommandPage()
{}


//-----------------------------------------------------------------------------
// 
// ---
CommandButton::CommandButton(QWidget* parentToolBar)
: QToolButton(parentToolBar)
{
    QObject::connect(this, SIGNAL(triggered(QAction*)),
                     parentToolBar, SIGNAL(actionTriggered(QAction*)));
}

//-----------------------------------------------------------------------------
// 
// ---
CommandButton::~CommandButton()
{}

//-----------------------------------------------------------------------------
// 
// ---
void CommandButton::paintEvent(QPaintEvent* event)
{
    QToolButton::paintEvent(event);
#ifdef DEBUG_LAYOUT_TURN_ON
    QPainter p(this);
    QRect rc = rect();
    p.setPen(QColor(0, 255, 0));
    p.drawRect(rc.adjusted(0, 0, -1, -1));
#endif
}

//-----------------------------------------------------------------------------
// 
// ---
SwitchCommandButton::SwitchCommandButton(QWidget* parentToolBar)
: QToolButton(parentToolBar)
{
    QObject::connect(parentToolBar, SIGNAL(iconSizeChanged(QSize)),
                     this, SLOT(setIconSize(QSize)));
    QObject::connect(parentToolBar, SIGNAL(toolButtonStyleChanged(Qt::ToolButtonStyle)),
                     this, SLOT(setToolButtonStyle(Qt::ToolButtonStyle)));

    setCheckable(true);
    setAutoRaise(false);
}

//-----------------------------------------------------------------------------
// 
// ---
SwitchCommandButton::~SwitchCommandButton()
{}

//-----------------------------------------------------------------------------
// 
// ---
void SwitchCommandButton::paintEvent(QPaintEvent* event)
{
    QToolButton::paintEvent(event);
#ifdef DEBUG_LAYOUT_TURN_ON
    QPainter p(this);
    QRect rc = rect();
    p.setPen(QColor(0, 255, 0));
    p.drawRect(rc.adjusted(0, 0, -1, -1));
#endif
}


//-----------------------------------------------------------------------------
// 
// ---
QtCommandBar::QtCommandBar(QWidget* parent)
: QToolBar(parent)
, m_baseWidget(nullptr)
, m_gridLayout(nullptr)
, m_separator(nullptr)
, m_switchCommandsWidget(nullptr)
, m_switchCommandsLayout(nullptr)
, m_buttonGroup(nullptr)
, m_switchCommands()
, m_stackedWidget(nullptr)
, m_commandPages()
, m_switchCommandsColumnsNumber(3)
, m_commandPageColumnsNumber(-1)
, m_switchButtonToCommandButtonRatio(0.67)
{
    membersInitialization();
    connect(this, SIGNAL(orientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged()));
    updateContent();
}

//-----------------------------------------------------------------------------
// Creates widgets that make up the command bar.
// ---
void QtCommandBar::membersInitialization()
{
    // create base widget of the commandBar
    m_baseWidget = new QWidget(this);
    addWidget(m_baseWidget);
    m_gridLayout = new QGridLayout(m_baseWidget);
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_baseWidget->setLayout(m_gridLayout);

    // create widget for switch buttons
    m_switchCommandsWidget = new QWidget(m_baseWidget);
    m_switchCommandsLayout = new QGridLayout(m_switchCommandsWidget);
    m_switchCommandsLayout->setSpacing(0);
    m_switchCommandsLayout->setContentsMargins(0, 0, 0, 0);
    m_switchCommandsWidget->setLayout(m_switchCommandsLayout);

    // create widget for switching pages by switch buttons
    m_buttonGroup = new QButtonGroup(m_baseWidget);
    // create widget for collecting pages
    m_stackedWidget = new QStackedWidget(m_baseWidget);

    connect(m_buttonGroup, SIGNAL(idClicked(int)), m_stackedWidget, SLOT(setCurrentIndex(int)));
}

//-----------------------------------------------------------------------------
// 
// ---
QSize QtCommandBar::sizeHint() const
{
    const auto size = QSize(calcDimension(DimType::Width), calcDimension(DimType::Height));
    const_cast<QtCommandBar*>(this)->setMinimumSize(size);
    const_cast<QtCommandBar*>(this)->setMaximumSize(size);
    return size;
}

//-----------------------------------------------------------------------------
// 
// ---
QSize QtCommandBar::switchButtonSizeHint() const
{
    return m_switchCommands.front()->sizeHint();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::clearGridLayout(QGridLayout* gridLayout_)
{
    if (gridLayout_ != nullptr)
    {
        QLayoutItem* child;
        while ((child = gridLayout_->takeAt(0)) != nullptr)
        {
            delete child;
        }
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::addWidgetsIntoGridLayout(std::vector<int>::iterator rIt, std::vector<int>::iterator cIt)
{
    if (m_switchCommands.size() > 1) // add a switch buttons area and a separator for more then 1 page
    {
        m_gridLayout->addWidget(m_switchCommandsWidget, *(rIt++), *(cIt++), Qt::AlignTop);

        m_separator = m_separator == nullptr ? new SeparatorArea(this, this) : m_separator; // create m_separator
        m_gridLayout->addWidget(m_separator, *(rIt++), *(cIt++));
    }
    m_gridLayout->addWidget(m_stackedWidget, *(rIt++), *(cIt++), Qt::AlignTop);
}

//-----------------------------------------------------------------------------
// Clear the base gridLayout and the switch area and fills them again.
// ---
void QtCommandBar::updateContent()
{
    clearGridLayout(m_gridLayout);

    std::vector<int> rowIdx, colIdx;
    if (m_switchCommands.size() == 1)
    {
        rowIdx.reserve(2); colIdx.reserve(2);
        rowIdx = {0, 0};   colIdx = {0, 1};
    }
    else
    {
        rowIdx.reserve(3);  colIdx.reserve(3);
        rowIdx = {0, 0, 0}; colIdx = {0, 1, 2};
    }
    orientation() == Qt::Vertical ? addWidgetsIntoGridLayout(colIdx.begin(), rowIdx.begin()) :
                                    addWidgetsIntoGridLayout(rowIdx.begin(), colIdx.begin());

    updateSwitchArea();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::updateSwitchArea()
{
    clearGridLayout(m_switchCommandsLayout);

    if (!m_switchCommands.empty())
    {
        const bool vertical = orientation() == Qt::Vertical;
        auto i = [this, vertical]() { return vertical ? m_switchCommandsLayout->count() / m_switchCommandsColumnsNumber :
                                                        m_switchCommandsLayout->count() % m_switchCommandsColumnsNumber; };
        auto j = [this, vertical]() { return vertical ? m_switchCommandsLayout->count() % m_switchCommandsColumnsNumber :
                                                        m_switchCommandsLayout->count() / m_switchCommandsColumnsNumber; };
        for(QToolButton* button : m_switchCommands)
            m_switchCommandsLayout->addWidget(button, i(), j(), vertical ? Qt::AlignTop : Qt::AlignLeft);

        m_switchCommands.at(0)->setHidden(m_switchCommands.size() == 1);
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::onOrientationChanged()
{
    updateContent();
/*
    // set cursor on a grip corner
    const QRect gripRect = calcGripRect();
    const QPoint gripCorner = gripRect.topRight();
    QCursor::setPos(mapToGlobal(gripCorner));
*/
}

//-----------------------------------------------------------------------------
// 
// ---
QRect QtCommandBar::calcGripRect() const
{
    QStyle* style = this->style();
    QStyleOptionToolBar opt;
    initStyleOption(&opt);
    const int gripDim = style->pixelMetric(QStyle::PM_ToolBarHandleExtent, &opt, this);

    const bool vertical = orientation() == Qt::Vertical;
    int gripWidth  = vertical ? calcDimension(DimType::Width) : gripDim;
    int gripHeight = vertical ? gripDim : calcDimension(DimType::Height);

    return QRect(0, 0, gripWidth, gripHeight);
}

//-----------------------------------------------------------------------------
// Dimension of widget (width or height).
// ---
template<class Dim>
struct Dimension
{
    Dim dim;
    Dimension(const Dim& dim_) : dim(dim_) {}

    int operator()(const QWidget& w) const
    {
        return dim == Dim::Width ? w.sizeHint().width() : w.sizeHint().height();
    }
};

//-----------------------------------------------------------------------------
// Returns range of projections max value.
// ---
template<typename Proj>
static auto maxElem = [](const auto& range, const Proj& proj)
{
    auto comp = [&proj](const auto& elem1, const auto& elem2) {
        return proj(*elem1) < proj(*elem2); };

    const auto max = *(std::max_element(range.begin(), range.end(), comp));
    return  proj(*max);
};

//-----------------------------------------------------------------------------
// Calculates a corresponding dimension of QtCommandBar widget.
// ---
int QtCommandBar::calcDimension(const DimType& dimType) const
{
    if (m_switchCommands.empty())
        return 0;

    //consider subelements of QtCommandBar
    QStyle* style = this->style();
    QStyleOptionToolBar opt;
    initStyleOption(&opt);

    int dimStyle  = 2 * style->pixelMetric(QStyle::PM_ToolBarFrameWidth, &opt, this);
        dimStyle += 2 * style->pixelMetric(QStyle::PM_ToolBarItemMargin, &opt, this);

    int dim = dimStyle;

    Dimension<DimType> dimension {dimType}; // functor for returning a specific dimension
    if (m_switchCommands.size() > 1) // switch buttons area presents for more then 1 page
    {
        // calculate a specific dimension of the switch buttons area
        dim += (dimType == DimType::Width ? switchCommandsColumnsNumber() :
                                            switchCommandsRowsNumber()) *
               dimension(*m_switchCommands.front());
    }

    const int pagesDim = maxElem<Dimension<DimType>>(m_commandPages, dimension);
    if (orientation() == Qt::Horizontal && dimType == DimType::Width ||
        orientation() == Qt::Vertical   && dimType == DimType::Height)
    {
        dim += style->pixelMetric(QStyle::PM_ToolBarHandleExtent, &opt, this);
        dim += m_separator != nullptr ? dimension(*m_separator) : 0; // separator presents for more then 1 page
        dim += pagesDim;
    }
    else
        dim = pagesDim > dim ? pagesDim + dimStyle : dim; // if pages dimension > switch buttons area

    return dim;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::paintEvent(QPaintEvent* event)
{
    QToolBar::paintEvent(event);
#ifdef DEBUG_LAYOUT_TURN_ON
    QPainter p(this);
    QRect rc = rect();
    p.setPen(QColor(255, 0, 0));
    p.drawRect(rc.adjusted(0, 0, -1, -1));
#endif
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::setSwitchCommandsColumnsNumber(const int columnsNumber_)
{
    m_switchCommandsColumnsNumber = columnsNumber_ > 0 ? columnsNumber_ : 3;
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandBar::switchCommandsColumnsNumber() const
{
    return orientation() == Qt::Vertical ?
                m_switchCommandsColumnsNumber :
                (int)(ceil(double(m_switchCommands.size()) / double(m_switchCommandsColumnsNumber)));
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandBar::switchCommandsRowsNumber() const
{
    return orientation() == Qt::Vertical ?
                (int)(ceil(double(m_switchCommands.size()) / double(m_switchCommandsColumnsNumber))) :
                m_switchCommandsColumnsNumber;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::setCommandPageColumnsNumber(const int columnsNumber_)
{
    m_commandPageColumnsNumber = columnsNumber_ > 0 ? columnsNumber_ : 2;
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandBar::commandPageColumnsNumber() const
{
    return m_commandPageColumnsNumber;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::setSwitchButtonToCommandButtonRatio(const int ratio_)
{
    m_switchButtonToCommandButtonRatio = ratio_;
}

//-----------------------------------------------------------------------------
// 
// ---
int QtCommandBar::switchButtonToCommandButtonRatio() const
{
    return m_switchButtonToCommandButtonRatio;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::addSwitchCommand(const QIcon& icon)
{
    m_switchCommands.append(new SwitchCommandButton(this));
    m_switchCommands.back()->setIcon(icon);
    m_switchCommands.at(0)->click(); //TODO
    m_buttonGroup->addButton(m_switchCommands.back(), m_switchCommands.size() - 1);
    updateSwitchArea();
}

//-----------------------------------------------------------------------------
// Calculates the command page columns number depending on switchButton to commandButton ratio.
// ---
int QtCommandBar::calcCommandPageColumnsNumber() const
{
    return round(double(m_switchCommandsColumnsNumber) * double(m_switchButtonToCommandButtonRatio));
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::addCommandPage(QtCommandPage* commandPage)
{
    if (commandPage == nullptr)
    {
        commandPage = new QtCommandPage(this, this);
        m_commandPageColumnsNumber = m_commandPageColumnsNumber > 0 ? m_commandPageColumnsNumber : calcCommandPageColumnsNumber();
        commandPage->setColumnsNumber(m_commandPageColumnsNumber);
    }

    m_commandPages.append(commandPage);
    m_stackedWidget->addWidget(m_commandPages.back());
}

//-----------------------------------------------------------------------------
// 
// ---
QtCommandPage* QtCommandBar::addPage(const QIcon& icon, QtCommandPage* commandPage)
{
    addSwitchCommand(icon);
    addCommandPage(commandPage);
    emit iconSizeChanged(this->iconSize());

    return m_commandPages.back();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtCommandBar::removePage(QtCommandPage* commandPage)
{
    auto it = std::find(m_commandPages.begin(), m_commandPages.end(), commandPage);
    int idx = std::distance(m_commandPages.begin(), it);
    m_buttonGroup->removeButton(m_switchCommands.at(idx));
    m_switchCommandsLayout->removeWidget(m_switchCommands.at(idx));
    m_switchCommands.removeAt(idx);

    m_stackedWidget->removeWidget(commandPage);
    m_commandPages.removeOne(commandPage);
}

//-----------------------------------------------------------------------------
// 
// ---
QtCommandBar::~QtCommandBar()
{}

} // namespace QtVision
} // namespace VSN
