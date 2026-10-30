#ifndef __VSN_VARIANTPROPERTY_H
#define __VSN_VARIANTPROPERTY_H

#include <qt_propertybrowser.h>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <qt_global.h>

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate how to use the Vision kernel
               with Qt library and its classes. This header file can be changed from a version to a version with
               no warning or completely deleted.\~
*/

namespace VSN {
namespace QtVision {

typedef QMap<int, QIcon> IconMap;

class VarPropManager;
/* VarProperty */
class QT_CLASS VarProperty : public Property
{
public:
    ~VarProperty();
public:
    QVariant value() const;
    QVariant attributeValue(const QString& attribute) const;
    int valueType() const;
    int propertyType() const;
    void setValue(const QVariant& value);
    void setAttribute(const QString& attribute, const QVariant& value);
protected:
    VarProperty(VarPropManager* manager, const Id& id);
private:
    friend class VarPropManager;
    QScopedPointer<class QtVariantPropertyPrivate> d_ptr;
};

class VarPropManagerPrivate;
/* VarPropManager */
class QT_CLASS VarPropManager : public AbsPropertyManager
{
    Q_OBJECT
public:
    VarPropManager(QObject* parent = nullptr);
    ~VarPropManager();
public:
    virtual VarProperty* addProperty(int propertyType, const QString& name = QString(), const Id& id = 0);

    int propertyType(const Property* property) const;
    int valueType(const Property* property) const;
    VarProperty* variantProperty(const Property* property) const;

    virtual bool isPropertyTypeSupported(int propertyType) const;
    virtual int valueType(int propertyType) const;
    virtual QStringList attributes(int propertyType) const;
    virtual int attributeType(int propertyType, const QString& attribute) const;

    virtual QVariant value(const Property* property) const;
    virtual QVariant attributeValue(const Property* property, const QString& attribute) const;

    static int enumTypeId();
    static int flagTypeId();
    static int groupTypeId();
    static int iconMapTypeId();
    static int sliderTypeId();
public Q_SLOTS:
    virtual void setValue(Property* property, const QVariant& val);
    virtual void setAttribute(Property* property, const QString& attribute, const QVariant& value);
Q_SIGNALS:
    void valueChanged(Property* property, const QVariant& val);
    void attributeChanged(Property* property, const QString& attribute, const QVariant& val);
protected:
    bool hasValue(const Property* property) const override;
    QString valueText(const Property* property) const override;
    QIcon valueIcon(const Property* property) const override;
    void initializeProperty(Property* property) override;
    void uninitializeProperty(Property* property) override;
    Property* createProperty(const Id& id) override;
private Q_SLOTS:
    void slotValueChanged(Property*, int);
    void slotRangeChanged(Property*, int, int);
    void slotSingleStepChanged(Property*, int);
    void slotValueChanged(Property*, double);
    void slotRangeChanged(Property*, double, double);
    void slotSingleStepChanged(Property*, double);
    void slotDecimalsChanged(Property*, int);
    void slotValueChanged(Property*, bool);
    void slotValueChanged(Property*, const QString&);
    void slotRegExpChanged(Property*, const QRegularExpression&);
    void slotValueChanged(Property*, const QDate&);
    void slotRangeChanged(Property*, const QDate&, const QDate&);
    void slotValueChanged(Property*, const QTime&);
    void slotValueChanged(Property*, const QDateTime&);
    void slotValueChanged(Property*, const QKeySequence&);
    void slotValueChanged(Property*, const QChar&);
    void slotValueChanged(Property*, const QLocale&);
    void slotValueChanged(Property*, const QPoint&);
    void slotValueChanged(Property*, const QPointF&);
    void slotValueChanged(Property*, const QSize&);
    void slotRangeChanged(Property*, const QSize&, const QSize&);
    void slotValueChanged(Property*, const QSizeF&);
    void slotRangeChanged(Property*, const QSizeF&, const QSizeF&);
    void slotValueChanged(Property*, const QRect&);
    void slotConstraintChanged(Property*, const QRect&);
    void slotValueChanged(Property*, const QRectF&);
    void slotConstraintChanged(Property*, const QRectF&);
    void slotValueChanged(Property*, const QColor&);
    void slotEnumNamesChanged(Property*, const QStringList&);
    void slotEnumIconsChanged(Property*, const QMap<int, QIcon>&);
    void slotValueChanged(Property*, const QSizePolicy&);
    void slotValueChanged(Property*, const QFont&);
    void slotValueChanged(Property*, const QCursor&);
    void slotFlagNamesChanged(Property*, const QStringList&);

    void slotPropertyInserted(Property*, Property*, Property*);
    void slotPropertyRemoved(Property*, Property*);
private:
    QScopedPointer<class VarPropManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(VarPropManager);
    VSN_DISABLE_COPY(VarPropManager);
};

class VariantEditorFactoryPrivate;
/* VariantEditorFactory */
class QT_CLASS VariantEditorFactory : public AbsEditorFactory<VarPropManager>
{
    Q_OBJECT
public:
    VariantEditorFactory(QObject* parent = nullptr);
    ~VariantEditorFactory();
protected:
    void connectPropertyManager(VarPropManager* manager);
    QWidget* createEditor(VarPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(VarPropManager* manager);
private:
    QScopedPointer<class VariantEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(VariantEditorFactory);
    VSN_DISABLE_COPY(VariantEditorFactory);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_VARIANTPROPERTY_H */
