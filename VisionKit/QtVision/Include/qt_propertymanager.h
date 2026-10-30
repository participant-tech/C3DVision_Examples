#ifndef __VSN_PROPERTYMANAGER_H
#define __VSN_PROPERTYMANAGER_H

#include <QtCore/QLocale>
#include <QtCore/QMetaEnum>
#include <qt_propertybrowser.h>
#include <vsn_global.h>

class QDate;
class QTime;
class QDateTime;
class QLocale;

namespace VSN {
namespace QtVision {

class MetaEnumProvider
{
public:
    MetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }

    QStringList languageEnumNames() const { return m_languageEnumNames; }

    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language* language, QLocale::Country* country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int* languageIndex, int* countryIndex) const;
private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country>> m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int>> m_countryToIndex;
    QMetaEnum m_policyEnum;
};

/* GroupPropManager */
class GroupPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    GroupPropManager(QObject* parent = nullptr);
    ~GroupPropManager();
protected:
    virtual bool hasValue(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
};

class IntPropManagerPrivate;
/* IntPropManager */
class IntPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    IntPropManager(QObject* parent = nullptr);
    ~IntPropManager();
public:
    int value(const Property* property) const;
    int minimum(const Property* property) const;
    int maximum(const Property* property) const;
    int singleStep(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, int val);
    void setMinimum(Property* property, int minVal);
    void setMaximum(Property* property, int maxVal);
    void setRange(Property* property, int minVal, int maxVal);
    void setSingleStep(Property* property, int step);
Q_SIGNALS:
    void valueChanged(Property* property, int val);
    void rangeChanged(Property* property, int minVal, int maxVal);
    void singleStepChanged(Property* property, int step);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<IntPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(IntPropManager);
    VSN_DISABLE_COPY(IntPropManager);
};

class BoolPropManagerPrivate;
/* BoolPropManager */
class BoolPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    BoolPropManager(QObject* parent = nullptr);
    ~BoolPropManager();
public:
    bool value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, bool val);
Q_SIGNALS:
    void valueChanged(Property* property, bool val);
protected:
    QString valueText(const Property* property) const;
    QIcon valueIcon(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<BoolPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(BoolPropManager);
    VSN_DISABLE_COPY(BoolPropManager);
};

class DoublePropManagerPrivate;
/* DoublePropManager */
class DoublePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    DoublePropManager(QObject* parent = nullptr);
    ~DoublePropManager();
public:
    double value(const Property* property) const;
    double minimum(const Property* property) const;
    double maximum(const Property* property) const;
    double singleStep(const Property* property) const;
    int decimals(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, double val);
    void setMinimum(Property* property, double minVal);
    void setMaximum(Property* property, double maxVal);
    void setRange(Property* property, double minVal, double maxVal);
    void setSingleStep(Property* property, double step);
    void setDecimals(Property* property, int prec);
Q_SIGNALS:
    void valueChanged(Property* property, double val);
    void rangeChanged(Property* property, double minVal, double maxVal);
    void singleStepChanged(Property* property, double step);
    void decimalsChanged(Property* property, int prec);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<DoublePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DoublePropManager);
    VSN_DISABLE_COPY(DoublePropManager);
};

class StringPropManagerPrivate;
/* StringPropManager */
class StringPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    StringPropManager(QObject* parent = nullptr);
    ~StringPropManager();
public:
    QString value(const Property* property) const;
    QRegularExpression regExp(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QString& val);
    void setRegExp(Property* property, const QRegularExpression& regExp);
Q_SIGNALS:
    void valueChanged(Property* property, const QString& val);
    void regExpChanged(Property* property, const QRegularExpression& regExp);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<StringPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(StringPropManager);
    VSN_DISABLE_COPY(StringPropManager);
};

class DatePropManagerPrivate;
/* DatePropManager */
class DatePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    DatePropManager(QObject* parent = nullptr);
    ~DatePropManager();
public:
    QDate value(const Property* property) const;
    QDate minimum(const Property* property) const;
    QDate maximum(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QDate& val);
    void setMinimum(Property* property, const QDate& minVal);
    void setMaximum(Property* property, const QDate& maxVal);
    void setRange(Property* property, const QDate& minVal, const QDate& maxVal);
Q_SIGNALS:
    void valueChanged(Property* property, const QDate& val);
    void rangeChanged(Property* property, const QDate& minVal, const QDate& maxVal);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<DatePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DatePropManager);
    VSN_DISABLE_COPY(DatePropManager);
};

class TimePropManagerPrivate;
/* TimePropManager */
class TimePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    TimePropManager(QObject* parent = nullptr);
    ~TimePropManager();
public:
    QTime value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QTime& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QTime& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<TimePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(TimePropManager);
    VSN_DISABLE_COPY(TimePropManager);
};

class DateTimePropManagerPrivate;
/* DateTimePropManager */
class DateTimePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    DateTimePropManager(QObject* parent = nullptr);
    ~DateTimePropManager();
