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

#include <qt_aspects.h>

#include <qt_algorithm.h>
#include <qt_environment.h>
#include <qt_fancylineedit.h>
//#include "layoutbuilder.h"
#include <qt_pathchooser.h>
//#include "qtcsettings.h"
//#include "variablechooser.h"

#include <QAction>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPointer>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSpinBox>
#include <QTextEdit>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* BaseAspectPrivate */
class BaseAspectPrivate
{
public:
    Id m_id;
    QVariant m_value;
    QVariant m_defaultValue;
    std::function<QVariant(const QVariant &)> m_toSettings;
    std::function<QVariant(const QVariant &)> m_fromSettings;

    QString m_displayName;
    QString m_settingsKey; // Name of data in settings.
    QString m_tooltip;
    QString m_labelText;
    QPixmap m_labelPixmap;
    QIcon m_icon;
    QPointer<QLabel> m_label; // Owned by configuration widget
    QPointer<QAction> m_action; // Owned by us.

    bool m_visible = true;
    bool m_enabled = true;
    bool m_readOnly = true;
    bool m_autoApply = true;
    int m_spanX = 1;
    int m_spanY = 1;
    BaseAspect::ConfigWidgetCreator m_configWidgetCreator;
    QList<QPointer<QWidget>> m_subWidgets;

    BaseAspect::DataCreator m_dataCreator;
    BaseAspect::DataCloner m_dataCloner;
    QList<BaseAspect::DataExtractor> m_dataExtractors;
};


/* BaseAspect */
BaseAspect::BaseAspect()
    : d(new BaseAspectPrivate)
{
    addDataExtractor(this, &BaseAspect::value, &Data::value);
}

// --------------------------------------------------------------------------------------
// Destructs a BaseAspect.
// ---
BaseAspect::~BaseAspect()
{
    delete d->m_action;
}

Id BaseAspect::id() const
{
    return d->m_id;
}

void BaseAspect::setId(Id id)
{
    d->m_id = id;
}

QVariant BaseAspect::value() const
{
    return d->m_value;
}

// --------------------------------------------------------------------------------------
// Sets value.
// Emits changed() if the value changed.
// ---
void BaseAspect::setValue(const QVariant &value)
{
    if (setValueQuietly(value)) {
        emit changed();
        emitChangedValue();
    }
}

// --------------------------------------------------------------------------------------
// Sets value without emitting changed()
// Returns whether the value changed.
// ---
bool BaseAspect::setValueQuietly(const QVariant &value)
{
    if (d->m_value == value)
        return false;
    d->m_value = value;
    return true;
}

QVariant BaseAspect::defaultValue() const
{
    return d->m_defaultValue;
}

// --------------------------------------------------------------------------------------
// Sets a default value and the current value for this aspect.
//
// The current value will be set silently to the same value.
// It is reasonable to only set default values in the setup phase
// of the aspect.
// Default values will not be stored in settings.
// ---
void BaseAspect::setDefaultValue(const QVariant &value)
{
    d->m_defaultValue = value;
    d->m_value = value;
}

void BaseAspect::setDisplayName(const QString &displayName)
{
    d->m_displayName = displayName;
}

bool BaseAspect::isVisible() const
{
    return d->m_visible;
}

// --------------------------------------------------------------------------------------
// Shows or hides the visual representation of this aspect depending
// on the value of visible.
// By default, it is visible.
// ---
void BaseAspect::setVisible(bool visible)
{
    d->m_visible = visible;
    for (QWidget *w : qAsConst(d->m_subWidgets)) 
    {
        QTV_ASSERT(w, continue);
        // This may happen during layout building. Explicit setting visibility here
        // may create a show a toplevel widget for a moment until it is parented
        // to some non-shown widget.
        if (w->parentWidget())
            w->setVisible(visible);
    }
}

void BaseAspect::setupLabel()
{
    QTV_ASSERT(!d->m_label, delete d->m_label);
    if (d->m_labelText.isEmpty() && d->m_labelPixmap.isNull())
        return;
    d->m_label = new QLabel(d->m_labelText);
    d->m_label->setTextInteractionFlags(d->m_label->textInteractionFlags()
                                        | Qt::TextSelectableByMouse);
    connect(d->m_label, &QLabel::linkActivated, this, [this](const QString &link) {
        emit labelLinkActivated(link);
    });
    if (!d->m_labelPixmap.isNull())
        d->m_label->setPixmap(d->m_labelPixmap);
    registerSubWidget(d->m_label);
}

void BaseAspect::addLabeledItem(LayoutBuilder& /*builder*/, QWidget* /*widget*/)
{
    setupLabel();
    Q_ASSERT(false);
    /*
    if (QLabel* l = label()) 
    {
        l->setBuddy(widget);
        builder.addItem(l);
        LayoutBuilder::LayoutItem item(widget);
        item.span = std::max(d->m_spanX - 1, 1);
        builder.addItem(item);
    } 
    else 
    {
        builder.addItem(LayoutBuilder::LayoutItem(widget));
    }
    */
}

// --------------------------------------------------------------------------------------
// Sets labelText as text for the separate label in the visual
// representation of this aspect.
// ---
void BaseAspect::setLabelText(const QString &labelText)
{
    d->m_labelText = labelText;
    if (d->m_label)
        d->m_label->setText(labelText);
}

// --------------------------------------------------------------------------------------
// Sets labelPixmap as pixmap for the separate label in the visual
// representation of this aspect.
// ---
void BaseAspect::setLabelPixmap(const QPixmap &labelPixmap)
{
    d->m_labelPixmap = labelPixmap;
    if (d->m_label)
        d->m_label->setPixmap(labelPixmap);
}

void BaseAspect::setIcon(const QIcon &icon)
{
    d->m_icon = icon;
    if (d->m_action)
        d->m_action->setIcon(icon);
}

// --------------------------------------------------------------------------------------
// Returns the current text for the separate label in the visual
// representation of this aspect.
// ---
QString BaseAspect::labelText() const
{
    return d->m_labelText;
}

QLabel *BaseAspect::label() const
{
    return d->m_label.data();
}

QString BaseAspect::toolTip() const
{
    return d->m_tooltip;
}

// --------------------------------------------------------------------------------------
// Sets tooltip as tool tip for the visual representation of this aspect.
// ---
void BaseAspect::setToolTip(const QString &tooltip)
{
    d->m_tooltip = tooltip;
    for (QWidget *w : qAsConst(d->m_subWidgets)) {
        QTV_ASSERT(w, continue);
        w->setToolTip(tooltip);
    }
}

bool BaseAspect::isEnabled() const
{
    return d->m_enabled;
}

void BaseAspect::setEnabled(bool enabled)
{
    d->m_enabled = enabled;
    for (QWidget *w : qAsConst(d->m_subWidgets)) 
    {
        QTV_ASSERT(w, continue);
        w->setEnabled(enabled);
    }
}

// --------------------------------------------------------------------------------------
// Makes the enabled state of this aspect depend on the checked state of \a checker.
// ---
void BaseAspect::setEnabler(BoolAspect *checker)
{
    QTV_ASSERT(checker, return);
    setEnabled(checker->value());
    connect(checker, &BoolAspect::volatileValueChanged, this, &BaseAspect::setEnabled);
    connect(checker, &BoolAspect::valueChanged, this, &BaseAspect::setEnabled);
}

bool BaseAspect::isReadOnly() const
{
    return d->m_readOnly;
}

void BaseAspect::setReadOnly(bool readOnly)
{
    d->m_readOnly = readOnly;
    for (QWidget *w : qAsConst(d->m_subWidgets)) {
        QTV_ASSERT(w, continue);
        if (auto lineEdit = qobject_cast<QLineEdit *>(w))
            lineEdit->setReadOnly(readOnly);
        else if (auto textEdit = qobject_cast<QTextEdit *>(w))
            textEdit->setReadOnly(readOnly);
    }
}

void BaseAspect::setSpan(int x, int y)
{
    d->m_spanX = x;
    d->m_spanY = y;
}

bool BaseAspect::isAutoApply() const
{
    return d->m_autoApply;
}

// --------------------------------------------------------------------------------------
// Sets auto-apply mode. When auto-apply mode is on, user interaction to this
// aspect's widget will not modify the \c value of the aspect until \c apply()
// is called programmatically.
// ---
void BaseAspect::setAutoApply(bool on)
{
    d->m_autoApply = on;
}

