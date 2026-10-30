#ifndef __VSN_BUTTONPROPERTYBROWSER_H
#define __VSN_BUTTONPROPERTYBROWSER_H

#include <qt_propertybrowser.h>
#include <vsn_global.h>

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate how to use the Vision kernel
               with Qt library and its classes. This header file can be changed from a version to a version with
               no warning or completely deleted.\~
*/

namespace VSN {
namespace QtVision {

class ButtonPropBrowserPrivate;
/* ButtonPropBrowser */
class ButtonPropBrowser : public AbsPropBrowser
{
    Q_OBJECT
public:
    ButtonPropBrowser(QWidget* parent = 0);
    ~ButtonPropBrowser();
public:
    void setExpanded(BrowserItem* item, bool expanded);
    bool isExpanded(BrowserItem* item) const;
Q_SIGNALS:
    void collapsed(BrowserItem* item);
    void expanded(BrowserItem* item);
protected:
    virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem);
    virtual void itemRemoved(BrowserItem* item);
    virtual void itemChanged(BrowserItem* item);
private Q_SLOTS:
    void slotUpdate();
    void slotEditorDestroyed();
    void slotToggled(bool);
private:    
    QScopedPointer<ButtonPropBrowserPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(ButtonPropBrowser);
    VSN_DISABLE_COPY(ButtonPropBrowser);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_BUTTONPROPERTYBROWSER_H */
