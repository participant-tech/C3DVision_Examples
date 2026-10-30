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

#include <qt_propertymanager.h>
#include <qt_propertymanagerprivate.h>
#include <qt_propertybrowserutilsprivate.h>
#include <QtCore/QDateTime>
//#include <QtCore/QLocale>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtGui/QIcon>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QStyle>
#include <QtWidgets/QApplication>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>

#include <limits>
#include <limits.h>
#include <float.h>

// Q_GLOBAL_STATIC must be before #include <vsn_last.h> because the operator is overridden
Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)
Q_GLOBAL_STATIC(QtVision::CursorDatabase, cursorDatabase)
Q_GLOBAL_STATIC(QtVision::MetaEnumProvider, metaEnumProvider)

#include <vsn_last.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

//namespace VSN {
//namespace QtVision {

template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
        data->maxVal = data->minVal;

    if (data->val < data->minVal)
        data->val = data->minVal;
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
        data->minVal = data->maxVal;

    if (data->val > data->maxVal)
        data->val = data->maxVal;
}

template <class PrivateData, class Value>
static void setSizeMinimumData(PrivateData *data, const Value &newMinVal)
{
    data->minVal = newMinVal;
    if (data->maxVal.width() < data->minVal.width())
        data->maxVal.setWidth(data->minVal.width());
    if (data->maxVal.height() < data->minVal.height())
        data->maxVal.setHeight(data->minVal.height());

    if (data->val.width() < data->minVal.width())
        data->val.setWidth(data->minVal.width());
    if (data->val.height() < data->minVal.height())
        data->val.setHeight(data->minVal.height());
}

template <class PrivateData, class Value>
static void setSizeMaximumData(PrivateData *data, const Value &newMaxVal)
{
    data->maxVal = newMaxVal;
    if (data->minVal.width() > data->maxVal.width())
        data->minVal.setWidth(data->maxVal.width());
    if (data->minVal.height() > data->maxVal.height())
        data->minVal.setHeight(data->maxVal.height());

    if (data->val.width() > data->maxVal.width())
        data->val.setWidth(data->maxVal.width());
    if (data->val.height() > data->maxVal.height())
        data->val.setHeight(data->maxVal.height());
}

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
    SizeValue croppedVal = val;
    if (minVal.width() > val.width())
        croppedVal.setWidth(minVal.width());
    else if (maxVal.width() < val.width())
        croppedVal.setWidth(maxVal.width());

    if (minVal.height() > val.height())
        croppedVal.setHeight(minVal.height());
    else if (maxVal.height() < val.height())
        croppedVal.setHeight(maxVal.height());

    return croppedVal;
}