void BaseAspect::setConfigWidgetCreator(const ConfigWidgetCreator &configWidgetCreator)
{
    d->m_configWidgetCreator = configWidgetCreator;
}

// --------------------------------------------------------------------------------------
// Returns the key to be used when accessing the settings.
// ---
QString BaseAspect::settingsKey() const
{
    return d->m_settingsKey;
}

// --------------------------------------------------------------------------------------
// Sets the key to be used when accessing the settings.
// ---
void BaseAspect::setSettingsKey(const QString &key)
{
    d->m_settingsKey = key;
}

// --------------------------------------------------------------------------------------
// Sets the key and group to be used when accessing the settings.
// ---
void BaseAspect::setSettingsKey(const QString &group, const QString &key)
{
    d->m_settingsKey = group + "/" + key;
}

// --------------------------------------------------------------------------------------
// Returns the string that should be used when this action appears in menus
// or other places that are typically used with Book style capitalization.
// If no display name is set, the label text will be used as fallback.
// ---
QString BaseAspect::displayName() const
{
    return d->m_displayName.isEmpty() ? d->m_labelText : d->m_displayName;
}

QWidget* BaseAspect::createConfigWidget() const
{
    return d->m_configWidgetCreator ? d->m_configWidgetCreator() : nullptr;
}

QAction* BaseAspect::action()
{
    if (!d->m_action) 
    {
        d->m_action = new QAction(labelText());
        d->m_action->setIcon(d->m_icon);
    }
    return d->m_action;
}

// --------------------------------------------------------------------------------------
// Adds the visual representation of this aspect to a layout using
// a layout builder.
// ---
void BaseAspect::addToLayout(LayoutBuilder &)
{
}

// --------------------------------------------------------------------------------------
// Updates this aspect's value from user-initiated changes in the widget.
// This has only an effect if isAutoApply is false.
// ---
void BaseAspect::apply()
{
    QTV_CHECK(!d->m_autoApply);
    if (isDirty())
        setValue(volatileValue());
}

// --------------------------------------------------------------------------------------
// Discard user changes in the widget and restore widget contents from
// aspect's value.
// This has only an effect if \c isAutoApply is false.
// ---
void BaseAspect::cancel()
{
    QTV_CHECK(!d->m_autoApply);
    if (!d->m_subWidgets.isEmpty())
        setVolatileValue(d->m_value);
}

void BaseAspect::finish()
{
    // No qDeleteAll() possible as long as the connect in registerSubWidget() exist.
    while (d->m_subWidgets.size())
        delete d->m_subWidgets.takeLast();
}

bool BaseAspect::hasAction() const
{
    return d->m_action != nullptr;
}

bool BaseAspect::isDirty() const
{
    QTV_CHECK(!isAutoApply());
    // Aspects that were never shown cannot contain unsaved user changes.
    if (d->m_subWidgets.isEmpty())
        return false;
    return volatileValue() != d->m_value;
}

QVariant BaseAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    return {};
}

void BaseAspect::setVolatileValue(const QVariant &val)
{
    Q_UNUSED(val);
}

void BaseAspect::registerSubWidget(QWidget *widget)
{
    d->m_subWidgets.append(widget);

    // FIXME: This interferes with qDeleteAll() in finish() and destructor,
    // it would not be needed when all users actually deleted their subwidgets,
    // e.g. the SettingsPage::finish() base implementation, but this still
    // leaves the cases where no such base functionality is available, e.g.
    // in the run/build config aspects.
    connect(widget, &QObject::destroyed, this, [this, widget] {
        d->m_subWidgets.removeAll(widget);
    });

    widget->setEnabled(d->m_enabled);
    widget->setToolTip(d->m_tooltip);

    // Visible is on by default. Not setting it explicitly avoid popping
    // it up when the parent is not set yet, the normal case.
    if (!d->m_visible)
        widget->setVisible(d->m_visible);
}

void BaseAspect::saveToMap(QVariantMap &data, const QVariant &value,
                           const QVariant &defaultValue, const QString &key)
{
    if (key.isEmpty())
        return;
    if (value == defaultValue)
        data.remove(key);
    else
        data.insert(key, value);
}

/*!
    Retrieves the internal value of this BaseAspect from a \c QVariantMap.
*/
void BaseAspect::fromMap(const QVariantMap &map)
{
    const QVariant val = map.value(settingsKey(), toSettingsValue(defaultValue()));
    setValue(fromSettingsValue(val));
}

/*!
    Stores the internal value of this BaseAspect into a \c QVariantMap.
*/
void BaseAspect::toMap(QVariantMap &map) const
{
    saveToMap(map, toSettingsValue(d->m_value), toSettingsValue(d->m_defaultValue), settingsKey());
}

void BaseAspect::readSettings(const QSettings *settings)
{
    if (settingsKey().isEmpty())
        return;
    const QVariant &val = settings->value(settingsKey());
    setValue(val.isValid() ? fromSettingsValue(val) : defaultValue());
}

void BaseAspect::writeSettings(QSettings* /*settings*/) const
{
    if (settingsKey().isEmpty())
        return;
    Q_ASSERT(false);

//    QtcSettings::setValueWithDefault(settings,
//                                     settingsKey(),
//                                     toSettingsValue(value()),
//                                     toSettingsValue(defaultValue()));
}

void BaseAspect::setFromSettingsTransformation(const SavedValueTransformation &transform)
{
    d->m_fromSettings = transform;
}

void BaseAspect::setToSettingsTransformation(const SavedValueTransformation &transform)
{
    d->m_toSettings = transform;
}

QVariant BaseAspect::toSettingsValue(const QVariant &val) const
{
    return d->m_toSettings ? d->m_toSettings(val) : val;
}

QVariant BaseAspect::fromSettingsValue(const QVariant &val) const
{
    return d->m_fromSettings ? d->m_fromSettings(val) : val;
}

class BoolAspectPrivate
{
public:
    BoolAspect::LabelPlacement m_labelPlacement = BoolAspect::LabelPlacement::AtCheckBox;
    QPointer<QCheckBox> m_checkBox; // Owned by configuration widget
    QPointer<QGroupBox> m_groupBox; // For BoolAspects handling GroupBox check boxes
};

class SelectionAspectPrivate
{
public:
    ~SelectionAspectPrivate() { delete m_buttonGroup; }

    SelectionAspect::DisplayStyle m_displayStyle
            = SelectionAspect::DisplayStyle::RadioButtons;
    QVector<SelectionAspect::Option> m_options;

    // These are all owned by the configuration widget.
    QList<QPointer<QRadioButton>> m_buttons;
    QPointer<QComboBox> m_comboBox;
    QPointer<QButtonGroup> m_buttonGroup;
};

/* MultiSelectionAspectPrivate */
class MultiSelectionAspectPrivate
{
public:
    explicit MultiSelectionAspectPrivate(MultiSelectionAspect *q) : q(q) {}

    bool setValueSelectedHelper(const QString &value, bool on);

    MultiSelectionAspect *q;
    QStringList m_allValues;
    MultiSelectionAspect::DisplayStyle m_displayStyle
        = MultiSelectionAspect::DisplayStyle::ListView;

    // These are all owned by the configuration widget.
    QPointer<QListWidget> m_listView;
};

/* StringAspectPrivate */
class StringAspectPrivate
{
public:
    StringAspect::DisplayStyle m_displayStyle = StringAspect::LabelDisplay;
    StringAspect::CheckBoxPlacement m_checkBoxPlacement
        = StringAspect::CheckBoxPlacement::Right;
    StringAspect::UncheckedSemantics m_uncheckedSemantics
        = StringAspect::UncheckedSemantics::Disabled;
    std::function<QString(const QString &)> m_displayFilter;
    std::unique_ptr<BoolAspect> m_checker;

    Qt::TextElideMode m_elideMode = Qt::ElideNone;
    QString m_placeHolderText;
    QString m_historyCompleterKey;
    PathChooser::Kind m_expectedKind = PathChooser::File;
    EnvironmentChange m_environmentChange;
    QPointer<ElidingLabel> m_labelDisplay;
    QPointer<FancyLineEdit> m_lineEditDisplay;
    QPointer<PathChooser> m_pathChooserDisplay;
    QPointer<QTextEdit> m_textEditDisplay;
    MacroExpanderProvider m_expanderProvider;
    FilePath m_baseFileName;
    StringAspect::ValueAcceptor m_valueAcceptor;
    FancyLineEdit::ValidationFunction m_validator;
    std::function<void()> m_openTerminal;

