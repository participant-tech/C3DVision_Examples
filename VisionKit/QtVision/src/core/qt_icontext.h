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

#ifndef __QT_CONTEXT_H
#define __QT_CONTEXT_H

#include <qt_id.h>

#include <QList>
#include <QObject>
#include <QPointer>
#include <QWidget>

#include <functional>

namespace VSN {
namespace QtVision {

/* Context */
class Context
{
public:
    Context();
public:
    explicit Context(Id c1) { add(c1); }
    Context(Id c1, Id c2) { add(c1); add(c2); }
    Context(Id c1, Id c2, Id c3) { add(c1); add(c2); add(c3); }
    bool contains(Id c) const { return d.contains(c); }
    int size() const { return d.size(); }
    bool isEmpty() const { return d.isEmpty(); }
    Id at(int i) const { return d.at(i); }

    // FIXME: Make interface slimmer.
    using const_iterator = QList<Id>::const_iterator;
    const_iterator begin() const { return d.begin(); }
    const_iterator end() const { return d.end(); }
    int indexOf(Id c) const { return d.indexOf(c); }
    void removeAt(int i) { d.removeAt(i); }
    void prepend(Id c) { d.prepend(c); }
    void add(const Context &c) { d += c.d; }
    void add(Id c) { d.append(c); }
    bool operator==(const Context &c) const { return d == c.d; }
private:
    QList<Id> d;
};

/* IContext */
class IContext : public QObject
{
    Q_OBJECT
public:
    IContext(QObject* parent = nullptr) : QObject(parent) {}
public:
    virtual Context context() const { return m_context; }
    virtual QWidget* widget() const { return m_widget; }
//    using HelpCallback = std::function<void(const HelpItem &item)>;
//    virtual void contextHelp(const HelpCallback &callback) const { callback(m_contextHelp); }

    virtual void setContext(const Context& context) { m_context = context; }
    virtual void setWidget(QWidget* widget) { m_widget = widget; }
//    virtual void setContextHelp(const HelpItem &id) { m_contextHelp = id; }

    friend QDebug operator<<(QDebug debug, const QtVision::Context& context);
protected:
    Context m_context;
    QPointer<QWidget> m_widget;
//    HelpItem m_contextHelp;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_CONTEXT_H */
