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

#include "qt_propertybrowser.h"
#include <QtCore/QSet>
#include <QtCore/QMap>
//#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtGui/QIcon>

// Q_GLOBAL_STATIC must be before #include <vsn_last.h> because the operator is overridden
typedef QMap<QtVision::AbsPropBrowser*, QMap<QtVision::AbsPropertyManager*, QtVision::AbsEditorFactoryBase*>> Map1;
typedef QMap<QtVision::AbsPropertyManager*, QMap<QtVision::AbsEditorFactoryBase*, QList<QtVision::AbsPropBrowser*>>> Map2;
Q_GLOBAL_STATIC(Map1, m_viewToManagerToFactory)
Q_GLOBAL_STATIC(Map2, m_managerToFactoryToViews)

#include <vsn_last.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif
namespace VSN {
namespace QtVision {

/* PropertyPrivate */
class PropertyPrivate
{
public:
    PropertyPrivate(AbsPropertyManager* manager, const Id& id) 
        : m_id(id)
        , m_enabled(true)
        , m_modified(false)
        , m_manager(manager)
    {
    }
    Property* q_ptr;

    QSet<Property*> m_parentItems;
    QList<Property*> m_subItems;

    QString m_valueToolTip;
    QString m_descriptionToolTip;
    QString m_statusTip;
    QString m_whatsThis;
    QString m_name;
    Id m_id;
    bool m_enabled;
    bool m_modified;
    AbsPropertyManager * const m_manager;
};

class AbsPropertyManagerPrivate
{
    AbsPropertyManager *q_ptr;
    VSN_DECLARE_PUBLIC(AbsPropertyManager);
public:
    void propertyDestroyed(Property *property);
    void propertyChanged(Property *property) const;
    void propertyRemoved(Property *property,
                Property *parentProperty) const;
    void propertyInserted(Property *property, Property *parentProperty,
                Property *afterProperty) const;