    bool m_undoRedoEnabled = true;
    bool m_acceptRichText = false;
    bool m_showToolTipOnLabel = false;
    bool m_fileDialogOnly = false;
    bool m_useResetButton = false;
    bool m_autoApplyOnEditingFinished = false;
    // Used to block recursive editingFinished signals for example when return is pressed, and
    // the validation changes focus by opening a dialog
    bool m_blockAutoApply = false;

    template<class Widget> void updateWidgetFromCheckStatus(StringAspect *aspect, Widget *w)
    {
        const bool enabled = !m_checker || m_checker->value();
        if (m_uncheckedSemantics == StringAspect::UncheckedSemantics::Disabled)
            w->setEnabled(enabled && aspect->isEnabled());
        else
            w->setReadOnly(!enabled || aspect->isReadOnly());
    }
};

class IntegerAspectPrivate
{
public:
    VSN::QtVision::optional<qint64> m_minimumValue;
    VSN::QtVision::optional<qint64> m_maximumValue;
    int m_displayIntegerBase = 10;
    qint64 m_displayScaleFactor = 1;
    QString m_prefix;
    QString m_suffix;
    QString m_specialValueText;
    int m_singleStep = 1;
    QPointer<QSpinBox> m_spinBox; // Owned by configuration widget
};

class DoubleAspectPrivate
{
public:
    VSN::QtVision::optional<double> m_minimumValue;
    VSN::QtVision::optional<double> m_maximumValue;
    QString m_prefix;
    QString m_suffix;
    QString m_specialValueText;
    double m_singleStep = 1;
    QPointer<QDoubleSpinBox> m_spinBox; // Owned by configuration widget
};

class StringListAspectPrivate
{
public:
};

class TextDisplayPrivate
{
public:
    QString m_message;
    InfoLabel::InfoType m_type;
    QPointer<InfoLabel> m_label;
};

/*
    The DisplayStyle enum describes the main visual characteristics of a
    string aspect.

      \value LabelDisplay
             Based on QLabel, used for text that cannot be changed by the
             user in this place, for example names of executables that are
             defined in the build system.

      \value LineEditDisplay
             Based on QLineEdit, used for user-editable strings that usually
             fit on a line.

      \value TextEditDisplay
             Based on QTextEdit, used for user-editable strings that often
             do not fit on a line.

      \value PathChooserDisplay
             Based on Utils::PathChooser.
*/

/*
    A string aspect is a string-like property of some object, together with
    a description of its behavior for common operations like visualizing or
    persisting.

    String aspects can represent for example a parameter for an external commands,
    paths in a file system, or simply strings.

    The string can be displayed using a QLabel, QLineEdit, QTextEdit or
    Utils::PathChooser.

    The visual representation often contains a label in front of the display
    of the actual value.
*/

/* StringAspect */
StringAspect::StringAspect()
    : d(new StringAspectPrivate)
{
    setDefaultValue(QString());
    setSpan(2, 1); // Default: Label + something

    addDataExtractor(this, &StringAspect::value, &Data::value);
    addDataExtractor(this, &StringAspect::filePath, &Data::filePath);
}

StringAspect::~StringAspect() = default;

void StringAspect::setValueAcceptor(StringAspect::ValueAcceptor &&acceptor)
{
    d->m_valueAcceptor = std::move(acceptor);
}

// --------------------------------------------------------------------------------------
// Returns the value of this StringAspect as an ordinary QString.
// ---
QString StringAspect::value() const
{
    return BaseAspect::value().toString();
}

// --------------------------------------------------------------------------------------
// Sets the value of this StringAspect from an ordinary QString.
// ---
void StringAspect::setValue(const QString &val)
{
    const bool isSame = val == value();
    if (isSame)
        return;

    QString processedValue = val;
    if (d->m_valueAcceptor) {
        const VSN::QtVision::optional<QString> tmp = d->m_valueAcceptor(value(), val);
        if (!tmp) {
            update(); // Make sure the original value is retained in the UI
            return;
        }
        processedValue = tmp.value();
    }

    if (BaseAspect::setValueQuietly(QVariant(processedValue))) {
        update();
        emit changed();
        emit valueChanged(processedValue);
    }
}

void StringAspect::setDefaultValue(const QString &val)
{
    BaseAspect::setDefaultValue(val);
}

void StringAspect::fromMap(const QVariantMap &map)
{
    if (!settingsKey().isEmpty())
        BaseAspect::setValueQuietly(map.value(settingsKey(), defaultValue()));
    if (d->m_checker)
        d->m_checker->fromMap(map);
}

void StringAspect::toMap(QVariantMap &map) const
{
    saveToMap(map, value(), defaultValue(), settingsKey());
    if (d->m_checker)
        d->m_checker->toMap(map);
}

// --------------------------------------------------------------------------------------
// Returns the value of this string aspect as \c Utils::FilePath.
// This simply uses \c FilePath::fromUserInput() for the
// conversion. It does not use any check that the value is actually
// a valid file path.
// ---
FilePath StringAspect::filePath() const
{
    return FilePath::fromUserInput(value());
}

// --------------------------------------------------------------------------------------
// Sets the value of this string aspect to \a value.
// This simply uses \c FilePath::toUserOutput() for the
// conversion. It does not use any check that the value is actually
// a file path.
// ---
void StringAspect::setFilePath(const FilePath &value)
{
    setValue(value.toUserOutput());
}

void StringAspect::setDefaultFilePath(const FilePath &value)
{
    setDefaultValue(value.toUserOutput());
}

PathChooser *StringAspect::pathChooser() const
{
    return d->m_pathChooserDisplay.data();
}

void StringAspect::setShowToolTipOnLabel(bool show)
{
    d->m_showToolTipOnLabel = show;
    update();
}

// --------------------------------------------------------------------------------------
// Sets a displayFilter for fine-tuning the visual appearance
//    of the value of this string aspect.
// ---
void StringAspect::setDisplayFilter(const std::function<QString(const QString &)> &displayFilter)
{
    d->m_displayFilter = displayFilter;
}

// --------------------------------------------------------------------------------------
// Returns the check box value.
// ---
bool StringAspect::isChecked() const
{
    return !d->m_checker || d->m_checker->value();
}

// --------------------------------------------------------------------------------------
// Sets the check box of this aspect to checked.
// a makeCheckable(), isChecked()
// ---
void StringAspect::setChecked(bool checked)
{
    QTV_ASSERT(d->m_checker, return);
    d->m_checker->setValue(checked);
}

// --------------------------------------------------------------------------------------
// Selects the main display characteristics of the aspect according to
// displayStyle.
// Not all StringAspect features are available with all display styles.
// a Utils::StringAspect::DisplayStyle
// ---
void StringAspect::setDisplayStyle(DisplayStyle displayStyle)
{
    d->m_displayStyle = displayStyle;
}

// --------------------------------------------------------------------------------------
// Sets placeHolderText as place holder for line and text displays.
// ---
void StringAspect::setPlaceHolderText(const QString &placeHolderText)
{
    d->m_placeHolderText = placeHolderText;
    if (d->m_lineEditDisplay)
        d->m_lineEditDisplay->setPlaceholderText(placeHolderText);
    if (d->m_textEditDisplay)
        d->m_textEditDisplay->setPlaceholderText(placeHolderText);
}

// --------------------------------------------------------------------------------------
// Sets elideMode as label elide mode.
// ---
void StringAspect::setElideMode(Qt::TextElideMode elideMode)
{
    d->m_elideMode = elideMode;
    if (d->m_labelDisplay)
        d->m_labelDisplay->setElideMode(elideMode);
}

// --------------------------------------------------------------------------------------
// Sets historyCompleterKey as key for the history completer settings for
// line edits and path chooser displays.
// a PathChooser::setExpectedKind()
// ---
void StringAspect::setHistoryCompleter(const QString &historyCompleterKey)
{
    d->m_historyCompleterKey = historyCompleterKey;
    if (d->m_lineEditDisplay)
        d->m_lineEditDisplay->setHistoryCompleter(historyCompleterKey);
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setHistoryCompleter(historyCompleterKey);
}

// --------------------------------------------------------------------------------------
// Sets expectedKind as expected kind for path chooser displays.
// ---
void StringAspect::setExpectedKind(const PathChooser::Kind expectedKind)
{
    d->m_expectedKind = expectedKind;
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setExpectedKind(expectedKind);
}

void StringAspect::setEnvironmentChange(const EnvironmentChange &change)
{
    d->m_environmentChange = change;
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setEnvironmentChange(change);
}

