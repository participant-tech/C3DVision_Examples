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

#include <qt_c3dstyle.h>
#include <qt_hostosinfo.h>

#include <qt_stylehelper.h>
#include <qt_headsuptoolbar.h>
#include <qt_theme.h>

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDockWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QSpinBox>
#include <QStatusBar>
#include <QStyleFactory>
#include <QStyleOption>
#include <QToolBar>
#include <QToolButton>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* C3DStylePrivate*/
class C3DStylePrivate
{
public:
    explicit C3DStylePrivate();
    void init();
public:
//    const QIcon extButtonIcon;
//    const QPixmap closeButtonPixmap;
//    StyleAnimator animator;
};

C3DStylePrivate::C3DStylePrivate()
//    : extButtonIcon(Utils::Icons::TOOLBAR_EXTENSION.icon())
//    , closeButtonPixmap(Utils::Icons::CLOSE_FOREGROUND.pixmap())
{
}


// Определяем неиспользуемое в настоящее время состояние для обозначения анимации.
const QStyle::State State_Animating = QStyle::State(0x00000040);

// Потому что WorkShop необходимо отключить это для предварительного просмотра виджетов.
//у нас есть пользовательское свойство, которое наследуется
bool styleEnabled(const QWidget* widget)
{
    const QWidget* p = widget;
    while (p)
    {
        if (p->property("_q_custom_style_disabled").toBool())
            return false;
        p = p->parentWidget();
    }
    return true;
}

//---------------------------------------------------------------------------------------
//
// ---
static bool isInUnstyledDialogOrPopup(const QWidget* widget)
{
    // Не оформляйте содержимое диалоговых окон или всплывающих окон без свойства "panelwidget"
    const QWidget* window = widget->window();
    if (window->property("panelwidget").toBool())
        return false;
    const Qt::WindowType windowType = window->windowType();
    return (windowType == Qt::Dialog || windowType == Qt::Popup);
}

// --------------------------------------------------------------------------------------
// необходимо подумайте о том, чтобы сделать это в составе C3DStyle.
// ----
bool panelWidget(const QWidget* widget)
{
    if (!widget)
        return false;

    if (isInUnstyledDialogOrPopup(widget))
        return false;

//    if (qobject_cast<const FancyMainWindow*>(widget))
//        return true;

    if (qobject_cast<const QTabBar*>(widget))
        return styleEnabled(widget);

    const QWidget* p = widget;
    while (p) 
    {
        if (qobject_cast<const QToolBar*>(p)   ||
            qobject_cast<const QStatusBar*>(p) ||
            qobject_cast<const QMenuBar*>(p)   ||
            p->property("panelwidget").toBool())
            return styleEnabled(widget);
        p = p->parentWidget();
    }
    return false;
}

//---------------------------------------------------------------------------------------
//
// ---
bool lightColored(const QWidget* widget)
{
    if (!widget)
        return false;

    if (isInUnstyledDialogOrPopup(widget))
        return false;

    const QWidget* p = widget;
    while (p)
    {
        if (p->property("lightColored").toBool())
            return true;
        p = p->parentWidget();
    }
    return false;
}

//---------------------------------------------------------------------------------------
//
// ---
static bool isDarkFusionStyle(const QStyle* style)
{
    return visionTheme()->flag(Theme::DarkUserInterface)
        && strcmp(style->metaObject()->className(), "QFusionStyle") == 0;
}

/* C3DStyle */
C3DStyle::C3DStyle(const QString& baseStyleName)
    : QProxyStyle(QStyleFactory::create(baseStyleName))
    , d(new C3DStylePrivate())
{
}

C3DStyle::~C3DStyle()
{
    VSN_DELETE_AND_NULL(d);
}

//---------------------------------------------------------------------------------------
//
// ---
QPixmap C3DStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap& pixmap, const QStyleOption* opt) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, opt);
}

//---------------------------------------------------------------------------------------
//
// ---
QSize C3DStyle::sizeFromContents(ContentsType type, const QStyleOption* option,
    const QSize& size, const QWidget* widget) const
{
    QSize newSize = QProxyStyle::sizeFromContents(type, option, size, widget);

    if (type == CT_Splitter && widget && widget->property("minisplitter").toBool())
        return QSize(1, 1);
    else if (type == CT_ComboBox && panelWidget(widget))
        newSize += QSize(14, 0);
    return newSize;
}

//---------------------------------------------------------------------------------------
//
// ---
QRect C3DStyle::subElementRect(SubElement element, const QStyleOption* option, const QWidget* widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}

QRect C3DStyle::subControlRect(ComplexControl control, const QStyleOptionComplex* option,
    SubControl subControl, const QWidget* widget) const
{
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 5)
    if (control == CC_ScrollBar)
    {
        const auto scrollbar = qstyleoption_cast<const QStyleOptionSlider*>(option);
        if (scrollbar && qint64(scrollbar->maximum) - scrollbar->minimum > INT_MAX)
            return QRect(); // ломает полосу прокрутки, но позволяет избежать сбоя
    }
#endif
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

//---------------------------------------------------------------------------------------
//
// ---
QStyle::SubControl C3DStyle::hitTestComplexControl(ComplexControl control, const QStyleOptionComplex* option,
    const QPoint& pos, const QWidget* widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, pos, widget);
}