    QSet<Property *> m_properties;
};

/* Property */
Property::Property(AbsPropertyManager* manager, const Id& id)
    : d_ptr(new PropertyPrivate(manager, id))
{
    d_ptr->q_ptr = this;
}

Property::~Property()
{
    for (Property* property : qAsConst(d_ptr->m_parentItems))
        property->d_ptr->m_manager->d_ptr->propertyRemoved(this, property);

    d_ptr->m_manager->d_ptr->propertyDestroyed(this);

    for (Property* property : qAsConst(d_ptr->m_subItems))
        property->d_ptr->m_parentItems.remove(this);

    for (Property* property : qAsConst(d_ptr->m_parentItems))
        property->d_ptr->m_subItems.removeAll(this);
}

QList<Property*> Property::subProperties() const
{
    return d_ptr->m_subItems;
}

Property* Property::subProperty(const Id& id) const
{
    for (Property* property : qAsConst(d_ptr->m_subItems))
        if (property->propertyId() == id)
            return property;
    return nullptr;
}

AbsPropertyManager *Property::propertyManager() const
{
    return d_ptr->m_manager;
}

QString Property::valueToolTip() const
{
    return d_ptr->m_valueToolTip;
}

QString Property::descriptionToolTip() const
{
    return d_ptr->m_descriptionToolTip;
}

QString Property::statusTip() const
{
    return d_ptr->m_statusTip;
}

QString Property::whatsThis() const
{
    return d_ptr->m_whatsThis;
}

QString Property::propertyName() const
{
    return d_ptr->m_name;
}

Id Property::propertyId() const
{
    return d_ptr->m_id;
}

bool Property::isEnabled() const
{
    return d_ptr->m_enabled;
}

bool Property::isModified() const
{
    return d_ptr->m_modified;
}

bool Property::hasValue() const
{
    return d_ptr->m_manager->hasValue(this);
}

QIcon Property::valueIcon() const
{
    return d_ptr->m_manager->valueIcon(this);
}

QString Property::valueText() const
{
    return d_ptr->m_manager->valueText(this);
}

void Property::setValueToolTip(const QString &text)
{
    if (d_ptr->m_valueToolTip == text)
        return;

    d_ptr->m_valueToolTip = text;
    propertyChanged();
}

void Property::setDescriptionToolTip(const QString &text)
{
    if (d_ptr->m_descriptionToolTip == text)
        return;

    d_ptr->m_descriptionToolTip = text;
    propertyChanged();
}

void Property::setStatusTip(const QString &text)
{
    if (d_ptr->m_statusTip == text)
        return;

    d_ptr->m_statusTip = text;
    propertyChanged();
}

void Property::setWhatsThis(const QString &text)
{
    if (d_ptr->m_whatsThis == text)
        return;

    d_ptr->m_whatsThis = text;
    propertyChanged();
}

void Property::setPropertyName(const QString &text)
{
    if (d_ptr->m_name == text)
        return;

    d_ptr->m_name = text;
    propertyChanged();
}

void Property::setPropertyId(const Id& id)
{
    if (d_ptr->m_id == id)
        return;
    d_ptr->m_id = id;
}

void Property::setEnabled(bool enable)
{
    if (d_ptr->m_enabled == enable)
        return;

    d_ptr->m_enabled = enable;
    propertyChanged();
}

void Property::setModified(bool modified)
{
    if (d_ptr->m_modified == modified)
        return;

    d_ptr->m_modified = modified;
    propertyChanged();
}

void Property::addSubProperty(Property* property)
{
    Property *after = 0;
    if (d_ptr->m_subItems.count() > 0)
        after = d_ptr->m_subItems.last();
    insertSubProperty(property, after);
}

void Property::insertSubProperty(Property* property, Property* afterProperty)
{
    if (!property)
        return;

    if (property == this)
        return;

    auto pendingList = property->subProperties();
    QMap<Property *, bool> visited;
    while (!pendingList.isEmpty()) 
    {
        Property *i = pendingList.first();
        if (i == this)
            return;
        pendingList.removeFirst();
        if (visited.contains(i))
            continue;
        visited[i] = true;
        pendingList += i->subProperties();
    }

    pendingList = subProperties();
    int pos = 0;
    int newPos = 0;
    Property* properAfterProperty = 0;
    while (pos < pendingList.count()) 
    {
        Property* i = pendingList.at(pos);
        if (i == property)
            return;
        if (i == afterProperty) 
        {
            newPos = pos + 1;
            properAfterProperty = afterProperty;
        }
        pos++;
    }

    d_ptr->m_subItems.insert(newPos, property);
    property->d_ptr->m_parentItems.insert(this);
    d_ptr->m_manager->d_ptr->propertyInserted(property, this, properAfterProperty);
}

void Property::removeSubProperty(Property* property)
{
    if (!property)
        return;

    d_ptr->m_manager->d_ptr->propertyRemoved(property, this);

    auto pendingList = subProperties();
    int pos = 0;
    while (pos < pendingList.count()) 
    {
        if (pendingList.at(pos) == property) 
        {
            d_ptr->m_subItems.removeAt(pos);
            property->d_ptr->m_parentItems.remove(this);
            return;
        }
        pos++;
    }
}

void Property::removeSubProperty(const Id& id)
{ 
    if (Property* prop = subProperty(id))
        removeSubProperty(prop);
}

void Property::propertyChanged()
{
    d_ptr->m_manager->d_ptr->propertyChanged(this);
}

void AbsPropertyManagerPrivate::propertyDestroyed(Property* property)
{
    if (m_properties.contains(property)) 
    {
        emit q_ptr->propertyDestroyed(property);
        q_ptr->uninitializeProperty(property);
        m_properties.remove(property);
    }
}

void AbsPropertyManagerPrivate::propertyChanged(Property *property) const
{
    emit q_ptr->propertyChanged(property);
}

void AbsPropertyManagerPrivate::propertyRemoved(Property *property,
            Property *parentProperty) const
{
    emit q_ptr->propertyRemoved(property, parentProperty);
}

void AbsPropertyManagerPrivate::propertyInserted(Property *property,
            Property *parentProperty, Property *afterProperty) const
{
    emit q_ptr->propertyInserted(property, parentProperty, afterProperty);
}

/* AbsPropertyManager */
AbsPropertyManager::AbsPropertyManager(QObject *parent)
    : QObject(parent), d_ptr(new AbsPropertyManagerPrivate)
{
    d_ptr->q_ptr = this;

}

AbsPropertyManager::~AbsPropertyManager()
{
    clear();
}

void AbsPropertyManager::clear() const
{
    while (!d_ptr->m_properties.isEmpty())
        delete *d_ptr->m_properties.cbegin();
}

QSet<Property *> AbsPropertyManager::properties() const
{ return d_ptr->m_properties; }

// ---
Property* AbsPropertyManager::property(const Id& id)
{
    for (auto it : d_ptr->m_properties)
    {
        if (it->propertyId() == id)
            return it;
    }
    return nullptr;
}

bool AbsPropertyManager::hasValue(const Property* property) const
{
    Q_UNUSED(property);
    return true;
}

QIcon AbsPropertyManager::valueIcon(const Property* property) const
{
    Q_UNUSED(property);
    return QIcon();
}

QString AbsPropertyManager::valueText(const Property* property) const
{
    Q_UNUSED(property);
    return QString();
}

Property* AbsPropertyManager::addProperty(const QString& name, const Id& id)
{
    Property* property = createProperty(id);
    if (property != nullptr) 
    {
        property->setPropertyId(id);
        property->setPropertyName(name);
        d_ptr->m_properties.insert(property);
        initializeProperty(property);
    }
    return property;
}

Property* AbsPropertyManager::createProperty(const Id& id)
{
     return new Property(this, id);
}

void AbsPropertyManager::uninitializeProperty(Property* property)
{
   Q_UNUSED(property);
}

/* BrowserItemPrivate */
class BrowserItemPrivate
{
public:
    BrowserItemPrivate(AbsPropBrowser* browser, Property* property, BrowserItem* parent)
        : m_browser(browser), m_property(property), m_parent(parent), q_ptr(0) {}
public:
    void addChild(BrowserItem* index, BrowserItem* after);
    void removeChild(BrowserItem* index);
public:
    AbsPropBrowser* const m_browser;
    Property* m_property;
    BrowserItem* m_parent;
    BrowserItem* q_ptr;
    QList<BrowserItem*> m_children;
};

void BrowserItemPrivate::addChild(BrowserItem* index, BrowserItem* after)
{
    if (m_children.contains(index))
        return;
    int idx = m_children.indexOf(after) + 1;
    m_children.insert(idx, index);
}

void BrowserItemPrivate::removeChild(BrowserItem* index)
{
    m_children.removeAll(index);
}


Property* BrowserItem::property() const
{
    return d_ptr->m_property;
}

BrowserItem *BrowserItem::parent() const
{
    return d_ptr->m_parent;
}

QList<BrowserItem *> BrowserItem::children() const
{
    return d_ptr->m_children;
}

AbsPropBrowser* BrowserItem::browser() const
{
    return d_ptr->m_browser;
}

/* BrowserItem */
BrowserItem::BrowserItem(AbsPropBrowser *browser, Property *property, BrowserItem *parent)
    : d_ptr(new BrowserItemPrivate(browser, property, parent))
{
    d_ptr->q_ptr = this;
}

BrowserItem::~BrowserItem()
{
}


/* AbsPropBrowserPrivate */
class AbsPropBrowserPrivate
{
    AbsPropBrowser* q_ptr;
    VSN_DECLARE_PUBLIC(AbsPropBrowser);
public:
    AbsPropBrowserPrivate();
public:
    void insertSubTree(Property* property, Property* parentProperty);
    void removeSubTree(Property* property, Property* parentProperty);
    void createBrowserIndexes(Property* property, Property* parentProperty, Property* afterProperty);
    void removeBrowserIndexes(Property* property, Property* parentProperty);
    BrowserItem *createBrowserIndex(Property* property, BrowserItem* parentIndex, BrowserItem* afterIndex);
    void removeBrowserIndex(BrowserItem* index);
    void clearIndex(BrowserItem* index);