void StringAspect::setBaseFileName(const FilePath &baseFileName)
{
    d->m_baseFileName = baseFileName;
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setBaseDirectory(baseFileName);
}

void StringAspect::setUndoRedoEnabled(bool undoRedoEnabled)
{
    d->m_undoRedoEnabled = undoRedoEnabled;
    if (d->m_textEditDisplay)
        d->m_textEditDisplay->setUndoRedoEnabled(undoRedoEnabled);
}

void StringAspect::setAcceptRichText(bool acceptRichText)
{
    d->m_acceptRichText = acceptRichText;
    if (d->m_textEditDisplay)
        d->m_textEditDisplay->setAcceptRichText(acceptRichText);
}

void StringAspect::setMacroExpanderProvider(const MacroExpanderProvider &expanderProvider)
{
    d->m_expanderProvider = expanderProvider;
}

void StringAspect::setUseGlobalMacroExpander()
{
    d->m_expanderProvider = &globalMacroExpander;
}

void StringAspect::setUseResetButton()
{
    d->m_useResetButton = true;
}

void StringAspect::setValidationFunction(const FancyLineEdit::ValidationFunction &validator)
{
    d->m_validator = validator;
    if (d->m_lineEditDisplay)
        d->m_lineEditDisplay->setValidationFunction(d->m_validator);
    else if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setValidationFunction(d->m_validator);
}

void StringAspect::setOpenTerminalHandler(const std::function<void ()> &openTerminal)
{
    d->m_openTerminal = openTerminal;
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->setOpenTerminalHandler(openTerminal);
}

void StringAspect::setAutoApplyOnEditingFinished(bool applyOnEditingFinished)
{
    d->m_autoApplyOnEditingFinished = applyOnEditingFinished;
}

void StringAspect::validateInput()
{
    if (d->m_pathChooserDisplay)
        d->m_pathChooserDisplay->triggerChanged();
    if (d->m_lineEditDisplay)
        d->m_lineEditDisplay->validate();
}

void StringAspect::setUncheckedSemantics(StringAspect::UncheckedSemantics semantics)
{
    d->m_uncheckedSemantics = semantics;
}

void StringAspect::addToLayout(LayoutBuilder& /*builder*/)
{
    if (d->m_checker && d->m_checkBoxPlacement == CheckBoxPlacement::Top) 
    {
        Q_ASSERT(false);
//        d->m_checker->addToLayout(builder);
//        builder.finishRow();
    }

    const auto useMacroExpander = [this](QWidget* /*w*/)
    {
        if (!d->m_expanderProvider)
            return;
        Q_ASSERT(false);
//        const auto chooser = new VariableChooser(w);
//        chooser->addSupportedWidget(w);
//        chooser->addMacroExpanderProvider(d->m_expanderProvider);
    };

    const QString displayedString = d->m_displayFilter ? d->m_displayFilter(value()) : value();

    switch (d->m_displayStyle) {
    case PathChooserDisplay:
        d->m_pathChooserDisplay = createSubWidget<PathChooser>();
        d->m_pathChooserDisplay->setExpectedKind(d->m_expectedKind);
        if (!d->m_historyCompleterKey.isEmpty())
            d->m_pathChooserDisplay->setHistoryCompleter(d->m_historyCompleterKey);
        if (d->m_validator)
            d->m_pathChooserDisplay->setValidationFunction(d->m_validator);
        d->m_pathChooserDisplay->setEnvironmentChange(d->m_environmentChange);
        d->m_pathChooserDisplay->setBaseDirectory(d->m_baseFileName);
        d->m_pathChooserDisplay->setOpenTerminalHandler(d->m_openTerminal);
        if (defaultValue() == value())
            d->m_pathChooserDisplay->setDefaultValue(defaultValue().toString());
        else
            d->m_pathChooserDisplay->setFilePath(FilePath::fromUserInput(displayedString));
        d->updateWidgetFromCheckStatus(this, d->m_pathChooserDisplay.data());
        Q_ASSERT(false);
//        addLabeledItem(builder, d->m_pathChooserDisplay);
        useMacroExpander(d->m_pathChooserDisplay->lineEdit());
        if (isAutoApply()) {
            if (d->m_autoApplyOnEditingFinished) {
                const auto setPathChooserValue = [this] {
                    if (d->m_blockAutoApply)
                        return;
                    d->m_blockAutoApply = true;
                    setValue(d->m_pathChooserDisplay->filePath().toString());
                    d->m_blockAutoApply = false;
                };
                connect(d->m_pathChooserDisplay, &PathChooser::editingFinished, this, setPathChooserValue);
                connect(d->m_pathChooserDisplay, &PathChooser::browsingFinished, this, setPathChooserValue);
            } else {
                connect(d->m_pathChooserDisplay, &PathChooser::pathChanged,
                        this, [this](const QString &path) {
                    setValue(path);
                });
            }
        }
        break;
    case LineEditDisplay:
        d->m_lineEditDisplay = createSubWidget<FancyLineEdit>();
        d->m_lineEditDisplay->setPlaceholderText(d->m_placeHolderText);
        if (!d->m_historyCompleterKey.isEmpty())
            d->m_lineEditDisplay->setHistoryCompleter(d->m_historyCompleterKey);
        if (d->m_validator)
            d->m_lineEditDisplay->setValidationFunction(d->m_validator);
        d->m_lineEditDisplay->setTextKeepingActiveCursor(displayedString);
        d->updateWidgetFromCheckStatus(this, d->m_lineEditDisplay.data());
        Q_ASSERT(false);
//        addLabeledItem(builder, d->m_lineEditDisplay);
        useMacroExpander(d->m_lineEditDisplay);
        if (isAutoApply()) {
            if (d->m_autoApplyOnEditingFinished) {
                connect(d->m_lineEditDisplay, &FancyLineEdit::editingFinished, this, [this] {
                    if (d->m_blockAutoApply)
                        return;
                    d->m_blockAutoApply = true;
                    setValue(d->m_lineEditDisplay->text());
                    d->m_blockAutoApply = false;
                });
            } else {
                connect(d->m_lineEditDisplay,
                        &FancyLineEdit::textEdited,
                        this,
                        &StringAspect::setValue);
                connect(d->m_lineEditDisplay, &FancyLineEdit::editingFinished, this, [this] {
                    setValue(d->m_lineEditDisplay->text());
                });
            }
        }
        if (d->m_useResetButton) {
            auto resetButton = createSubWidget<QPushButton>(tr("Reset"));
            resetButton->setEnabled(d->m_lineEditDisplay->text() != defaultValue());
            connect(resetButton, &QPushButton::clicked, this, [this] {
                d->m_lineEditDisplay->setText(defaultValue().toString());
            });
            connect(d->m_lineEditDisplay, &QLineEdit::textChanged, this, [this, resetButton] {
                resetButton->setEnabled(d->m_lineEditDisplay->text() != defaultValue());
            });
            Q_ASSERT(false);
//            builder.addItem(resetButton);
        }
        break;
    case TextEditDisplay:
        d->m_textEditDisplay = createSubWidget<QTextEdit>();
        d->m_textEditDisplay->setPlaceholderText(d->m_placeHolderText);
        d->m_textEditDisplay->setUndoRedoEnabled(d->m_undoRedoEnabled);
        d->m_textEditDisplay->setAcceptRichText(d->m_acceptRichText);
        d->m_textEditDisplay->setTextInteractionFlags(Qt::TextEditorInteraction);
        d->m_textEditDisplay->setText(displayedString);
        d->updateWidgetFromCheckStatus(this, d->m_textEditDisplay.data());
        Q_ASSERT(false);
//        addLabeledItem(builder, d->m_textEditDisplay);
        useMacroExpander(d->m_textEditDisplay);
        if (isAutoApply()) {
            connect(d->m_textEditDisplay, &QTextEdit::textChanged, this, [this] {
                setValue(d->m_textEditDisplay->document()->toPlainText());
            });
        }
        break;
    case LabelDisplay:
        d->m_labelDisplay = createSubWidget<ElidingLabel>();
        d->m_labelDisplay->setElideMode(d->m_elideMode);
        d->m_labelDisplay->setTextInteractionFlags(Qt::TextSelectableByMouse);
        d->m_labelDisplay->setText(displayedString);
        d->m_labelDisplay->setToolTip(d->m_showToolTipOnLabel ? displayedString : toolTip());
        Q_ASSERT(false);
//        addLabeledItem(builder, d->m_labelDisplay);
        break;
    }

    validateInput();

    if (d->m_checker && d->m_checkBoxPlacement == CheckBoxPlacement::Right)
    {
        Q_ASSERT(false);
//        d->m_checker->addToLayout(builder);
    }
}

