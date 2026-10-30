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

#ifndef __QT_IOPTIONSPAGE_H
#define __QT_IOPTIONSPAGE_H

#include <qt_icon.h>
#include <qt_id.h>
#include <qt_global.h>

#include <QObject>
#include <QPointer>
#include <QStringList>
#include <QWidget>
#include <functional>


namespace VSN {
namespace QtVision {

class FilePath;
class AspectContainer;

/*IOptionsPageWidget */
class IOptionsPageWidget : public QWidget
{
    Q_OBJECT
public:
    virtual void apply() = 0;
    virtual void finish() {}
};

/* IOptionsPage */
class IOptionsPage : public QObject
{
    Q_OBJECT
public:
    IOptionsPage(QObject* parent = nullptr, bool registerGlobally = true);
    ~IOptionsPage() override;
public:
    static const QList<IOptionsPage*> allOptionsPages();

    Id id() const { return m_id; }
    QString displayName() const { return m_displayName; }
    Id category() const { return m_category; }
    QString displayCategory() const { return m_displayCategory; }
    QIcon categoryIcon() const;

    using WidgetCreator = std::function<IOptionsPageWidget*()>;
    void setWidgetCreator(const WidgetCreator& widgetCreator);

    virtual bool matches(const QRegularExpression& regexp) const;
    virtual QWidget* widget();
    virtual void apply();
    virtual void finish();
protected:
    void setId(Id id) { m_id = id; }
    void setDisplayName(const QString &displayName) { m_displayName = displayName; }
    void setCategory(Id category) { m_category = category; }
    void setDisplayCategory(const QString &displayCategory) { m_displayCategory = displayCategory; }
    void setCategoryIcon(const Icon& categoryIcon) { m_categoryIcon = categoryIcon; }
    void setCategoryIconPath(const FilePath& categoryIconPath);
    void setSettings(AspectContainer *settings);
    void setLayouter(const std::function<void(QWidget *w)> &layouter);
    // Used in FontSettingsPage. FIXME?
    QPointer<QWidget> m_widget; // Used in conjunction with m_widgetCreator
private:
    Id m_id;
    Id m_category;
    QString m_displayName;
    QString m_displayCategory;
    Icon m_categoryIcon;
    WidgetCreator m_widgetCreator;

    mutable bool m_keywordsInitialized = false;
    mutable QStringList m_keywords;

    AspectContainer* m_settings = nullptr;
    std::function<void(QWidget* w)> m_layouter;
};

/*
    Alternative way for providing option pages instead of adding IOptionsPage
    objects into the plugin manager pool. Should only be used if creation of the
    actual option pages is not possible or too expensive at Qt Vision startup.
    (Like the designer integration, which needs to initialize designer plugins
    before the options pages get available.)
*/
class IOptionsPageProvider : public QObject
{
    Q_OBJECT
public:
    IOptionsPageProvider(QObject* parent = nullptr);
    ~IOptionsPageProvider() override;
public:
    static const QList<IOptionsPageProvider*> allOptionsPagesProviders();

    Id category() const { return m_category; }
    QString displayCategory() const { return m_displayCategory; }
    QIcon categoryIcon() const;

    virtual QList<IOptionsPage*> pages() const = 0;
    virtual bool matches(const QRegularExpression &regexp) const = 0;
protected:
    void setCategory(Id category) { m_category = category; }
    void setDisplayCategory(const QString& displayCategory) { m_displayCategory = displayCategory; }
    void setCategoryIcon(const Icon& categoryIcon) { m_categoryIcon = categoryIcon; }

    Id m_category;
    QString m_displayCategory;
    Icon m_categoryIcon;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_IOPTIONSPAGE_H */
