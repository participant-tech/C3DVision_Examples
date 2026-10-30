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

#include <qt_variantproperty.h>
#include <qt_propertymanager.h>
#include <qt_editorfactory.h>
#include <QtCore/QVariant>
#include <QtCore/QRegularExpression>
#include <QtGui/QIcon>
#include <QtCore/QDate>
#include <QtCore/QLocale>

// Q_GLOBAL_STATIC must be before #include <vsn_last.h> because the operator is overridden
typedef QMap<const QtVision::Property*, QtVision::Property*> PropertyMap;
Q_GLOBAL_STATIC(PropertyMap, propertyToWrappedProperty)

#include <vsn_last.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

namespace VSN {
namespace QtVision {

class EnumPropType
{
};


class FlagPropType
{
};


class GroupPropType
{
};

class SliderPropType
{
};


static Property* wrappedProperty(Property* property)
{
    return propertyToWrappedProperty()->value(property, 0);
}

/* QtVariantPropertyPrivate */
class QtVariantPropertyPrivate
{
public:
    QtVariantPropertyPrivate(VarPropManager* m) : manager(m) {}

    VarPropManager* manager;
};

/* VarProperty */
VarProperty::VarProperty(VarPropManager* manager, const Id& id)
    : Property(manager, id), d_ptr(new QtVariantPropertyPrivate(manager))
{
}

VarProperty::~VarProperty()
{
}

QVariant VarProperty::value() const
{
    return d_ptr->manager->value(this);
}

QVariant VarProperty::attributeValue(const QString& attribute) const
{
    return d_ptr->manager->attributeValue(this, attribute);
}

int VarProperty::valueType() const
{
    return d_ptr->manager->valueType(this);
}

int VarProperty::propertyType() const
{
    return d_ptr->manager->propertyType(this);
}

void VarProperty::setValue(const QVariant &value)
{
    d_ptr->manager->setValue(this, value);
}

void VarProperty::setAttribute(const QString& attribute, const QVariant& value)
{
    d_ptr->manager->setAttribute(this, attribute, value);
}

/* VarPropManagerPrivate */
class VarPropManagerPrivate
{
    VarPropManager *q_ptr;
    Q_DECLARE_PUBLIC(VarPropManager)
public:
    VarPropManagerPrivate();

    bool m_creatingProperty;
    bool m_creatingSubProperties;
    bool m_destroyingSubProperties;
    int m_propertyType;

    void slotValueChanged(Property *property, int val);
    void slotRangeChanged(Property *property, int min, int max);
    void slotSingleStepChanged(Property *property, int step);
    void slotValueChanged(Property *property, double val);
    void slotRangeChanged(Property *property, double min, double max);
    void slotSingleStepChanged(Property *property, double step);
    void slotDecimalsChanged(Property *property, int prec);
    void slotValueChanged(Property *property, bool val);
    void slotValueChanged(Property *property, const QString &val);
    void slotRegExpChanged(Property *property, const QRegularExpression&regExp);
    void slotValueChanged(Property *property, const QDate &val);
    void slotRangeChanged(Property *property, const QDate &min, const QDate &max);
    void slotValueChanged(Property *property, const QTime &val);
    void slotValueChanged(Property *property, const QDateTime &val);
    void slotValueChanged(Property *property, const QKeySequence &val);
    void slotValueChanged(Property *property, const QChar &val);
    void slotValueChanged(Property *property, const QLocale &val);
    void slotValueChanged(Property *property, const QPoint &val);
    void slotValueChanged(Property *property, const QPointF &val);
    void slotValueChanged(Property *property, const QSize &val);
    void slotRangeChanged(Property *property, const QSize &min, const QSize &max);
    void slotValueChanged(Property *property, const QSizeF &val);
    void slotRangeChanged(Property *property, const QSizeF &min, const QSizeF &max);
    void slotValueChanged(Property *property, const QRect &val);
    void slotConstraintChanged(Property *property, const QRect &val);
    void slotValueChanged(Property *property, const QRectF &val);
    void slotConstraintChanged(Property *property, const QRectF &val);
    void slotValueChanged(Property *property, const QColor &val);
    void slotEnumChanged(Property *property, int val);
    void slotEnumNamesChanged(Property *property, const QStringList &enumNames);
    void slotEnumIconsChanged(Property *property, const QMap<int, QIcon> &enumIcons);
    void slotValueChanged(Property *property, const QSizePolicy &val);
    void slotValueChanged(Property *property, const QFont &val);
    void slotValueChanged(Property *property, const QCursor &val);
    void slotFlagChanged(Property *property, int val);
    void slotFlagNamesChanged(Property *property, const QStringList &flagNames);
    void slotPropertyInserted(Property *property, Property *parent, Property *after);
    void slotPropertyRemoved(Property *property, Property *parent);

    void valueChanged(Property *property, const QVariant &val);

    int internalPropertyToType(Property *property) const;
    VarProperty *createSubProperty(VarProperty *parent, VarProperty *after,
            Property *internal);
    void removeSubProperty(VarProperty *property);

    QMap<int, AbsPropertyManager *> m_typeToPropertyManager;
    QMap<int, QMap<QString, int> > m_typeToAttributeToAttributeType;
    QMap<const Property *, QPair<VarProperty *, int> > m_propertyToType;
    QMap<int, int> m_typeToValueType;
    QMap<Property *, VarProperty *> m_internalToProperty;

    const QString m_constraintAttribute;
    const QString m_singleStepAttribute;
    const QString m_decimalsAttribute;
    const QString m_enumIconsAttribute;
    const QString m_enumNamesAttribute;
    const QString m_flagNamesAttribute;
    const QString m_maximumAttribute;
    const QString m_minimumAttribute;
    const QString m_regExpAttribute;
};

VarPropManagerPrivate::VarPropManagerPrivate() :
    m_constraintAttribute(QLatin1String("constraint")),
    m_singleStepAttribute(QLatin1String("singleStep")),
    m_decimalsAttribute(QLatin1String("decimals")),
    m_enumIconsAttribute(QLatin1String("enumIcons")),
    m_enumNamesAttribute(QLatin1String("enumNames")),
    m_flagNamesAttribute(QLatin1String("flagNames")),
    m_maximumAttribute(QLatin1String("maximum")),
    m_minimumAttribute(QLatin1String("minimum")),
    m_regExpAttribute(QLatin1String("regExp"))
{
}

int VarPropManagerPrivate::internalPropertyToType(Property* property) const
{
    int type = 0;
    AbsPropertyManager *internPropertyManager = property->propertyManager();
    if (qobject_cast<IntPropManager*>(internPropertyManager))
        type = QVariant::Int;
    else if (qobject_cast<EnumPropManager*>(internPropertyManager))
        type = VarPropManager::enumTypeId();
    else if (qobject_cast<BoolPropManager*>(internPropertyManager))
        type = QVariant::Bool;
    else if (qobject_cast<DoublePropManager*>(internPropertyManager))
        type = QVariant::Double;
//    else if (qobject_cast<SliderPropManager*>(internPropertyManager))
//        type = VarPropManager::sliderTypeId();
    return type;
}

VarProperty* VarPropManagerPrivate::createSubProperty(VarProperty* parent,
    VarProperty* after, Property* internal)
{
    int type = internalPropertyToType(internal);
    if (!type)
        return 0;

    bool wasCreatingSubProperties = m_creatingSubProperties;
    m_creatingSubProperties = true;

    VarProperty* varChild = q_ptr->addProperty(type, internal->propertyName());

    m_creatingSubProperties = wasCreatingSubProperties;

    varChild->setPropertyName(internal->propertyName());
    varChild->setPropertyId(internal->propertyId());
    varChild->setToolTip(internal->toolTip());
    varChild->setStatusTip(internal->statusTip());
    varChild->setWhatsThis(internal->whatsThis());

    parent->insertSubProperty(varChild, after);

    m_internalToProperty[internal] = varChild;
    propertyToWrappedProperty()->insert(varChild, internal);
    return varChild;
}

void VarPropManagerPrivate::removeSubProperty(VarProperty *property)
{
    Property *internChild = wrappedProperty(property);
    bool wasDestroyingSubProperties = m_destroyingSubProperties;
    m_destroyingSubProperties = true;
    delete property;
    m_destroyingSubProperties = wasDestroyingSubProperties;
    m_internalToProperty.remove(internChild);
    propertyToWrappedProperty()->remove(property);
}

void VarPropManagerPrivate::slotPropertyInserted(Property *property,
            Property *parent, Property *after)
{
    if (m_creatingProperty)
        return;

    VarProperty *varParent = m_internalToProperty.value(parent, 0);
    if (!varParent)
        return;

    VarProperty *varAfter = 0;
    if (after) {
        varAfter = m_internalToProperty.value(after, 0);
        if (!varAfter)
            return;
    }

    createSubProperty(varParent, varAfter, property);
}

void VarPropManagerPrivate::slotPropertyRemoved(Property *property, Property *parent)
{
    Q_UNUSED(parent);

    VarProperty *varProperty = m_internalToProperty.value(property, 0);
    if (!varProperty)
        return;

    removeSubProperty(varProperty);
}

void VarPropManagerPrivate::valueChanged(Property* property, const QVariant &val)
{
    VarProperty *varProp = m_internalToProperty.value(property, 0);
    if (!varProp)
        return;
    emit q_ptr->valueChanged(varProp, val);
    emit q_ptr->propertyChanged(varProp);
}

void VarPropManagerPrivate::slotValueChanged(Property* property, int val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRangeChanged(Property* property, int min, int max)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) 
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void VarPropManagerPrivate::slotSingleStepChanged(Property* property, int step)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, double val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRangeChanged(Property* property, double min, double max)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void VarPropManagerPrivate::slotSingleStepChanged(Property* property, double step)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
}

void VarPropManagerPrivate::slotDecimalsChanged(Property* property, int prec)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_decimalsAttribute, QVariant(prec));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, bool val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QString &val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRegExpChanged(Property* property, const QRegularExpression& regExp)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_regExpAttribute, QVariant(regExp));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QDate &val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRangeChanged(Property* property, const QDate& min, const QDate& max)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) 
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QTime& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QDateTime& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QKeySequence& val)
{
    QVariant v;
    v.setValue(val);
    valueChanged(property, v);
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QChar& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QLocale& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QPoint& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QPointF& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QSize& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRangeChanged(Property* property, const QSize& min, const QSize& max)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) 
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QSizeF& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotRangeChanged(Property* property, const QSizeF& min, const QSizeF& max)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) 
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QRect& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotConstraintChanged(Property *property, const QRect &constraint)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
}

