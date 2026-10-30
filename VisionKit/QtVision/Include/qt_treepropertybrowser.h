#ifndef __VSN_TREEPROPERTYBROWSER_H
#define __VSN_TREEPROPERTYBROWSER_H

#include <qt_propertybrowser.h>
#include <qt_global.h>


/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate how to use the Vision kernel
               with Qt library and its classes. This header file can be changed from a version to a version with
               no warning or completely deleted.\~
*/

class QTreeWidgetItem;

namespace VSN {
namespace QtVision {

class TreePropBrowserPrivate;
/* TreePropBrowser */
class QT_CLASS TreePropBrowser : public AbsPropBrowser
{
    Q_OBJECT
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
    Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
    Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)
public:
    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents
    };
    Q_ENUM(ResizeMode)
public:
    TreePropBrowser(QWidget *parent = nullptr);
    ~TreePropBrowser();
public:
    int indentation() const;
    void setIndentation(int i);

    bool rootIsDecorated() const;
    void setRootIsDecorated(bool show);

    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool enable);

    bool isHeaderVisible() const;
    void setHeaderVisible(bool visible);

    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode mode);

    int splitterPosition() const;
    void setSplitterPosition(int position);

    void setExpanded(BrowserItem* item, bool expanded);
    bool isExpanded(BrowserItem* item) const;

    bool isItemVisible(BrowserItem* item) const;
    void setItemVisible(BrowserItem* item, bool visible);

    void setBackgroundColor(BrowserItem* item, const QColor& color);
    QColor backgroundColor(BrowserItem* item) const;
    QColor calculatedBackgroundColor(BrowserItem *item) const;

    void setPropertiesWithoutValueMarked(bool mark);
    bool propertiesWithoutValueMarked() const;

    void editItem(BrowserItem* item);
Q_SIGNALS:
    void collapsed(BrowserItem* item);
    void expanded(BrowserItem* item);
protected:
    void itemInserted(BrowserItem* item, BrowserItem* afterItem) override;
    void itemRemoved(BrowserItem* item) override;
    void itemChanged(BrowserItem* item) override;
private Q_SLOTS:
    // TODO Q_PRIVATE_SLOT
    void slotCollapsed(const QModelIndex&);
    void slotExpanded(const QModelIndex&);
    void slotCurrentBrowserItemChanged(BrowserItem*);
    void slotCurrentTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);
private:
    QScopedPointer<TreePropBrowserPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(TreePropBrowser);
    VSN_DISABLE_COPY(TreePropBrowser);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_TREEPROPERTYBROWSER_H */