QVariant StringAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    switch (d->m_displayStyle) {
    case PathChooserDisplay:
        QTV_ASSERT(d->m_pathChooserDisplay, return {});
        return d->m_pathChooserDisplay->filePath().toString();
    case LineEditDisplay:
        QTV_ASSERT(d->m_lineEditDisplay, return {});
        return d->m_lineEditDisplay->text();
    case TextEditDisplay:
        QTV_ASSERT(d->m_textEditDisplay, return {});
        return d->m_textEditDisplay->document()->toPlainText();
    case LabelDisplay:
        break;
    }
    return {};
}

void StringAspect::setVolatileValue(const QVariant &val)
{
    switch (d->m_displayStyle) {
    case PathChooserDisplay:
        if (d->m_pathChooserDisplay)
            d->m_pathChooserDisplay->setFilePath(FilePath::fromVariant(val));
        break;
    case LineEditDisplay:
        if (d->m_lineEditDisplay)
            d->m_lineEditDisplay->setText(val.toString());
        break;
    case TextEditDisplay:
        if (d->m_textEditDisplay)
            d->m_textEditDisplay->document()->setPlainText(val.toString());
        break;
    case LabelDisplay:
        break;
    }
}

void StringAspect::emitChangedValue()
{
    emit valueChanged(value());
}

void StringAspect::update()
{
    const QString displayedString = d->m_displayFilter ? d->m_displayFilter(value()) : value();

    if (d->m_pathChooserDisplay) {
        d->m_pathChooserDisplay->setFilePath(FilePath::fromString(displayedString));
        d->updateWidgetFromCheckStatus(this, d->m_pathChooserDisplay.data());
    }

    if (d->m_lineEditDisplay) {
        d->m_lineEditDisplay->setTextKeepingActiveCursor(displayedString);
        d->updateWidgetFromCheckStatus(this, d->m_lineEditDisplay.data());
    }

    if (d->m_textEditDisplay) {
        const QString old = d->m_textEditDisplay->document()->toPlainText();
        if (displayedString != old)
            d->m_textEditDisplay->setText(displayedString);
        d->updateWidgetFromCheckStatus(this, d->m_textEditDisplay.data());
    }

    if (d->m_labelDisplay) {
        d->m_labelDisplay->setText(displayedString);
        d->m_labelDisplay->setToolTip(d->m_showToolTipOnLabel ? displayedString : toolTip());
    }

    validateInput();
}

// --------------------------------------------------------------------------------------
// Adds a check box with a checkerLabel according to checkBoxPlacement
// to the line edit.
// The state of the check box is made persistent when using a non-emtpy
// checkerKey.
// ---
void StringAspect::makeCheckable(CheckBoxPlacement checkBoxPlacement,
                                     const QString &checkerLabel, const QString &checkerKey)
{
    QTV_ASSERT(!d->m_checker, return);
    d->m_checkBoxPlacement = checkBoxPlacement;
    d->m_checker.reset(new BoolAspect);
    d->m_checker->setLabel(checkerLabel, checkBoxPlacement == CheckBoxPlacement::Top
                           ? BoolAspect::LabelPlacement::InExtraLabel
                           : BoolAspect::LabelPlacement::AtCheckBox);
    d->m_checker->setSettingsKey(checkerKey);

    connect(d->m_checker.get(), &BoolAspect::changed, this, &StringAspect::update);
    connect(d->m_checker.get(), &BoolAspect::changed, this, &StringAspect::changed);
    connect(d->m_checker.get(), &BoolAspect::changed, this, &StringAspect::checkedChanged);

    update();
}

// --------------------------------------------------------------------------------------
// A boolean aspect is a boolean property of some object, together with
// a description of its behavior for common operations like visualizing or
// persisting.

// The boolean aspect is displayed using a QCheckBox.

// The visual representation often contains a label in front or after
// the display of the actual checkmark.
// ---
BoolAspect::BoolAspect(const QString &settingsKey)
    : d(new BoolAspectPrivate)
{
    setDefaultValue(false);
    setSettingsKey(settingsKey);
    setSpan(2, 1);

    addDataExtractor(this, &BoolAspect::value, &Data::value);
}

BoolAspect::~BoolAspect() = default;

void BoolAspect::addToLayout(LayoutBuilder& /*builder*/)
{
    QTV_CHECK(!d->m_checkBox);
    d->m_checkBox = createSubWidget<QCheckBox>();
    switch (d->m_labelPlacement) {
    case LabelPlacement::AtCheckBoxWithoutDummyLabel:
        d->m_checkBox->setText(labelText());
        Q_ASSERT(false);
//        builder.addItem(d->m_checkBox.data());
        break;
    case LabelPlacement::AtCheckBox: {
        d->m_checkBox->setText(labelText());
        Q_ASSERT(false);
//        LayoutBuilder::LayoutType type = builder.layoutType();
//        if (type == LayoutBuilder::FormLayout)
//            builder.addItem(createSubWidget<QLabel>());
//        builder.addItem(d->m_checkBox.data());
        break;
    }
    case LabelPlacement::InExtraLabel:
        Q_ASSERT(false);
//        addLabeledItem(builder, d->m_checkBox);
        break;
    }
    d->m_checkBox->setChecked(value());
    if (isAutoApply()) {
        connect(d->m_checkBox.data(), &QAbstractButton::clicked,
                this, [this](bool val) { setValue(val); });
    }
    connect(d->m_checkBox.data(), &QAbstractButton::clicked,
            this, &BoolAspect::volatileValueChanged);
}

QAction *BoolAspect::action()
{
    if (hasAction())
        return BaseAspect::action();
    auto act = BaseAspect::action(); // Creates it.
    act->setCheckable(true);
    act->setChecked(value());
    act->setToolTip(toolTip());
    connect(act, &QAction::triggered, this, [this](bool newValue) {
        // The check would be nice to have in simple conditions, but if we
        // have an action that's used both on a settings page and as action
        // in a menu like "Use FakeVim", isAutoApply() is false, and yet this
        // here can trigger.
        //QTV_CHECK(isAutoApply());
        setValue(newValue);
    });
    return act;
}

QVariant BoolAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    if (d->m_checkBox)
        return d->m_checkBox->isChecked();
    if (d->m_groupBox)
        return d->m_groupBox->isChecked();
    QTV_CHECK(false);
    return {};
}

void BoolAspect::setVolatileValue(const QVariant &val)
{
    QTV_CHECK(!isAutoApply());
    if (d->m_checkBox)
        d->m_checkBox->setChecked(val.toBool());
    else if (d->m_groupBox)
        d->m_groupBox->setChecked(val.toBool());
}

void BoolAspect::emitChangedValue()
{
    emit valueChanged(value());
}

bool BoolAspect::value() const
{
    return BaseAspect::value().toBool();
}

void BoolAspect::setValue(bool value)
{
    if (BaseAspect::setValueQuietly(value)) {
        if (d->m_checkBox)
            d->m_checkBox->setChecked(value);
        //qDebug() << "SetValue: Changing" << labelText() << " to " << value;
        emit changed();
        //QTV_CHECK(!labelText().isEmpty());
        emit valueChanged(value);
        //qDebug() << "SetValue: Changed" << labelText() << " to " << value;
        if (hasAction()) {
            //qDebug() << "SetValue: Triggering " << labelText() << "with" << value;
            emit action()->triggered(value);
        }
    }
}

void BoolAspect::setDefaultValue(bool val)
{
    BaseAspect::setDefaultValue(val);
}

void BoolAspect::setLabel(const QString &labelText, LabelPlacement labelPlacement)
{
    BaseAspect::setLabelText(labelText);
    d->m_labelPlacement = labelPlacement;
}

void BoolAspect::setLabelPlacement(BoolAspect::LabelPlacement labelPlacement)
{
    d->m_labelPlacement = labelPlacement;
}

void BoolAspect::setHandlesGroup(QGroupBox *box)
{
    registerSubWidget(box);
    d->m_groupBox = box;
}

// --------------------------------------------------------------------------------------
// A selection aspect represents a specific choice out of
// several.
// The selection aspect is displayed using a QComboBox or
// QRadioButtons in a QButtonGroup.
// ---
SelectionAspect::SelectionAspect()
    : d(new SelectionAspectPrivate)
{
    setSpan(2, 1);
}