    void slotPropertyInserted(Property* property, Property* parentProperty, Property* afterProperty);
    void slotPropertyRemoved(Property* property, Property* parentProperty);
    void slotPropertyDestroyed(Property* property);
    void slotPropertyDataChanged(Property* property);

    QList<Property*> m_subItems;
    QMap<AbsPropertyManager*, QList<Property*> > m_managerToProperties;
    QMap<Property*, QList<Property*> > m_propertyToParents;

    QMap<Property*, BrowserItem*> m_topLevelPropertyToIndex;
    QList<BrowserItem*> m_topLevelIndexes;
    QMap<Property*, QList<BrowserItem*> > m_propertyToIndexes;

    BrowserItem* m_currentItem;
};

AbsPropBrowserPrivate::AbsPropBrowserPrivate() 
    : m_currentItem(0)
{
}

void AbsPropBrowserPrivate::insertSubTree(Property* property, Property* parentProperty)
{
    if (m_propertyToParents.contains(property)) 
    {
        m_propertyToParents[property].append(parentProperty);
        return;
    }
    AbsPropertyManager *manager = property->propertyManager();
    if (m_managerToProperties[manager].isEmpty()) 
    {
        q_ptr->connect(manager, SIGNAL(propertyInserted(Property *, Property *, Property *)), q_ptr, SLOT(slotPropertyInserted(Property *, Property *, Property *)));
        q_ptr->connect(manager, SIGNAL(propertyRemoved(Property *, Property *)), q_ptr, SLOT(slotPropertyRemoved(Property*,Property*)));
        q_ptr->connect(manager, SIGNAL(propertyDestroyed(Property*)), q_ptr, SLOT(slotPropertyDestroyed(Property*)));
        q_ptr->connect(manager, SIGNAL(propertyChanged(Property*)), q_ptr, SLOT(slotPropertyDataChanged(Property*)));
    }
    m_managerToProperties[manager].append(property);
    m_propertyToParents[property].append(parentProperty);

    const auto subList = property->subProperties();
    for (Property *subProperty : subList)
        insertSubTree(subProperty, property);
}

void AbsPropBrowserPrivate::removeSubTree(Property* property, Property* parentProperty)
{
    if (!m_propertyToParents.contains(property)) 
    {
        // ASSERT
        return;
    }

    m_propertyToParents[property].removeAll(parentProperty);
    if (!m_propertyToParents[property].isEmpty())
        return;

    m_propertyToParents.remove(property);
    AbsPropertyManager *manager = property->propertyManager();
    m_managerToProperties[manager].removeAll(property);
    if (m_managerToProperties[manager].isEmpty()) 
    {
        q_ptr->disconnect(manager, SIGNAL(propertyInserted(Property *, Property *, Property *)), q_ptr, SLOT(slotPropertyInserted(Property *, Property *, Property *)));
        q_ptr->disconnect(manager, SIGNAL(propertyRemoved(Property *, Property *)), q_ptr, SLOT(slotPropertyRemoved(Property*,Property*)));
        q_ptr->disconnect(manager, SIGNAL(propertyDestroyed(Property*)), q_ptr, SLOT(slotPropertyDestroyed(Property*)));
        q_ptr->disconnect(manager, SIGNAL(propertyChanged(Property*)), q_ptr, SLOT(slotPropertyDataChanged(Property*)));
        m_managerToProperties.remove(manager);
    }

    const auto subList = property->subProperties();
    for (Property *subProperty : subList)
        removeSubTree(subProperty, property);
}

void AbsPropBrowserPrivate::createBrowserIndexes(Property* property, Property* parentProperty, Property* afterProperty)
{
    QMap<BrowserItem *, BrowserItem *> parentToAfter;
    if (afterProperty) {
        const auto it = m_propertyToIndexes.constFind(afterProperty);
        if (it == m_propertyToIndexes.constEnd())
            return;

        for (BrowserItem *idx : it.value()) {
            BrowserItem *parentIdx = idx->parent();
            if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
                parentToAfter[idx->parent()] = idx;
        }
    } else if (parentProperty) {
        const auto it = m_propertyToIndexes.find(parentProperty);
        if (it == m_propertyToIndexes.constEnd())
            return;

        for (BrowserItem *idx : it.value())
            parentToAfter[idx] = 0;
    } else {
        parentToAfter[0] = 0;
    }

    const QMap<BrowserItem *, BrowserItem *>::ConstIterator pcend = parentToAfter.constEnd();
    for (QMap<BrowserItem *, BrowserItem *>::ConstIterator it = parentToAfter.constBegin(); it != pcend; ++it)
        createBrowserIndex(property, it.key(), it.value());
}

BrowserItem* AbsPropBrowserPrivate::createBrowserIndex(Property* property,
        BrowserItem* parentIndex, BrowserItem* afterIndex)
{
    BrowserItem *newIndex = new BrowserItem(q_ptr, property, parentIndex);
    if (parentIndex) {
        parentIndex->d_ptr->addChild(newIndex, afterIndex);
    } else {
        m_topLevelPropertyToIndex[property] = newIndex;
        m_topLevelIndexes.insert(m_topLevelIndexes.indexOf(afterIndex) + 1, newIndex);
    }
    m_propertyToIndexes[property].append(newIndex);

    q_ptr->itemInserted(newIndex, afterIndex);

    const auto subItems = property->subProperties();
    BrowserItem* afterChild = 0;
    for (Property* child : subItems)
        afterChild = createBrowserIndex(child, newIndex, afterChild);
    return newIndex;
}

void AbsPropBrowserPrivate::removeBrowserIndexes(Property* property, Property* parentProperty)
{
    QList<BrowserItem *> toRemove;
    const auto it = m_propertyToIndexes.constFind(property);
    if (it == m_propertyToIndexes.constEnd())
        return;

    for (BrowserItem *idx : it.value()) 
    {
        BrowserItem *parentIdx = idx->parent();
        if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
            toRemove.append(idx);
    }

    for (BrowserItem *index : qAsConst(toRemove))
        removeBrowserIndex(index);
}

void AbsPropBrowserPrivate::removeBrowserIndex(BrowserItem* index)
{
    const auto children = index->children();
    for (int i = children.count(); i > 0; i--) {
        removeBrowserIndex(children.at(i - 1));
    }

    q_ptr->itemRemoved(index);

    if (index->parent()) 
    {
        index->parent()->d_ptr->removeChild(index);
    } 
    else 
    {
        m_topLevelPropertyToIndex.remove(index->property());
        m_topLevelIndexes.removeAll(index);
    }

    Property* property = index->property();

    m_propertyToIndexes[property].removeAll(index);
    if (m_propertyToIndexes[property].isEmpty())
        m_propertyToIndexes.remove(property);

    delete index;
}

void AbsPropBrowserPrivate::clearIndex(BrowserItem *index)
{
    const auto children = index->children();
    for (BrowserItem *item : children)
        clearIndex(item);
    delete index;
}

void AbsPropBrowserPrivate::slotPropertyInserted(Property* property, Property* parentProperty, Property* afterProperty)
{
    if (!m_propertyToParents.contains(parentProperty))
        return;
    createBrowserIndexes(property, parentProperty, afterProperty);
    insertSubTree(property, parentProperty);
    //q_ptr->propertyInserted(property, parentProperty, afterProperty);
}

void AbsPropBrowserPrivate::slotPropertyRemoved(Property* property, Property* parentProperty)
{
    if (!m_propertyToParents.contains(parentProperty))
        return;
    removeSubTree(property, parentProperty); // this line should be probably moved down after propertyRemoved call
    //q_ptr->propertyRemoved(property, parentProperty);
    removeBrowserIndexes(property, parentProperty);
}

void AbsPropBrowserPrivate::slotPropertyDestroyed(Property* property)
{
    if (!m_subItems.contains(property))
        return;
    q_ptr->removeProperty(property);
}

void AbsPropBrowserPrivate::slotPropertyDataChanged(Property* property)
{
    if (!m_propertyToParents.contains(property))
        return;

    const auto it = m_propertyToIndexes.constFind(property);
    if (it == m_propertyToIndexes.constEnd())
        return;

    const auto indexes = it.value();
    for (BrowserItem *idx : indexes)
        q_ptr->itemChanged(idx);
    //q_ptr->propertyChanged(property);
}

/* AbsPropBrowser */
AbsPropBrowser::AbsPropBrowser(QWidget* parent)
    : QWidget(parent), d_ptr(new AbsPropBrowserPrivate)
{
    d_ptr->q_ptr = this;
}

AbsPropBrowser::~AbsPropBrowser()
{
    const auto indexes = topLevelItems();
    for (BrowserItem *item : indexes)
        d_ptr->clearIndex(item);
}

QList<Property *> AbsPropBrowser::properties() const
{
    return d_ptr->m_subItems;
}

QList<BrowserItem *> AbsPropBrowser::items(Property *property) const
{
    return d_ptr->m_propertyToIndexes.value(property);
}

BrowserItem *AbsPropBrowser::topLevelItem(Property *property) const
{
    return d_ptr->m_topLevelPropertyToIndex.value(property);
}

QList<BrowserItem *> AbsPropBrowser::topLevelItems() const
{
    return d_ptr->m_topLevelIndexes;
}

void AbsPropBrowser::clear()
{
    const auto subList = properties();
    for (auto rit = subList.crbegin(), rend = subList.crend(); rit != rend; ++rit)
        removeProperty(*rit);
}

BrowserItem* AbsPropBrowser::addProperty(Property* property)
{
    Property* afterProperty = 0;
    if (d_ptr->m_subItems.count() > 0)
        afterProperty = d_ptr->m_subItems.last();
    return insertProperty(property, afterProperty);
}

BrowserItem* AbsPropBrowser::insertProperty(Property* property, Property* afterProperty)
{
    if (!property)
        return nullptr;
    auto pendingList = properties();
    int pos = 0;
    int newPos = 0;
    while (pos < pendingList.count()) {
        Property *prop = pendingList.at(pos);
        if (prop == property)
            return nullptr;
        if (prop == afterProperty) {
            newPos = pos + 1;
        }
        pos++;
    }
    d_ptr->createBrowserIndexes(property, 0, afterProperty);
    d_ptr->insertSubTree(property, 0);
    d_ptr->m_subItems.insert(newPos, property);
    return topLevelItem(property);
}

void AbsPropBrowser::removeProperty(Property* property)
{
    if (!property)
        return;
    auto pendingList = properties();
    int pos = 0;
    while (pos < pendingList.count()) 
    {
        if (pendingList.at(pos) == property) 
        {
            d_ptr->m_subItems.removeAt(pos);
            d_ptr->removeSubTree(property, 0);
            //propertyRemoved(property, 0);
            d_ptr->removeBrowserIndexes(property, 0);
            return;
        }
        pos++;
    }
}

QWidget* AbsPropBrowser::createEditor(Property* property, QWidget* parent)
{
    AbsEditorFactoryBase* factory = nullptr;
    AbsPropertyManager* manager = property->propertyManager();

    if (m_viewToManagerToFactory()->contains(this) &&
        (*m_viewToManagerToFactory())[this].contains(manager)) 
        factory = (*m_viewToManagerToFactory())[this][manager];

    if (!factory)
        return nullptr;

    QWidget* w = factory->createEditor(property, parent);
    if (w)
        w->setFocusPolicy(Qt::WheelFocus);
    return w;
}

bool AbsPropBrowser::addFactory(AbsPropertyManager* abstractManager, AbsEditorFactoryBase* abstractFactory)
{
    bool connectNeeded = false;
    if (!m_managerToFactoryToViews()->contains(abstractManager) || 
        !(*m_managerToFactoryToViews())[abstractManager].contains(abstractFactory)) 
        connectNeeded = true;
    else if ((*m_managerToFactoryToViews())[abstractManager][abstractFactory].contains(this)) 
        return connectNeeded;

    if (m_viewToManagerToFactory()->contains(this) && (*m_viewToManagerToFactory())[this].contains(abstractManager)) 
        unsetFactoryForManager(abstractManager);

    (*m_managerToFactoryToViews())[abstractManager][abstractFactory].append(this);
    (*m_viewToManagerToFactory())[this][abstractManager] = abstractFactory;

    return connectNeeded;
}

void AbsPropBrowser::slotPropertyInserted(Property* property, Property* parentProperty, Property* afterProperty)
{
    d_ptr->slotPropertyInserted(property, parentProperty, afterProperty);
}

void AbsPropBrowser::slotPropertyRemoved(Property* property, Property* parentProperty)
{
    d_ptr->slotPropertyRemoved(property, parentProperty);
}

void AbsPropBrowser::slotPropertyDestroyed(Property* property)
{
    d_ptr->slotPropertyDestroyed(property);
}

void AbsPropBrowser::slotPropertyDataChanged(Property* property)
{
    d_ptr->slotPropertyDataChanged(property);
}

void AbsPropBrowser::unsetFactoryForManager(AbsPropertyManager *manager)
{
    if (!m_viewToManagerToFactory()->contains(this) ||
        !(*m_viewToManagerToFactory())[this].contains(manager))
    {
        return;
    }
    AbsEditorFactoryBase* abstractFactory = (*m_viewToManagerToFactory())[this][manager];
    (*m_viewToManagerToFactory())[this].remove(manager);

    if ((*m_viewToManagerToFactory())[this].isEmpty()) 
        (*m_viewToManagerToFactory()).remove(this);

    (*m_managerToFactoryToViews())[manager][abstractFactory].removeAll(this);
    if ((*m_managerToFactoryToViews())[manager][abstractFactory].isEmpty()) 
    {
        (*m_managerToFactoryToViews())[manager].remove(abstractFactory);
        abstractFactory->breakConnection(manager);
        if ((*m_managerToFactoryToViews())[manager].isEmpty())
            (*m_managerToFactoryToViews()).remove(manager);
    }
}

BrowserItem* AbsPropBrowser::currentItem() const
{ return d_ptr->m_currentItem; }

void AbsPropBrowser::setCurrentItem(BrowserItem *item)
{
    BrowserItem* oldItem = d_ptr->m_currentItem;
    d_ptr->m_currentItem = item;
    if (oldItem != item)
        emit currentItemChanged(item);
}

} // namespace QtVision
} // namespace VSN