public:
    QDateTime value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QDateTime& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QDateTime& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<DateTimePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DateTimePropManager);
    VSN_DISABLE_COPY(DateTimePropManager);
};

class KeySequencePropManagerPrivate;
/* KeySequencePropManager */
class KeySequencePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    KeySequencePropManager(QObject* parent = nullptr);
    ~KeySequencePropManager();
public:
    QKeySequence value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QKeySequence& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QKeySequence& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<KeySequencePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(KeySequencePropManager);
    VSN_DISABLE_COPY(KeySequencePropManager);
};

class CharPropManagerPrivate;
/* CharPropManager */
class CharPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    CharPropManager(QObject* parent = nullptr);
    ~CharPropManager();
public:
    QChar value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QChar& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QChar& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<CharPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(CharPropManager);
    VSN_DISABLE_COPY(CharPropManager);
};

class EnumPropManager;
class LocalePropManagerPrivate;
/* LocalePropManager */
class LocalePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    LocalePropManager(QObject* parent = nullptr);
    ~LocalePropManager();
public:
    EnumPropManager* subEnumPropertyManager() const;
    QLocale value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QLocale& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QLocale& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotEnumChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<LocalePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(LocalePropManager);
    VSN_DISABLE_COPY(LocalePropManager);
};

class PointPropManagerPrivate;
/* PointPropManager */
class PointPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    PointPropManager(QObject* parent = nullptr);
    ~PointPropManager();
public:
    IntPropManager* subIntPropertyManager() const;
    QPoint value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QPoint& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QPoint& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<PointPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(PointPropManager);
    VSN_DISABLE_COPY(PointPropManager);
};

class PointFPropManagerPrivate;
/* PointFPropManager */
class PointFPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    PointFPropManager(QObject* parent = nullptr);
    ~PointFPropManager();
public:
    DoublePropManager* subDoublePropertyManager() const;
    QPointF value(const Property* property) const;
    int decimals(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QPointF& val);
    void setDecimals(Property* property, int prec);
Q_SIGNALS:
    void valueChanged(Property* property, const QPointF& val);
    void decimalsChanged(Property* property, int prec);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotDoubleChanged(Property*, double);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<PointFPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(PointFPropManager);
    VSN_DISABLE_COPY(PointFPropManager);
};

class SizePropManagerPrivate;
/* SizePropManager */
class SizePropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    SizePropManager(QObject *parent = nullptr);
    ~SizePropManager();
public:
    IntPropManager *subIntPropertyManager() const;

    QSize value(const Property* property) const;
    QSize minimum(const Property* property) const;
    QSize maximum(const Property* property) const;

public Q_SLOTS:
    void setValue(Property* property, const QSize& val);
    void setMinimum(Property* property, const QSize& minVal);
    void setMaximum(Property* property, const QSize& maxVal);
    void setRange(Property* property, const QSize& minVal, const QSize& maxVal);
Q_SIGNALS:
    void valueChanged(Property* property, const QSize& val);
    void rangeChanged(Property* property, const QSize& minVal, const QSize& maxVal);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<SizePropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(SizePropManager);
    VSN_DISABLE_COPY(SizePropManager);
};

class SizeFPropManagerPrivate;
/* SizeFPropManager */
class SizeFPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    SizeFPropManager(QObject* parent = nullptr);
    ~SizeFPropManager();
public:
    DoublePropManager* subDoublePropertyManager() const;

    QSizeF value(const Property* property) const;
    QSizeF minimum(const Property* property) const;
    QSizeF maximum(const Property* property) const;
    int decimals(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QSizeF& val);
    void setMinimum(Property* property, const QSizeF& minVal);
    void setMaximum(Property* property, const QSizeF& maxVal);
    void setRange(Property* property, const QSizeF& minVal, const QSizeF& maxVal);
    void setDecimals(Property* property, int prec);
Q_SIGNALS:
    void valueChanged(Property* property, const QSizeF& val);
    void rangeChanged(Property* property, const QSizeF& minVal, const QSizeF& maxVal);
    void decimalsChanged(Property* property, int prec);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotDoubleChanged(Property*, double);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<SizeFPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(SizeFPropManager);
    VSN_DISABLE_COPY(SizeFPropManager);
};

class RectPropManagerPrivate;
/* RectPropManager */
class RectPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    RectPropManager(QObject* parent = nullptr);
    ~RectPropManager();
public:
    IntPropManager* subIntPropertyManager() const;

    QRect value(const Property* property) const;
    QRect constraint(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QRect& val);
    void setConstraint(Property* property, const QRect& constraint);
Q_SIGNALS:
    void valueChanged(Property* property, const QRect& val);
    void constraintChanged(Property* property, const QRect& constraint);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<RectPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(RectPropManager);
    VSN_DISABLE_COPY(RectPropManager);
};

class RectFPropManagerPrivate;
/* RectFPropManager */
class RectFPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    RectFPropManager(QObject* parent = nullptr);
    ~RectFPropManager();
