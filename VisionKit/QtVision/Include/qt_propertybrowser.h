#ifndef __VSN_PROPERTYBROWSER_H
#define __VSN_PROPERTYBROWSER_H

#include <QtWidgets/QWidget>
#include <QtCore/QSet>
#include <qt_id.h>
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

const char ID_COLOR_RED[]   = "ColorProperty.Red";
const char ID_COLOR_GREEN[] = "ColorProperty.Green";
const char ID_COLOR_BLUE[]  = "ColorProperty.Blue";
const char ID_COLOR_ALPHA[] = "ColorProperty.Alpha";

class AbsPropertyManager;
class PropertyPrivate;
/* Property */
class QT_CLASS Property
{
public:
    virtual ~Property();
public:
    QList<Property*> subProperties() const;
    Property* subProperty(const Id& id) const;
    AbsPropertyManager* propertyManager() const;

    QString toolTip() const { return valueToolTip(); }
    QString valueToolTip() const;
    QString descriptionToolTip() const;
    QString statusTip() const;
    QString whatsThis() const;
    QString propertyName() const;
    Id propertyId() const;
    bool isEnabled() const;
    bool isModified() const;

    bool hasValue() const;
    QIcon valueIcon() const;
    QString valueText() const;

    void setToolTip(const QString& text) { setValueToolTip(text); }
    void setValueToolTip(const QString& text);
    void setDescriptionToolTip(const QString &text);
    void setStatusTip(const QString& text);
    void setWhatsThis(const QString& text);
    void setPropertyName(const QString& text);
    void setPropertyId(const Id& id);

    void setEnabled(bool enable);
    void setModified(bool modified);

    void addSubProperty(Property* property);
    void insertSubProperty(Property* property, Property* afterProperty);
    void removeSubProperty(Property* property);
    void removeSubProperty(const Id& id);
protected:
    explicit Property(AbsPropertyManager* manager, const Id& id);
    void propertyChanged();
private:
    friend class AbsPropertyManager;
    QScopedPointer<PropertyPrivate> d_ptr;
};

class AbsPropertyManagerPrivate;
/* AbsPropertyManager */
class QT_CLASS AbsPropertyManager : public QObject
{
    Q_OBJECT
public:
    explicit AbsPropertyManager(QObject* parent = nullptr);
    ~AbsPropertyManager();
public:
    QSet<Property*> properties() const;
    Property* property(const Id& id);
    Property* addProperty(const QString& name = QString(), const Id& id = 0);
    void clear() const;
Q_SIGNALS:
    void propertyInserted(Property* property, Property* parent, Property* after);
    void propertyChanged(Property* property);
    void propertyRemoved(Property* property, Property* parent);
    void propertyDestroyed(Property *property);
protected:
    virtual bool hasValue(const Property* property) const ;
    virtual QIcon valueIcon(const Property* property) const;
    virtual QString valueText(const Property* property) const;
    virtual void initializeProperty(Property* property) = 0;
    virtual void uninitializeProperty(Property* property);
    virtual Property* createProperty(const Id& id);
private:
    friend class Property;
    QScopedPointer<AbsPropertyManagerPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(AbsPropertyManager);
    VSN_DISABLE_COPY(AbsPropertyManager);
};

/* AbsEditorFactoryBase */
class QT_CLASS AbsEditorFactoryBase : public QObject
{
    Q_OBJECT
public:
    virtual QWidget* createEditor(Property* property, QWidget* parent) = 0;
protected:
    explicit AbsEditorFactoryBase(QObject* parent = 0) : QObject(parent) {}
protected:
    virtual void breakConnection(AbsPropertyManager* manager) = 0;
protected Q_SLOTS:
    virtual void managerDestroyed(QObject* manager) = 0;
    friend class AbsPropBrowser;
};

/* AbsEditorFactory */
template <class PropertyManager>
class AbsEditorFactory : public AbsEditorFactoryBase
{
public:
    explicit AbsEditorFactory(QObject* parent) : AbsEditorFactoryBase(parent) {}
public:
    QWidget* createEditor(Property* property, QWidget* parent)
    {
        for (PropertyManager* manager : qAsConst(m_managers)) 
        {
            if (manager == property->propertyManager()) 
                return createEditor(manager, property, parent);
        }
        return nullptr;
    }