void VarPropManagerPrivate::slotValueChanged(Property *property, const QRectF &val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotConstraintChanged(Property* property, const QRectF& constraint)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QColor& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotEnumNamesChanged(Property* property, const QStringList& enumNames)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_enumNamesAttribute, QVariant(enumNames));
}

void VarPropManagerPrivate::slotEnumIconsChanged(Property* property, const QMap<int, QIcon>& enumIcons)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0)) 
    {
        QVariant v;
        v.setValue(enumIcons);
        emit q_ptr->attributeChanged(varProp, m_enumIconsAttribute, v);
    }
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QSizePolicy& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QFont& val)
{
    valueChanged(property, QVariant(val));
}

void VarPropManagerPrivate::slotValueChanged(Property* property, const QCursor& val)
{
#ifndef QT_NO_CURSOR
    valueChanged(property, QVariant(val));
#endif
}

void VarPropManagerPrivate::slotFlagNamesChanged(Property* property, const QStringList& flagNames)
{
    if (VarProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_flagNamesAttribute, QVariant(flagNames));
}

/* VarPropManager */
VarPropManager::VarPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new VarPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_creatingProperty = false;
    d_ptr->m_creatingSubProperties = false;
    d_ptr->m_destroyingSubProperties = false;
    d_ptr->m_propertyType = 0;

    // IntPropertyManager
    int sliderId = sliderTypeId();
    IntPropManager* intSliderPropertyManager = new IntPropManager(this);
    d_ptr->m_typeToPropertyManager[sliderId] = intSliderPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[sliderId][d_ptr->m_minimumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[sliderId][d_ptr->m_maximumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[sliderId][d_ptr->m_singleStepAttribute] = QVariant::Int;
    d_ptr->m_typeToValueType[sliderId] = QVariant::Int;
    connect(intSliderPropertyManager, SIGNAL(valueChanged(Property*, int)),
        this, SLOT(slotValueChanged(Property*, int)));
    connect(intSliderPropertyManager, SIGNAL(rangeChanged(Property*, int, int)),
        this, SLOT(slotRangeChanged(Property*, int, int)));
    connect(intSliderPropertyManager, SIGNAL(singleStepChanged(Property*, int)),
        this, SLOT(slotSingleStepChanged(Property*, int)));
/*
    int flagId = flagTypeId();
    FlagPropManager* flagPropertyManager = new FlagPropManager(this);
    d_ptr->m_typeToPropertyManager[flagId] = flagPropertyManager;
    d_ptr->m_typeToValueType[flagId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[flagId][d_ptr->m_flagNamesAttribute] =
        QVariant::StringList;
    connect(flagPropertyManager, SIGNAL(valueChanged(Property*, int)),
        this, SLOT(slotValueChanged(Property*, int)));
    connect(flagPropertyManager, SIGNAL(flagNamesChanged(Property*, QStringList)),
        this, SLOT(slotFlagNamesChanged(Property*, QStringList)));
    connect(flagPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(Property*, bool)),
        this, SLOT(slotValueChanged(Property*, bool)));
    connect(flagPropertyManager, SIGNAL(propertyInserted(Property*, Property*, Property*)),
        this, SLOT(slotPropertyInserted(Property*, Property*, Property*)));
    connect(flagPropertyManager, SIGNAL(propertyRemoved(Property*, Property*)),
        this, SLOT(slotPropertyRemoved(Property*, Property*)));
*/

    // IntPropertyManager
    IntPropManager* intPropertyManager = new IntPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Int] = intPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_minimumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_maximumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_singleStepAttribute] = QVariant::Int;
    d_ptr->m_typeToValueType[QVariant::Int] = QVariant::Int;
    connect(intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(intPropertyManager, SIGNAL(rangeChanged(Property*,int,int)),
                this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(intPropertyManager, SIGNAL(singleStepChanged(Property*,int)),
                this, SLOT(slotSingleStepChanged(Property*,int)));
    // DoublePropertyManager
    DoublePropManager* doublePropertyManager = new DoublePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Double] = doublePropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_minimumAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_maximumAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_singleStepAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    d_ptr->m_typeToValueType[QVariant::Double] = QVariant::Double;
    connect(doublePropertyManager, SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotValueChanged(Property*,double)));
    connect(doublePropertyManager, SIGNAL(rangeChanged(Property*,double,double)),
                this, SLOT(slotRangeChanged(Property*,double,double)));
    connect(doublePropertyManager, SIGNAL(singleStepChanged(Property*,double)),
                this, SLOT(slotSingleStepChanged(Property*,double)));
    connect(doublePropertyManager, SIGNAL(decimalsChanged(Property*,int)),
                this, SLOT(slotDecimalsChanged(Property*,int)));
    // BoolPropertyManager
    BoolPropManager* boolPropertyManager = new BoolPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Bool] = boolPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Bool] = QVariant::Bool;
    connect(boolPropertyManager, SIGNAL(valueChanged(Property*,bool)),
                this, SLOT(slotValueChanged(Property*,bool)));
    // StringPropertyManager
    StringPropManager *stringPropertyManager = new StringPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::String] = stringPropertyManager;
    d_ptr->m_typeToValueType[QVariant::String] = QVariant::String;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_regExpAttribute] =
            QVariant::RegularExpression;
    connect(stringPropertyManager, SIGNAL(valueChanged(Property*,QString)),
                this, SLOT(slotValueChanged(Property*,QString)));
    connect(stringPropertyManager, SIGNAL(regExpChanged(Property*, QRegularExpression)),
                this, SLOT(slotRegExpChanged(Property*, QRegularExpression)));
    // DatePropertyManager
    DatePropManager *datePropertyManager = new DatePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Date] = datePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Date] = QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_minimumAttribute] =
            QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_maximumAttribute] =
            QVariant::Date;
    connect(datePropertyManager, SIGNAL(valueChanged(Property*,QDate)),
                this, SLOT(slotValueChanged(Property*,QDate)));
    connect(datePropertyManager, SIGNAL(rangeChanged(Property*,QDate,QDate)),
                this, SLOT(slotRangeChanged(Property*,QDate,QDate)));
    // TimePropertyManager
    TimePropManager *timePropertyManager = new TimePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Time] = timePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Time] = QVariant::Time;
    connect(timePropertyManager, SIGNAL(valueChanged(Property*,QTime)),
                this, SLOT(slotValueChanged(Property*,QTime)));
    // DateTimePropertyManager
    DateTimePropManager *dateTimePropertyManager = new DateTimePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::DateTime] = dateTimePropertyManager;
    d_ptr->m_typeToValueType[QVariant::DateTime] = QVariant::DateTime;
    connect(dateTimePropertyManager, SIGNAL(valueChanged(Property*,QDateTime)),
                this, SLOT(slotValueChanged(Property*,QDateTime)));
    // KeySequencePropertyManager
    KeySequencePropManager *keySequencePropertyManager = new KeySequencePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::KeySequence] = keySequencePropertyManager;
    d_ptr->m_typeToValueType[QVariant::KeySequence] = QVariant::KeySequence;
    connect(keySequencePropertyManager, SIGNAL(valueChanged(Property*,QKeySequence)),
                this, SLOT(slotValueChanged(Property*,QKeySequence)));
    // CharPropertyManager
    CharPropManager *charPropertyManager = new CharPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Char] = charPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Char] = QVariant::Char;
    connect(charPropertyManager, SIGNAL(valueChanged(Property*,QChar)),
                this, SLOT(slotValueChanged(Property*,QChar)));
    // LocalePropertyManager
    LocalePropManager *localePropertyManager = new LocalePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Locale] = localePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Locale] = QVariant::Locale;
    connect(localePropertyManager, SIGNAL(valueChanged(Property*,QLocale)),
                this, SLOT(slotValueChanged(Property*,QLocale)));
    connect(localePropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(localePropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(localePropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // PointPropertyManager
    PointPropManager *pointPropertyManager = new PointPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Point] = pointPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Point] = QVariant::Point;
    connect(pointPropertyManager, SIGNAL(valueChanged(Property*,QPoint)),
                this, SLOT(slotValueChanged(Property*,QPoint)));
    connect(pointPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(pointPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(pointPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // PointFPropertyManager
    PointFPropManager *pointFPropertyManager = new PointFPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::PointF] = pointFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::PointF] = QVariant::PointF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::PointF][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    connect(pointFPropertyManager, SIGNAL(valueChanged(Property*,QPointF)),
                this, SLOT(slotValueChanged(Property*,QPointF)));
    connect(pointFPropertyManager, SIGNAL(decimalsChanged(Property*,int)),
                this, SLOT(slotDecimalsChanged(Property*,int)));
    connect(pointFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotValueChanged(Property*,double)));
    connect(pointFPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(pointFPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // SizePropertyManager
    SizePropManager *sizePropertyManager = new SizePropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Size] = sizePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Size] = QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_minimumAttribute] =
            QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_maximumAttribute] =
            QVariant::Size;
    connect(sizePropertyManager, SIGNAL(valueChanged(Property*,QSize)),
                this, SLOT(slotValueChanged(Property*,QSize)));
    connect(sizePropertyManager, SIGNAL(rangeChanged(Property*,QSize,QSize)),
                this, SLOT(slotRangeChanged(Property*,QSize,QSize)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(Property*,int,int)),
                this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(sizePropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(sizePropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // SizeFPropertyManager
    SizeFPropManager *sizeFPropertyManager = new SizeFPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizeF] = sizeFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizeF] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_minimumAttribute] =
            QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_maximumAttribute] =
            QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    connect(sizeFPropertyManager, SIGNAL(valueChanged(Property*,QSizeF)),
                this, SLOT(slotValueChanged(Property*,QSizeF)));
    connect(sizeFPropertyManager, SIGNAL(rangeChanged(Property*,QSizeF,QSizeF)),
                this, SLOT(slotRangeChanged(Property*,QSizeF,QSizeF)));
    connect(sizeFPropertyManager, SIGNAL(decimalsChanged(Property*,int)),
                this, SLOT(slotDecimalsChanged(Property*,int)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotValueChanged(Property*,double)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(Property*,double,double)),
                this, SLOT(slotRangeChanged(Property*,double,double)));
    connect(sizeFPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(sizeFPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // RectPropertyManager
    RectPropManager *rectPropertyManager = new RectPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Rect] = rectPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Rect] = QVariant::Rect;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Rect][d_ptr->m_constraintAttribute] =
            QVariant::Rect;
    connect(rectPropertyManager, SIGNAL(valueChanged(Property*,QRect)),
                this, SLOT(slotValueChanged(Property*,QRect)));
    connect(rectPropertyManager, SIGNAL(constraintChanged(Property*,QRect)),
                this, SLOT(slotConstraintChanged(Property*,QRect)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(Property*,int,int)),
                this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(rectPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(rectPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // RectFPropertyManager
    RectFPropManager *rectFPropertyManager = new RectFPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::RectF] = rectFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::RectF] = QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_constraintAttribute] =
            QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    connect(rectFPropertyManager, SIGNAL(valueChanged(Property*,QRectF)),
                this, SLOT(slotValueChanged(Property*,QRectF)));
    connect(rectFPropertyManager, SIGNAL(constraintChanged(Property*,QRectF)),
                this, SLOT(slotConstraintChanged(Property*,QRectF)));
    connect(rectFPropertyManager, SIGNAL(decimalsChanged(Property*,int)),
                this, SLOT(slotDecimalsChanged(Property*,int)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotValueChanged(Property*,double)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(Property*,double,double)),
                this, SLOT(slotRangeChanged(Property*,double,double)));
    connect(rectFPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(rectFPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // ColorPropertyManager
    ColorPropManager *colorPropertyManager = new ColorPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Color] = colorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Color] = QVariant::Color;
    connect(colorPropertyManager, SIGNAL(valueChanged(Property*,QColor)),
                this, SLOT(slotValueChanged(Property*,QColor)));
    connect(colorPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(colorPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(colorPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // EnumPropertyManager
    int enumId = enumTypeId();
    EnumPropManager* enumPropertyManager = new EnumPropManager(this);
    d_ptr->m_typeToPropertyManager[enumId] = enumPropertyManager;
    d_ptr->m_typeToValueType[enumId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumNamesAttribute] =
            QVariant::StringList;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumIconsAttribute] =
            iconMapTypeId();
    connect(enumPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(enumPropertyManager, SIGNAL(enumNamesChanged(Property*,QStringList)),
                this, SLOT(slotEnumNamesChanged(Property*,QStringList)));
    connect(enumPropertyManager, SIGNAL(enumIconsChanged(Property*,QMap<int,QIcon>)),
                this, SLOT(slotEnumIconsChanged(Property*,QMap<int,QIcon>)));
    // SizePolicyPropertyManager
    SizePolicyPropManager *sizePolicyPropertyManager = new SizePolicyPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizePolicy] = sizePolicyPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizePolicy] = QVariant::SizePolicy;
    connect(sizePolicyPropertyManager, SIGNAL(valueChanged(Property*,QSizePolicy)),
                this, SLOT(slotValueChanged(Property*,QSizePolicy)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(Property*,int,int)),
                this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(),
                SIGNAL(enumNamesChanged(Property*,QStringList)),
                this, SLOT(slotEnumNamesChanged(Property*,QStringList)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // FontPropertyManager
    FontPropManager *fontPropertyManager = new FontPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Font] = fontPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Font] = QVariant::Font;
    connect(fontPropertyManager, SIGNAL(valueChanged(Property*,QFont)),
                this, SLOT(slotValueChanged(Property*,QFont)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(Property*,int,int)),
                this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(fontPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(fontPropertyManager->subEnumPropertyManager(),
                SIGNAL(enumNamesChanged(Property*,QStringList)),
                this, SLOT(slotEnumNamesChanged(Property*,QStringList)));
    connect(fontPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(Property*,bool)),
                this, SLOT(slotValueChanged(Property*,bool)));
    connect(fontPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(fontPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // CursorPropertyManager
    CursorPropManager* cursorPropertyManager = new CursorPropManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Cursor] = cursorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Cursor] = QVariant::Cursor;
    connect(cursorPropertyManager, SIGNAL(valueChanged(Property*,QCursor)),
                this, SLOT(slotValueChanged(Property*,QCursor)));
    // FlagPropertyManager
    int flagId = flagTypeId();
    FlagPropManager* flagPropertyManager = new FlagPropManager(this);
    d_ptr->m_typeToPropertyManager[flagId] = flagPropertyManager;
    d_ptr->m_typeToValueType[flagId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[flagId][d_ptr->m_flagNamesAttribute] =
            QVariant::StringList;
    connect(flagPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotValueChanged(Property*,int)));
    connect(flagPropertyManager, SIGNAL(flagNamesChanged(Property*,QStringList)),
                this, SLOT(slotFlagNamesChanged(Property*,QStringList)));
    connect(flagPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(Property*,bool)),
                this, SLOT(slotValueChanged(Property*,bool)));
    connect(flagPropertyManager, SIGNAL(propertyInserted(Property*,Property*,Property*)),
                this, SLOT(slotPropertyInserted(Property*,Property*,Property*)));
    connect(flagPropertyManager, SIGNAL(propertyRemoved(Property*,Property*)),
                this, SLOT(slotPropertyRemoved(Property*,Property*)));
    // FlagPropertyManager
    int groupId = groupTypeId();
    GroupPropManager* groupPropertyManager = new GroupPropManager(this);
    d_ptr->m_typeToPropertyManager[groupId] = groupPropertyManager;
    d_ptr->m_typeToValueType[groupId] = QVariant::Invalid;
}

