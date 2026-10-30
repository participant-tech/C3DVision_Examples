#ifndef __VSN_GROUPBOXPROPERTYBROWSER_H
#define __VSN_GROUPBOXPROPERTYBROWSER_H

#include <qt_propertybrowser.h>
#include <vsn_global.h>
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

class GroupBoxPropBrowserPrivate;
/* GroupBoxPropBrowser */
class QT_CLASS GroupBoxPropBrowser : public AbsPropBrowser
{
    Q_OBJECT
public:
    GroupBoxPropBrowser(QWidget *parent = 0);
    ~GroupBoxPropBrowser();
protected:
    void itemInserted(BrowserItem* item, BrowserItem* afterItem) override;
    void itemRemoved(BrowserItem* item) override;
    void itemChanged(BrowserItem* item) override;
private Q_SLOTS:
    void slotUpdate();
    void slotEditorDestroyed();
private:
    QScopedPointer<GroupBoxPropBrowserPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(GroupBoxPropBrowser);
    VSN_DISABLE_COPY(GroupBoxPropBrowser);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_GROUPBOXPROPERTYBROWSER_H */