    void appendPropertyManager(PropertyManager* manager)
    {
        if (m_managers.contains(manager))
            return;
        m_managers.insert(manager);
        connectPropertyManager(manager);
        connect(manager, SIGNAL(destroyed(QObject*)), this, SLOT(managerDestroyed(QObject*)));
    }

    void removePropertyManager(PropertyManager* manager)
    {
        if (!m_managers.contains(manager))
            return;
        disconnect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject*)));
        disconnectPropertyManager(manager);
        m_managers.remove(manager);
    }

    QSet<PropertyManager*> propertyManagers() const { return m_managers; }
    PropertyManager* propertyManager(Property* property) const
    {
        AbsPropertyManager* manager = property->propertyManager();
        for (PropertyManager* m : qAsConst(m_managers)) 
        {
            if (m == manager) 
                return m;
        }
        return 0;
    }
protected:
    virtual void connectPropertyManager(PropertyManager *manager) = 0;
    virtual QWidget *createEditor(PropertyManager *manager, Property *property, QWidget *parent) = 0;
    virtual void disconnectPropertyManager(PropertyManager *manager) = 0;
    void managerDestroyed(QObject *manager)
    {
        for (PropertyManager* m : qAsConst(m_managers)) 
        {
            if (m == manager)
            {
                m_managers.remove(m);
                return;
            }
        }
    }
private:
    void breakConnection(AbsPropertyManager *manager)
    {
        for (PropertyManager* m : qAsConst(m_managers)) 
        {
            if (m == manager) 
            {
                removePropertyManager(m);
                return;
            }
        }
    }
private:
    QSet<PropertyManager*> m_managers;
};

class AbsPropBrowser;
class BrowserItemPrivate;
/* BrowserItem */
class QT_CLASS BrowserItem
{
public:
    Property* property() const;
    BrowserItem* parent() const;
    QList<BrowserItem*> children() const;
    AbsPropBrowser* browser() const;
private:
    explicit BrowserItem(AbsPropBrowser* browser, Property* property, BrowserItem* parent);
    ~BrowserItem();
    QScopedPointer<BrowserItemPrivate> d_ptr;
    friend class AbsPropBrowserPrivate;
};

class AbsPropBrowserPrivate;
/* AbsPropBrowser */
class QT_CLASS AbsPropBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit AbsPropBrowser(QWidget* parent = nullptr);
    ~AbsPropBrowser();
public:
    QList<Property*> properties() const;
    QList<BrowserItem*> items(Property* property) const;
    BrowserItem* topLevelItem(Property* property) const;
    QList<BrowserItem*> topLevelItems() const;
    void clear();

    template <class PropertyManager>
    void setFactoryForManager(PropertyManager* manager, AbsEditorFactory<PropertyManager>* factory) 
    {
        AbsPropertyManager* abstractManager = manager;
        AbsEditorFactoryBase* abstractFactory = factory;
        if (addFactory(abstractManager, abstractFactory))
            factory->appendPropertyManager(manager);
    }

    void unsetFactoryForManager(AbsPropertyManager* manager);

    BrowserItem* currentItem() const;
    void setCurrentItem(BrowserItem*);
Q_SIGNALS:
    void currentItemChanged(BrowserItem*);
public Q_SLOTS:
    BrowserItem* addProperty(Property* property);
    BrowserItem* insertProperty(Property* property, Property* afterProperty);
    void removeProperty(Property *property);
protected:
    virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem) = 0;
    virtual void itemRemoved(BrowserItem* item) = 0;
    // can be tooltip, statustip, whatsthis, name, icon, text.
    virtual void itemChanged(BrowserItem* item) = 0;
    virtual QWidget* createEditor(Property* property, QWidget* parent);
private:
    bool addFactory(AbsPropertyManager* abstractManager, AbsEditorFactoryBase* abstractFactory);
private Q_SLOTS:
    void slotPropertyInserted(Property*, Property*, Property*);
    void slotPropertyRemoved(Property*, Property*);
    void slotPropertyDestroyed(Property*);
    void slotPropertyDataChanged(Property*);
private:
    QScopedPointer<AbsPropBrowserPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(AbsPropBrowser);
    VSN_DISABLE_COPY(AbsPropBrowser);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_PROPERTYBROWSER_H */