VarPropManager::~VarPropManager()
{
    clear();
}

VarProperty* VarPropManager::variantProperty(const Property* property) const
{
    const QMap<const Property*, QPair<VarProperty*, int> >::const_iterator it = d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
        return 0;
    return it.value().first;
}

bool VarPropManager::isPropertyTypeSupported(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
        return true;
    return false;
}

VarProperty* VarPropManager::addProperty(int propertyType, const QString& name, const Id& id)
{
    if (!isPropertyTypeSupported(propertyType))
        return 0;

    bool wasCreating = d_ptr->m_creatingProperty;
    d_ptr->m_creatingProperty = true;
    d_ptr->m_propertyType = propertyType;
    Property* property = AbsPropertyManager::addProperty(name, id);
    d_ptr->m_creatingProperty = wasCreating;
    d_ptr->m_propertyType = 0;

    if (!property)
        return nullptr;

    return variantProperty(property);
}

QVariant VarPropManager::value(const Property* property) const
{
    Property *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return QVariant();

    AbsPropertyManager *manager = internProp->propertyManager();
    if (IntPropManager *intManager = qobject_cast<IntPropManager *>(manager)) {
        return intManager->value(internProp);
    } else if (DoublePropManager *doubleManager = qobject_cast<DoublePropManager *>(manager)) {
        return doubleManager->value(internProp);
    } else if (BoolPropManager *boolManager = qobject_cast<BoolPropManager *>(manager)) {
        return boolManager->value(internProp);
    } else if (StringPropManager *stringManager = qobject_cast<StringPropManager *>(manager)) {
        return stringManager->value(internProp);
    } else if (DatePropManager *dateManager = qobject_cast<DatePropManager *>(manager)) {
        return dateManager->value(internProp);
    } else if (TimePropManager *timeManager = qobject_cast<TimePropManager *>(manager)) {
        return timeManager->value(internProp);
    } else if (DateTimePropManager *dateTimeManager = qobject_cast<DateTimePropManager *>(manager)) {
        return dateTimeManager->value(internProp);
    } else if (KeySequencePropManager *keySequenceManager = qobject_cast<KeySequencePropManager *>(manager)) {
        return QVariant::fromValue(keySequenceManager->value(internProp));
    } else if (CharPropManager *charManager = qobject_cast<CharPropManager *>(manager)) {
        return charManager->value(internProp);
    } else if (LocalePropManager *localeManager = qobject_cast<LocalePropManager *>(manager)) {
        return localeManager->value(internProp);
    } else if (PointPropManager *pointManager = qobject_cast<PointPropManager *>(manager)) {
        return pointManager->value(internProp);
    } else if (PointFPropManager *pointFManager = qobject_cast<PointFPropManager *>(manager)) {
        return pointFManager->value(internProp);
    } else if (SizePropManager *sizeManager = qobject_cast<SizePropManager *>(manager)) {
        return sizeManager->value(internProp);
    } else if (SizeFPropManager *sizeFManager = qobject_cast<SizeFPropManager *>(manager)) {
        return sizeFManager->value(internProp);
    } else if (RectPropManager *rectManager = qobject_cast<RectPropManager *>(manager)) {
        return rectManager->value(internProp);
    } else if (RectFPropManager *rectFManager = qobject_cast<RectFPropManager *>(manager)) {
        return rectFManager->value(internProp);
    } else if (ColorPropManager *colorManager = qobject_cast<ColorPropManager *>(manager)) {
        return colorManager->value(internProp);
    } else if (EnumPropManager *enumManager = qobject_cast<EnumPropManager *>(manager)) {
        return enumManager->value(internProp);
    } else if (SizePolicyPropManager *sizePolicyManager =
               qobject_cast<SizePolicyPropManager *>(manager)) {
        return sizePolicyManager->value(internProp);
    } else if (FontPropManager *fontManager = qobject_cast<FontPropManager *>(manager)) {
        return fontManager->value(internProp);
#ifndef QT_NO_CURSOR
    } else if (CursorPropManager *cursorManager = qobject_cast<CursorPropManager *>(manager)) {
        return cursorManager->value(internProp);
#endif
    } else if (FlagPropManager *flagManager = qobject_cast<FlagPropManager *>(manager)) {
        return flagManager->value(internProp);
    }
    return QVariant();
}