//---------------------------------------------------------------------------------------
//
// ---
int C3DStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    int retval = 0;
    retval = QProxyStyle::pixelMetric(metric, option, widget);

    switch (metric) 
    {
        case PM_SplitterWidth:
            if (widget && widget->property("minisplitter").toBool())
                retval = int(StyleHelper::dpiScaled(1.0, option));
            break;
        case PM_ToolBarIconSize:
        case PM_ButtonIconSize:
//            if (panelWidget(widget))
                retval = int(StyleHelper::dpiScaled(18.0, option)); // 16;
            break;
        case PM_SmallIconSize:
//            if (!qobject_cast<const QMenu*>(widget))
                retval = int(StyleHelper::dpiScaled(18.0, option)); // 16;
            break;
        case PM_DockWidgetHandleExtent:
        case PM_DockWidgetSeparatorExtent:
            return 1;
        case PM_MenuPanelWidth:
        case PM_MenuBarHMargin:
        case PM_MenuBarVMargin:
        case PM_ToolBarFrameWidth:
            if (panelWidget(widget))
                retval = 1;
            break;
        case PM_ButtonShiftVertical:
        case PM_ButtonShiftHorizontal:
        case PM_MenuBarPanelWidth:
        case PM_ToolBarItemMargin:
        case PM_ToolBarItemSpacing:
            if (panelWidget(widget))
                retval = 0;
            break;
        case PM_DefaultFrameWidth:
            if (qobject_cast<const QLineEdit*>(widget) && panelWidget(widget))
                return 1;
            break;
        default:
            break;
    }
    return retval;
}