SelectionAspect::~SelectionAspect() = default;

void SelectionAspect::addToLayout(LayoutBuilder& /*builder*/)
{
    QTV_CHECK(d->m_buttonGroup == nullptr);
    QTV_CHECK(!d->m_comboBox);
    QTV_ASSERT(d->m_buttons.isEmpty(), d->m_buttons.clear());

    switch (d->m_displayStyle) 
    {
        case DisplayStyle::RadioButtons:
            d->m_buttonGroup = new QButtonGroup();
            d->m_buttonGroup->setExclusive(true);
            for (int i = 0, n = d->m_options.size(); i < n; ++i) 
            {
                const Option &option = d->m_options.at(i);
                auto button = createSubWidget<QRadioButton>(option.displayName);
                button->setChecked(i == value());
                button->setEnabled(option.enabled);
                button->setToolTip(option.tooltip);
                Q_ASSERT(false);
    //            builder.addItems({{}, button});
                d->m_buttons.append(button);
                d->m_buttonGroup->addButton(button, i);
                if (isAutoApply()) {
                    connect(button, &QAbstractButton::clicked, this, [this, i] {
                        setValue(i);
                    });
                }
            }
            break;
        case DisplayStyle::ComboBox:
            setLabelText(displayName());
            d->m_comboBox = createSubWidget<QComboBox>();
            for (int i = 0, n = d->m_options.size(); i < n; ++i)
                d->m_comboBox->addItem(d->m_options.at(i).displayName);
            if (isAutoApply()) {
                connect(d->m_comboBox.data(), QOverload<int>::of(&QComboBox::activated),
                        this, &SelectionAspect::setValue);
            }
            connect(d->m_comboBox.data(), QOverload<int>::of(&QComboBox::currentIndexChanged),
                    this, &SelectionAspect::volatileValueChanged);
            d->m_comboBox->setCurrentIndex(value());
            Q_ASSERT(false);
    //        addLabeledItem(builder, d->m_comboBox);
            break;
    }
}

QVariant SelectionAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    switch (d->m_displayStyle) 
    {
        case DisplayStyle::RadioButtons:
            QTV_ASSERT(d->m_buttonGroup, return {});
            return d->m_buttonGroup->checkedId();
        case DisplayStyle::ComboBox:
            QTV_ASSERT(d->m_comboBox, return {});
            return d->m_comboBox->currentIndex();
    }
    return {};
}

void SelectionAspect::setVolatileValue(const QVariant &val)
{
    QTV_CHECK(!isAutoApply());
    switch (d->m_displayStyle) 
    {
    case DisplayStyle::RadioButtons: 
    {
        if (d->m_buttonGroup) 
        {
            QAbstractButton *button = d->m_buttonGroup->button(val.toInt());
            QTV_ASSERT(button, return);
            button->setChecked(true);
        }
        break;
    }
    case DisplayStyle::ComboBox:
        if (d->m_comboBox)
            d->m_comboBox->setCurrentIndex(val.toInt());
        break;
    }
}

void SelectionAspect::finish()
{
    delete d->m_buttonGroup;
    d->m_buttonGroup = nullptr;
    BaseAspect::finish();
    d->m_buttons.clear();
}

void SelectionAspect::setDisplayStyle(SelectionAspect::DisplayStyle style)
{
    d->m_displayStyle = style;
}

int SelectionAspect::value() const
{
    return BaseAspect::value().toInt();
}

void SelectionAspect::setValue(int value)
{
    if (BaseAspect::setValueQuietly(value)) {
        if (d->m_buttonGroup && 0 <= value && value < d->m_buttons.size())
            d->m_buttons.at(value)->setChecked(true);
        else if (d->m_comboBox)
            d->m_comboBox->setCurrentIndex(value);
        emit changed();
    }
}

void SelectionAspect::setStringValue(const QString &val)
{
    const int index = indexForDisplay(val);
    QTV_ASSERT(index >= 0, return);
    setValue(index);
}

void SelectionAspect::setDefaultValue(int val)
{
    BaseAspect::setDefaultValue(val);
}

// Note: This needs to be set after all options are added.
void SelectionAspect::setDefaultValue(const QString &val)
{
    BaseAspect::setDefaultValue(indexForDisplay(val));
}

QString SelectionAspect::stringValue() const
{
    return d->m_options.at(value()).displayName;
}

QVariant SelectionAspect::itemValue() const
{
    return d->m_options.at(value()).itemData;
}

void SelectionAspect::addOption(const QString &displayName, const QString &toolTip)
{
    d->m_options.append(Option(displayName, toolTip, {}));
}

void SelectionAspect::addOption(const Option &option)
{
    d->m_options.append(option);
}

int SelectionAspect::indexForDisplay(const QString &displayName) const
{
    for (int i = 0, n = d->m_options.size(); i < n; ++i) {
        if (d->m_options.at(i).displayName == displayName)
            return i;
    }
    return -1;
}

QString SelectionAspect::displayForIndex(int index) const
{
    QTV_ASSERT(index >= 0 && index < d->m_options.size(), return {});
    return d->m_options.at(index).displayName;
}

int SelectionAspect::indexForItemValue(const QVariant &value) const
{
    for (int i = 0, n = d->m_options.size(); i < n; ++i) {
        if (d->m_options.at(i).itemData == value)
            return i;
    }
    return -1;
}

QVariant SelectionAspect::itemValueForIndex(int index) const
{
    QTV_ASSERT(index >= 0 && index < d->m_options.size(), return {});
    return d->m_options.at(index).itemData;
}

// --------------------------------------------------------------------------------------
// A multi-selection aspect represents one or more choices out of
// several.
// The multi-selection aspect is displayed using a QListWidget with
// checkable items.
// ---
MultiSelectionAspect::MultiSelectionAspect()
    : d(new MultiSelectionAspectPrivate(this))
{
    setDefaultValue(QStringList());
    setSpan(2, 1);
}

MultiSelectionAspect::~MultiSelectionAspect() = default;

void MultiSelectionAspect::addToLayout(LayoutBuilder &builder)
{
    QTV_CHECK(d->m_listView == nullptr);
    if (d->m_allValues.isEmpty())
        return;

    switch (d->m_displayStyle) 
    {
        case DisplayStyle::ListView:
            d->m_listView = createSubWidget<QListWidget>();
            for (const QString &val : qAsConst(d->m_allValues)) {
                auto item = new QListWidgetItem(val, d->m_listView);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(value().contains(item->text()) ? Qt::Checked : Qt::Unchecked);
            }
            connect(d->m_listView, &QListWidget::itemChanged, this,
                [this](QListWidgetItem *item) {
                if (d->setValueSelectedHelper(item->text(), item->checkState() & Qt::Checked))
                    emit changed();
            });
            addLabeledItem(builder, d->m_listView);
    }
}

bool MultiSelectionAspectPrivate::setValueSelectedHelper(const QString &val, bool on)
{
    QStringList list = q->value();
    if (on && !list.contains(val)) 
    {
        list.append(val);
        q->setValue(list);
        return true;
    }
    if (!on && list.contains(val)) 
    {
        list.removeOne(val);
        q->setValue(list);
        return true;
    }
    return false;
}

QStringList MultiSelectionAspect::allValues() const
{
    return d->m_allValues;
}

void MultiSelectionAspect::setAllValues(const QStringList &val)
{
    d->m_allValues = val;
}

void MultiSelectionAspect::setDisplayStyle(MultiSelectionAspect::DisplayStyle style)
{
    d->m_displayStyle = style;
}

QStringList MultiSelectionAspect::value() const
{
    return BaseAspect::value().toStringList();
}

void MultiSelectionAspect::setValue(const QStringList &value)
{
    if (BaseAspect::setValueQuietly(value)) {
        if (d->m_listView) {
            const int n = d->m_listView->count();
            QTV_CHECK(n == d->m_allValues.size());
            for (int i = 0; i != n; ++i) {
                auto item = d->m_listView->item(i);
                item->setCheckState(value.contains(item->text()) ? Qt::Checked : Qt::Unchecked);
            }
        } else {
            emit changed();
        }
    }
}