int VarPropManager::valueType(const Property *property) const
{
    int propType = propertyType(property);
    return valueType(propType);
}

int VarPropManager::valueType(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
        return d_ptr->m_typeToValueType[propertyType];
    return 0;
}

int VarPropManager::propertyType(const Property *property) const
{
    const QMap<const Property *, QPair<VarProperty *, int> >::const_iterator it = d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
        return 0;
    return it.value().second;
}

QVariant VarPropManager::attributeValue(const Property *property, const QString &attribute) const
{
    int propType = propertyType(property);
    if (!propType)
        return QVariant();

    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return QVariant();

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
        return QVariant();

    Property *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return QVariant();

    AbsPropertyManager *manager = internProp->propertyManager();
    if (IntPropManager *intManager = qobject_cast<IntPropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return intManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return intManager->minimum(internProp);
        if (attribute == d_ptr->m_singleStepAttribute)
            return intManager->singleStep(internProp);
        return QVariant();
    } else if (DoublePropManager *doubleManager = qobject_cast<DoublePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return doubleManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return doubleManager->minimum(internProp);
        if (attribute == d_ptr->m_singleStepAttribute)
            return doubleManager->singleStep(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return doubleManager->decimals(internProp);
        return QVariant();
    } else if (StringPropManager *stringManager = qobject_cast<StringPropManager *>(manager)) {
        if (attribute == d_ptr->m_regExpAttribute)
            return stringManager->regExp(internProp);
        return QVariant();
    } else if (DatePropManager *dateManager = qobject_cast<DatePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return dateManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return dateManager->minimum(internProp);
        return QVariant();
    } else if (PointFPropManager *pointFManager = qobject_cast<PointFPropManager *>(manager)) {
        if (attribute == d_ptr->m_decimalsAttribute)
            return pointFManager->decimals(internProp);
        return QVariant();
    } else if (SizePropManager *sizeManager = qobject_cast<SizePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return sizeManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return sizeManager->minimum(internProp);
        return QVariant();
    } else if (SizeFPropManager *sizeFManager = qobject_cast<SizeFPropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return sizeFManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return sizeFManager->minimum(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return sizeFManager->decimals(internProp);
        return QVariant();
    } else if (RectPropManager *rectManager = qobject_cast<RectPropManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            return rectManager->constraint(internProp);
        return QVariant();
    } else if (RectFPropManager *rectFManager = qobject_cast<RectFPropManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            return rectFManager->constraint(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return rectFManager->decimals(internProp);
        return QVariant();
    } else if (EnumPropManager *enumManager = qobject_cast<EnumPropManager *>(manager)) {
        if (attribute == d_ptr->m_enumNamesAttribute)
            return enumManager->enumNames(internProp);
        if (attribute == d_ptr->m_enumIconsAttribute) {
            QVariant v;
            v.setValue(enumManager->enumIcons(internProp));
            return v;
        }
        return QVariant();
    } else if (FlagPropManager *flagManager = qobject_cast<FlagPropManager *>(manager)) {
        if (attribute == d_ptr->m_flagNamesAttribute)
            return flagManager->flagNames(internProp);
        return QVariant();
    }
    return QVariant();
}

QStringList VarPropManager::attributes(int propertyType) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return QStringList();
    return it.value().keys();
}

int VarPropManager::attributeType(int propertyType, const QString &attribute) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return 0;

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
        return 0;
    return itAttr.value();
}

void VarPropManager::setValue(Property *property, const QVariant &val)
{
    int propType = val.userType();
    if (!propType)
        return;

    int valType = valueType(property);

    if (propType != valType && !val.canConvert(static_cast<QVariant::Type>(valType)))
        return;

    Property *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return;


    AbsPropertyManager* manager = internProp->propertyManager();
    if (IntPropManager* intManager = qobject_cast<IntPropManager *>(manager)) {
        intManager->setValue(internProp, qvariant_cast<int>(val));
        return;
    } else if (DoublePropManager *doubleManager = qobject_cast<DoublePropManager *>(manager)) {
        doubleManager->setValue(internProp, qvariant_cast<double>(val));
        return;
    } else if (BoolPropManager *boolManager = qobject_cast<BoolPropManager *>(manager)) {
        boolManager->setValue(internProp, qvariant_cast<bool>(val));
        return;
    } else if (StringPropManager *stringManager = qobject_cast<StringPropManager *>(manager)) {
        stringManager->setValue(internProp, qvariant_cast<QString>(val));
        return;
    } else if (DatePropManager *dateManager = qobject_cast<DatePropManager *>(manager)) {
        dateManager->setValue(internProp, qvariant_cast<QDate>(val));
        return;
    } else if (TimePropManager *timeManager = qobject_cast<TimePropManager *>(manager)) {
        timeManager->setValue(internProp, qvariant_cast<QTime>(val));
        return;
    } else if (DateTimePropManager *dateTimeManager = qobject_cast<DateTimePropManager *>(manager)) {
        dateTimeManager->setValue(internProp, qvariant_cast<QDateTime>(val));
        return;
    } else if (KeySequencePropManager *keySequenceManager = qobject_cast<KeySequencePropManager *>(manager)) {
        keySequenceManager->setValue(internProp, qvariant_cast<QKeySequence>(val));
        return;
    } else if (CharPropManager *charManager = qobject_cast<CharPropManager *>(manager)) {
        charManager->setValue(internProp, qvariant_cast<QChar>(val));
        return;
    } else if (LocalePropManager *localeManager = qobject_cast<LocalePropManager *>(manager)) {
        localeManager->setValue(internProp, qvariant_cast<QLocale>(val));
        return;
    } else if (PointPropManager *pointManager = qobject_cast<PointPropManager *>(manager)) {
        pointManager->setValue(internProp, qvariant_cast<QPoint>(val));
        return;
    } else if (PointFPropManager *pointFManager = qobject_cast<PointFPropManager *>(manager)) {
        pointFManager->setValue(internProp, qvariant_cast<QPointF>(val));
        return;
    } else if (SizePropManager *sizeManager = qobject_cast<SizePropManager *>(manager)) {
        sizeManager->setValue(internProp, qvariant_cast<QSize>(val));
        return;
    } else if (SizeFPropManager *sizeFManager = qobject_cast<SizeFPropManager *>(manager)) {
        sizeFManager->setValue(internProp, qvariant_cast<QSizeF>(val));
        return;
    } else if (RectPropManager *rectManager = qobject_cast<RectPropManager *>(manager)) {
        rectManager->setValue(internProp, qvariant_cast<QRect>(val));
        return;
    } else if (RectFPropManager *rectFManager = qobject_cast<RectFPropManager *>(manager)) {
        rectFManager->setValue(internProp, qvariant_cast<QRectF>(val));
        return;
    } else if (ColorPropManager *colorManager = qobject_cast<ColorPropManager *>(manager)) {
        colorManager->setValue(internProp, qvariant_cast<QColor>(val));
        return;
    } else if (EnumPropManager *enumManager = qobject_cast<EnumPropManager *>(manager)) {
        enumManager->setValue(internProp, qvariant_cast<int>(val));
        return;
    } else if (SizePolicyPropManager *sizePolicyManager =
               qobject_cast<SizePolicyPropManager *>(manager)) {
        sizePolicyManager->setValue(internProp, qvariant_cast<QSizePolicy>(val));
        return;
    } else if (FontPropManager *fontManager = qobject_cast<FontPropManager *>(manager)) {
        fontManager->setValue(internProp, qvariant_cast<QFont>(val));
        return;
#ifndef QT_NO_CURSOR
    } else if (CursorPropManager *cursorManager = qobject_cast<CursorPropManager *>(manager)) {
        cursorManager->setValue(internProp, qvariant_cast<QCursor>(val));
        return;
#endif
    } else if (FlagPropManager *flagManager = qobject_cast<FlagPropManager *>(manager)) {
        flagManager->setValue(internProp, qvariant_cast<int>(val));
        return;
    }
}

void VarPropManager::setAttribute(Property* property, const QString& attribute, const QVariant &value)
{
    QVariant oldAttr = attributeValue(property, attribute);
    if (!oldAttr.isValid())
        return;

    int attrType = value.userType();
    if (!attrType)
        return;

    if (attrType != attributeType(propertyType(property), attribute) &&
                !value.canConvert((QVariant::Type)attrType))
        return;

    Property* internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == nullptr)
        return;

    AbsPropertyManager *manager = internProp->propertyManager();
    if (IntPropManager* intManager = qobject_cast<IntPropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            intManager->setMaximum(internProp, qvariant_cast<int>(value));
        else if (attribute == d_ptr->m_minimumAttribute)
            intManager->setMinimum(internProp, qvariant_cast<int>(value));
        else if (attribute == d_ptr->m_singleStepAttribute)
            intManager->setSingleStep(internProp, qvariant_cast<int>(value));
        return;
    } else if (DoublePropManager* doubleManager = qobject_cast<DoublePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            doubleManager->setMaximum(internProp, qvariant_cast<double>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            doubleManager->setMinimum(internProp, qvariant_cast<double>(value));
        if (attribute == d_ptr->m_singleStepAttribute)
            doubleManager->setSingleStep(internProp, qvariant_cast<double>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            doubleManager->setDecimals(internProp, qvariant_cast<int>(value));
        return;
    } else if (StringPropManager* stringManager = qobject_cast<StringPropManager *>(manager)) {
        if (attribute == d_ptr->m_regExpAttribute)
            stringManager->setRegExp(internProp, qvariant_cast<QRegularExpression>(value));
        return;
    } else if (DatePropManager* dateManager = qobject_cast<DatePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            dateManager->setMaximum(internProp, qvariant_cast<QDate>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            dateManager->setMinimum(internProp, qvariant_cast<QDate>(value));
        return;
    } else if (PointFPropManager* pointFManager = qobject_cast<PointFPropManager *>(manager)) {
        if (attribute == d_ptr->m_decimalsAttribute)
            pointFManager->setDecimals(internProp, qvariant_cast<int>(value));
        return;
    } else if (SizePropManager* sizeManager = qobject_cast<SizePropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            sizeManager->setMaximum(internProp, qvariant_cast<QSize>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            sizeManager->setMinimum(internProp, qvariant_cast<QSize>(value));
        return;
    } else if (SizeFPropManager* sizeFManager = qobject_cast<SizeFPropManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            sizeFManager->setMaximum(internProp, qvariant_cast<QSizeF>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            sizeFManager->setMinimum(internProp, qvariant_cast<QSizeF>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            sizeFManager->setDecimals(internProp, qvariant_cast<int>(value));
        return;
    } else if (RectPropManager* rectManager = qobject_cast<RectPropManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            rectManager->setConstraint(internProp, qvariant_cast<QRect>(value));
        return;
    } else if (RectFPropManager* rectFManager = qobject_cast<RectFPropManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            rectFManager->setConstraint(internProp, qvariant_cast<QRectF>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            rectFManager->setDecimals(internProp, qvariant_cast<int>(value));
        return;
    } else if (EnumPropManager* enumManager = qobject_cast<EnumPropManager *>(manager)) {
        if (attribute == d_ptr->m_enumNamesAttribute)
            enumManager->setEnumNames(internProp, qvariant_cast<QStringList>(value));
        if (attribute == d_ptr->m_enumIconsAttribute)
            enumManager->setEnumIcons(internProp, qvariant_cast<IconMap>(value));
        return;
    } else if (FlagPropManager* flagManager = qobject_cast<FlagPropManager *>(manager)) {
        if (attribute == d_ptr->m_flagNamesAttribute)
            flagManager->setFlagNames(internProp, qvariant_cast<QStringList>(value));
        return;
    }
}

bool VarPropManager::hasValue(const Property *property) const
{
    if (propertyType(property) == groupTypeId())
        return false;
    return true;
}

QString VarPropManager::valueText(const Property *property) const
{
    const Property* internProp = propertyToWrappedProperty()->value(property, 0);
    return internProp ? internProp->valueText() : QString();
}

QIcon VarPropManager::valueIcon(const Property* property) const
{
    const Property* internProp = propertyToWrappedProperty()->value(property, 0);
    return internProp ? internProp->valueIcon() : QIcon();
}

void VarPropManager::initializeProperty(Property* property)
{
    VarProperty* varProp = variantProperty(property);
    if (!varProp)
        return;

    QMap<int, AbsPropertyManager*>::ConstIterator it =
            d_ptr->m_typeToPropertyManager.find(d_ptr->m_propertyType);
    if (it != d_ptr->m_typeToPropertyManager.constEnd()) 
    {
        Property* internProp = nullptr;
        if (!d_ptr->m_creatingSubProperties) 
        {
            AbsPropertyManager* manager = it.value();
            internProp = manager->addProperty();
            d_ptr->m_internalToProperty[internProp] = varProp;
        }
        propertyToWrappedProperty()->insert(varProp, internProp);
        if (internProp) 
        {
            const auto children = internProp->subProperties();
            VarProperty* lastProperty = nullptr;
            for (Property* child : children) 
            {
                VarProperty* prop = d_ptr->createSubProperty(varProp, lastProperty, child);
                lastProperty = prop ? prop : lastProperty;
            }
        }
    }
}

void VarPropManager::uninitializeProperty(Property* property)
{
    const QMap<const Property*, QPair<VarProperty*, int> >::iterator type_it = d_ptr->m_propertyToType.find(property);
    if (type_it == d_ptr->m_propertyToType.end())
        return;

    PropertyMap::iterator it = propertyToWrappedProperty()->find(property);
    if (it != propertyToWrappedProperty()->end()) 
    {
        Property* internProp = it.value();
        if (internProp) 
        {
            d_ptr->m_internalToProperty.remove(internProp);
            if (!d_ptr->m_destroyingSubProperties) 
                delete internProp;
        }
        propertyToWrappedProperty()->erase(it);
    }
    d_ptr->m_propertyToType.erase(type_it);
}

Property* VarPropManager::createProperty(const Id& id)
{
    if (!d_ptr->m_creatingProperty)
        return 0;

    VarProperty* property = new VarProperty(this, id);
    d_ptr->m_propertyToType.insert(property, qMakePair(property, d_ptr->m_propertyType));

    return property;
}

void VarPropManager::slotValueChanged(Property* property, int val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRangeChanged(Property* property, int min, int max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void VarPropManager::slotSingleStepChanged(Property* property, int step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void VarPropManager::slotValueChanged(Property* property, double val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRangeChanged(Property* property, double min, double max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void VarPropManager::slotSingleStepChanged(Property* property, double step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void VarPropManager::slotDecimalsChanged(Property* property, int val)
{
    d_ptr->slotDecimalsChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, bool val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QString& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRegExpChanged(Property* property, const QRegularExpression& regExp)
{
    d_ptr->slotRegExpChanged(property, regExp);
}

void VarPropManager::slotValueChanged(Property* property, const QDate& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRangeChanged(Property* property, const QDate& min, const QDate& max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void VarPropManager::slotValueChanged(Property* property, const QTime& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QDateTime& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QKeySequence& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QChar& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QLocale& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QPoint& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QPointF& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QSize& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRangeChanged(Property* property, const QSize& min, const QSize& max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void VarPropManager::slotValueChanged(Property* property, const QSizeF& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotRangeChanged(Property* property, const QSizeF& min, const QSizeF& max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void VarPropManager::slotValueChanged(Property* property, const QRect& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotConstraintChanged(Property* property, const QRect& val)
{
    d_ptr->slotConstraintChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QRectF& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotConstraintChanged(Property* property, const QRectF& val)
{
    d_ptr->slotConstraintChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QColor& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotEnumNamesChanged(Property* property, const QStringList& enumNames)
{
    d_ptr->slotEnumNamesChanged(property, enumNames);
}

void VarPropManager::slotEnumIconsChanged(Property* property, const QMap<int, QIcon>& enumIcons)
{
    d_ptr->slotEnumIconsChanged(property, enumIcons);
}

void VarPropManager::slotValueChanged(Property* property, const QSizePolicy& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QFont& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotValueChanged(Property* property, const QCursor& val)
{
    d_ptr->slotValueChanged(property, val);
}

void VarPropManager::slotFlagNamesChanged(Property* property, const QStringList& flagNames)
{
    d_ptr->slotFlagNamesChanged(property, flagNames);
}

void VarPropManager::slotPropertyInserted(Property* property, Property* parent, Property* after)
{
    d_ptr->slotPropertyInserted(property, parent, after);
}

void VarPropManager::slotPropertyRemoved(Property* property, Property* parent)
{
    d_ptr->slotPropertyRemoved(property, parent);
}

/* VariantEditorFactoryPrivate*/
class VariantEditorFactoryPrivate
{
    VariantEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(VariantEditorFactory)
public:
    SliderFactory*            m_sliderFactory;
    SpinBoxFactory*           m_spinBoxFactory;
    DoubleSpinBoxFactory*     m_doubleSpinBoxFactory;
    CheckBoxFactory*          m_checkBoxFactory;
    LineEditFactory*          m_lineEditFactory;
    DateEditFactory*          m_dateEditFactory;
    TimeEditFactory*          m_timeEditFactory;
    DateTimeEditFactory*      m_dateTimeEditFactory;
    KeySequenceEditorFactory* m_keySequenceEditorFactory;
    CharEditorFactory*        m_charEditorFactory;
    EnumEditorFactory*        m_comboBoxFactory;
    CursorEditorFactory*      m_cursorEditorFactory;
    ColorEditorFactory*       m_colorEditorFactory;
    FontEditorFactory*        m_fontEditorFactory;

    QMap<AbsEditorFactoryBase*, int> m_factoryToType;
    QMap<int, AbsEditorFactoryBase*> m_typeToFactory;
};

/* VariantEditorFactory */
VariantEditorFactory::VariantEditorFactory(QObject* parent)
    : AbsEditorFactory<VarPropManager>(parent), d_ptr(new VariantEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;

    d_ptr->m_sliderFactory = new SliderFactory(this);
    const int sliderId = VarPropManager::sliderTypeId();
    d_ptr->m_factoryToType[d_ptr->m_sliderFactory] = sliderId;
    d_ptr->m_typeToFactory[sliderId] = d_ptr->m_sliderFactory;

    d_ptr->m_spinBoxFactory = new SpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_spinBoxFactory] = QVariant::Int;
    d_ptr->m_typeToFactory[QVariant::Int] = d_ptr->m_spinBoxFactory;

    d_ptr->m_doubleSpinBoxFactory = new DoubleSpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_doubleSpinBoxFactory] = QVariant::Double;
    d_ptr->m_typeToFactory[QVariant::Double] = d_ptr->m_doubleSpinBoxFactory;

    d_ptr->m_checkBoxFactory = new CheckBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_checkBoxFactory] = QVariant::Bool;
    d_ptr->m_typeToFactory[QVariant::Bool] = d_ptr->m_checkBoxFactory;

    d_ptr->m_lineEditFactory = new LineEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_lineEditFactory] = QVariant::String;
    d_ptr->m_typeToFactory[QVariant::String] = d_ptr->m_lineEditFactory;

    d_ptr->m_dateEditFactory = new DateEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateEditFactory] = QVariant::Date;
    d_ptr->m_typeToFactory[QVariant::Date] = d_ptr->m_dateEditFactory;

    d_ptr->m_timeEditFactory = new TimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_timeEditFactory] = QVariant::Time;
    d_ptr->m_typeToFactory[QVariant::Time] = d_ptr->m_timeEditFactory;

    d_ptr->m_dateTimeEditFactory = new DateTimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateTimeEditFactory] = QVariant::DateTime;
    d_ptr->m_typeToFactory[QVariant::DateTime] = d_ptr->m_dateTimeEditFactory;

    d_ptr->m_keySequenceEditorFactory = new KeySequenceEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_keySequenceEditorFactory] = QVariant::KeySequence;
    d_ptr->m_typeToFactory[QVariant::KeySequence] = d_ptr->m_keySequenceEditorFactory;

    d_ptr->m_charEditorFactory = new CharEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_charEditorFactory] = QVariant::Char;
    d_ptr->m_typeToFactory[QVariant::Char] = d_ptr->m_charEditorFactory;

    d_ptr->m_cursorEditorFactory = new CursorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_cursorEditorFactory] = QVariant::Cursor;
    d_ptr->m_typeToFactory[QVariant::Cursor] = d_ptr->m_cursorEditorFactory;

    d_ptr->m_colorEditorFactory = new ColorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_colorEditorFactory] = QVariant::Color;
    d_ptr->m_typeToFactory[QVariant::Color] = d_ptr->m_colorEditorFactory;

    d_ptr->m_fontEditorFactory = new FontEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_fontEditorFactory] = QVariant::Font;
    d_ptr->m_typeToFactory[QVariant::Font] = d_ptr->m_fontEditorFactory;

    d_ptr->m_comboBoxFactory = new EnumEditorFactory(this);
    const int enumId = VarPropManager::enumTypeId();
    d_ptr->m_factoryToType[d_ptr->m_comboBoxFactory] = enumId;
    d_ptr->m_typeToFactory[enumId] = d_ptr->m_comboBoxFactory;
}

VariantEditorFactory::~VariantEditorFactory()
{
}

void VariantEditorFactory::connectPropertyManager(VarPropManager *manager)
{
    const auto intPropertyManagers = manager->findChildren<IntPropManager *>();
    for (IntPropManager* managerI : intPropertyManagers)
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerI);

    const auto intSliderPropertyManagers = manager->findChildren<IntPropManager*>();
    for (IntPropManager* managerIS : intSliderPropertyManagers)
        d_ptr->m_sliderFactory->appendPropertyManager(managerIS);

    const auto doublePropertyManagers = manager->findChildren<DoublePropManager *>();
    for (DoublePropManager* managerD : doublePropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->appendPropertyManager(managerD);

    const auto boolPropertyManagers = manager->findChildren<BoolPropManager *>();
    for (BoolPropManager* managerB : boolPropertyManagers)
        d_ptr->m_checkBoxFactory->appendPropertyManager(managerB);

    const auto stringPropertyManagers = manager->findChildren<StringPropManager *>();
    for (StringPropManager* managerS : stringPropertyManagers)
        d_ptr->m_lineEditFactory->appendPropertyManager(managerS);

    const auto datePropertyManagers = manager->findChildren<DatePropManager *>();
    for (DatePropManager* managerDate : datePropertyManagers)
        d_ptr->m_dateEditFactory->appendPropertyManager(managerDate);

    const auto timePropertyManagers = manager->findChildren<TimePropManager *>();
    for (TimePropManager* managerTime : timePropertyManagers)
        d_ptr->m_timeEditFactory->appendPropertyManager(managerTime);

    const auto dateTimePropertyManagers = manager->findChildren<DateTimePropManager *>();
    for (DateTimePropManager* managerDateT : dateTimePropertyManagers)
        d_ptr->m_dateTimeEditFactory->appendPropertyManager(managerDateT);

    const auto keySequencePropertyManagers = manager->findChildren<KeySequencePropManager *>();
    for (KeySequencePropManager* managerKey : keySequencePropertyManagers)
        d_ptr->m_keySequenceEditorFactory->appendPropertyManager(managerKey);

    const auto charPropertyManagers = manager->findChildren<CharPropManager *>();
    for (CharPropManager* managerChar : charPropertyManagers)
        d_ptr->m_charEditorFactory->appendPropertyManager(managerChar);

    const auto localePropertyManagers = manager->findChildren<LocalePropManager *>();
    for (LocalePropManager* managerLocale : localePropertyManagers)
        d_ptr->m_comboBoxFactory->appendPropertyManager(managerLocale->subEnumPropertyManager());

    const auto pointPropertyManagers = manager->findChildren<PointPropManager *>();
    for (PointPropManager* managerPoint : pointPropertyManagers)
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerPoint->subIntPropertyManager());

    const auto pointFPropertyManagers = manager->findChildren<PointFPropManager *>();
    for (PointFPropManager* managerPointF : pointFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->appendPropertyManager(managerPointF->subDoublePropertyManager());

    const auto sizePropertyManagers = manager->findChildren<SizePropManager *>();
    for (SizePropManager* managerSize : sizePropertyManagers)
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerSize->subIntPropertyManager());

    const auto sizeFPropertyManagers = manager->findChildren<SizeFPropManager *>();
    for (SizeFPropManager* managerSizeF : sizeFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->appendPropertyManager(managerSizeF->subDoublePropertyManager());

    const auto rectPropertyManagers = manager->findChildren<RectPropManager *>();
    for (RectPropManager* managerRect : rectPropertyManagers)
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerRect->subIntPropertyManager());

    const auto rectFPropertyManagers = manager->findChildren<RectFPropManager *>();
    for (RectFPropManager* managerRectF : rectFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->appendPropertyManager(managerRectF->subDoublePropertyManager());

    const auto colorPropertyManagers = manager->findChildren<ColorPropManager *>();
    for (ColorPropManager* managerColor : colorPropertyManagers) 
    {
        d_ptr->m_colorEditorFactory->appendPropertyManager(managerColor);
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerColor->subIntPropertyManager());
    }

    const auto enumPropertyManagers = manager->findChildren<EnumPropManager *>();
    for (EnumPropManager* managerEnum : enumPropertyManagers)
        d_ptr->m_comboBoxFactory->appendPropertyManager(managerEnum);

    const auto sizePolicyPropertyManagers = manager->findChildren<SizePolicyPropManager *>();
    for (SizePolicyPropManager* managerSizeP : sizePolicyPropertyManagers) 
    {
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerSizeP->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->appendPropertyManager(managerSizeP->subEnumPropertyManager());
    }

    const auto fontPropertyManagers = manager->findChildren<FontPropManager *>();
    for (FontPropManager* managerFont : fontPropertyManagers) 
    {
        d_ptr->m_fontEditorFactory->appendPropertyManager(managerFont);
        d_ptr->m_spinBoxFactory->appendPropertyManager(managerFont->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->appendPropertyManager(managerFont->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->appendPropertyManager(managerFont->subBoolPropertyManager());
    }

    const auto cursorPropertyManagers = manager->findChildren<CursorPropManager *>();
    for (CursorPropManager* managerCursor : cursorPropertyManagers)
        d_ptr->m_cursorEditorFactory->appendPropertyManager(managerCursor);

    const auto flagPropertyManagers = manager->findChildren<FlagPropManager *>();
    for (FlagPropManager* managerFlag : flagPropertyManagers)
        d_ptr->m_checkBoxFactory->appendPropertyManager(managerFlag->subBoolPropertyManager());
}

QWidget* VariantEditorFactory::createEditor(VarPropManager* manager, Property* property, QWidget* parent)
{
    const int propType = manager->propertyType(property);
    AbsEditorFactoryBase* factory = d_ptr->m_typeToFactory.value(propType, 0);
    if (!factory)
        return nullptr;
    return factory->createEditor(wrappedProperty(property), parent);
}

void VariantEditorFactory::disconnectPropertyManager(VarPropManager *manager)
{
    const auto intPropertyManagers = manager->findChildren<IntPropManager *>();
    for (IntPropManager* managerI : intPropertyManagers)
        d_ptr->m_spinBoxFactory->removePropertyManager(managerI);

    const auto intSliderPropertyManagers = manager->findChildren<IntPropManager*>();
    for (IntPropManager* managerIS : intSliderPropertyManagers)
        d_ptr->m_sliderFactory->removePropertyManager(managerIS);

    const auto doublePropertyManagers = manager->findChildren<DoublePropManager *>();
    for (DoublePropManager* managerD : doublePropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(managerD);

    const auto boolPropertyManagers = manager->findChildren<BoolPropManager *>();
    for (BoolPropManager* managerB : boolPropertyManagers)
        d_ptr->m_checkBoxFactory->removePropertyManager(managerB);

    const auto stringPropertyManagers = manager->findChildren<StringPropManager *>();
    for (StringPropManager* managerS : stringPropertyManagers)
        d_ptr->m_lineEditFactory->removePropertyManager(managerS);

    const auto datePropertyManagers = manager->findChildren<DatePropManager *>();
    for (DatePropManager* managerDate : datePropertyManagers)
        d_ptr->m_dateEditFactory->removePropertyManager(managerDate);

    const auto timePropertyManagers = manager->findChildren<TimePropManager *>();
    for (TimePropManager* managerTime : timePropertyManagers)
        d_ptr->m_timeEditFactory->removePropertyManager(managerTime);

    const auto dateTimePropertyManagers = manager->findChildren<DateTimePropManager *>();
    for (DateTimePropManager* managerDate : dateTimePropertyManagers)
        d_ptr->m_dateTimeEditFactory->removePropertyManager(managerDate);

    const auto keySequencePropertyManagers = manager->findChildren<KeySequencePropManager *>();
    for (KeySequencePropManager* managerKey : keySequencePropertyManagers)
        d_ptr->m_keySequenceEditorFactory->removePropertyManager(managerKey);

    const auto charPropertyManagers = manager->findChildren<CharPropManager *>();
    for (CharPropManager* managerChar : charPropertyManagers)
        d_ptr->m_charEditorFactory->removePropertyManager(managerChar);

    const auto localePropertyManagers = manager->findChildren<LocalePropManager *>();
    for (LocalePropManager* managerLocale : localePropertyManagers)
        d_ptr->m_comboBoxFactory->removePropertyManager(managerLocale->subEnumPropertyManager());

    const auto pointPropertyManagers = manager->findChildren<PointPropManager *>();
    for (PointPropManager* managerPoint : pointPropertyManagers)
        d_ptr->m_spinBoxFactory->removePropertyManager(managerPoint->subIntPropertyManager());

    const auto pointFPropertyManagers = manager->findChildren<PointFPropManager *>();
    for (PointFPropManager* managerPointF : pointFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(managerPointF->subDoublePropertyManager());

    const auto sizePropertyManagers = manager->findChildren<SizePropManager *>();
    for (SizePropManager* managerSize : sizePropertyManagers)
        d_ptr->m_spinBoxFactory->removePropertyManager(managerSize->subIntPropertyManager());

    const auto sizeFPropertyManagers = manager->findChildren<SizeFPropManager *>();
    for (SizeFPropManager* managerSizeF : sizeFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(managerSizeF->subDoublePropertyManager());

    const auto rectPropertyManagers = manager->findChildren<RectPropManager *>();
    for (RectPropManager* managerRect : rectPropertyManagers)
        d_ptr->m_spinBoxFactory->removePropertyManager(managerRect->subIntPropertyManager());

    const auto rectFPropertyManagers = manager->findChildren<RectFPropManager *>();
    for (RectFPropManager* managerRectF : rectFPropertyManagers)
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(managerRectF->subDoublePropertyManager());

    const auto colorPropertyManagers = manager->findChildren<ColorPropManager *>();
    for (ColorPropManager* managerColor : colorPropertyManagers) 
    {
        d_ptr->m_colorEditorFactory->removePropertyManager(managerColor);
        d_ptr->m_spinBoxFactory->removePropertyManager(managerColor->subIntPropertyManager());
    }

    const auto enumPropertyManagers = manager->findChildren<EnumPropManager *>();
    for (EnumPropManager* managerEnum : enumPropertyManagers)
        d_ptr->m_comboBoxFactory->removePropertyManager(managerEnum);

    const auto sizePolicyPropertyManagers = manager->findChildren<SizePolicyPropManager *>();
    for (SizePolicyPropManager* managerSizeP : sizePolicyPropertyManagers) 
    {
        d_ptr->m_spinBoxFactory->removePropertyManager(managerSizeP->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(managerSizeP->subEnumPropertyManager());
    }

    const auto fontPropertyManagers = manager->findChildren<FontPropManager *>();
    for (FontPropManager* managerFont : fontPropertyManagers) 
    {
        d_ptr->m_fontEditorFactory->removePropertyManager(managerFont);
        d_ptr->m_spinBoxFactory->removePropertyManager(managerFont->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(managerFont->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->removePropertyManager(managerFont->subBoolPropertyManager());
    }

    const auto cursorPropertyManagers = manager->findChildren<CursorPropManager *>();
    for (CursorPropManager* managerCursor : cursorPropertyManagers)
        d_ptr->m_cursorEditorFactory->removePropertyManager(managerCursor);

    const auto flagPropertyManagers = manager->findChildren<FlagPropManager *>();
    for (FlagPropManager* managerFlag : flagPropertyManagers)
        d_ptr->m_checkBoxFactory->removePropertyManager(managerFlag->subBoolPropertyManager());
}

} // namespace QtVision
} // namespace VSN

QT_BEGIN_NAMESPACE
Q_DECLARE_METATYPE(VSN::QtVision::EnumPropType)
Q_DECLARE_METATYPE(VSN::QtVision::FlagPropType)
Q_DECLARE_METATYPE(VSN::QtVision::GroupPropType)
Q_DECLARE_METATYPE(VSN::QtVision::SliderPropType)
QT_END_NAMESPACE

namespace VSN {
namespace QtVision {

int VarPropManager::enumTypeId()
{
    return qMetaTypeId<EnumPropType>();
}

int VarPropManager::flagTypeId()
{
    return qMetaTypeId<FlagPropType>();
}

int VarPropManager::groupTypeId()
{
    return qMetaTypeId<GroupPropType>();
}

int VarPropManager::iconMapTypeId()
{
    return qMetaTypeId<IconMap>();
}

int VarPropManager::sliderTypeId()
{
    return qMetaTypeId<SliderPropType>();
}

} // namespace QtVision
} // namespace VSN