//---------------------------------------------------------------------------------------
//
// ---
QPalette C3DStyle::standardPalette() const {
    return QProxyStyle::standardPalette();
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::polish(QApplication* app)
{
    QProxyStyle::polish(app);
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::unpolish(QApplication* app)
{
    QProxyStyle::unpolish(app);
}

//---------------------------------------------------------------------------------------
//
// ---
QPalette panelPalette(const QPalette& oldPalette, bool lightColored = false)
{
    QColor color = visionTheme()->color(lightColored ? Theme::PanelTextColorDark
        : Theme::PanelTextColorLight);
    QPalette pal = oldPalette;
    pal.setBrush(QPalette::All, QPalette::WindowText, color);
    pal.setBrush(QPalette::All, QPalette::ButtonText, color);
    if (lightColored)
        color.setAlpha(100);
    else
        color = visionTheme()->color(Theme::IconsDisabledColor);
    pal.setBrush(QPalette::Disabled, QPalette::WindowText, color);
    pal.setBrush(QPalette::Disabled, QPalette::ButtonText, color);
    return pal;
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::polish(QWidget* widget)
{
    QProxyStyle::polish(widget);

    // OxygenStyle принудительно отображает закругленную маску виджетов на панелях инструментов и закрепляемых виджетах.
    if (baseStyle()->inherits("OxygenStyle") || baseStyle()->inherits("Oxygen::Style"))
    {
        if (qobject_cast<QToolBar*>(widget) || qobject_cast<QDockWidget*>(widget))
        {
            widget->removeEventFilter(baseStyle());
            widget->setContentsMargins(0, 0, 0, 0);
        }
    }
    if (panelWidget(widget))
    {
        // Oxygen и возможно другие стили переопределяют это
        if (qobject_cast<QDockWidget*>(widget))
            widget->setContentsMargins(0, 0, 0, 0);

        widget->setAttribute(Qt::WA_LayoutUsesWidgetRect, true);
        // Чтобы текст не обрезался при редактировании строк, полях со списком... и т.д.
        const int height = qMax(StyleHelper::navigationWidgetHeight(), QApplication::fontMetrics().height());
        if ((qobject_cast<QToolButton*>(widget) || qobject_cast<QLineEdit*>(widget)))
        {
            widget->setAttribute(Qt::WA_Hover);
            if (widget->property("_vsn_height").toBool())
                widget->setMaximumHeight(height - 2);
        }
        else if (qobject_cast<QLabel*>(widget) || qobject_cast<QSpinBox*>(widget)
            || qobject_cast<QCheckBox*>(widget)) {
            widget->setPalette(panelPalette(widget->palette(), lightColored(widget)));
        }
        else if (widget->property("panelwidget_singlerow").toBool()) {
            widget->setFixedHeight(height);
        }
        else if (qobject_cast<QStatusBar*>(widget))
        {
// TODO           widget->setFixedHeight(height + 2);
        }
        else if (qobject_cast<QComboBox*>(widget))
        {
            const bool isLightColored = lightColored(widget);
            QPalette palette = panelPalette(widget->palette(), isLightColored);
            if (!isLightColored)
                palette.setBrush(QPalette::All, QPalette::WindowText,
                    visionTheme()->color(Theme::ComboBoxTextColor));
            widget->setPalette(palette);
// TODO            widget->setMaximumHeight(height - 2);
            widget->setAttribute(Qt::WA_Hover);
        }
    }
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::unpolish(QWidget* widget)
{
    QProxyStyle::unpolish(widget);
    if (panelWidget(widget))
    {
        widget->setAttribute(Qt::WA_LayoutUsesWidgetRect, false);
        if (qobject_cast<QTabBar*>(widget)
            || qobject_cast<QToolBar*>(widget)
            || qobject_cast<QComboBox*>(widget)) {
            widget->setAttribute(Qt::WA_Hover, false);
        }
    }
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::polish(QPalette& pal)
{
    QProxyStyle::polish(pal);
}

//---------------------------------------------------------------------------------------
//
// ---
QPixmap C3DStyle::standardPixmap(StandardPixmap standardPixmap, const QStyleOption* opt,
    const QWidget* widget) const
{
    if (widget && !panelWidget(widget))
        return QProxyStyle::standardPixmap(standardPixmap, opt, widget);

    QPixmap pixmap;
    switch (standardPixmap) {
    case QStyle::SP_TitleBarCloseButton:
//        pixmap = d->closeButtonPixmap;
        break;
    default:
        pixmap = QProxyStyle::standardPixmap(standardPixmap, opt, widget);
        break;
    }
    return pixmap;
}

//---------------------------------------------------------------------------------------
//
// ---
QIcon C3DStyle::standardIcon(StandardPixmap standardIcon, const QStyleOption* option, const QWidget* widget) const
{
    QIcon icon;
    switch (standardIcon)
    {
    case QStyle::SP_ToolBarHorizontalExtensionButton:
//        icon = d->extButtonIcon;
        break;
    default:
        icon = QProxyStyle::standardIcon(standardIcon, option, widget);
        break;
    }

    if (standardIcon == QStyle::SP_ComputerIcon)
    {
        const QList<QSize>& sizes = icon.availableSizes();
        if (Utils::allOf(sizes, [](const QSize& size) { return size.width() < 32; }))
            icon = QIcon(":/res/desktop.png");
    }
    return icon;
}

//---------------------------------------------------------------------------------------
//
// ---
int C3DStyle::styleHint(StyleHint hint, const QStyleOption* option, const QWidget* widget,
    QStyleHintReturn* returnData) const
{
    int ret = QProxyStyle::styleHint(hint, option, widget, returnData);
    switch (hint)
    {
    case QStyle::SH_EtchDisabledText:
        if (panelWidget(widget) || qobject_cast<const QMenu*> (widget))
            ret = false;
        break;
    case QStyle::SH_ItemView_ArrowKeysNavigateIntoChildren:
        ret = true;
        break;
    case QStyle::SH_ItemView_ActivateItemOnSingleClick:
        // по умолчанию зависит от стиля
        if (widget)
        {
            QVariant activationMode = widget->property("ActivationMode");
            if (activationMode.isValid())
                ret = activationMode.toBool();
        }
        break;
    case QStyle::SH_FormLayoutFieldGrowthPolicy:
        // Значение по умолчанию в QMacStyle, FieldsStayAtSizeHint
        // всегда неправильное.Используйте то же,
        // что и во всех других поставляемых стилях.
        if (HostOsInfo::isMacHost())
            ret = QFormLayout::AllNonFixedFieldsGrow;
        break;
    case QStyle::SH_Widget_Animation_Duration:
        if (widget && widget->inherits("QTreeView"))
            ret = 0;
        break;
    case QStyle::SH_ComboBox_AllowWheelScrolling:
        // Включайте это только при одновременном нажатии Ctrl, чтобы предотвратить случайное изменение текущего индекса,
        // например.в режиме прокрутки
        ret = QGuiApplication::keyboardModifiers()
            == (HostOsInfo::isMacHost() ? Qt::MetaModifier : Qt::ControlModifier);
        break;
    default:
        break;
    }
    return ret;
}

//---------------------------------------------------------------------------------------
//
// ---
static void drawPrimitiveTweakedForDarkTheme(QStyle::PrimitiveElement element, const QStyleOption* option,
                                             QPainter* painter, const QWidget* widget)
{
    const bool hasFocus = option->state & QStyle::State_HasFocus;
    const bool isChecked = option->state & QStyle::State_On;
    const bool isPartiallyChecked = option->state & QStyle::State_NoChange;
    const bool isEnabled = option->state & QStyle::State_Enabled;
    const bool isSunken = option->state & QStyle::State_Sunken;

    const QColor frameColor = isEnabled ? option->palette.color(QPalette::Mid).darker(132)
                                        : visionTheme()->color(Theme::BackgroundColorDisabled);
    const QColor indicatorColor = isEnabled ? option->palette.color(QPalette::Mid).darker(90)
                                            : visionTheme()->color(Theme::BackgroundColorDisabled);
    const QColor bgColor = isSunken ? option->palette.color(QPalette::Mid).darker()
        : option->palette.color(QPalette::Window);
    const QColor hlColor = option->palette.color(QPalette::Highlight);

    QPen framePen(hasFocus ? hlColor : frameColor, 1);
    framePen.setJoinStyle(Qt::MiterJoin);
    QPen indicatorPen(indicatorColor, 1);
    indicatorPen.setJoinStyle(Qt::MiterJoin);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    switch (element)
    {
    case QStyle::PE_Frame:
    {
        const QRectF frameRectF = QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5);
        painter->setPen(framePen);
        painter->drawRect(frameRectF);
        break;
    }
    case QStyle::PE_FrameLineEdit:
    {
        const bool isComboBox = widget && widget->inherits("QComboBox");
        const QRectF frameRectF =
            QRectF(option->rect).adjusted(0.5, 0.5, isComboBox ? -8.5 : -0.5, -0.5);
        painter->setPen(framePen);
        painter->drawRect(frameRectF);
        break;
    }
    case QStyle::PE_FrameGroupBox:
    {
        // Фрагмент из QFusionStyle::drawPrimitive - BEGIN
        static const int groupBoxTopMargin = 3;
        int topMargin = 0;
        auto control = dynamic_cast<const QGroupBox*>(widget);
        if (control && !control->isCheckable() && control->title().isEmpty())
        {
            // Уменьшение верхнего поля, если флажок не установлен и заголовок пуст
            topMargin = groupBoxTopMargin;
        }
        else
        {
            const int exclusiveIndicatorHeight = widget ? widget->style()->pixelMetric(QStyle::PM_ExclusiveIndicatorHeight) : 0;
            topMargin = qMax(exclusiveIndicatorHeight,
                option->fontMetrics.height()) + groupBoxTopMargin;
        }
        // Фрагмент из QFusionStyle::drawPrimitive - END
        const QRectF frameRectF = QRectF(option->rect).adjusted(0.5, topMargin + 0.5, -0.5, -0.5);
        painter->setPen(framePen);
        if (isEnabled)
            painter->setOpacity(0.5);
        painter->drawRect(frameRectF);
        break;
    }
    case QStyle::PE_IndicatorRadioButton:
    {
        const qreal lineWidth = 1.666;
        qreal o = lineWidth / 2;
        indicatorPen.setWidth(lineWidth);
        painter->setPen(framePen);
        if (isEnabled)
            painter->setBrush(bgColor);
        painter->drawRoundedRect(QRectF(option->rect).adjusted(o, o, -o, -o),
            100, 100, Qt::RelativeSize);

        if (isChecked)
        {
            painter->setPen(Qt::NoPen);
            painter->setBrush(indicatorColor);
            o = 4.25;
            painter->drawRoundedRect(QRectF(option->rect).adjusted(o, o, -o, -o),
                100, 100, Qt::RelativeSize);
        }
        break;
    }
    case QStyle::PE_IndicatorCheckBox:
    {
        const QRectF frameRectF = QRectF(option->rect).adjusted(0.5, 0.5, -0.5, -0.5);
        painter->setPen(framePen);
        if (isEnabled)
            painter->setBrush(bgColor);
        painter->drawRect(frameRectF);

        if (isPartiallyChecked)
        {
            QPen outline(indicatorColor, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
            painter->setPen(outline);
            QColor fill(frameColor);
            fill.setAlphaF(0.8f);
            painter->setBrush(fill);
            const double o = 3.5;
            painter->drawRect(QRectF(option->rect).adjusted(o, o, -o, -o));
        }
        else if (isChecked)
        {
            const double o = 3;
            const QRectF r = QRectF(option->rect).adjusted(o, o, -o, -o);
            QPen checkMarkPen(indicatorColor, 1.75, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
            painter->setPen(checkMarkPen);
            painter->drawPolyline(QPolygonF({ QPointF(r.left(), r.top() + r.height() / 2),
                                             QPointF(r.left() + r.width() / 2.3, r.bottom()),
                                             r.topRight() }));
        }
        break;
    }
    case QStyle::PE_IndicatorTabClose:
    {
        QWindow* window = widget ? widget->window()->windowHandle() : nullptr;
        QRect iconRect = QRect(0, 0, 16, 16);
        iconRect.moveCenter(option->rect.center());
        const QIcon::Mode mode = !isEnabled ? QIcon::Disabled : QIcon::Normal;
        const static QIcon closeIcon = QIcon(":/res/close.png");//Utils::Icons::CLOSE_FOREGROUND.icon();
        if (option->state & QStyle::State_MouseOver && widget)
            widget->style()->drawPrimitive(QStyle::PE_PanelButtonCommand, option, painter, widget);
        const int devicePixelRatio = widget ? widget->devicePixelRatio() : 1;
        const QPixmap iconPx =
            closeIcon.pixmap(window, iconRect.size() * devicePixelRatio, mode);
        painter->drawPixmap(iconRect, iconPx);
        break;
    }
    default:
        QTV_ASSERT_STRING("Unhandled QStyle::PrimitiveElement case");
        break;
    }
    painter->restore();
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option,
    QPainter* painter, const QWidget* widget) const
{
    const bool isPanelWidget = panelWidget(widget);
    if (!isPanelWidget) {
        const bool tweakDarkTheme =
            (element == PE_Frame
                || element == PE_FrameLineEdit
                || element == PE_FrameGroupBox
                || element == PE_IndicatorRadioButton
                || element == PE_IndicatorCheckBox
                || element == PE_IndicatorTabClose)
            && isDarkFusionStyle(baseStyle());
        if (tweakDarkTheme)
            drawPrimitiveTweakedForDarkTheme(element, option, painter, widget);
        else
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        return;
    }

    bool animating = (option->state & State_Animating);
    int state = option->state;
    QRect rect = option->rect;
    QRect oldRect;
    QRect newRect;
    if (widget && (element == PE_PanelButtonTool) && !animating)
    {
        auto w = const_cast<QWidget*> (widget);
        int oldState = w->property("_q_stylestate").toInt();
        oldRect = w->property("_q_stylerect").toRect();
        newRect = w->rect();
        w->setProperty("_q_stylestate", (int)option->state);
        w->setProperty("_q_stylerect", w->rect());

        // Определить анимированный переход
        bool doTransition = ((state & State_On) != (oldState & State_On) ||
            (state & State_MouseOver) != (oldState & State_MouseOver));
        if (oldRect != newRect)
        {
            doTransition = false;
//            d->animator.stopAnimation(widget);
        }

        if (doTransition)
        {
            QImage startImage(option->rect.size(), QImage::Format_ARGB32_Premultiplied);
            QImage endImage(option->rect.size(), QImage::Format_ARGB32_Premultiplied);
//            Animation* anim = d->animator.widgetAnimation(widget);
            QStyleOption opt = *option;
            opt.state = (QStyle::State)oldState;
            opt.state |= State_Animating;
            startImage.fill(0);
//            auto t = new Transition;
//            t->setWidget(w);
            QPainter startPainter(&startImage);
            drawPrimitive(element, &opt, &startPainter, widget); // TODO

//            if (!anim) {
//                drawPrimitive(element, &opt, &startPainter, widget);
//            }
//            else {
//                anim->paint(&startPainter, &opt);
//                d->animator.stopAnimation(widget);
//            }
            QStyleOption endOpt = *option;
            endOpt.state |= State_Animating;
//            t->setStartImage(startImage);
//            d->animator.startAnimation(t);
            endImage.fill(0);
            QPainter endPainter(&endImage);
            drawPrimitive(element, &endOpt, &endPainter, widget);
//            t->setEndImage(endImage);
//            if (oldState & State_MouseOver)
//                t->setDuration(150);
//            else
//                t->setDuration(75);
//            t->setStartTime(QTime::currentTime());
        }
    }

    switch (element)
    {
    case PE_IndicatorDockWidgetResizeHandle:
            painter->fillRect(option->rect, visionTheme()->color(Theme::DockWidgetResizeHandleColor));
        break;
    case PE_FrameDockWidget:
            QCommonStyle::drawPrimitive(element, option, painter, widget);
        break;
    case PE_PanelLineEdit:
    {
        painter->save();

        // Заполните фон редактирования строки
        QRectF backgroundRect = option->rect;
        Q_ASSERT(false);
/*
        const bool enabled = option->state & State_Enabled;
        if (Utils::visionTheme()->flag(Theme::FlatToolBars)) {
            painter->save();
            if (!enabled)
                painter->setOpacity(0.75);
            painter->fillRect(backgroundRect, option->palette.base());
            painter->restore();
        }
        else {
            backgroundRect.adjust(1, 1, -1, -1);
            painter->setBrushOrigin(backgroundRect.topLeft());
            painter->fillRect(backgroundRect, option->palette.base());

            static const QImage bg(StyleHelper::dpiSpecificImageFile(
                QLatin1String(":/utils/images/inputfield.png")));
            static const QImage bg_disabled(StyleHelper::dpiSpecificImageFile(
                QLatin1String(":/utils/images/inputfield_disabled.png")));

            StyleHelper::drawCornerImage(enabled ? bg : bg_disabled,
                painter, option->rect, 5, 5, 5, 5);
        }

        const bool hasFocus = state & State_HasFocus;
        if (enabled && (hasFocus || state & State_MouseOver)) {
            QColor hover = StyleHelper::baseColor();
            hover.setAlpha(hasFocus ? 100 : 50);
            painter->setPen(QPen(hover, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter->drawRect(backgroundRect.adjusted(0.5, 0.5, -0.5, -0.5));
        }
        painter->restore();
*/
    }
    break;

    case PE_FrameStatusBarItem:
        break;

    case PE_PanelButtonTool:
    {
//        Animation* anim = d->animator.widgetAnimation(widget);
//        if (!animating && anim) {
//            anim->paint(painter, option);
//        }
//        else {
            bool pressed = option->state & State_Sunken || option->state & State_On;
            painter->setPen(StyleHelper::sidebarShadow());
            if (pressed) {
                const QColor shade = visionTheme()->color(Theme::FancyToolButtonSelectedColor);
                painter->fillRect(rect, shade);
                if (!visionTheme()->flag(Theme::FlatToolBars))
                {
                    const QRectF borderRect = QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5);
                    painter->drawLine(borderRect.topLeft() + QPointF(1, 0), borderRect.topRight() - QPointF(1, 0));
                    painter->drawLine(borderRect.topLeft(), borderRect.bottomLeft());
                    painter->drawLine(borderRect.topRight(), borderRect.bottomRight());
                }
            }
            else if (option->state & State_Enabled && option->state & State_MouseOver) {
                painter->fillRect(rect, visionTheme()->color(Theme::FancyToolButtonHoverColor));
            }
            else if (widget && widget->property("highlightWidget").toBool())
            {
                QColor shade(0, 0, 0, 128);
                painter->fillRect(rect, shade);
            }
            if (option->state & State_HasFocus && (option->state & State_KeyboardFocusChange))
            {
                QColor highlight = option->palette.highlight().color();
                highlight.setAlphaF(0.4f);
                painter->setPen(QPen(highlight.lighter(), 1));
                highlight.setAlphaF(0.3f);
                painter->setBrush(highlight);
                painter->setRenderHint(QPainter::Antialiasing);
                const QRectF rectLoc = option->rect;
                painter->drawRoundedRect(rectLoc.adjusted(2.5, 2.5, -2.5, -2.5), 2, 2);
            }
//        }
    }
    break;

    case PE_PanelStatusBar:
    {
        const QRectF borderRect = QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5);
        painter->save();
        if (visionTheme()->flag(Theme::FlatToolBars))
        {
            painter->fillRect(rect, StyleHelper::baseColor());
        }
        else
        {
            QLinearGradient grad = StyleHelper::statusBarGradient(rect);
            painter->fillRect(rect, grad);
            painter->setPen(QColor(255, 255, 255, 60));
            painter->drawLine(borderRect.topLeft() + QPointF(0, 1),
                borderRect.topRight() + QPointF(0, 1));
            painter->setPen(StyleHelper::borderColor().darker(110)); //TODO: сделать тематическим
            painter->drawLine(borderRect.topLeft(), borderRect.topRight());
        }
        if (visionTheme()->flag(Theme::DrawToolBarBorders))
        {
            painter->setPen(StyleHelper::toolBarBorderColor());
            painter->drawLine(borderRect.topLeft(), borderRect.topRight());
        }
        painter->restore();
    }
    break;

    case PE_IndicatorToolBarSeparator:
    {
        QRect separatorRect = rect;
        separatorRect.setLeft(rect.width() / 2);
        separatorRect.setWidth(1);
        drawButtonSeparator(painter, separatorRect, false);
    }
    break;

    case PE_IndicatorToolBarHandle:
    {
        bool horizontal = option->state & State_Horizontal;
        painter->save();
        QPainterPath path;
        int x = option->rect.x() + (horizontal ? 2 : 6);
        int y = option->rect.y() + (horizontal ? 6 : 2);
        static const int RectHeight = 2;
        if (horizontal) {
            while (y < option->rect.height() - RectHeight - 6) {
                path.moveTo(x, y);
                path.addRect(x, y, RectHeight, RectHeight);
                y += 6;
            }
        }
        else {
            while (x < option->rect.width() - RectHeight - 6) {
                path.moveTo(x, y);
                path.addRect(x, y, RectHeight, RectHeight);
                x += 6;
            }
        }

        painter->setPen(Qt::NoPen);
        QColor dark = StyleHelper::borderColor();
        dark.setAlphaF(0.4f);

        QColor light = StyleHelper::baseColor();
        light.setAlphaF(0.4f);

        painter->fillPath(path, light);
        painter->save();
        painter->translate(1, 1);
        painter->fillPath(path, dark);
        painter->restore();
        painter->translate(3, 3);
        painter->fillPath(path, light);
        painter->translate(1, 1);
        painter->fillPath(path, dark);
        painter->restore();
    }
    break;
    case PE_IndicatorArrowUp:
    case PE_IndicatorArrowDown:
    case PE_IndicatorArrowRight:
    case PE_IndicatorArrowLeft:
        if (qobject_cast<const QMenu*>(widget)) // оставить рисование стрелки подменю в покое
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        else
            StyleHelper::drawArrow(element, painter, option);
        break;

    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
        break;
    }
}

//---------------------------------------------------------------------------------------
//
// ---
void C3DStyle::drawControl(ControlElement element, const QStyleOption* option,
    QPainter* painter, const QWidget* widget) const
{
    if (!panelWidget(widget) && !qobject_cast<const QMenu*>(widget))
    {
        QProxyStyle::drawControl(element, option, painter, widget);
        return;
    }

    switch (element)
    {
    case CE_MenuItem:
        painter->save();
        if (const auto mbi = qstyleoption_cast<const QStyleOptionMenuItem*>(option))
        {
            const bool enabled = mbi->state & State_Enabled;
            QStyleOptionMenuItem item = *mbi;
            item.rect = mbi->rect;
            const QColor color = visionTheme()->color(enabled
                ? Theme::MenuItemTextColorNormal
                : Theme::MenuItemTextColorDisabled);
            if (color.isValid())
            {
                QPalette pal = mbi->palette;
                pal.setBrush(QPalette::Text, color);
                item.palette = pal;
            }
            QProxyStyle::drawControl(element, &item, painter, widget);
        }
        painter->restore();
        break;

    case CE_MenuBarItem:
        painter->save();
        if (const auto mbi = qstyleoption_cast<const QStyleOptionMenuItem*>(option))
        {
            const bool act = mbi->state & (State_Sunken | State_Selected);
            const bool dis = !(mbi->state & State_Enabled);

            if (visionTheme()->flag(Theme::FlatMenuBar))
                painter->fillRect(option->rect, StyleHelper::baseColor());
            else
                StyleHelper::menuGradient(painter, option->rect, option->rect);

            QStyleOptionMenuItem item = *mbi;
            item.rect = mbi->rect;
            QPalette pal = mbi->palette;
            pal.setBrush(QPalette::ButtonText, dis ? visionTheme()->color(Theme::MenuBarItemTextColorDisabled)
                                                   : visionTheme()->color(Theme::MenuBarItemTextColorNormal));
            item.palette = pal;
            QCommonStyle::drawControl(element, &item, painter, widget);

            if (act)
            {
                // Fill|
                const QColor fillColor = StyleHelper::alphaBlendedColors(StyleHelper::baseColor(),
                    visionTheme()->color(Theme::FancyToolButtonHoverColor));
                painter->fillRect(option->rect, fillColor);

                QPalette palSrc = mbi->palette;
                uint alignment = Qt::AlignCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
                if (!styleHint(SH_UnderlineShortcut, mbi, widget))
                    alignment |= Qt::TextHideMnemonic;
                palSrc.setBrush(QPalette::Text, visionTheme()->color(dis
                    ? Theme::IconsDisabledColor
                    : Theme::PanelTextColorLight));
                drawItemText(painter, item.rect, alignment, palSrc, !dis, mbi->text, QPalette::Text);
            }
        }
        painter->restore();
        break;

    case CE_ComboBoxLabel:
        if (const auto cb = qstyleoption_cast<const QStyleOptionComboBox*>(option))
        {
            if (panelWidget(widget))
            {
                painter->save();
                QRect editRect = subControlRect(CC_ComboBox, cb, SC_ComboBoxEditField, widget);
                QPalette customPal = cb->palette;
                bool drawIcon = !(widget && widget->property("hideicon").toBool());

                if (!cb->currentIcon.isNull() && drawIcon) {
                    QIcon::Mode mode = cb->state & State_Enabled ? QIcon::Normal
                        : QIcon::Disabled;
                    QPixmap pixmap = cb->currentIcon.pixmap(cb->iconSize, mode);
                    QRect iconRect(editRect);
                    iconRect.setWidth(cb->iconSize.width() + 4);
                    iconRect = alignedRect(cb->direction,
                        Qt::AlignLeft | Qt::AlignVCenter,
                        iconRect.size(), editRect);
                    if (cb->editable)
                        painter->fillRect(iconRect, customPal.brush(QPalette::Base));
                    drawItemPixmap(painter, iconRect, Qt::AlignCenter, pixmap);

                    if (cb->direction == Qt::RightToLeft)
                        editRect.translate(-4 - cb->iconSize.width(), 0);
                    else
                        editRect.translate(cb->iconSize.width() + 4, 0);

                    // Зарезервируем место для стрелки вниз
                    editRect.adjust(0, 0, -13, 0);
                }

                Qt::TextElideMode elideMode = Qt::ElideRight;
                if (widget && widget->dynamicPropertyNames().contains("elidemode"))
                    elideMode = widget->property("elidemode").value<Qt::TextElideMode>();

                QLatin1Char asterisk('*');
                int elideWidth = editRect.width();

                bool notElideAsterisk = elideMode == Qt::ElideRight && widget
                    && widget->property("notelideasterisk").toBool()
                    && cb->currentText.endsWith(asterisk)
                    && option->fontMetrics.horizontalAdvance(cb->currentText) > elideWidth;

                QString text;
                if (notElideAsterisk)
                {
                    elideWidth -= option->fontMetrics.horizontalAdvance(asterisk);
                    text = asterisk;
                }
                text.prepend(option->fontMetrics.elidedText(cb->currentText, elideMode, elideWidth));

                if (visionTheme()->flag(Theme::ComboBoxDrawTextShadow)
                    && (option->state & State_Enabled))
                {
                    painter->setPen(StyleHelper::toolBarDropShadowColor());
                    painter->drawText(editRect.adjusted(1, 0, -1, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                }
                painter->setPen((option->state & State_Enabled)
                    ? option->palette.color(QPalette::WindowText)
                    : visionTheme()->color(Theme::IconsDisabledColor));
                painter->drawText(editRect.adjusted(1, 0, -1, 0), Qt::AlignLeft | Qt::AlignVCenter, text);

                painter->restore();
            }
            else
                QProxyStyle::drawControl(element, option, painter, widget);
        }
        break;

    case CE_SizeGrip:
    {
        painter->save();
        QColor dark = Qt::white;
        dark.setAlphaF(0.1f);
        int x, y, w, h;
        option->rect.getRect(&x, &y, &w, &h);
        int sw = qMin(h, w);
        if (h > w)
            painter->translate(0, h - w);
        else
            painter->translate(w - h, 0);
        int sx = x;
        int sy = y;
        int s = 4;
        painter->setPen(dark);
        if (option->direction == Qt::RightToLeft)
        {
            sx = x + sw;
            for (int i = 0; i < 4; ++i)
            {
                painter->drawLine(x, sy, sx, sw);
                sx -= s;
                sy += s;
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                painter->drawLine(sx, sw, sw, sy);
                sx += s;
                sy += s;
            }
        }
        painter->restore();
    }
    break;

    case CE_MenuBarEmptyArea:
    {
        if (visionTheme()->flag(Theme::FlatMenuBar))
            painter->fillRect(option->rect, StyleHelper::baseColor());
        else
            StyleHelper::menuGradient(painter, option->rect, option->rect);

        painter->save();
        painter->setPen(StyleHelper::toolBarBorderColor());
        painter->drawLine(option->rect.bottomLeft() + QPointF(0.5, 0.5),
            option->rect.bottomRight() + QPointF(0.5, 0.5));
        painter->restore();
    }
    break;

    case CE_ToolBar:
    {
        QRect rect = option->rect;
        const QRectF borderRect = QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5);
        bool horizontal = option->state & State_Horizontal;

        // Смещение карты для глобального градиента окна
        QRect gradientSpan;
        if (widget)
        {
            QPoint offset = widget->window()->mapToGlobal(option->rect.topLeft()) -
                widget->mapToGlobal(option->rect.topLeft());
            gradientSpan = QRect(offset, widget->window()->size());
        }

        bool drawLightColored = lightColored(widget);
        // рисует фон заголовков 'Type hierarchy', 'Projects' headers
        if (visionTheme()->flag(Theme::FlatToolBars))
            painter->fillRect(rect, StyleHelper::baseColor(drawLightColored));
        else if (horizontal)
            StyleHelper::horizontalGradient(painter, gradientSpan, rect, drawLightColored);
        else
            StyleHelper::verticalGradient(painter, gradientSpan, rect, drawLightColored);

        if (visionTheme()->flag(Theme::DrawToolBarHighlights))
        {
            if (!drawLightColored)
                painter->setPen(StyleHelper::toolBarBorderColor());
            else
                painter->setPen(QColor(0x888888));

            if (horizontal)
            {
                // Примечание: Это способ определить, панель инструментов
                // должна рисовать верхний или нижний контур(необходимо,
                // например, для панели инструментов поиска)
                const QColor hightLight = visionTheme()->flag(Theme::FlatToolBars)
                    ? visionTheme()->color(Theme::FancyToolBarSeparatorColor)
                    : StyleHelper::sidebarHighlight();
                const QColor borderColor = drawLightColored
                    ? QColor(255, 255, 255, 180) : hightLight;
                if (widget && widget->property("topBorder").toBool()) {
                    painter->drawLine(borderRect.topLeft(), borderRect.topRight());
                    painter->setPen(borderColor);
                    painter->drawLine(borderRect.topLeft() + QPointF(0, 1), borderRect.topRight() + QPointF(0, 1));
                }
                else {
                    painter->drawLine(borderRect.bottomLeft(), borderRect.bottomRight());
                    painter->setPen(borderColor);
                    painter->drawLine(borderRect.topLeft(), borderRect.topRight());
                }
            }
            else {
                painter->drawLine(borderRect.topLeft(), borderRect.bottomLeft());
                painter->drawLine(borderRect.topRight(), borderRect.bottomRight());
            }
        }
        if (visionTheme()->flag(Theme::DrawToolBarBorders)) {
            painter->setPen(StyleHelper::toolBarBorderColor());
            if (widget && widget->property("topBorder").toBool())
                painter->drawLine(borderRect.topLeft(), borderRect.topRight());
            else
                painter->drawLine(borderRect.bottomLeft(), borderRect.bottomRight());
        }
    }
    break;
    case CE_ToolButtonLabel:
        // Directly use QCommonStyle to circumvent funny painting in QMacStyle
        // which ignores the palette and adds an alpha
        QCommonStyle::drawControl(element, option, painter, widget);
        break;
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
        break;
    }
}

void C3DStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex* option,
    QPainter* painter, const QWidget* widget) const
{
    if (!panelWidget(widget))
        return QProxyStyle::drawComplexControl(control, option, painter, widget);

    QRect rect = option->rect;
    switch (control)
    {
    case CC_ToolButton:
        if (const auto toolbutton = qstyleoption_cast<const QStyleOptionToolButton*>(option))
        {
            bool reverse = option->direction == Qt::RightToLeft;
            bool drawborder = (widget && widget->property("showborder").toBool());

            if (drawborder)
                drawButtonSeparator(painter, rect, reverse);

            QRect button, menuarea;
            button = subControlRect(control, toolbutton, SC_ToolButton, widget);
            menuarea = subControlRect(control, toolbutton, SC_ToolButtonMenu, widget);

            State bflags = toolbutton->state;
            if (bflags & State_AutoRaise)
            {
                if (!(bflags & State_MouseOver))
                    bflags &= ~State_Raised;
            }

            State mflags = bflags;
            if (toolbutton->state & State_Sunken)
            {
                if (toolbutton->activeSubControls & SC_ToolButton)
                    bflags |= State_Sunken;
                if (toolbutton->activeSubControls & SC_ToolButtonMenu)
                    mflags |= State_Sunken;
            }

            QStyleOption tool(0);
            tool.palette = toolbutton->palette;
            if (toolbutton->subControls & SC_ToolButton)
            {
                tool.rect = button;
                tool.state = bflags;
                drawPrimitive(PE_PanelButtonTool, &tool, painter, widget);
            }

            QStyleOptionToolButton label = *toolbutton;

            label.palette = panelPalette(option->palette, lightColored(widget));
            if (widget && widget->property("highlightWidget").toBool())
            {
                label.palette.setColor(QPalette::ButtonText,
                    visionTheme()->color(Theme::IconsWarningToolBarColor));
            }
            int fw = pixelMetric(PM_DefaultFrameWidth, option, widget);
            label.rect = button.adjusted(fw, fw, -fw, -fw);

            drawControl(CE_ToolButtonLabel, &label, painter, widget);

            if (toolbutton->subControls & SC_ToolButtonMenu)
            {
                tool.state = mflags;
                tool.rect = menuarea.adjusted(1, 1, -1, -1);
                if (mflags & (State_Sunken | State_On | State_Raised))
                {
                    painter->setPen(Qt::gray);
                    const QRectF lineRect = QRectF(tool.rect).adjusted(-0.5, 2.5, 0, -2.5);
                    painter->drawLine(lineRect.topLeft(), lineRect.bottomLeft());
                    if (mflags & (State_Sunken))
                    {
                        QColor shade(0, 0, 0, 50);
                        painter->fillRect(tool.rect.adjusted(0, -1, 1, 1), shade);
                    }
                    else if (!HostOsInfo::isMacHost() && (mflags & State_MouseOver)) 
                    {
                        QColor shade(255, 255, 255, 50);
                        painter->fillRect(tool.rect.adjusted(0, -1, 1, 1), shade);
                    }
                }
                tool.rect = tool.rect.adjusted(2, 2, -2, -2);
                drawPrimitive(PE_IndicatorArrowDown, &tool, painter, widget);
            }
            else if (toolbutton->features & QStyleOptionToolButton::HasMenu && widget && 
                     !widget->property("noArrow").toBool() /*&&
                     !widget->inherits(QStringLiteral("QtOrientationToolButton"))*/)
            {
                int arrowSize = 6;
                QRect ir = toolbutton->rect.adjusted(1, 1, -1, -1);
                QStyleOptionToolButton newBtn = *toolbutton;
                newBtn.palette = panelPalette(option->palette);
                newBtn.rect = QRect(ir.right() - arrowSize - 1,
                    ir.height() - arrowSize - 2, arrowSize, arrowSize);
                drawPrimitive(PE_IndicatorArrowDown, &newBtn, painter, widget);
            }
        }
        break;
/* TODO
    case CC_ComboBox:
        if (const auto cb = qstyleoption_cast<const QStyleOptionComboBox*>(option))
        {
            painter->save();
            bool isEmpty = cb->currentText.isEmpty() && cb->currentIcon.isNull();
            bool reverse = option->direction == Qt::RightToLeft;
            bool drawborder = !(widget && widget->property("hideborder").toBool());
            bool drawleftborder = (widget && widget->property("drawleftborder").toBool());
            bool alignarrow = !(widget && widget->property("alignarrow").toBool());

            if (drawborder)
            {
                drawButtonSeparator(painter, rect, reverse);
                if (drawleftborder)
                    drawButtonSeparator(painter, rect.adjusted(0, 0, -rect.width() + 2, 0), reverse);
            }

            QStyleOption toolbutton = *option;
            if (isEmpty)
                toolbutton.state &= ~(State_Enabled | State_Sunken);
            painter->save();
            if (drawborder)
            {
                int leftClipAdjust = 0;
                if (drawleftborder)
                    leftClipAdjust = 2;
                painter->setClipRect(toolbutton.rect.adjusted(leftClipAdjust, 0, -2, 0));
            }
            drawPrimitive(PE_PanelButtonTool, &toolbutton, painter, widget);
            painter->restore();
            // Draw arrow
            int menuButtonWidth = 12;
            int left = !reverse ? rect.right() - menuButtonWidth : rect.left();
            int right = !reverse ? rect.right() : rect.left() + menuButtonWidth;
            QRect arrowRect((left + right) / 2 + (reverse ? 6 : -6), rect.center().y() - 3, 9, 9);

            if (!alignarrow)
            {
                int labelwidth = option->fontMetrics.horizontalAdvance(cb->currentText);
                if (reverse)
                    arrowRect.moveLeft(qMax(rect.width() - labelwidth - menuButtonWidth - 2, 4));
                else
                    arrowRect.moveLeft(qMin(labelwidth + menuButtonWidth - 2, rect.width() - menuButtonWidth - 4));
            }
            if (option->state & State_On)
                arrowRect.translate(QProxyStyle::pixelMetric(PM_ButtonShiftHorizontal, option, widget),
                    QProxyStyle::pixelMetric(PM_ButtonShiftVertical, option, widget));

            QStyleOption arrowOpt = *option;
            arrowOpt.rect = arrowRect;
            if (isEmpty)
                arrowOpt.state &= ~(State_Enabled | State_Sunken);

            if (styleHint(SH_ComboBox_Popup, option, widget))
            {
                arrowOpt.rect.translate(0, -3);
                drawPrimitive(PE_IndicatorArrowUp, &arrowOpt, painter, widget);
                arrowOpt.rect.translate(0, 6);
                drawPrimitive(PE_IndicatorArrowDown, &arrowOpt, painter, widget);
            }
            else

                drawPrimitive(PE_IndicatorArrowDown, &arrowOpt, painter, widget);

            painter->restore();
        }
        break;
*/
    default:
        QProxyStyle::drawComplexControl(control, option, painter, widget);
        break;
    }
}

void C3DStyle::drawButtonSeparator(QPainter* painter, const QRect& rect, bool reverse)
{
    const QRectF borderRect = QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5);
    if (visionTheme()->flag(Theme::FlatToolBars))
    {
        const int margin = 3;
        painter->setPen(visionTheme()->color(Theme::FancyToolBarSeparatorColor));
        painter->drawLine(borderRect.topRight() + QPointF(0, margin),
            borderRect.bottomRight() - QPointF(0, margin));
    }
    else
    {
        QLinearGradient grad(rect.topRight(), rect.bottomRight());
        grad.setColorAt(0, QColor(255, 255, 255, 20));
        grad.setColorAt(0.4, QColor(255, 255, 255, 60));
        grad.setColorAt(0.7, QColor(255, 255, 255, 50));
        grad.setColorAt(1, QColor(255, 255, 255, 40));
        painter->setPen(QPen(grad, 1));
        painter->drawLine(borderRect.topRight(), borderRect.bottomRight());
        grad.setColorAt(0, QColor(0, 0, 0, 30));
        grad.setColorAt(0.4, QColor(0, 0, 0, 70));
        grad.setColorAt(0.7, QColor(0, 0, 0, 70));
        grad.setColorAt(1, QColor(0, 0, 0, 40));
        painter->setPen(QPen(grad, 1));
        if (!reverse)
            painter->drawLine(borderRect.topRight() - QPointF(1, 0), borderRect.bottomRight() - QPointF(1, 0));
        else
            painter->drawLine(borderRect.topLeft(), borderRect.bottomLeft());
    }
}

} // namespace QtVision
} // namespace VSN