// --------------------------------------------------------------------------------------
// An integer aspect is a integral property of some object, together with
// a description of its behavior for common operations like visualizing or
// persisting.
// The integer aspect is displayed using a QSpinBox.
// The visual representation often contains a label in front
// the display of the spin box.
// ---
IntegerAspect::IntegerAspect()
    : d(new IntegerAspectPrivate)
{
    setDefaultValue(qint64(0));
    setSpan(2, 1);

    addDataExtractor(this, &IntegerAspect::value, &Data::value);
}

IntegerAspect::~IntegerAspect() = default;

void IntegerAspect::addToLayout(LayoutBuilder &builder)
{
    QTV_CHECK(!d->m_spinBox);
    d->m_spinBox = createSubWidget<QSpinBox>();
    d->m_spinBox->setDisplayIntegerBase(d->m_displayIntegerBase);
    d->m_spinBox->setPrefix(d->m_prefix);
    d->m_spinBox->setSuffix(d->m_suffix);
    d->m_spinBox->setSingleStep(d->m_singleStep);
    d->m_spinBox->setSpecialValueText(d->m_specialValueText);
    if (d->m_maximumValue && d->m_maximumValue)
        d->m_spinBox->setRange(int(d->m_minimumValue.value() / d->m_displayScaleFactor),
                               int(d->m_maximumValue.value() / d->m_displayScaleFactor));
    d->m_spinBox->setValue(int(value() / d->m_displayScaleFactor)); // Must happen after setRange()
    addLabeledItem(builder, d->m_spinBox);

    if (isAutoApply()) {
        connect(d->m_spinBox.data(), QOverload<int>::of(&QSpinBox::valueChanged),
                this, [this] { setValue(d->m_spinBox->value()); });
    }
}

QVariant IntegerAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    QTV_ASSERT(d->m_spinBox, return {});
    return d->m_spinBox->value() * d->m_displayScaleFactor;
}

void IntegerAspect::setVolatileValue(const QVariant &val)
{
    QTV_CHECK(!isAutoApply());
    if (d->m_spinBox)
        d->m_spinBox->setValue(int(val.toLongLong() / d->m_displayScaleFactor));
}

qint64 IntegerAspect::value() const
{
    return BaseAspect::value().toLongLong();
}

void IntegerAspect::setValue(qint64 value)
{
    BaseAspect::setValue(value);
}

void IntegerAspect::setRange(qint64 min, qint64 max)
{
    d->m_minimumValue = min;
    d->m_maximumValue = max;
}

void IntegerAspect::setLabel(const QString &label)
{
    setLabelText(label);
}

void IntegerAspect::setPrefix(const QString &prefix)
{
    d->m_prefix = prefix;
}

void IntegerAspect::setSuffix(const QString &suffix)
{
    d->m_suffix = suffix;
}

void IntegerAspect::setDisplayIntegerBase(int base)
{
    d->m_displayIntegerBase = base;
}

void IntegerAspect::setDisplayScaleFactor(qint64 factor)
{
    d->m_displayScaleFactor = factor;
}

void IntegerAspect::setDefaultValue(qint64 defaultValue)
{
    BaseAspect::setDefaultValue(defaultValue);
}

void IntegerAspect::setSpecialValueText(const QString &specialText)
{
    d->m_specialValueText = specialText;
}

void IntegerAspect::setSingleStep(qint64 step)
{
    d->m_singleStep = step;
}


// --------------------------------------------------------------------------------------
// An double aspect is a numerical property of some object, together with
// a description of its behavior for common operations like visualizing or
// persisting.
// The double aspect is displayed using a QDoubleSpinBox.
// The visual representation often contains a label in front
// the display of the spin box.
// ----
DoubleAspect::DoubleAspect()
    : d(new DoubleAspectPrivate)
{
    setDefaultValue(double(0));
    setSpan(2, 1);
}

DoubleAspect::~DoubleAspect() = default;

void DoubleAspect::addToLayout(LayoutBuilder &builder)
{
    QTV_CHECK(!d->m_spinBox);
    d->m_spinBox = createSubWidget<QDoubleSpinBox>();
    d->m_spinBox->setPrefix(d->m_prefix);
    d->m_spinBox->setSuffix(d->m_suffix);
    d->m_spinBox->setSingleStep(d->m_singleStep);
    d->m_spinBox->setSpecialValueText(d->m_specialValueText);
    if (d->m_maximumValue && d->m_maximumValue)
        d->m_spinBox->setRange(d->m_minimumValue.value(), d->m_maximumValue.value());
    d->m_spinBox->setValue(value()); // Must happen after setRange()!
    addLabeledItem(builder, d->m_spinBox);

    if (isAutoApply()) {
        connect(d->m_spinBox.data(), QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, [this] { setValue(d->m_spinBox->value()); });
    }
}

QVariant DoubleAspect::volatileValue() const
{
    QTV_CHECK(!isAutoApply());
    QTV_ASSERT(d->m_spinBox, return {});
    return d->m_spinBox->value();
}

void DoubleAspect::setVolatileValue(const QVariant &val)
{
    QTV_CHECK(!isAutoApply());
    if (d->m_spinBox)
        d->m_spinBox->setValue(val.toDouble());
}

double DoubleAspect::value() const
{
    return BaseAspect::value().toDouble();
}

void DoubleAspect::setValue(double value)
{
    BaseAspect::setValue(value);
}

void DoubleAspect::setRange(double min, double max)
{
    d->m_minimumValue = min;
    d->m_maximumValue = max;
}

void DoubleAspect::setPrefix(const QString &prefix)
{
    d->m_prefix = prefix;
}

void DoubleAspect::setSuffix(const QString &suffix)
{
    d->m_suffix = suffix;
}

void DoubleAspect::setDefaultValue(double defaultValue)
{
    BaseAspect::setDefaultValue(defaultValue);
}

void DoubleAspect::setSpecialValueText(const QString &specialText)
{
    d->m_specialValueText = specialText;
}

void DoubleAspect::setSingleStep(double step)
{
    d->m_singleStep = step;
}

// --------------------------------------------------------------------------------------
// A tristate aspect is a property of some object that can have
// three values: enabled, disabled, and unspecified.
// Its visual representation is a QComboBox with three items.
// ---
TriStateAspect::TriStateAspect(const QString onString, const QString &offString,
                               const QString &defaultString)
{
    setDisplayStyle(DisplayStyle::ComboBox);
    setDefaultValue(TriState::Default);
    addOption(onString);
    addOption(offString);
    addOption(defaultString);
}

TriState TriStateAspect::value() const
{
    return TriState::fromVariant(BaseAspect::value());
}

void TriStateAspect::setValue(TriState value)
{
    SelectionAspect::setValue(value.toInt());
}

void TriStateAspect::setDefaultValue(TriState value)
{
    BaseAspect::setDefaultValue(value.toVariant());
}

const TriState TriState::Enabled{TriState::EnabledValue};
const TriState TriState::Disabled{TriState::DisabledValue};
const TriState TriState::Default{TriState::DefaultValue};

TriState TriState::fromVariant(const QVariant &variant)
{
    int v = variant.toInt();
    QTV_ASSERT(v == EnabledValue || v == DisabledValue || v == DefaultValue, v = DefaultValue);
    return TriState(Value(v));
}


/*!
    A string list aspect represents a property of some object
    that is a list of strings.
*/

StringListAspect::StringListAspect()
    : d(new StringListAspectPrivate)
{
    setDefaultValue(QStringList());
}

StringListAspect::~StringListAspect() = default;

void StringListAspect::addToLayout(LayoutBuilder &builder)
{
    Q_UNUSED(builder)
    // TODO - when needed.
}

QStringList StringListAspect::value() const
{
    return BaseAspect::value().toStringList();
}

void StringListAspect::setValue(const QStringList &value)
{
    BaseAspect::setValue(value);
}

void StringListAspect::appendValue(const QString &s, bool allowDuplicates)
{
    QStringList val = value();
    if (allowDuplicates || !val.contains(s))
        val.append(s);
    setValue(val);
}

void StringListAspect::removeValue(const QString &s)
{
    QStringList val = value();
    val.removeAll(s);
    setValue(val);
}

void StringListAspect::appendValues(const QStringList &values, bool allowDuplicates)
{
    QStringList val = value();
    for (const QString &s : values) {
        if (allowDuplicates || !val.contains(s))
            val.append(s);
    }
    setValue(val);
}

void StringListAspect::removeValues(const QStringList &values)
{
    QStringList val = value();
    for (const QString &s : values)
        val.removeAll(s);
    setValue(val);
}