QSize qBound(QSize minVal, QSize val, QSize maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

namespace VSN {
namespace QtVision {

namespace {

namespace {
template <class Value>
void orderBorders(Value &minVal, Value &maxVal)
{
    if (minVal > maxVal)
        qSwap(minVal, maxVal);
}

template <class Value>
static void orderSizeBorders(Value &minVal, Value &maxVal)
{
    Value fromSize = minVal;
    Value toSize = maxVal;
    if (fromSize.width() > toSize.width()) {
        fromSize.setWidth(maxVal.width());
        toSize.setWidth(minVal.width());
    }
    if (fromSize.height() > toSize.height()) {
        fromSize.setHeight(maxVal.height());
        toSize.setHeight(minVal.height());
    }
    minVal = fromSize;
    maxVal = toSize;
}

void orderBorders(QSize &minVal, QSize &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

void orderBorders(QSizeF &minVal, QSizeF &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

}
}

template <class Value, class PrivateData>
static Value getData(const QMap<const Property *, PrivateData> &propertyMap,
            Value PrivateData::*data,
            const Property *property, const Value &defaultValue = Value())
{
    const auto it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
        return defaultValue;
    return it.value().*data;
}

template <class Value, class PrivateData>
static Value getValue(const QMap<const Property *, PrivateData> &propertyMap,
            const Property *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMinimum(const QMap<const Property *, PrivateData> &propertyMap,
            const Property *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::minVal, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMaximum(const QMap<const Property *, PrivateData> &propertyMap,
            const Property *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::maxVal, property, defaultValue);
}

template <class ValueChangeParameter, class Value, class PropertyManager>
static void setSimpleValue(QMap<const Property *, Value> &propertyMap,
            PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            Property *property, const Value &val)
{
    const auto it = propertyMap.find(property);
    if (it == propertyMap.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setValueInRange(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            Property *property, const Value &val,
            void (PropertyManagerPrivate::*setSubPropertyValue)(Property *, ValueChangeParameter))
{
    const auto it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    auto &data = it.value();

    if (data.val == val)
        return;

    const Value oldVal = data.val;

    data.val = qBound(data.minVal, val, data.maxVal);

    if (data.val == oldVal)
        return;

    if (setSubPropertyValue)
        (managerPrivate->*setSubPropertyValue)(property, data.val);

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setBorderValues(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(Property *, ValueChangeParameter, ValueChangeParameter),
            Property *property, const Value &minVal, const Value &maxVal,
            void (PropertyManagerPrivate::*setSubPropertyRange)(Property *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    const auto it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    Value fromVal = minVal;
    Value toVal = maxVal;
    orderBorders(fromVal, toVal);

    auto &data = it.value();

    if (data.minVal == fromVal && data.maxVal == toVal)
        return;

    const Value oldVal = data.val;

    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    if (data.val == oldVal)
        return;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setBorderValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(Property *, ValueChangeParameter, ValueChangeParameter),
            Property *property,
            Value (PrivateData::*getRangeVal)() const,
            void (PrivateData::*setRangeVal)(ValueChangeParameter), const Value &borderVal,
            void (PropertyManagerPrivate::*setSubPropertyRange)(Property *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    const auto it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    PrivateData &data = it.value();

    if ((data.*getRangeVal)() == borderVal)
        return;

    const Value oldVal = data.val;

    (data.*setRangeVal)(borderVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    if (data.val == oldVal)
        return;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMinimumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(Property *, ValueChangeParameter, ValueChangeParameter),
            Property *property, const Value &minVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(Property *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>(manager, managerPrivate,
            propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManagerPrivate::Data::minimumValue, &PropertyManagerPrivate::Data::setMinimumValue, minVal, setSubPropertyRange);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMaximumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(Property *),
            void (PropertyManager::*valueChangedSignal)(Property *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(Property *, ValueChangeParameter, ValueChangeParameter),
            Property *property, const Value &maxVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(Property *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>(manager, managerPrivate,
            propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManagerPrivate::Data::maximumValue, &PropertyManagerPrivate::Data::setMaximumValue, maxVal, setSubPropertyRange);
}

/*
class MetaEnumProvider
{
public:
    MetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }
    QStringList languageEnumNames() const { return m_languageEnumNames; }
    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const;

private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country> > m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int> > m_countryToIndex;
    QMetaEnum m_policyEnum;
};
*/
static QList<QLocale::Country> sortCountries(const QList<QLocale::Country> &countries)
{
    QMultiMap<QString, QLocale::Country> nameToCountry;
    for (QLocale::Country country : countries)
        nameToCountry.insert(QLocale::countryToString(country), country);
    return nameToCountry.values();
}

void MetaEnumProvider::initLocale()
{
    QMultiMap<QString, QLocale::Language> nameToLanguage;
    for (int l = QLocale::C, last = QLocale::LastLanguage; l <= last; ++l) {
        const QLocale::Language language = static_cast<QLocale::Language>(l);
        QLocale locale(language);
        if (locale.language() == language)
            nameToLanguage.insert(QLocale::languageToString(language), language);
    }

    const QLocale system = QLocale::system();
    if (!nameToLanguage.contains(QLocale::languageToString(system.language())))
        nameToLanguage.insert(QLocale::languageToString(system.language()), system.language());

    const auto languages = nameToLanguage.values();
    for (QLocale::Language language : languages) {
        QList<QLocale::Country> countries;
        countries = QLocale::countriesForLanguage(language);
        if (countries.isEmpty() && language == system.language())
            countries << system.country();

        if (!countries.isEmpty() && !m_languageToIndex.contains(language)) {
            countries = sortCountries(countries);
            int langIdx = m_languageEnumNames.count();
            m_indexToLanguage[langIdx] = language;
            m_languageToIndex[language] = langIdx;
            QStringList countryNames;
            int countryIdx = 0;
            for (QLocale::Country country : qAsConst(countries)) {
                countryNames << QLocale::countryToString(country);
                m_indexToCountry[langIdx][countryIdx] = country;
                m_countryToIndex[language][country] = countryIdx;
                ++countryIdx;
            }
            m_languageEnumNames << QLocale::languageToString(language);
            m_countryEnumNames[language] = countryNames;
        }
    }
}

MetaEnumProvider::MetaEnumProvider()
{
    QMetaProperty p;

    p = MetaEnumWrapper::staticMetaObject.property(
                MetaEnumWrapper::staticMetaObject.propertyOffset() + 0);
    m_policyEnum = p.enumerator();
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
        m_policyEnumNames << QLatin1String(m_policyEnum.key(i));

    initLocale();
}

QSizePolicy::Policy MetaEnumProvider::indexToSizePolicy(int index) const
{
    return static_cast<QSizePolicy::Policy>(m_policyEnum.value(index));
}

int MetaEnumProvider::sizePolicyToIndex(QSizePolicy::Policy policy) const
{
     const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
        if (indexToSizePolicy(i) == policy)
            return i;
    return -1;
}

void MetaEnumProvider::indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const
{
    QLocale::Language l = QLocale::C;
    QLocale::Country c = QLocale::AnyCountry;
    if (m_indexToLanguage.contains(languageIndex)) {
        l = m_indexToLanguage[languageIndex];
        if (m_indexToCountry.contains(languageIndex) && m_indexToCountry[languageIndex].contains(countryIndex))
            c = m_indexToCountry[languageIndex][countryIndex];
    }
    if (language)
        *language = l;
    if (country)
        *country = c;
}

void MetaEnumProvider::localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const
{
    int l = -1;
    int c = -1;
    if (m_languageToIndex.contains(language)) {
        l = m_languageToIndex[language];
        if (m_countryToIndex.contains(language) && m_countryToIndex[language].contains(country))
            c = m_countryToIndex[language][country];
    }

    if (languageIndex)
        *languageIndex = l;
    if (countryIndex)
        *countryIndex = c;
}

// GroupPropManager 
GroupPropManager::GroupPropManager(QObject *parent)
    : AbsPropertyManager(parent)
{
}

GroupPropManager::~GroupPropManager()
{
}

bool GroupPropManager::hasValue(const Property *property) const
{
    Q_UNUSED(property);
    return false;
}

void GroupPropManager::initializeProperty(Property *property)
{
    Q_UNUSED(property);
}

void GroupPropManager::uninitializeProperty(Property *property)
{
    Q_UNUSED(property);
}

// IntPropManagerPrivate 
class IntPropManagerPrivate
{
    IntPropManager* q_ptr;
    Q_DECLARE_PUBLIC(IntPropManager)
public:
    struct Data
    {
        int val{0};
        int minVal{-INT_MAX};
        int maxVal{INT_MAX};
        int singleStep{1};
        int minimumValue() const { return minVal; }
        int maximumValue() const { return maxVal; }
        void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

// IntPropManager 
IntPropManager::IntPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new IntPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

IntPropManager::~IntPropManager()
{
    clear();
}

int IntPropManager::value(const Property *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

int IntPropManager::minimum(const Property *property) const
{
    return getMinimum<int>(d_ptr->m_values, property, 0);
}

int IntPropManager::maximum(const Property *property) const
{
    return getMaximum<int>(d_ptr->m_values, property, 0);
}

int IntPropManager::singleStep(const Property *property) const
{
    return getData<int>(d_ptr->m_values, &IntPropManagerPrivate::Data::singleStep, property, 0);
}

QString IntPropManager::valueText(const Property *property) const
{
    const IntPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return QString::number(it.value().val);
}

void IntPropManager::setValue(Property *property, int val)
{
    void (IntPropManagerPrivate::*setSubPropertyValue)(Property *, int) = 0;
    setValueInRange<int, IntPropManagerPrivate, IntPropManager, int>(this, d_ptr.data(),
                &IntPropManager::propertyChanged,
                &IntPropManager::valueChanged,
                property, val, setSubPropertyValue);
}

void IntPropManager::setMinimum(Property *property, int minVal)
{
    setMinimumValue<int, IntPropManagerPrivate, IntPropManager, int, IntPropManagerPrivate::Data>(this, d_ptr.data(),
                &IntPropManager::propertyChanged,
                &IntPropManager::valueChanged,
                &IntPropManager::rangeChanged,
                property, minVal);
}

void IntPropManager::setMaximum(Property *property, int maxVal)
{
    setMaximumValue<int, IntPropManagerPrivate, IntPropManager, int, IntPropManagerPrivate::Data>(this, d_ptr.data(),
                &IntPropManager::propertyChanged,
                &IntPropManager::valueChanged,
                &IntPropManager::rangeChanged,
                property, maxVal);
}

void IntPropManager::setRange(Property* property, int minVal, int maxVal)
{
    void (IntPropManagerPrivate::*setSubPropertyRange)(Property*, int, int, int) = 0;
    setBorderValues<int, IntPropManagerPrivate, IntPropManager, int>(this, d_ptr.data(),
                &IntPropManager::propertyChanged,
                &IntPropManager::valueChanged,
                &IntPropManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

void IntPropManager::setSingleStep(Property* property, int step)
{
    const IntPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    IntPropManagerPrivate::Data data = it.value();

    if (step < 0)
        step = 0;

    if (data.singleStep == step)
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

void IntPropManager::initializeProperty(Property* property)
{
    d_ptr->m_values[property] = IntPropManagerPrivate::Data();
}

void IntPropManager::uninitializeProperty(Property* property)
{
    d_ptr->m_values.remove(property);
}

// DoublePropManagerPrivate 
class DoublePropManagerPrivate
{
    DoublePropManager* q_ptr;
    Q_DECLARE_PUBLIC(DoublePropManager)
public:
    struct Data
    {
        double val{0};
        double minVal{-DBL_MAX};
        double maxVal{DBL_MAX};
        double singleStep{1};
        int decimals{2};
        double minimumValue() const { return minVal; }
        double maximumValue() const { return maxVal; }
        void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

// DoublePropManager 
DoublePropManager::DoublePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new DoublePropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

DoublePropManager::~DoublePropManager()
{
    clear();
}

double DoublePropManager::value(const Property* property) const
{
    return getValue<double>(d_ptr->m_values, property, 0.0);
}

double DoublePropManager::minimum(const Property* property) const
{
    return getMinimum<double>(d_ptr->m_values, property, 0.0);
}

double DoublePropManager::maximum(const Property* property) const
{
    return getMaximum<double>(d_ptr->m_values, property, 0.0);
}

double DoublePropManager::singleStep(const Property* property) const
{
    return getData<double>(d_ptr->m_values, &DoublePropManagerPrivate::Data::singleStep, property, 0);
}

int DoublePropManager::decimals(const Property *property) const
{
    return getData<int>(d_ptr->m_values, &DoublePropManagerPrivate::Data::decimals, property, 0);
}

QString DoublePropManager::valueText(const Property *property) const
{
    const DoublePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return QString::number(it.value().val, 'f', it.value().decimals);
}

void DoublePropManager::setValue(Property *property, double val)
{
    void (DoublePropManagerPrivate::*setSubPropertyValue)(Property *, double) = 0;
    setValueInRange<double, DoublePropManagerPrivate, DoublePropManager, double>(this, d_ptr.data(),
                &DoublePropManager::propertyChanged,
                &DoublePropManager::valueChanged,
                property, val, setSubPropertyValue);
}

void DoublePropManager::setSingleStep(Property *property, double step)
{
    const DoublePropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    DoublePropManagerPrivate::Data data = it.value();

    if (step < 0)
        step = 0;

    if (data.singleStep == step)
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

void DoublePropManager::setDecimals(Property *property, int prec)
{
    const DoublePropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    DoublePropManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

void DoublePropManager::setMinimum(Property* property, double minVal)
{
    setMinimumValue<double, DoublePropManagerPrivate, DoublePropManager, double, DoublePropManagerPrivate::Data>(this, d_ptr.data(),
                &DoublePropManager::propertyChanged,
                &DoublePropManager::valueChanged,
                &DoublePropManager::rangeChanged,
                property, minVal);
}

void DoublePropManager::setMaximum(Property* property, double maxVal)
{
    setMaximumValue<double, DoublePropManagerPrivate, DoublePropManager, double, DoublePropManagerPrivate::Data>(this, d_ptr.data(),
                &DoublePropManager::propertyChanged,
                &DoublePropManager::valueChanged,
                &DoublePropManager::rangeChanged,
                property, maxVal);
}

void DoublePropManager::setRange(Property *property, double minVal, double maxVal)
{
    void (DoublePropManagerPrivate::*setSubPropertyRange)(Property *, double, double, double) = 0;
    setBorderValues<double, DoublePropManagerPrivate, DoublePropManager, double>(this, d_ptr.data(),
                &DoublePropManager::propertyChanged,
                &DoublePropManager::valueChanged,
                &DoublePropManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

void DoublePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = DoublePropManagerPrivate::Data();
}

void DoublePropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// StringPropManagerPrivate 
class StringPropManagerPrivate
{
    StringPropManager *q_ptr;
    Q_DECLARE_PUBLIC(StringPropManager)
public:
    struct Data
    {
        Data()
        : regExp(QString(QLatin1Char('*')))
        {
        }
        QString val;
        QRegularExpression regExp;
    };
    typedef QMap<const Property *, Data> PropertyValueMap;
    QMap<const Property *, Data> m_values;
};

// StringPropManager 
StringPropManager::StringPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new StringPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

StringPropManager::~StringPropManager()
{
    clear();
}

QString StringPropManager::value(const Property *property) const
{
    return getValue<QString>(d_ptr->m_values, property);
}

QRegularExpression StringPropManager::regExp(const Property *property) const
{
    return getData<QRegularExpression>(d_ptr->m_values, &StringPropManagerPrivate::Data::regExp, property, QRegularExpression());
}

QString StringPropManager::valueText(const Property *property) const
{
    const StringPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().val;
}

void StringPropManager::setValue(Property *property, const QString &val)
{
    const StringPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    StringPropManagerPrivate::Data data = it.value();
    if (data.val == val)
        return;
    if (data.regExp.isValid() && !data.regExp.match(val).hasMatch())
        return;

    data.val = val;
    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void StringPropManager::setRegExp(Property *property, const QRegularExpression&regExp)
{
    const StringPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    StringPropManagerPrivate::Data data = it.value() ;
    if (data.regExp == regExp)
        return;
    data.regExp = regExp;
    it.value() = data;
    emit regExpChanged(property, data.regExp);
}

void StringPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = StringPropManagerPrivate::Data();
}

void StringPropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

static QIcon drawCheckBox(bool value)
{
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // Center?
        const int xoff = (pixmapWidth  > indicatorWidth)  ? (pixmapWidth  - indicatorWidth)  / 2 : 0;
        const int yoff = (pixmapHeight > indicatorHeight) ? (pixmapHeight - indicatorHeight) / 2 : 0;
        QPainter painter(&pixmap);
        painter.translate(xoff, yoff);
        style->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, &painter);
    }
    return QIcon(pixmap);
}

// BoolPropManagerPrivate
class BoolPropManagerPrivate
{
    BoolPropManager *q_ptr;
    Q_DECLARE_PUBLIC(BoolPropManager)
public:
    BoolPropManagerPrivate();
public:
    QMap<const Property *, bool> m_values;
    const QIcon m_checkedIcon;
    const QIcon m_uncheckedIcon;
};

BoolPropManagerPrivate::BoolPropManagerPrivate() 
    : m_checkedIcon(drawCheckBox(true))
    , m_uncheckedIcon(drawCheckBox(false))
{
}

// BoolPropManager 
BoolPropManager::BoolPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new BoolPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

BoolPropManager::~BoolPropManager()
{
    clear();
}

bool BoolPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, false);
}

QString BoolPropManager::valueText(const Property *property) const
{
    const QMap<const Property *, bool>::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    static const QString trueText = tr("True");
    static const QString falseText = tr("False");
    return it.value() ? trueText : falseText;
}

QIcon BoolPropManager::valueIcon(const Property *property) const
{
    const QMap<const Property *, bool>::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return it.value() ? d_ptr->m_checkedIcon : d_ptr->m_uncheckedIcon;
}

void BoolPropManager::setValue(Property *property, bool val)
{
    setSimpleValue<bool, bool, BoolPropManager>(d_ptr->m_values, this,
                &BoolPropManager::propertyChanged,
                &BoolPropManager::valueChanged,
                property, val);
}

void BoolPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = false;
}

void BoolPropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// DatePropManagerPrivate 
class DatePropManagerPrivate
{
    DatePropManager *q_ptr;
    Q_DECLARE_PUBLIC(DatePropManager)
public:
    explicit DatePropManagerPrivate(DatePropManager *q);

    struct Data
    {
        QDate val{QDate::currentDate()};
        QDate minVal{QDate(1752, 9, 14)};
        QDate maxVal{QDate(9999, 12, 31)};
        QDate minimumValue() const { return minVal; }
        QDate maximumValue() const { return maxVal; }
        void setMinimumValue(const QDate &newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(const QDate &newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    QString m_format;

    typedef QMap<const Property *, Data> PropertyValueMap;
    QMap<const Property *, Data> m_values;
};

DatePropManagerPrivate::DatePropManagerPrivate(DatePropManager *q) :
    q_ptr(q),
    m_format(PropBrowserUtils::dateFormat())
{
}

// DatePropManager 
DatePropManager::DatePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new DatePropManagerPrivate(this))
{
}

DatePropManager::~DatePropManager()
{
    clear();
}

QDate DatePropManager::value(const Property *property) const
{
    return getValue<QDate>(d_ptr->m_values, property);
}

QDate DatePropManager::minimum(const Property *property) const
{
    return getMinimum<QDate>(d_ptr->m_values, property);
}

QDate DatePropManager::maximum(const Property *property) const
{
    return getMaximum<QDate>(d_ptr->m_values, property);
}

QString DatePropManager::valueText(const Property *property) const
{
    const DatePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().val.toString(d_ptr->m_format);
}

void DatePropManager::setValue(Property *property, const QDate &val)
{
    void (DatePropManagerPrivate::*setSubPropertyValue)(Property *, const QDate &) = 0;
    setValueInRange<const QDate &, DatePropManagerPrivate, DatePropManager, const QDate>(this, d_ptr.data(),
                &DatePropManager::propertyChanged,
                &DatePropManager::valueChanged,
                property, val, setSubPropertyValue);
}

void DatePropManager::setMinimum(Property *property, const QDate &minVal)
{
    setMinimumValue<const QDate &, DatePropManagerPrivate, DatePropManager, QDate, DatePropManagerPrivate::Data>(this, d_ptr.data(),
                &DatePropManager::propertyChanged,
                &DatePropManager::valueChanged,
                &DatePropManager::rangeChanged,
                property, minVal);
}

void DatePropManager::setMaximum(Property *property, const QDate &maxVal)
{
    setMaximumValue<const QDate &, DatePropManagerPrivate, DatePropManager, QDate, DatePropManagerPrivate::Data>(this, d_ptr.data(),
                &DatePropManager::propertyChanged,
                &DatePropManager::valueChanged,
                &DatePropManager::rangeChanged,
                property, maxVal);
}

void DatePropManager::setRange(Property *property, const QDate &minVal, const QDate &maxVal)
{
    void (DatePropManagerPrivate::*setSubPropertyRange)(Property *, const QDate &,
          const QDate &, const QDate &) = 0;
    setBorderValues<const QDate &, DatePropManagerPrivate, DatePropManager, QDate>(this, d_ptr.data(),
                &DatePropManager::propertyChanged,
                &DatePropManager::valueChanged,
                &DatePropManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

void DatePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = DatePropManagerPrivate::Data();
}

void DatePropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// TimePropManagerPrivate 
class TimePropManagerPrivate
{
    TimePropManager *q_ptr;
    Q_DECLARE_PUBLIC(TimePropManager)
public:
    explicit TimePropManagerPrivate(TimePropManager *q);

    const QString m_format;

    typedef QMap<const Property *, QTime> PropertyValueMap;
    PropertyValueMap m_values;
};

TimePropManagerPrivate::TimePropManagerPrivate(TimePropManager *q) :
    q_ptr(q),
    m_format(PropBrowserUtils::timeFormat())
{
}

// TimePropManager 
TimePropManager::TimePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new TimePropManagerPrivate(this))
{
}

TimePropManager::~TimePropManager()
{
    clear();
}

QTime TimePropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QTime());
}

QString TimePropManager::valueText(const Property *property) const
{
   const TimePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(d_ptr->m_format);
}

void TimePropManager::setValue(Property *property, const QTime &val)
{
    setSimpleValue<const QTime &, QTime, TimePropManager>(d_ptr->m_values, this,
                &TimePropManager::propertyChanged,
                &TimePropManager::valueChanged,
                property, val);
}

void TimePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = QTime::currentTime();
}

void TimePropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// DateTimePropManagerPrivate 
class DateTimePropManagerPrivate
{
    DateTimePropManager *q_ptr;
    Q_DECLARE_PUBLIC(DateTimePropManager)
public:
    explicit DateTimePropManagerPrivate(DateTimePropManager *q);

    const QString m_format;

    typedef QMap<const Property *, QDateTime> PropertyValueMap;
    PropertyValueMap m_values;
};

DateTimePropManagerPrivate::DateTimePropManagerPrivate(DateTimePropManager *q) :
    q_ptr(q),
    m_format(PropBrowserUtils::dateTimeFormat())
{
}

// DateTimePropManager
DateTimePropManager::DateTimePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new DateTimePropManagerPrivate(this))
{
}

DateTimePropManager::~DateTimePropManager()
{
    clear();
}

QDateTime DateTimePropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QDateTime());
}

QString DateTimePropManager::valueText(const Property *property) const
{
   const DateTimePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(d_ptr->m_format);
}

void DateTimePropManager::setValue(Property *property, const QDateTime &val)
{
    setSimpleValue<const QDateTime &, QDateTime, DateTimePropManager>(d_ptr->m_values, this,
                &DateTimePropManager::propertyChanged,
                &DateTimePropManager::valueChanged,
                property, val);
}

void DateTimePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = QDateTime::currentDateTime();
}

void DateTimePropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// KeySequencePropManagerPrivate 
class KeySequencePropManagerPrivate
{
    KeySequencePropManager *q_ptr;
    Q_DECLARE_PUBLIC(KeySequencePropManager)
public:

    QString m_format;

    typedef QMap<const Property *, QKeySequence> PropertyValueMap;
    PropertyValueMap m_values;
};

// KeySequencePropManager 
KeySequencePropManager::KeySequencePropManager(QObject *parent)
    : AbsPropertyManager(parent)
    , d_ptr(new KeySequencePropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

KeySequencePropManager::~KeySequencePropManager()
{
    clear();
}

QKeySequence KeySequencePropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QKeySequence());
}

QString KeySequencePropManager::valueText(const Property *property) const
{
    const KeySequencePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(QKeySequence::NativeText);
}

void KeySequencePropManager::setValue(Property *property, const QKeySequence &val)
{
    setSimpleValue<const QKeySequence &, QKeySequence, KeySequencePropManager>(d_ptr->m_values, this,
                &KeySequencePropManager::propertyChanged,
                &KeySequencePropManager::valueChanged,
                property, val);
}

void KeySequencePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = QKeySequence();
}

void KeySequencePropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// CharPropManagerPrivate
class CharPropManagerPrivate
{
    CharPropManager *q_ptr;
    Q_DECLARE_PUBLIC(CharPropManager)
public:

    typedef QMap<const Property *, QChar> PropertyValueMap;
    PropertyValueMap m_values;
};

// CharPropManager 
CharPropManager::CharPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new CharPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

CharPropManager::~CharPropManager()
{
    clear();
}

QChar CharPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QChar());
}

QString CharPropManager::valueText(const Property *property) const
{
   const CharPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QChar c = it.value();
    return c.isNull() ? QString() : QString(c);
}

void CharPropManager::setValue(Property *property, const QChar &val)
{
    setSimpleValue<const QChar &, QChar, CharPropManager>(d_ptr->m_values, this,
                &CharPropManager::propertyChanged,
                &CharPropManager::valueChanged,
                property, val);
}

void CharPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = QChar();
}

void CharPropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// LocalePropManagerPrivate 
class LocalePropManagerPrivate
{
    LocalePropManager *q_ptr;
    Q_DECLARE_PUBLIC(LocalePropManager)
public:
    LocalePropManagerPrivate();

    void slotEnumChanged(Property *property, int value);
    void slotPropertyDestroyed(Property *property);

    typedef QMap<const Property *, QLocale> PropertyValueMap;
    PropertyValueMap m_values;

    EnumPropManager *m_enumPropertyManager;

    QMap<const Property *, Property *> m_propertyToLanguage;
    QMap<const Property *, Property *> m_propertyToCountry;

    QMap<const Property *, Property *> m_languageToProperty;
    QMap<const Property *, Property *> m_countryToProperty;
};

LocalePropManagerPrivate::LocalePropManagerPrivate()
{
}

void LocalePropManagerPrivate::slotEnumChanged(Property *property, int value)
{
    if (Property *prop = m_languageToProperty.value(property, 0)) 
    {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(value, 0, &newLanguage, 0);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    } 
    else if (prop = m_countryToProperty.value(property, 0)) 
    {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(m_enumPropertyManager->value(m_propertyToLanguage.value(prop)), value, &newLanguage, &newCountry);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    }
}

void LocalePropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property *subProp = m_languageToProperty.value(property, 0)) 
    {
        m_propertyToLanguage[subProp] = 0;
        m_languageToProperty.remove(property);
    } 
    else if (subProp = m_countryToProperty.value(property, 0)) 
    {
        m_propertyToCountry[subProp] = 0;
        m_countryToProperty.remove(property);
    }
}

// LocalePropManager 
LocalePropManager::LocalePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new LocalePropManagerPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->m_enumPropertyManager = new EnumPropManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotEnumChanged(Property*,int)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

LocalePropManager::~LocalePropManager()
{
    clear();
}

EnumPropManager *LocalePropManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

QLocale LocalePropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QLocale());
}

QString LocalePropManager::valueText(const Property *property) const
{
    const LocalePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QLocale loc = it.value();

    int langIdx = 0;
    int countryIdx = 0;
    const MetaEnumProvider *me = metaEnumProvider();
    me->localeToIndex(loc.language(), loc.country(), &langIdx, &countryIdx);
    if (langIdx < 0) {
        qWarning("LocalePropManager::valueText: Unknown language %d", loc.language());
        return tr("<Invalid>");
    }
    const QString languageName = me->languageEnumNames().at(langIdx);
    if (countryIdx < 0) {
        qWarning("LocalePropManager::valueText: Unknown country %d for %s", loc.country(), qPrintable(languageName));
        return languageName;
    }
    const QString countryName = me->countryEnumNames(loc.language()).at(countryIdx);
    return tr("%1, %2").arg(languageName, countryName);
}

void LocalePropManager::setValue(Property *property, const QLocale &val)
{
    const LocalePropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    const QLocale loc = it.value();
    if (loc == val)
        return;

    it.value() = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);
    if (loc.language() != val.language()) 
    {
        d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToLanguage.value(property), langIdx);
        d_ptr->m_enumPropertyManager->setEnumNames(d_ptr->m_propertyToCountry.value(property),
                    metaEnumProvider()->countryEnumNames(val.language()));
    }
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToCountry.value(property), countryIdx);

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void LocalePropManager::initializeProperty(Property *property)
{
    QLocale val;
    d_ptr->m_values[property] = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);

    Property *languageProp = d_ptr->m_enumPropertyManager->addProperty();
    languageProp->setPropertyName(tr("Language"));
    d_ptr->m_enumPropertyManager->setEnumNames(languageProp, metaEnumProvider()->languageEnumNames());
    d_ptr->m_enumPropertyManager->setValue(languageProp, langIdx);
    d_ptr->m_propertyToLanguage[property] = languageProp;
    d_ptr->m_languageToProperty[languageProp] = property;
    property->addSubProperty(languageProp);

    Property *countryProp = d_ptr->m_enumPropertyManager->addProperty();
    countryProp->setPropertyName(tr("Country"));
    d_ptr->m_enumPropertyManager->setEnumNames(countryProp, metaEnumProvider()->countryEnumNames(val.language()));
    d_ptr->m_enumPropertyManager->setValue(countryProp, countryIdx);
    d_ptr->m_propertyToCountry[property] = countryProp;
    d_ptr->m_countryToProperty[countryProp] = property;
    property->addSubProperty(countryProp);
}

void LocalePropManager::uninitializeProperty(Property *property)
{
    Property *languageProp = d_ptr->m_propertyToLanguage[property];
    if (languageProp) {
        d_ptr->m_languageToProperty.remove(languageProp);
        delete languageProp;
    }
    d_ptr->m_propertyToLanguage.remove(property);

    Property *countryProp = d_ptr->m_propertyToCountry[property];
    if (countryProp) {
        d_ptr->m_countryToProperty.remove(countryProp);
        delete countryProp;
    }
    d_ptr->m_propertyToCountry.remove(property);
    d_ptr->m_values.remove(property);
}

void LocalePropManager::slotEnumChanged(Property* property, int value)
{
    d_ptr->slotEnumChanged(property, value);
}

void LocalePropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// PointPropManagerPrivate 
class PointPropManagerPrivate
{
    PointPropManager *q_ptr;
    Q_DECLARE_PUBLIC(PointPropManager)
public:

    void slotIntChanged(Property *property, int value);
    void slotPropertyDestroyed(Property *property);

    typedef QMap<const Property *, QPoint> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager *m_intPropertyManager;

    QMap<const Property *, Property *> m_propertyToX;
    QMap<const Property *, Property *> m_propertyToY;

    QMap<const Property *, Property *> m_xToProperty;
    QMap<const Property *, Property *> m_yToProperty;
};

void PointPropManagerPrivate::slotIntChanged(Property *property, int value)
{
    if (Property *xprop = m_xToProperty.value(property, 0)) 
    {
        QPoint p = m_values[xprop];
        p.setX(value);
        q_ptr->setValue(xprop, p);
    } 
    else if (Property *yprop = m_yToProperty.value(property, 0)) 
    {
        QPoint p = m_values[yprop];
        p.setY(value);
        q_ptr->setValue(yprop, p);
    }
}

void PointPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property *pointProp = m_xToProperty.value(property, 0)) 
    {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } 
    else if (pointProp = m_yToProperty.value(property, 0)) 
    {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
}

// PointPropManager
PointPropManager::PointPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new PointPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

PointPropManager::~PointPropManager()
{
    clear();
}

IntPropManager *PointPropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QPoint PointPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QPoint());
}

QString PointPropManager::valueText(const Property *property) const
{
    const PointPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPoint v = it.value();
    return tr("(%1, %2)").arg(QString::number(v.x()))
                         .arg(QString::number(v.y()));
}

void PointPropManager::setValue(Property *property, const QPoint &val)
{
    const PointPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void PointPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = QPoint(0, 0);

    Property *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    Property *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

void PointPropManager::uninitializeProperty(Property *property)
{
    Property *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    Property *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

void PointPropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void PointPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// PointFPropManagerPrivate
class PointFPropManagerPrivate
{
    PointFPropManager *q_ptr;
    Q_DECLARE_PUBLIC(PointFPropManager)
public:
    struct Data
    {
        QPointF val;
        int decimals{2};
    };

    void slotDoubleChanged(Property *property, double value);
    void slotPropertyDestroyed(Property *property);

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    DoublePropManager *m_doublePropertyManager;

    QMap<const Property *, Property *> m_propertyToX;
    QMap<const Property *, Property *> m_propertyToY;

    QMap<const Property *, Property *> m_xToProperty;
    QMap<const Property *, Property *> m_yToProperty;
};

void PointFPropManagerPrivate::slotDoubleChanged(Property *property, double value)
{
    if (Property *prop = m_xToProperty.value(property, 0)) 
    {
        QPointF p = m_values[prop].val;
        p.setX(value);
        q_ptr->setValue(prop, p);
    } 
    else if (prop = m_yToProperty.value(property, 0)) 
    {
        QPointF p = m_values[prop].val;
        p.setY(value);
        q_ptr->setValue(prop, p);
    }
}

void PointFPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property *pointProp  = m_xToProperty.value(property, 0)) 
    {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } 
    else if (pointProp = m_yToProperty.value(property, 0)) 
    {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
}

// PointFPropManager 
PointFPropManager::PointFPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new PointFPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new DoublePropManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotDoubleChanged(Property*,double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

PointFPropManager::~PointFPropManager()
{
    clear();
}

DoublePropManager *PointFPropManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QPointF PointFPropManager::value(const Property *property) const
{
    return getValue<QPointF>(d_ptr->m_values, property);
}

int PointFPropManager::decimals(const Property *property) const
{
    return getData<int>(d_ptr->m_values, &PointFPropManagerPrivate::Data::decimals, property, 0);
}

QString PointFPropManager::valueText(const Property *property) const
{
    const PointFPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPointF v = it.value().val;
    const int dec =  it.value().decimals;
    return tr("(%1, %2)").arg(QString::number(v.x(), 'f', dec))
                         .arg(QString::number(v.y(), 'f', dec));
}

void PointFPropManager::setValue(Property *property, const QPointF &val)
{
    const PointFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void PointFPropManager::setDecimals(Property *property, int prec)
{
    const PointFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    PointFPropManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

void PointFPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = PointFPropManagerPrivate::Data();

    Property *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    Property *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

void PointFPropManager::uninitializeProperty(Property *property)
{
    Property *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    Property *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

void PointFPropManager::slotDoubleChanged(Property* property, double value)
{
    d_ptr->slotDoubleChanged(property, value);
}

void PointFPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

 // SizePropManagerPrivate
class SizePropManagerPrivate
{
    SizePropManager *q_ptr;
    Q_DECLARE_PUBLIC(SizePropManager)
public:

    void slotIntChanged(Property *property, int value);
    void slotPropertyDestroyed(Property *property);
    void setValue(Property *property, const QSize &val);
    void setRange(Property *property,
                const QSize &minVal, const QSize &maxVal, const QSize &val);

    struct Data
    {
        QSize val{0, 0};
        QSize minVal{0, 0};
        QSize maxVal{INT_MAX, INT_MAX};
        QSize minimumValue() const { return minVal; }
        QSize maximumValue() const { return maxVal; }
        void setMinimumValue(const QSize &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSize &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager *m_intPropertyManager;

    QMap<const Property *, Property *> m_propertyToW;
    QMap<const Property *, Property *> m_propertyToH;

    QMap<const Property *, Property *> m_wToProperty;
    QMap<const Property *, Property *> m_hToProperty;
};

void SizePropManagerPrivate::slotIntChanged(Property *property, int value)
{
    if (Property *prop = m_wToProperty.value(property, 0)) 
    {
        QSize s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } 
    else if (prop = m_hToProperty.value(property, 0)) 
    {
        QSize s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void SizePropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property *pointProp = m_wToProperty.value(property, 0)) 
    {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } 
    else if (pointProp = m_hToProperty.value(property, 0)) 
    {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void SizePropManagerPrivate::setValue(Property *property, const QSize &val)
{
    m_intPropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_intPropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void SizePropManagerPrivate::setRange(Property *property,
                const QSize &minVal, const QSize &maxVal, const QSize &val)
{
    Property *wProperty = m_propertyToW.value(property);
    Property *hProperty = m_propertyToH.value(property);
    m_intPropertyManager->setRange(wProperty, minVal.width(), maxVal.width());
    m_intPropertyManager->setValue(wProperty, val.width());
    m_intPropertyManager->setRange(hProperty, minVal.height(), maxVal.height());
    m_intPropertyManager->setValue(hProperty, val.height());
}

// SizePropManager
SizePropManager::SizePropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new SizePropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

SizePropManager::~SizePropManager()
{
    clear();
}

IntPropManager* SizePropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QSize SizePropManager::value(const Property *property) const
{
    return getValue<QSize>(d_ptr->m_values, property);
}

QSize SizePropManager::minimum(const Property *property) const
{
    return getMinimum<QSize>(d_ptr->m_values, property);
}

QSize SizePropManager::maximum(const Property *property) const
{
    return getMaximum<QSize>(d_ptr->m_values, property);
}

QString SizePropManager::valueText(const Property *property) const
{
    const SizePropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSize v = it.value().val;
    return tr("%1 x %2").arg(QString::number(v.width()))
                        .arg(QString::number(v.height()));
}

void SizePropManager::setValue(Property *property, const QSize &val)
{
    setValueInRange<const QSize &, SizePropManagerPrivate, SizePropManager, const QSize>(this, d_ptr.data(),
                &SizePropManager::propertyChanged,
                &SizePropManager::valueChanged,
                property, val, &SizePropManagerPrivate::setValue);
}

void SizePropManager::setMinimum(Property *property, const QSize &minVal)
{
    setBorderValue<const QSize &, SizePropManagerPrivate, SizePropManager, QSize, SizePropManagerPrivate::Data>(this, d_ptr.data(),
                &SizePropManager::propertyChanged,
                &SizePropManager::valueChanged,
                &SizePropManager::rangeChanged,
                property,
                &SizePropManagerPrivate::Data::minimumValue,
                &SizePropManagerPrivate::Data::setMinimumValue,
                minVal, &SizePropManagerPrivate::setRange);
}

void SizePropManager::setMaximum(Property *property, const QSize &maxVal)
{
    setBorderValue<const QSize &, SizePropManagerPrivate, SizePropManager, QSize, SizePropManagerPrivate::Data>(this, d_ptr.data(),
                &SizePropManager::propertyChanged,
                &SizePropManager::valueChanged,
                &SizePropManager::rangeChanged,
                property,
                &SizePropManagerPrivate::Data::maximumValue,
                &SizePropManagerPrivate::Data::setMaximumValue,
                maxVal, &SizePropManagerPrivate::setRange);
}

void SizePropManager::setRange(Property *property, const QSize &minVal, const QSize &maxVal)
{
    setBorderValues<const QSize &, SizePropManagerPrivate, SizePropManager, QSize>(this, d_ptr.data(),
                &SizePropManager::propertyChanged,
                &SizePropManager::valueChanged,
                &SizePropManager::rangeChanged,
                property, minVal, maxVal, &SizePropManagerPrivate::setRange);
}

void SizePropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = SizePropManagerPrivate::Data();

    Property *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    Property *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void SizePropManager::uninitializeProperty(Property *property)
{
    Property *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    Property *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

void SizePropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void SizePropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// SizeFPropManagerPrivate
class SizeFPropManagerPrivate
{
    SizeFPropManager *q_ptr;
    Q_DECLARE_PUBLIC(SizeFPropManager)
public:

    void slotDoubleChanged(Property *property, double value);
    void slotPropertyDestroyed(Property *property);
    void setValue(Property *property, const QSizeF &val);
    void setRange(Property *property,
                const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val);

    struct Data
    {
        QSizeF val{0, 0};
        QSizeF minVal{0, 0};
        QSizeF maxVal{std::numeric_limits<qreal>::max(), std::numeric_limits<qreal>::max()};
        int decimals{2};
        QSizeF minimumValue() const { return minVal; }
        QSizeF maximumValue() const { return maxVal; }
        void setMinimumValue(const QSizeF &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSizeF &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    DoublePropManager *m_doublePropertyManager;

    QMap<const Property *, Property *> m_propertyToW;
    QMap<const Property *, Property *> m_propertyToH;

    QMap<const Property *, Property *> m_wToProperty;
    QMap<const Property *, Property *> m_hToProperty;
};

void SizeFPropManagerPrivate::slotDoubleChanged(Property *property, double value)
{
    if (Property* prop = m_wToProperty.value(property, 0)) 
    {
        QSizeF s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } 
    else if (prop = m_hToProperty.value(property, 0)) 
    {
        QSizeF s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void SizeFPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property* pointProp = m_wToProperty.value(property, 0)) 
    {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } 
    else if (pointProp = m_hToProperty.value(property, 0)) 
    {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void SizeFPropManagerPrivate::setValue(Property *property, const QSizeF &val)
{
    m_doublePropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_doublePropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void SizeFPropManagerPrivate::setRange(Property *property,
                const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val)
{
    m_doublePropertyManager->setRange(m_propertyToW[property], minVal.width(), maxVal.width());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setRange(m_propertyToH[property], minVal.height(), maxVal.height());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

// SizeFPropManager
SizeFPropManager::SizeFPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new SizeFPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new DoublePropManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotDoubleChanged(Property*,double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

SizeFPropManager::~SizeFPropManager()
{
    clear();
}

DoublePropManager *SizeFPropManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QSizeF SizeFPropManager::value(const Property *property) const
{
    return getValue<QSizeF>(d_ptr->m_values, property);
}

int SizeFPropManager::decimals(const Property *property) const
{
    return getData<int>(d_ptr->m_values, &SizeFPropManagerPrivate::Data::decimals, property, 0);
}

QSizeF SizeFPropManager::minimum(const Property *property) const
{
    return getMinimum<QSizeF>(d_ptr->m_values, property);
}

QSizeF SizeFPropManager::maximum(const Property *property) const
{
    return getMaximum<QSizeF>(d_ptr->m_values, property);
}

QString SizeFPropManager::valueText(const Property *property) const
{
    const SizeFPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSizeF v = it.value().val;
    const int dec = it.value().decimals;
    return tr("%1 x %2").arg(QString::number(v.width(), 'f', dec))
                        .arg(QString::number(v.height(), 'f', dec));
}

void SizeFPropManager::setValue(Property *property, const QSizeF &val)
{
    setValueInRange<const QSizeF &, SizeFPropManagerPrivate, SizeFPropManager, QSizeF>(this, d_ptr.data(),
                &SizeFPropManager::propertyChanged,
                &SizeFPropManager::valueChanged,
                property, val, &SizeFPropManagerPrivate::setValue);
}

void SizeFPropManager::setDecimals(Property *property, int prec)
{
    const SizeFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    SizeFPropManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

void SizeFPropManager::setMinimum(Property *property, const QSizeF &minVal)
{
    setBorderValue<const QSizeF &, SizeFPropManagerPrivate, SizeFPropManager, QSizeF, SizeFPropManagerPrivate::Data>(this, d_ptr.data(),
                &SizeFPropManager::propertyChanged,
                &SizeFPropManager::valueChanged,
                &SizeFPropManager::rangeChanged,
                property,
                &SizeFPropManagerPrivate::Data::minimumValue,
                &SizeFPropManagerPrivate::Data::setMinimumValue,
                minVal, &SizeFPropManagerPrivate::setRange);
}

void SizeFPropManager::setMaximum(Property *property, const QSizeF &maxVal)
{
    setBorderValue<const QSizeF &, SizeFPropManagerPrivate, SizeFPropManager, QSizeF, SizeFPropManagerPrivate::Data>(this, d_ptr.data(),
                &SizeFPropManager::propertyChanged,
                &SizeFPropManager::valueChanged,
                &SizeFPropManager::rangeChanged,
                property,
                &SizeFPropManagerPrivate::Data::maximumValue,
                &SizeFPropManagerPrivate::Data::setMaximumValue,
                maxVal, &SizeFPropManagerPrivate::setRange);
}

void SizeFPropManager::setRange(Property *property, const QSizeF &minVal, const QSizeF &maxVal)
{
    setBorderValues<const QSizeF &, SizeFPropManagerPrivate, SizeFPropManager, QSizeF>(this, d_ptr.data(),
                &SizeFPropManager::propertyChanged,
                &SizeFPropManager::valueChanged,
                &SizeFPropManager::rangeChanged,
                property, minVal, maxVal, &SizeFPropManagerPrivate::setRange);
}

void SizeFPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = SizeFPropManagerPrivate::Data();

    Property *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    Property *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void SizeFPropManager::uninitializeProperty(Property *property)
{
    Property *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    Property *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

void SizeFPropManager::slotDoubleChanged(Property* property, double value)
{
    d_ptr->slotDoubleChanged(property, value);
}

void SizeFPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// RectPropManagerPrivate
class RectPropManagerPrivate
{
    RectPropManager *q_ptr;
    Q_DECLARE_PUBLIC(RectPropManager)
public:

    void slotIntChanged(Property *property, int value);
    void slotPropertyDestroyed(Property *property);
    void setConstraint(Property *property, const QRect &constraint, const QRect &val);

    struct Data
    {
        QRect val{0, 0, 0, 0};
        QRect constraint;
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager *m_intPropertyManager;

    QMap<const Property *, Property *> m_propertyToX;
    QMap<const Property *, Property *> m_propertyToY;
    QMap<const Property *, Property *> m_propertyToW;
    QMap<const Property *, Property *> m_propertyToH;

    QMap<const Property *, Property *> m_xToProperty;
    QMap<const Property *, Property *> m_yToProperty;
    QMap<const Property *, Property *> m_wToProperty;
    QMap<const Property *, Property *> m_hToProperty;
};

void RectPropManagerPrivate::slotIntChanged(Property *property, int value)
{
    if (Property* prop = m_xToProperty.value(property, 0)) 
    {
        QRect r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_yToProperty.value(property)) 
    {
        QRect r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_wToProperty.value(property, 0)) 
    {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_hToProperty.value(property, 0)) 
    {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void RectPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property* pointProp = m_xToProperty.value(property, 0)) 
    {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } 
    else if (pointProp = m_yToProperty.value(property, 0)) 
    {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    } 
    else if (pointProp = m_wToProperty.value(property, 0)) 
    {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } 
    else if (pointProp = m_hToProperty.value(property, 0)) 
    {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void RectPropManagerPrivate::setConstraint(Property *property,
            const QRect &constraint, const QRect &val)
{
    const bool isNull = constraint.isNull();
    const int left   = isNull ? INT_MIN : constraint.left();
    const int right  = isNull ? INT_MAX : constraint.left() + constraint.width();
    const int top    = isNull ? INT_MIN : constraint.top();
    const int bottom = isNull ? INT_MAX : constraint.top() + constraint.height();
    const int width  = isNull ? INT_MAX : constraint.width();
    const int height = isNull ? INT_MAX : constraint.height();

    m_intPropertyManager->setRange(m_propertyToX[property], left, right);
    m_intPropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_intPropertyManager->setRange(m_propertyToW[property], 0, width);
    m_intPropertyManager->setRange(m_propertyToH[property], 0, height);

    m_intPropertyManager->setValue(m_propertyToX[property], val.x());
    m_intPropertyManager->setValue(m_propertyToY[property], val.y());
    m_intPropertyManager->setValue(m_propertyToW[property], val.width());
    m_intPropertyManager->setValue(m_propertyToH[property], val.height());
}

// RectPropManager
RectPropManager::RectPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new RectPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

RectPropManager::~RectPropManager()
{
    clear();
}

IntPropManager *RectPropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QRect RectPropManager::value(const Property *property) const
{
    return getValue<QRect>(d_ptr->m_values, property);
}

QRect RectPropManager::constraint(const Property *property) const
{
    return getData<QRect>(d_ptr->m_values, &RectPropManagerPrivate::Data::constraint, property, QRect());
}

QString RectPropManager::valueText(const Property *property) const
{
    const RectPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRect v = it.value().val;
    return tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x()))
                                    .arg(QString::number(v.y()))
                                    .arg(QString::number(v.width()))
                                    .arg(QString::number(v.height()));
}

void RectPropManager::setValue(Property *property, const QRect &val)
{
    const RectPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    RectPropManagerPrivate::Data data = it.value();

    QRect newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRect r1 = data.constraint;
        const QRect r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (data.val == newRect)
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void RectPropManager::setConstraint(Property *property, const QRect &constraint)
{
    const RectPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    RectPropManagerPrivate::Data data = it.value();

    QRect newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
        return;

    const QRect oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRect r1 = data.constraint;
        QRect r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void RectPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = RectPropManagerPrivate::Data();

    Property *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    Property *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    Property *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    Property *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void RectPropManager::uninitializeProperty(Property *property)
{
    Property *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    Property *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    Property *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    Property *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

void RectPropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void RectPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// RectFPropManagerPrivate
class RectFPropManagerPrivate
{
    RectFPropManager *q_ptr;
    Q_DECLARE_PUBLIC(RectFPropManager)
public:

    void slotDoubleChanged(Property *property, double value);
    void slotPropertyDestroyed(Property *property);
    void setConstraint(Property *property, const QRectF &constraint, const QRectF &val);

    struct Data
    {
        QRectF val{0, 0, 0, 0};
        QRectF constraint;
        int decimals{2};
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    DoublePropManager *m_doublePropertyManager;

    QMap<const Property *, Property *> m_propertyToX;
    QMap<const Property *, Property *> m_propertyToY;
    QMap<const Property *, Property *> m_propertyToW;
    QMap<const Property *, Property *> m_propertyToH;

    QMap<const Property *, Property *> m_xToProperty;
    QMap<const Property *, Property *> m_yToProperty;
    QMap<const Property *, Property *> m_wToProperty;
    QMap<const Property *, Property *> m_hToProperty;
};

void RectFPropManagerPrivate::slotDoubleChanged(Property *property, double value)
{
    if (Property* prop = m_xToProperty.value(property, 0)) 
    {
        QRectF r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_yToProperty.value(property, 0)) 
    {
        QRectF r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_wToProperty.value(property, 0)) 
    {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } 
    else if (prop = m_hToProperty.value(property, 0)) 
    {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void RectFPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property* pointProp = m_xToProperty.value(property, 0))
    {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } 
    else if (pointProp = m_yToProperty.value(property, 0))
    {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    } 
    else if (pointProp = m_wToProperty.value(property, 0))
    {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } 
    else if (pointProp = m_hToProperty.value(property, 0))
    {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void RectFPropManagerPrivate::setConstraint(Property *property,
            const QRectF &constraint, const QRectF &val)
{
    const bool isNull = constraint.isNull();
    const float left   = isNull ? FLT_MIN : constraint.left();
    const float right  = isNull ? FLT_MAX : constraint.left() + constraint.width();
    const float top    = isNull ? FLT_MIN : constraint.top();
    const float bottom = isNull ? FLT_MAX : constraint.top() + constraint.height();
    const float width  = isNull ? FLT_MAX : constraint.width();
    const float height = isNull ? FLT_MAX : constraint.height();

    m_doublePropertyManager->setRange(m_propertyToX[property], left, right);
    m_doublePropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_doublePropertyManager->setRange(m_propertyToW[property], 0, width);
    m_doublePropertyManager->setRange(m_propertyToH[property], 0, height);

    m_doublePropertyManager->setValue(m_propertyToX[property], val.x());
    m_doublePropertyManager->setValue(m_propertyToY[property], val.y());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

// RectFPropManager 
RectFPropManager::RectFPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new RectFPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new DoublePropManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(Property*,double)),
                this, SLOT(slotDoubleChanged(Property*,double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

RectFPropManager::~RectFPropManager()
{
    clear();
}

DoublePropManager *RectFPropManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QRectF RectFPropManager::value(const Property *property) const
{
    return getValue<QRectF>(d_ptr->m_values, property);
}

int RectFPropManager::decimals(const Property *property) const
{
    return getData<int>(d_ptr->m_values, &RectFPropManagerPrivate::Data::decimals, property, 0);
}

QRectF RectFPropManager::constraint(const Property *property) const
{
    return getData<QRectF>(d_ptr->m_values, &RectFPropManagerPrivate::Data::constraint, property, QRect());
}

QString RectFPropManager::valueText(const Property *property) const
{
    const RectFPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRectF v = it.value().val;
    const int dec = it.value().decimals;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x(), 'f', dec))
                                .arg(QString::number(v.y(), 'f', dec))
                                .arg(QString::number(v.width(), 'f', dec))
                                .arg(QString::number(v.height(), 'f', dec)));
}

void RectFPropManager::setValue(Property *property, const QRectF &val)
{
    const RectFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    RectFPropManagerPrivate::Data data = it.value();

    QRectF newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRectF r1 = data.constraint;
        const QRectF r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (data.val == newRect)
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void RectFPropManager::setConstraint(Property *property, const QRectF &constraint)
{
    const RectFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    RectFPropManagerPrivate::Data data = it.value();

    QRectF newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
        return;

    const QRectF oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRectF r1 = data.constraint;
        QRectF r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void RectFPropManager::setDecimals(Property *property, int prec)
{
    const RectFPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    RectFPropManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

void RectFPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = RectFPropManagerPrivate::Data();

    Property *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    Property *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    Property *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    Property *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void RectFPropManager::uninitializeProperty(Property *property)
{
    Property *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    Property *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    Property *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    Property *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

void RectFPropManager::slotDoubleChanged(Property* property, double value)
{
    d_ptr->slotDoubleChanged(property, value);
}

void RectFPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// EnumPropManagerPrivate
class EnumPropManagerPrivate
{
    EnumPropManager* q_ptr;
    Q_DECLARE_PUBLIC(EnumPropManager)
public:
    struct Data
    {
        int val{-1};
        QStringList enumNames;
        QMap<int, QIcon> enumIcons;
    };
    typedef QMap<const Property*, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

// EnumPropManager
EnumPropManager::EnumPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new EnumPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

EnumPropManager::~EnumPropManager()
{
    clear();
}

int EnumPropManager::value(const Property *property) const
{
    return getValue<int>(d_ptr->m_values, property, -1);
}

QStringList EnumPropManager::enumNames(const Property *property) const
{
    return getData<QStringList>(d_ptr->m_values, &EnumPropManagerPrivate::Data::enumNames, property, QStringList());
}

QMap<int, QIcon> EnumPropManager::enumIcons(const Property *property) const
{
    return getData<QMap<int, QIcon> >(d_ptr->m_values, &EnumPropManagerPrivate::Data::enumIcons, property, QMap<int, QIcon>());
}

QString EnumPropManager::valueText(const Property *property) const
{
    const EnumPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const EnumPropManagerPrivate::Data &data = it.value();

    const int v = data.val;
    if (v >= 0 && v < data.enumNames.count())
        return data.enumNames.at(v);
    return QString();
}

QIcon EnumPropManager::valueIcon(const Property *property) const
{
    const EnumPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    const EnumPropManagerPrivate::Data &data = it.value();

    const int v = data.val;
    return data.enumIcons.value(v);
}

void EnumPropManager::setValue(Property* property, int val)
{
    const EnumPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    EnumPropManagerPrivate::Data data = it.value();

    if (val >= data.enumNames.count())
        return;

    if (val < 0 && data.enumNames.count() > 0)
        return;

    if (val < 0)
        val = -1;

    if (data.val == val)
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}
//#pragma warning(disable : 4996)
//#pragma warning(suppress : 4996)
void EnumPropManager::setEnumNames(Property* property, const QStringList& enumNames)
{
    const EnumPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    EnumPropManagerPrivate::Data& data = it.value();
    if (data.enumNames.size() == enumNames.size() && 
        std::equal(data.enumNames.begin(), data.enumNames.end(), enumNames.begin()))
        return;
// TODO   if (data.enumNames == enumNames)
//        return;

    data.enumNames = enumNames;
    data.val = -1;
    if (enumNames.count() > 0)
        data.val = 0;
    it.value() = data;

    emit enumNamesChanged(property, data.enumNames);
    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void EnumPropManager::setEnumIcons(Property *property, const QMap<int, QIcon> &enumIcons)
{
    const EnumPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    it.value().enumIcons = enumIcons;

    emit enumIconsChanged(property, it.value().enumIcons);

    emit propertyChanged(property);
}

void EnumPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = EnumPropManagerPrivate::Data();
}

void EnumPropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

// FlagPropManagerPrivate
class FlagPropManagerPrivate
{
    FlagPropManager *q_ptr;
    Q_DECLARE_PUBLIC(FlagPropManager)
public:

    void slotBoolChanged(Property *property, bool value);
    void slotPropertyDestroyed(Property *property);

    struct Data
    {
        int val{-1};
        QStringList flagNames;
    };

    typedef QMap<const Property *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    BoolPropManager *m_boolPropertyManager;

    QMap<const Property *, QList<Property *> > m_propertyToFlags;

    QMap<const Property *, Property *> m_flagToProperty;
};

void FlagPropManagerPrivate::slotBoolChanged(Property *property, bool value)
{
    Property *prop = m_flagToProperty.value(property, 0);
    if (prop == 0)
        return;

    const auto pfit = m_propertyToFlags.constFind(prop);
    if (pfit == m_propertyToFlags.constEnd())
            return;
    int level = 0;
    for (Property *p : pfit.value()) {
        if (p == property) {
            int v = m_values[prop].val;
            if (value) {
                v |= (1 << level);
            } else {
                v &= ~(1 << level);
            }
            q_ptr->setValue(prop, v);
            return;
        }
        level++;
    }
}

void FlagPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    Property *flagProperty = m_flagToProperty.value(property, 0);
    if (flagProperty == 0)
        return;

    m_propertyToFlags[flagProperty].replace(m_propertyToFlags[flagProperty].indexOf(property), 0);
    m_flagToProperty.remove(property);
}

// FlagPropManager
FlagPropManager::FlagPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new FlagPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_boolPropertyManager = new BoolPropManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(Property*,bool)),
                this, SLOT(slotBoolChanged(Property*,bool)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

FlagPropManager::~FlagPropManager()
{
    clear();
}

BoolPropManager *FlagPropManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

int FlagPropManager::value(const Property *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

QStringList FlagPropManager::flagNames(const Property *property) const
{
    return getData<QStringList>(d_ptr->m_values, &FlagPropManagerPrivate::Data::flagNames, property, QStringList());
}

QString FlagPropManager::valueText(const Property *property) const
{
    const FlagPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const FlagPropManagerPrivate::Data& data = it.value();

    QString str;
    int level = 0;
    const QChar bar = QLatin1Char('|');
    const QStringList::const_iterator fncend = data.flagNames.constEnd();
    for (QStringList::const_iterator itLoc =  data.flagNames.constBegin(); itLoc != fncend; ++itLoc)
    {
        if (data.val & (1 << level)) 
        {
            if (!str.isEmpty())
                str += bar;
            str += *itLoc;
        }
        level++;
    }
    return str;
}

void FlagPropManager::setValue(Property *property, int val)
{
    const FlagPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    FlagPropManagerPrivate::Data data = it.value();

    if (data.val == val)
        return;

    if (val > (1 << data.flagNames.count()) - 1)
        return;

    if (val < 0)
        return;

    data.val = val;

    it.value() = data;

    const auto pfit = d_ptr->m_propertyToFlags.constFind(property);
    int level = 0;
    if (pfit != d_ptr->m_propertyToFlags.constEnd()) {
        for (Property *prop : pfit.value()) {
            if (prop)
                d_ptr->m_boolPropertyManager->setValue(prop, val & (1 << level));
            level++;
        }
    }

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void FlagPropManager::setFlagNames(Property* property, const QStringList& flagNames)
{
    const FlagPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    FlagPropManagerPrivate::Data data = it.value();
    if (data.flagNames.size() == flagNames.size() && 
        std::equal(data.flagNames.begin(), data.flagNames.end(), flagNames.begin()))
        return;
//TODO    if (data.flagNames == flagNames)
//        return;

    data.flagNames = flagNames;
    data.val = 0;
    it.value() = data;

    const auto pfit = d_ptr->m_propertyToFlags.find(property);
    if (pfit != d_ptr->m_propertyToFlags.end()) 
    {
        for (Property *prop : qAsConst(pfit.value())) 
        {
            if (prop) 
            {
                delete prop;
                d_ptr->m_flagToProperty.remove(prop);
            }
        }
        pfit.value().clear();
    }

    for (const QString &flagName : flagNames) 
    {
        Property *prop = d_ptr->m_boolPropertyManager->addProperty();
        prop->setPropertyName(flagName);
        property->addSubProperty(prop);
        d_ptr->m_propertyToFlags[property].append(prop);
        d_ptr->m_flagToProperty[prop] = property;
    }

    emit flagNamesChanged(property, data.flagNames);
    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void FlagPropManager::initializeProperty(Property *property)
{
    d_ptr->m_values[property] = FlagPropManagerPrivate::Data();

    d_ptr->m_propertyToFlags[property] = QList<Property *>();
}

void FlagPropManager::uninitializeProperty(Property *property)
{
    const auto it = d_ptr->m_propertyToFlags.find(property);
    if (it != d_ptr->m_propertyToFlags.end()) {
        for (Property *prop : qAsConst(it.value()))  {
            if (prop) {
                d_ptr->m_flagToProperty.remove(prop);
                delete prop;
            }
        }
    }
    d_ptr->m_propertyToFlags.erase(it);

    d_ptr->m_values.remove(property);
}

void FlagPropManager::slotBoolChanged(Property* property, bool value)
{
    d_ptr->slotBoolChanged(property, value);
}

void FlagPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

// SizePolicyPropManagerPrivate
class SizePolicyPropManagerPrivate
{
    SizePolicyPropManager *q_ptr;
    Q_DECLARE_PUBLIC(SizePolicyPropManager)
public:

    SizePolicyPropManagerPrivate();

    void slotIntChanged(Property *property, int value);
    void slotEnumChanged(Property *property, int value);
    void slotPropertyDestroyed(Property *property);

    typedef QMap<const Property *, QSizePolicy> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager *m_intPropertyManager;
    EnumPropManager *m_enumPropertyManager;

    QMap<const Property *, Property *> m_propertyToHPolicy;
    QMap<const Property *, Property *> m_propertyToVPolicy;
    QMap<const Property *, Property *> m_propertyToHStretch;
    QMap<const Property *, Property *> m_propertyToVStretch;

    QMap<const Property *, Property *> m_hPolicyToProperty;
    QMap<const Property *, Property *> m_vPolicyToProperty;
    QMap<const Property *, Property *> m_hStretchToProperty;
    QMap<const Property *, Property *> m_vStretchToProperty;
};

SizePolicyPropManagerPrivate::SizePolicyPropManagerPrivate()
{
}

void SizePolicyPropManagerPrivate::slotIntChanged(Property *property, int value)
{
    if (Property* prop = m_hStretchToProperty.value(property, 0)) 
    {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalStretch(value);
        q_ptr->setValue(prop, sp);
    } 
    else if (prop = m_vStretchToProperty.value(property, 0)) 
    {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalStretch(value);
        q_ptr->setValue(prop, sp);
    }
}

void SizePolicyPropManagerPrivate::slotEnumChanged(Property *property, int value)
{
    if (Property* prop = m_hPolicyToProperty.value(property, 0)) 
    {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    } 
    else if (prop = m_vPolicyToProperty.value(property, 0)) 
    {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    }
}

void SizePolicyPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property* pointProp = m_hStretchToProperty.value(property, 0)) 
    {
        m_propertyToHStretch[pointProp] = 0;
        m_hStretchToProperty.remove(property);
    } 
    else if (pointProp = m_vStretchToProperty.value(property, 0)) 
    {
        m_propertyToVStretch[pointProp] = 0;
        m_vStretchToProperty.remove(property);
    } 
    else if (pointProp = m_hPolicyToProperty.value(property, 0)) 
    {
        m_propertyToHPolicy[pointProp] = 0;
        m_hPolicyToProperty.remove(property);
    } 
    else if (pointProp = m_vPolicyToProperty.value(property, 0)) 
    {
        m_propertyToVPolicy[pointProp] = 0;
        m_vPolicyToProperty.remove(property);
    }
}

// SizePolicyPropManager
SizePolicyPropManager::SizePolicyPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new SizePolicyPropManagerPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));
    d_ptr->m_enumPropertyManager = new EnumPropManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotEnumChanged(Property*,int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

SizePolicyPropManager::~SizePolicyPropManager()
{
    clear();
}

IntPropManager *SizePolicyPropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

EnumPropManager *SizePolicyPropManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

QSizePolicy SizePolicyPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QSizePolicy());
}

QString SizePolicyPropManager::valueText(const Property *property) const
{
    const SizePolicyPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QSizePolicy sp = it.value();
    const MetaEnumProvider *mep = metaEnumProvider();
    const int hIndex = mep->sizePolicyToIndex(sp.horizontalPolicy());
    const int vIndex = mep->sizePolicyToIndex(sp.verticalPolicy());
    const QString hPolicy = hIndex != -1 ? mep->policyEnumNames().at(hIndex) : tr("<Invalid>");
    const QString vPolicy = vIndex != -1 ? mep->policyEnumNames().at(vIndex) : tr("<Invalid>");
    const QString str = tr("[%1, %2, %3, %4]").arg(hPolicy, vPolicy).arg(sp.horizontalStretch()).arg(sp.verticalStretch());
    return str;
}

void SizePolicyPropManager::setValue(Property *property, const QSizePolicy &val)
{
    const SizePolicyPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToHPolicy[property],
                metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToVPolicy[property],
                metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToHStretch[property],
                val.horizontalStretch());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToVStretch[property],
                val.verticalStretch());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void SizePolicyPropManager::initializeProperty(Property *property)
{
    QSizePolicy val;
    d_ptr->m_values[property] = val;

    Property *hPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    hPolicyProp->setPropertyName(tr("Horizontal Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(hPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(hPolicyProp,
                metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_propertyToHPolicy[property] = hPolicyProp;
    d_ptr->m_hPolicyToProperty[hPolicyProp] = property;
    property->addSubProperty(hPolicyProp);

    Property *vPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    vPolicyProp->setPropertyName(tr("Vertical Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(vPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(vPolicyProp,
                metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_propertyToVPolicy[property] = vPolicyProp;
    d_ptr->m_vPolicyToProperty[vPolicyProp] = property;
    property->addSubProperty(vPolicyProp);

    Property *hStretchProp = d_ptr->m_intPropertyManager->addProperty();
    hStretchProp->setPropertyName(tr("Horizontal Stretch"));
    d_ptr->m_intPropertyManager->setValue(hStretchProp, val.horizontalStretch());
    d_ptr->m_intPropertyManager->setRange(hStretchProp, 0, 0xff);
    d_ptr->m_propertyToHStretch[property] = hStretchProp;
    d_ptr->m_hStretchToProperty[hStretchProp] = property;
    property->addSubProperty(hStretchProp);

    Property *vStretchProp = d_ptr->m_intPropertyManager->addProperty();
    vStretchProp->setPropertyName(tr("Vertical Stretch"));
    d_ptr->m_intPropertyManager->setValue(vStretchProp, val.verticalStretch());
    d_ptr->m_intPropertyManager->setRange(vStretchProp, 0, 0xff);
    d_ptr->m_propertyToVStretch[property] = vStretchProp;
    d_ptr->m_vStretchToProperty[vStretchProp] = property;
    property->addSubProperty(vStretchProp);

}

void SizePolicyPropManager::uninitializeProperty(Property *property)
{
    Property *hPolicyProp = d_ptr->m_propertyToHPolicy[property];
    if (hPolicyProp) {
        d_ptr->m_hPolicyToProperty.remove(hPolicyProp);
        delete hPolicyProp;
    }
    d_ptr->m_propertyToHPolicy.remove(property);

    Property *vPolicyProp = d_ptr->m_propertyToVPolicy[property];
    if (vPolicyProp) {
        d_ptr->m_vPolicyToProperty.remove(vPolicyProp);
        delete vPolicyProp;
    }
    d_ptr->m_propertyToVPolicy.remove(property);

    Property *hStretchProp = d_ptr->m_propertyToHStretch[property];
    if (hStretchProp) {
        d_ptr->m_hStretchToProperty.remove(hStretchProp);
        delete hStretchProp;
    }
    d_ptr->m_propertyToHStretch.remove(property);

    Property *vStretchProp = d_ptr->m_propertyToVStretch[property];
    if (vStretchProp) {
        d_ptr->m_vStretchToProperty.remove(vStretchProp);
        delete vStretchProp;
    }
    d_ptr->m_propertyToVStretch.remove(property);

    d_ptr->m_values.remove(property);
}

void SizePolicyPropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void SizePolicyPropManager::slotEnumChanged(Property* property, int value)
{
    d_ptr->slotEnumChanged(property, value);
}

void SizePolicyPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

class FontPropManagerPrivate
{
    FontPropManager *q_ptr;
    Q_DECLARE_PUBLIC(FontPropManager)
public:

    FontPropManagerPrivate();

    void slotIntChanged(Property *property, int value);
    void slotEnumChanged(Property *property, int value);
    void slotBoolChanged(Property *property, bool value);
    void slotPropertyDestroyed(Property *property);
    void slotFontDatabaseChanged();
    void slotFontDatabaseDelayedChange();

    QStringList m_familyNames;

    typedef QMap<const Property *, QFont> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager *m_intPropertyManager;
    EnumPropManager *m_enumPropertyManager;
    BoolPropManager *m_boolPropertyManager;

    QMap<const Property *, Property *> m_propertyToFamily;
    QMap<const Property *, Property *> m_propertyToPointSize;
    QMap<const Property *, Property *> m_propertyToBold;
    QMap<const Property *, Property *> m_propertyToItalic;
    QMap<const Property *, Property *> m_propertyToUnderline;
    QMap<const Property *, Property *> m_propertyToStrikeOut;
    QMap<const Property *, Property *> m_propertyToKerning;

    QMap<const Property *, Property *> m_familyToProperty;
    QMap<const Property *, Property *> m_pointSizeToProperty;
    QMap<const Property *, Property *> m_boldToProperty;
    QMap<const Property *, Property *> m_italicToProperty;
    QMap<const Property *, Property *> m_underlineToProperty;
    QMap<const Property *, Property *> m_strikeOutToProperty;
    QMap<const Property *, Property *> m_kerningToProperty;

    bool m_settingValue;
    QTimer *m_fontDatabaseChangeTimer;
};

FontPropManagerPrivate::FontPropManagerPrivate() :
    m_settingValue(false),
    m_fontDatabaseChangeTimer(0)
{
}

void FontPropManagerPrivate::slotIntChanged(Property *property, int value)
{
    if (m_settingValue)
        return;
    if (Property *prop = m_pointSizeToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setPointSize(value);
        q_ptr->setValue(prop, f);
    }
}

void FontPropManagerPrivate::slotEnumChanged(Property *property, int value)
{
    if (m_settingValue)
        return;
    if (Property *prop = m_familyToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setFamily(m_familyNames.at(value));
        q_ptr->setValue(prop, f);
    }
}

void FontPropManagerPrivate::slotBoolChanged(Property *property, bool value)
{
    if (m_settingValue)
        return;
    if (Property* prop = m_boldToProperty.value(property, 0)) 
    {
        QFont f = m_values[prop];
        f.setBold(value);
        q_ptr->setValue(prop, f);
    } 
    else if (prop = m_italicToProperty.value(property, 0)) 
    {
        QFont f = m_values[prop];
        f.setItalic(value);
        q_ptr->setValue(prop, f);
    } 
    else if (prop = m_underlineToProperty.value(property, 0)) 
    {
        QFont f = m_values[prop];
        f.setUnderline(value);
        q_ptr->setValue(prop, f);
    } 
    else if (prop = m_strikeOutToProperty.value(property, 0)) 
    {
        QFont f = m_values[prop];
        f.setStrikeOut(value);
        q_ptr->setValue(prop, f);
    } 
    else if (prop = m_kerningToProperty.value(property, 0)) 
    {
        QFont f = m_values[prop];
        f.setKerning(value);
        q_ptr->setValue(prop, f);
    }
}

void FontPropManagerPrivate::slotPropertyDestroyed(Property *property)
{
    if (Property* pointProp = m_pointSizeToProperty.value(property, 0)) 
    {
        m_propertyToPointSize[pointProp] = 0;
        m_pointSizeToProperty.remove(property);
    } 
    else if (pointProp = m_familyToProperty.value(property, 0)) 
    {
        m_propertyToFamily[pointProp] = 0;
        m_familyToProperty.remove(property);
    } 
    else if (pointProp = m_boldToProperty.value(property, 0)) 
    {
        m_propertyToBold[pointProp] = 0;
        m_boldToProperty.remove(property);
    } 
    else if (pointProp = m_italicToProperty.value(property, 0)) 
    {
        m_propertyToItalic[pointProp] = 0;
        m_italicToProperty.remove(property);
    } 
    else if (pointProp = m_underlineToProperty.value(property, 0)) 
    {
        m_propertyToUnderline[pointProp] = 0;
        m_underlineToProperty.remove(property);
    } 
    else if (pointProp = m_strikeOutToProperty.value(property, 0)) 
    {
        m_propertyToStrikeOut[pointProp] = 0;
        m_strikeOutToProperty.remove(property);
    } 
    else if (pointProp = m_kerningToProperty.value(property, 0)) 
    {
        m_propertyToKerning[pointProp] = 0;
        m_kerningToProperty.remove(property);
    }
}

void  FontPropManagerPrivate::slotFontDatabaseChanged()
{
    if (!m_fontDatabaseChangeTimer) {
        m_fontDatabaseChangeTimer = new QTimer(q_ptr);
        m_fontDatabaseChangeTimer->setInterval(0);
        m_fontDatabaseChangeTimer->setSingleShot(true);
        QObject::connect(m_fontDatabaseChangeTimer, SIGNAL(timeout()), q_ptr, SLOT(slotFontDatabaseDelayedChange()));
    }
    if (!m_fontDatabaseChangeTimer->isActive())
        m_fontDatabaseChangeTimer->start();
}

void FontPropManagerPrivate::slotFontDatabaseDelayedChange()
{
    typedef QMap<const Property *, Property *> PropertyPropertyMap;
    const QStringList oldFamilies = m_familyNames;
    m_familyNames = fontDatabase()->families();

    if (!m_propertyToFamily.isEmpty()) 
    {
        PropertyPropertyMap::const_iterator cend = m_propertyToFamily.constEnd();
        for (PropertyPropertyMap::const_iterator it = m_propertyToFamily.constBegin(); it != cend; ++it) 
        {
            Property *familyProp = it.value();
            const int oldIdx = m_enumPropertyManager->value(familyProp);
            int newIdx = m_familyNames.indexOf(oldFamilies.at(oldIdx));
            if (newIdx < 0)
                newIdx = 0;
            m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
            m_enumPropertyManager->setValue(familyProp, newIdx);
        }
    }
}

// FontPropManager
FontPropManager::FontPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new FontPropManagerPrivate)
{
    d_ptr->q_ptr = this;
    QObject::connect(qApp, SIGNAL(fontDatabaseChanged()), this, SLOT(slotFontDatabaseChanged()));

    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));
    d_ptr->m_enumPropertyManager = new EnumPropManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotEnumChanged(Property*,int)));
    d_ptr->m_boolPropertyManager = new BoolPropManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(Property*,bool)),
                this, SLOT(slotBoolChanged(Property*,bool)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

FontPropManager::~FontPropManager()
{
    clear();
}

IntPropManager *FontPropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

EnumPropManager *FontPropManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

BoolPropManager *FontPropManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

QFont FontPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QFont());
}

QString FontPropManager::valueText(const Property *property) const
{
    const FontPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return PropBrowserUtils::fontValueText(it.value());
}

QIcon FontPropManager::valueIcon(const Property *property) const
{
    const FontPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return PropBrowserUtils::fontValueIcon(it.value());
}

void FontPropManager::setValue(Property *property, const QFont& val)
{
    const FontPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    const QFont oldVal = it.value();
    if (oldVal == val && oldVal.resolve(oldVal) == val.resolve(val))
        return;

    it.value() = val;

    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    bool settingValue = d_ptr->m_settingValue;
    d_ptr->m_settingValue = true;
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToFamily[property], idx);
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToPointSize[property], val.pointSize());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToBold[property], val.bold());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToItalic[property], val.italic());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToUnderline[property], val.underline());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToStrikeOut[property], val.strikeOut());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToKerning[property], val.kerning());
    d_ptr->m_settingValue = settingValue;

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void FontPropManager::initializeProperty(Property *property)
{
    QFont val;
    d_ptr->m_values[property] = val;

    Property *familyProp = d_ptr->m_enumPropertyManager->addProperty();
    familyProp->setPropertyName(tr("Family"));
    if (d_ptr->m_familyNames.isEmpty())
        d_ptr->m_familyNames = fontDatabase()->families();
    d_ptr->m_enumPropertyManager->setEnumNames(familyProp, d_ptr->m_familyNames);
    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    d_ptr->m_enumPropertyManager->setValue(familyProp, idx);
    d_ptr->m_propertyToFamily[property] = familyProp;
    d_ptr->m_familyToProperty[familyProp] = property;
    property->addSubProperty(familyProp);

    Property *pointSizeProp = d_ptr->m_intPropertyManager->addProperty();
    pointSizeProp->setPropertyName(tr("Point Size"));
    d_ptr->m_intPropertyManager->setValue(pointSizeProp, val.pointSize());
    d_ptr->m_intPropertyManager->setMinimum(pointSizeProp, 1);
    d_ptr->m_propertyToPointSize[property] = pointSizeProp;
    d_ptr->m_pointSizeToProperty[pointSizeProp] = property;
    property->addSubProperty(pointSizeProp);

    Property *boldProp = d_ptr->m_boolPropertyManager->addProperty();
    boldProp->setPropertyName(tr("Bold"));
    d_ptr->m_boolPropertyManager->setValue(boldProp, val.bold());
    d_ptr->m_propertyToBold[property] = boldProp;
    d_ptr->m_boldToProperty[boldProp] = property;
    property->addSubProperty(boldProp);

    Property *italicProp = d_ptr->m_boolPropertyManager->addProperty();
    italicProp->setPropertyName(tr("Italic"));
    d_ptr->m_boolPropertyManager->setValue(italicProp, val.italic());
    d_ptr->m_propertyToItalic[property] = italicProp;
    d_ptr->m_italicToProperty[italicProp] = property;
    property->addSubProperty(italicProp);

    Property *underlineProp = d_ptr->m_boolPropertyManager->addProperty();
    underlineProp->setPropertyName(tr("Underline"));
    d_ptr->m_boolPropertyManager->setValue(underlineProp, val.underline());
    d_ptr->m_propertyToUnderline[property] = underlineProp;
    d_ptr->m_underlineToProperty[underlineProp] = property;
    property->addSubProperty(underlineProp);

    Property *strikeOutProp = d_ptr->m_boolPropertyManager->addProperty();
    strikeOutProp->setPropertyName(tr("Strikeout"));
    d_ptr->m_boolPropertyManager->setValue(strikeOutProp, val.strikeOut());
    d_ptr->m_propertyToStrikeOut[property] = strikeOutProp;
    d_ptr->m_strikeOutToProperty[strikeOutProp] = property;
    property->addSubProperty(strikeOutProp);

    Property *kerningProp = d_ptr->m_boolPropertyManager->addProperty();
    kerningProp->setPropertyName(tr("Kerning"));
    d_ptr->m_boolPropertyManager->setValue(kerningProp, val.kerning());
    d_ptr->m_propertyToKerning[property] = kerningProp;
    d_ptr->m_kerningToProperty[kerningProp] = property;
    property->addSubProperty(kerningProp);
}

void FontPropManager::uninitializeProperty(Property *property)
{
    Property *familyProp = d_ptr->m_propertyToFamily[property];
    if (familyProp) {
        d_ptr->m_familyToProperty.remove(familyProp);
        delete familyProp;
    }
    d_ptr->m_propertyToFamily.remove(property);

    Property *pointSizeProp = d_ptr->m_propertyToPointSize[property];
    if (pointSizeProp) {
        d_ptr->m_pointSizeToProperty.remove(pointSizeProp);
        delete pointSizeProp;
    }
    d_ptr->m_propertyToPointSize.remove(property);

    Property *boldProp = d_ptr->m_propertyToBold[property];
    if (boldProp) {
        d_ptr->m_boldToProperty.remove(boldProp);
        delete boldProp;
    }
    d_ptr->m_propertyToBold.remove(property);

    Property *italicProp = d_ptr->m_propertyToItalic[property];
    if (italicProp) {
        d_ptr->m_italicToProperty.remove(italicProp);
        delete italicProp;
    }
    d_ptr->m_propertyToItalic.remove(property);

    Property *underlineProp = d_ptr->m_propertyToUnderline[property];
    if (underlineProp) {
        d_ptr->m_underlineToProperty.remove(underlineProp);
        delete underlineProp;
    }
    d_ptr->m_propertyToUnderline.remove(property);

    Property *strikeOutProp = d_ptr->m_propertyToStrikeOut[property];
    if (strikeOutProp) {
        d_ptr->m_strikeOutToProperty.remove(strikeOutProp);
        delete strikeOutProp;
    }
    d_ptr->m_propertyToStrikeOut.remove(property);

    Property *kerningProp = d_ptr->m_propertyToKerning[property];
    if (kerningProp) {
        d_ptr->m_kerningToProperty.remove(kerningProp);
        delete kerningProp;
    }
    d_ptr->m_propertyToKerning.remove(property);

    d_ptr->m_values.remove(property);
}

void FontPropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void FontPropManager::slotEnumChanged(Property* property, int value)
{
    d_ptr->slotEnumChanged(property, value);
}

void FontPropManager::slotBoolChanged(Property* property, bool value)
{
    d_ptr->slotBoolChanged(property, value);
}

void FontPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

void FontPropManager::slotFontDatabaseChanged()
{
    d_ptr->slotFontDatabaseChanged();
}

void FontPropManager::slotFontDatabaseDelayedChange()
{
    d_ptr->slotFontDatabaseDelayedChange();
}

// ColorPropManagerPrivate
class ColorPropManagerPrivate
{
    ColorPropManager *q_ptr;
    Q_DECLARE_PUBLIC(ColorPropManager)
public:
    void slotIntChanged(Property* property, int value);
    void slotPropertyDestroyed(Property* property);

    typedef QMap<const Property*, QColor> PropertyValueMap;
    PropertyValueMap m_values;

    IntPropManager* m_intPropertyManager;

    QMap<const Property*, Property*> m_propertyToR;
    QMap<const Property*, Property*> m_propertyToG;
    QMap<const Property*, Property*> m_propertyToB;
    QMap<const Property*, Property*> m_propertyToA;

    QMap<const Property*, Property*> m_rToProperty;
    QMap<const Property*, Property*> m_gToProperty;
    QMap<const Property*, Property*> m_bToProperty;
    QMap<const Property*, Property*> m_aToProperty;
};

void ColorPropManagerPrivate::slotIntChanged(Property* property, int value)
{
    if (Property* prop = m_rToProperty.value(property, 0)) 
    {
        QColor c = m_values[prop];
        c.setRed(value);
        q_ptr->setValue(prop, c);
    } 
    else if (prop = m_gToProperty.value(property, 0)) 
    {
        QColor c = m_values[prop];
        c.setGreen(value);
        q_ptr->setValue(prop, c);
    } 
    else if (prop = m_bToProperty.value(property, 0)) 
    {
        QColor c = m_values[prop];
        c.setBlue(value);
        q_ptr->setValue(prop, c);
    } 
    else if (prop = m_aToProperty.value(property, 0)) 
    {
        QColor c = m_values[prop];
        c.setAlpha(value);
        q_ptr->setValue(prop, c);
    }
}

void ColorPropManagerPrivate::slotPropertyDestroyed(Property* property)
{
    if (Property* pointProp = m_rToProperty.value(property, 0)) 
    {
        m_propertyToR[pointProp] = 0;
        m_rToProperty.remove(property);
    } 
    else if (pointProp = m_gToProperty.value(property, 0)) 
    {
        m_propertyToG[pointProp] = 0;
        m_gToProperty.remove(property);
    } 
    else if (pointProp = m_bToProperty.value(property, 0)) 
    {
        m_propertyToB[pointProp] = 0;
        m_bToProperty.remove(property);
    } 
    else if (pointProp = m_aToProperty.value(property, 0)) 
    {
        m_propertyToA[pointProp] = 0;
        m_aToProperty.remove(property);
    }
}

// ColorPropManager
ColorPropManager::ColorPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new ColorPropManagerPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->m_intPropertyManager = new IntPropManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotIntChanged(Property*,int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(Property*)),
                this, SLOT(slotPropertyDestroyed(Property*)));
}

ColorPropManager::~ColorPropManager()
{
    clear();
}

IntPropManager* ColorPropManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QColor ColorPropManager::value(const Property* property) const
{
    return d_ptr->m_values.value(property, QColor());
}

QString ColorPropManager::valueText(const Property* property) const
{
    const ColorPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return PropBrowserUtils::colorValueText(it.value());
}

QIcon ColorPropManager::valueIcon(const Property* property) const
{
    const ColorPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();
    return PropBrowserUtils::brushValueIcon(QBrush(it.value()));
}

void ColorPropManager::setValue(Property* property, const QColor& val)
{
    const ColorPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToR[property], val.red());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToG[property], val.green());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToB[property], val.blue());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToA[property], val.alpha());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

void ColorPropManager::initializeProperty(Property* property)
{
    QColor val;
    d_ptr->m_values[property] = val;

    Property* rProp = d_ptr->m_intPropertyManager->addProperty(tr("Red"), ID_COLOR_RED);
    d_ptr->m_intPropertyManager->setValue(rProp, val.red());
    d_ptr->m_intPropertyManager->setRange(rProp, 0, 0xFF);
    d_ptr->m_propertyToR[property] = rProp;
    d_ptr->m_rToProperty[rProp] = property;
    property->addSubProperty(rProp);

    Property* gProp = d_ptr->m_intPropertyManager->addProperty(tr("Green"), ID_COLOR_GREEN);
    d_ptr->m_intPropertyManager->setValue(gProp, val.green());
    d_ptr->m_intPropertyManager->setRange(gProp, 0, 0xFF);
    d_ptr->m_propertyToG[property] = gProp;
    d_ptr->m_gToProperty[gProp] = property;
    property->addSubProperty(gProp);

    Property* bProp = d_ptr->m_intPropertyManager->addProperty(tr("Blue"), ID_COLOR_BLUE);
    d_ptr->m_intPropertyManager->setValue(bProp, val.blue());
    d_ptr->m_intPropertyManager->setRange(bProp, 0, 0xFF);
    d_ptr->m_propertyToB[property] = bProp;
    d_ptr->m_bToProperty[bProp] = property;
    property->addSubProperty(bProp);
    Property* aProp = d_ptr->m_intPropertyManager->addProperty(tr("Alpha"), ID_COLOR_ALPHA);
    d_ptr->m_intPropertyManager->setValue(aProp, val.alpha());
    d_ptr->m_intPropertyManager->setRange(aProp, 0, 0xFF);
    d_ptr->m_propertyToA[property] = aProp;
    d_ptr->m_aToProperty[aProp] = property;
    property->addSubProperty(aProp);
}

void ColorPropManager::uninitializeProperty(Property* property)
{
    if (Property* rProp = d_ptr->m_propertyToR[property])
    {
        d_ptr->m_rToProperty.remove(rProp);
        delete rProp;
    }
    d_ptr->m_propertyToR.remove(property);

    if (Property* gProp = d_ptr->m_propertyToG[property])
    {
        d_ptr->m_gToProperty.remove(gProp);
        delete gProp;
    }
    d_ptr->m_propertyToG.remove(property);

    if (Property* bProp = d_ptr->m_propertyToB[property])
    {
        d_ptr->m_bToProperty.remove(bProp);
        delete bProp;
    }
    d_ptr->m_propertyToB.remove(property);

    if (Property* aProp = d_ptr->m_propertyToA[property])
    {
        d_ptr->m_aToProperty.remove(aProp);
        delete aProp;
    }
    d_ptr->m_propertyToA.remove(property);

    d_ptr->m_values.remove(property);
}

void ColorPropManager::slotIntChanged(Property* property, int value)
{
    d_ptr->slotIntChanged(property, value);
}

void ColorPropManager::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

static void clearCursorDatabase();
namespace 
{
    struct structCursorDatabase : public CursorDatabase
    {
        structCursorDatabase()
        {
            qAddPostRoutine(clearCursorDatabase);
        }
    };
}

static void clearCursorDatabase()
{
    cursorDatabase()->clear();
}

// CursorPropManagerPrivate
class CursorPropManagerPrivate
{
    CursorPropManager *q_ptr;
    Q_DECLARE_PUBLIC(CursorPropManager)
public:
    typedef QMap<const Property *, QCursor> PropertyValueMap;
    PropertyValueMap m_values;
};

// CursorPropManager
CursorPropManager::CursorPropManager(QObject *parent)
    : AbsPropertyManager(parent), d_ptr(new CursorPropManagerPrivate)
{
    d_ptr->q_ptr = this;
}

CursorPropManager::~CursorPropManager()
{
    clear();
}

#ifndef QT_NO_CURSOR
QCursor CursorPropManager::value(const Property *property) const
{
    return d_ptr->m_values.value(property, QCursor());
}
#endif

QString CursorPropManager::valueText(const Property* property) const
{
   const CursorPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return cursorDatabase()->cursorToShapeName(it.value());
}

QIcon CursorPropManager::valueIcon(const Property *property) const
{
    const CursorPropManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return cursorDatabase()->cursorToShapeIcon(it.value());
}

void CursorPropManager::setValue(Property *property, const QCursor &value)
{
#ifndef QT_NO_CURSOR
    const CursorPropManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().shape() == value.shape() && value.shape() != Qt::BitmapCursor)
        return;
    it.value() = value;
    emit propertyChanged(property);
    emit valueChanged(property, value);
#endif
}

void CursorPropManager::initializeProperty(Property *property)
{
#ifndef QT_NO_CURSOR
    d_ptr->m_values[property] = QCursor();
#endif
}

void CursorPropManager::uninitializeProperty(Property *property)
{
    d_ptr->m_values.remove(property);
}

} // namespace QtVision
} // namespace VSN