public:
    DoublePropManager* subDoublePropertyManager() const;

    QRectF value(const Property* property) const;
    QRectF constraint(const Property* property) const;
    int decimals(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QRectF& val);
    void setConstraint(Property* property, const QRectF& constraint);
    void setDecimals(Property* property, int prec);
Q_SIGNALS:
    void valueChanged(Property* property, const QRectF& val);
    void constraintChanged(Property* property, const QRectF& constraint);
    void decimalsChanged(Property* property, int prec);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotDoubleChanged(Property*, double);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<RectFPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(RectFPropManager);
    VSN_DISABLE_COPY(RectFPropManager);
};

class EnumPropManagerPrivate;
/* EnumPropManager */
class EnumPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    EnumPropManager(QObject* parent = nullptr);
    ~EnumPropManager();
public:
    int value(const Property* property) const;
    QStringList enumNames(const Property* property) const;
    QMap<int, QIcon> enumIcons(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, int val);
    void setEnumNames(Property* property, const QStringList& names);
    void setEnumIcons(Property* property, const QMap<int, QIcon>& icons);
Q_SIGNALS:
    void valueChanged(Property* property, int val);
    void enumNamesChanged(Property* property, const QStringList& names);
    void enumIconsChanged(Property* property, const QMap<int, QIcon>& icons);
protected:
    QString valueText(const Property* property) const;
    QIcon valueIcon(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<EnumPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(EnumPropManager);
    VSN_DISABLE_COPY(EnumPropManager);
};

class FlagPropManagerPrivate;
/* FlagPropManager */
class FlagPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    FlagPropManager(QObject* parent = nullptr);
    ~FlagPropManager();
public:
    BoolPropManager* subBoolPropertyManager() const;
    int value(const Property *property) const;
    QStringList flagNames(const Property *property) const;
public Q_SLOTS:
    void setValue(Property* property, int val);
    void setFlagNames(Property* property, const QStringList& names);
Q_SIGNALS:
    void valueChanged(Property* property, int val);
    void flagNamesChanged(Property* property, const QStringList& names);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotBoolChanged(Property*, bool);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<FlagPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(FlagPropManager);
    VSN_DISABLE_COPY(FlagPropManager);
};

class SizePolicyPropManagerPrivate;
/* FlagPropManager */
class SizePolicyPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    SizePolicyPropManager(QObject* parent = nullptr);
    ~SizePolicyPropManager();
public:
    IntPropManager* subIntPropertyManager() const;
    EnumPropManager* subEnumPropertyManager() const;
    QSizePolicy value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QSizePolicy& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QSizePolicy& val);
protected:
    QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotEnumChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<SizePolicyPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(SizePolicyPropManager);
    VSN_DISABLE_COPY(SizePolicyPropManager);
};

class FontPropManagerPrivate;
/* FontPropManager */
class FontPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    FontPropManager(QObject* parent = nullptr);
    ~FontPropManager();
public:
    IntPropManager* subIntPropertyManager() const;
    EnumPropManager* subEnumPropertyManager() const;
    BoolPropManager* subBoolPropertyManager() const;
    QFont value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QFont& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QFont& val);
protected:
    QString valueText(const Property* property) const;
    QIcon valueIcon(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotEnumChanged(Property*, int);
    void slotBoolChanged(Property*, bool);
    void slotPropertyDestroyed(Property*);
    void slotFontDatabaseChanged();
    void slotFontDatabaseDelayedChange();
private:
    QScopedPointer<FontPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(FontPropManager);
    VSN_DISABLE_COPY(FontPropManager);
};

class ColorPropManagerPrivate;
/* ColorPropManager */
class ColorPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    ColorPropManager(QObject* parent = nullptr);
    ~ColorPropManager();
public:
    IntPropManager* subIntPropertyManager() const;
    QColor value(const Property* property) const;
public Q_SLOTS:
    void setValue(Property* property, const QColor& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QColor& val);
protected:
    QString valueText(const Property* property) const;
    QIcon valueIcon(const Property* property) const;
    void initializeProperty(Property* property) override;
    void uninitializeProperty(Property* property) override;
private Q_SLOTS:
    void slotIntChanged(Property*, int);
    void slotPropertyDestroyed(Property*);
private:
    QScopedPointer<ColorPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(ColorPropManager);
    VSN_DISABLE_COPY(ColorPropManager);
};

class CursorPropManagerPrivate;
/* CursorPropManager */
class CursorPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    CursorPropManager(QObject* parent = nullptr);
    ~CursorPropManager();
public:
#ifndef QT_NO_CURSOR
    QCursor value(const Property* property) const;
#endif
public Q_SLOTS:
    void setValue(Property* property, const QCursor& val);
Q_SIGNALS:
    void valueChanged(Property* property, const QCursor& val);
protected:
    QString valueText(const Property* property) const;
    QIcon valueIcon(const Property* property) const;
    virtual void initializeProperty(Property* property);
    virtual void uninitializeProperty(Property* property);
private:
    QScopedPointer<CursorPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(CursorPropManager);
    VSN_DISABLE_COPY(CursorPropManager);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_PROPERTYMANAGER_H */