// --------------------------------------------------------------------------------------
// A string list aspect represents a property of some object
// that is a list of strings.
// ---
IntegersAspect::IntegersAspect()
{
    setDefaultValue({});
}

IntegersAspect::~IntegersAspect() = default;

void IntegersAspect::addToLayout(LayoutBuilder &builder)
{
    Q_UNUSED(builder)
    // TODO - when needed.
}

void IntegersAspect::emitChangedValue()
{
    emit valueChanged(value());
}

QList<int> IntegersAspect::value() const
{
    return transform(BaseAspect::value().toList(),
                            [](QVariant v) { return v.toInt(); });
}

void IntegersAspect::setValue(const QList<int>& value)
{
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    BaseAspect::setValue(transform(value, &QVariant::fromValue<int>));
#else
    Q_UNUSED(value);
    Q_ASSERT(false);
#endif
}

void IntegersAspect::setDefaultValue(const QList<int>& value)
{
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    BaseAspect::setDefaultValue(transform(value, &QVariant::fromValue<int>));
#else
    Q_UNUSED(value);
    Q_ASSERT(false);
#endif
}


/*!

    \brief A text display is a phony aspect with the sole purpose of providing
    some text display using an Utils::InfoLabel in places where otherwise
    more expensive Utils::StringAspect items would be used.

    A text display does not have a real value.
*/

/*!
    Constructs a text display showing the message with an icon representing
    type type.
 */
TextDisplay::TextDisplay(const QString &message, InfoLabel::InfoType type)
    : d(new TextDisplayPrivate)
{
    d->m_message = message;
    d->m_type = type;
}

/*!
    \reimp
*/
TextDisplay::~TextDisplay() = default;

/*!
    \reimp
*/
void TextDisplay::addToLayout(LayoutBuilder& /*builder*/)
{
    if (!d->m_label) 
    {
        d->m_label = createSubWidget<InfoLabel>(d->m_message, d->m_type);
        d->m_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
        d->m_label->setElideMode(Qt::ElideNone);
        d->m_label->setWordWrap(true);
        // Do not use m_label->setVisible(isVisible()) unconditionally, it does not
        // have a QWidget parent yet when used in a LayoutBuilder.
        if (!isVisible())
            d->m_label->setVisible(false);
    }
    Q_ASSERT(false);
//    builder.addItem(d->m_label.data());
}

/*!
    Sets \a t as the information label type for the visual representation
    of this aspect.
 */
void TextDisplay::setIconType(InfoLabel::InfoType t)
{
    d->m_type = t;
    if (d->m_label)
        d->m_label->setType(t);
}

void TextDisplay::setText(const QString &message)
{
    d->m_message = message;
}

/*!
    The AspectContainer class wraps one or more aspects while providing
    the interface of a single aspect.
    Sub-aspects ownership can be declared using setOwnsSubAspects.
*/
class AspectContainerPrivate
{
public:
    QList<BaseAspect *> m_items; // Not owned
    bool m_autoApply = true;
    bool m_ownsSubAspects = false;
    QStringList m_settingsGroup;
};

AspectContainer::AspectContainer(QObject *parent)
    : QObject(parent), d(new AspectContainerPrivate)
{}

/*!
    \reimp
*/
AspectContainer::~AspectContainer()
{
    if (d->m_ownsSubAspects)
        qDeleteAll(d->m_items);
}

/*!
    \internal
*/
void AspectContainer::registerAspect(BaseAspect *aspect)
{
    aspect->setAutoApply(d->m_autoApply);
    d->m_items.append(aspect);
}

void AspectContainer::registerAspects(const AspectContainer &aspects)
{
    for (BaseAspect *aspect : qAsConst(aspects.d->m_items))
        registerAspect(aspect);
}

/*!
    Retrieves a BaseAspect with a given \a id, or nullptr if no such aspect is contained.

    \sa BaseAspect.
*/
BaseAspect *AspectContainer::aspect(Id id) const
{
    return findOrDefault(d->m_items, equal(&BaseAspect::id, id));
}

AspectContainer::const_iterator AspectContainer::begin() const
{
    return d->m_items.begin();
}

AspectContainer::const_iterator AspectContainer::end() const
{
    return d->m_items.end();
}

const QList<BaseAspect *> &AspectContainer::aspects() const
{
    return d->m_items;
}

void AspectContainer::fromMap(const QVariantMap &map)
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->fromMap(map);

    emit fromMapFinished();

}

void AspectContainer::toMap(QVariantMap &map) const
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->toMap(map);
}

void AspectContainer::readSettings(QSettings *settings)
{
    for (const QString &group : d->m_settingsGroup)
        settings->beginGroup(group);

    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->readSettings(settings);

    for (int i = 0; i != d->m_settingsGroup.size(); ++i)
        settings->endGroup();
}

void AspectContainer::writeSettings(QSettings *settings) const
{
    for (const QString &group : d->m_settingsGroup)
        settings->beginGroup(group);

    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->writeSettings(settings);

    for (int i = 0; i != d->m_settingsGroup.size(); ++i)
        settings->endGroup();
}

void AspectContainer::setSettingsGroup(const QString &groupKey)
{
    d->m_settingsGroup = QStringList{groupKey};
}

void AspectContainer::setSettingsGroups(const QString &groupKey, const QString &subGroupKey)
{
    d->m_settingsGroup = QStringList{groupKey, subGroupKey};
}

void AspectContainer::apply()
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->apply();

    emit applied();
}

void AspectContainer::cancel()
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->cancel();
}

void AspectContainer::finish()
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->finish();
}

void AspectContainer::reset()
{
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->setValueQuietly(aspect->defaultValue());
}

void AspectContainer::setAutoApply(bool on)
{
    d->m_autoApply = on;
    for (BaseAspect *aspect : qAsConst(d->m_items))
        aspect->setAutoApply(on);
}

void AspectContainer::setOwnsSubAspects(bool on)
{
    d->m_ownsSubAspects = on;
}

bool AspectContainer::isDirty() const
{
    for (BaseAspect *aspect : qAsConst(d->m_items)) {
        if (aspect->isDirty())
            return true;
    }
    return false;
}

bool AspectContainer::equals(const AspectContainer &other) const
{
    // FIXME: Expensive, but should not really be needed in a fully aspectified world.
    QVariantMap thisMap, thatMap;
    toMap(thisMap);
    other.toMap(thatMap);
    return thisMap == thatMap;
}

void AspectContainer::copyFrom(const AspectContainer &other)
{
    QVariantMap map;
    other.toMap(map);
    fromMap(map);
}

void AspectContainer::forEachAspect(const std::function<void(BaseAspect *)> &run) const
{
    for (BaseAspect *aspect : qAsConst(d->m_items)) {
        if (auto container = dynamic_cast<AspectContainer *>(aspect))
            container->forEachAspect(run);
        else
            run(aspect);
    }
}

BaseAspect::Data::Ptr BaseAspect::extractData() const
{
    QTV_ASSERT(d->m_dataCreator, return {});
    Data *data = d->m_dataCreator();
    data->m_classId = metaObject();
    data->m_id = id();
    data->m_cloner = d->m_dataCloner;
    for (const DataExtractor &extractor : d->m_dataExtractors)
        extractor(data);
    return Data::Ptr(data);
}

void BaseAspect::addDataExtractorHelper(const DataExtractor &extractor) const
{
    d->m_dataExtractors.append(extractor);
}

void BaseAspect::setDataCreatorHelper(const DataCreator &creator) const
{
    d->m_dataCreator = creator;
}

void BaseAspect::setDataClonerHelper(const DataCloner &cloner) const
{
    d->m_dataCloner = cloner;
}

const BaseAspect::Data *AspectContainerData::aspect(Id instanceId) const
{
    for (const BaseAspect::Data::Ptr &data : m_data) {
        if (data.get()->id() == instanceId)
            return data.get();
    }
    return nullptr;
}

const BaseAspect::Data *AspectContainerData::aspect(BaseAspect::Data::ClassId classId) const
{
    for (const BaseAspect::Data::Ptr &data : m_data) {
        if (data.get()->classId() == classId)
            return data.get();
    }
    return nullptr;
}

void AspectContainerData::append(const BaseAspect::Data::Ptr &data)
{
    m_data.append(data);
}

// BaseAspect::Data

BaseAspect::Data::~Data() = default;

void BaseAspect::Data::Ptr::operator=(const Ptr &other)
{
    if (this == &other)
        return;
    delete m_data;
    m_data = other.m_data->clone();
}

} // namespace QtVision
} // namespace VSN
