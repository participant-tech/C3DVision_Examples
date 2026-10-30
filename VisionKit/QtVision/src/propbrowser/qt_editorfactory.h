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

#ifndef __VSN_EDITORFACTORY_H
#define __VSN_EDITORFACTORY_H

#include <qt_propertymanager.h>
#include <vsn_global.h>

namespace VSN {
namespace QtVision {

class SpinBoxFactoryPrivate;
/* SpinBoxFactory */
class SpinBoxFactory : public AbsEditorFactory<IntPropManager>
{
    Q_OBJECT
public:
    SpinBoxFactory(QObject* parent = nullptr);
    ~SpinBoxFactory();
protected:
    void connectPropertyManager(IntPropManager* manager);
    QWidget* createEditor(IntPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(IntPropManager *manager);
private Q_SLOTS:
    // TODO Q_PRIVATE_SLOT
    void slotPropertyChanged(Property*, int);
    void slotRangeChanged(Property*, int, int);
    void slotSingleStepChanged(Property*, int);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<SpinBoxFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(SpinBoxFactory);
    VSN_DISABLE_COPY(SpinBoxFactory);
};

class SliderFactoryPrivate;
/* SliderFactory */
class SliderFactory : public AbsEditorFactory<IntPropManager>
{
    Q_OBJECT
public:
    SliderFactory(QObject* parent = nullptr);
    ~SliderFactory();
protected:
    void connectPropertyManager(IntPropManager* manager);
    QWidget* createEditor(IntPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(IntPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, int);
    void slotRangeChanged(Property*, int, int);
    void slotSingleStepChanged(Property*, int);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<SliderFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(SliderFactory);
    VSN_DISABLE_COPY(SliderFactory);
};

class ScrollBarFactoryPrivate;
/* ScrollBarFactory */
class ScrollBarFactory : public AbsEditorFactory<IntPropManager>
{
    Q_OBJECT
public:
    ScrollBarFactory(QObject* parent = nullptr);
    ~ScrollBarFactory();
protected:
    void connectPropertyManager(IntPropManager *manager);
    QWidget* createEditor(IntPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(IntPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, int);
    void slotRangeChanged(Property*, int, int);
    void slotSingleStepChanged(Property*, int);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<ScrollBarFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(ScrollBarFactory);
    VSN_DISABLE_COPY(ScrollBarFactory);
};

class CheckBoxFactoryPrivate;
/* CheckBoxFactory */
class CheckBoxFactory : public AbsEditorFactory<BoolPropManager>
{
    Q_OBJECT
public:
    CheckBoxFactory(QObject* parent = nullptr);
    ~CheckBoxFactory();
protected:
    void connectPropertyManager(BoolPropManager* manager);
    QWidget* createEditor(BoolPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(BoolPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, bool);
    void slotSetValue(bool);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<CheckBoxFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(CheckBoxFactory);
    VSN_DISABLE_COPY(CheckBoxFactory);
};

class DoubleSpinBoxFactoryPrivate;
/* DoubleSpinBoxFactory */
class DoubleSpinBoxFactory : public AbsEditorFactory<DoublePropManager>
{
    Q_OBJECT
public:
    DoubleSpinBoxFactory(QObject* parent = nullptr);
    ~DoubleSpinBoxFactory();
protected:
    void connectPropertyManager(DoublePropManager* manager);
    QWidget* createEditor(DoublePropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(DoublePropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, double);
    void slotRangeChanged(Property*, double, double);
    void slotSingleStepChanged(Property*, double);
    void slotDecimalsChanged(Property*, int);
    void slotSetValue(double);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<DoubleSpinBoxFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DoubleSpinBoxFactory);
    VSN_DISABLE_COPY(DoubleSpinBoxFactory);
};

class LineEditFactoryPrivate;
/* LineEditFactory */
class LineEditFactory : public AbsEditorFactory<StringPropManager>
{
    Q_OBJECT
public:
    LineEditFactory(QObject* parent = nullptr);
    ~LineEditFactory();
protected:
    void connectPropertyManager(StringPropManager* manager);
    QWidget* createEditor(StringPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(StringPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QString&);
    void slotRegExpChanged(Property*, const QRegularExpression&);
    void slotSetValue(const QString&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<LineEditFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(LineEditFactory);
    VSN_DISABLE_COPY(LineEditFactory);
};

class DateEditFactoryPrivate;
/* DateEditFactory */
class DateEditFactory : public AbsEditorFactory<DatePropManager>
{
    Q_OBJECT
public:
    DateEditFactory(QObject* parent = nullptr);
    ~DateEditFactory();
protected:
    void connectPropertyManager(DatePropManager* manager);
    QWidget* createEditor(DatePropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(DatePropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QDate&);
    void slotRangeChanged(Property*, const QDate&, const QDate&);
    void slotSetValue(const QDate&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<DateEditFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DateEditFactory);
    VSN_DISABLE_COPY(DateEditFactory);
};

class TimeEditFactoryPrivate;
/* TimeEditFactory */
class TimeEditFactory : public AbsEditorFactory<TimePropManager>
{
    Q_OBJECT
public:
    TimeEditFactory(QObject* parent = nullptr);
    ~TimeEditFactory();
protected:
    void connectPropertyManager(TimePropManager* manager);
    QWidget* createEditor(TimePropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(TimePropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QTime&);
    void slotSetValue(const QTime&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<TimeEditFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(TimeEditFactory);
    VSN_DISABLE_COPY(TimeEditFactory);
};

class DateTimeEditFactoryPrivate;
/* DateTimeEditFactory */
class DateTimeEditFactory : public AbsEditorFactory<DateTimePropManager>
{
    Q_OBJECT
public:
    DateTimeEditFactory(QObject* parent = nullptr);
    ~DateTimeEditFactory();
protected:
    void connectPropertyManager(DateTimePropManager* manager);
    QWidget* createEditor(DateTimePropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(DateTimePropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QDateTime&);
    void slotSetValue(const QDateTime&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<DateTimeEditFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(DateTimeEditFactory);
    VSN_DISABLE_COPY(DateTimeEditFactory);
};

class KeySequenceEditorFactoryPrivate;
/* KeySequenceEditorFactory */
class KeySequenceEditorFactory : public AbsEditorFactory<KeySequencePropManager>
{
    Q_OBJECT
public:
    KeySequenceEditorFactory(QObject* parent = nullptr);
    ~KeySequenceEditorFactory();
protected:
    void connectPropertyManager(KeySequencePropManager* manager);
    QWidget* createEditor(KeySequencePropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(KeySequencePropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QKeySequence&);
    void slotSetValue(const QKeySequence&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<KeySequenceEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(KeySequenceEditorFactory);
    VSN_DISABLE_COPY(KeySequenceEditorFactory);
};

class CharEditorFactoryPrivate;
/* CharEditorFactory */
class CharEditorFactory : public AbsEditorFactory<CharPropManager>
{
    Q_OBJECT
public:
    CharEditorFactory(QObject* parent = nullptr);
    ~CharEditorFactory();
protected:
    void connectPropertyManager(CharPropManager* manager);
    QWidget* createEditor(CharPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(CharPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QChar&);
    void slotSetValue(const QChar&);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<CharEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(CharEditorFactory);
    VSN_DISABLE_COPY(CharEditorFactory);
};

class EnumEditorFactoryPrivate;
/* EnumEditorFactory */
class EnumEditorFactory : public AbsEditorFactory<EnumPropManager>
{
    Q_OBJECT
public:
    EnumEditorFactory(QObject* parent = nullptr);
    ~EnumEditorFactory();
protected:
    void connectPropertyManager(EnumPropManager* manager);
    QWidget* createEditor(EnumPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(EnumPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, int);
    void slotEnumNamesChanged(Property*, const QStringList&);
    void slotEnumIconsChanged(Property*, const QMap<int, QIcon>&);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<EnumEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(EnumEditorFactory);
    VSN_DISABLE_COPY(EnumEditorFactory);
};

class CursorEditorFactoryPrivate;
/* CursorEditorFactory */
class CursorEditorFactory : public AbsEditorFactory<CursorPropManager>
{
    Q_OBJECT
public:
    CursorEditorFactory(QObject* parent = nullptr);
    ~CursorEditorFactory();
protected:
    void connectPropertyManager(CursorPropManager* manager);
    QWidget* createEditor(CursorPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(CursorPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property*, const QCursor&);
    void slotEnumChanged(Property*, int);
    void slotEditorDestroyed(QObject*);
private:
    QScopedPointer<CursorEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(CursorEditorFactory);
    VSN_DISABLE_COPY(CursorEditorFactory);
};

class ColorEditorFactoryPrivate;
/* ColorEditorFactory */
class ColorEditorFactory : public AbsEditorFactory<ColorPropManager>
{
    Q_OBJECT
public:
    ColorEditorFactory(QObject* parent = nullptr);
    ~ColorEditorFactory();
protected:
    void connectPropertyManager(ColorPropManager* manager);
    QWidget* createEditor(ColorPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(ColorPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property* property, const QColor& value);
    void slotEditorDestroyed(QObject* object);
    void slotSetValue(const QColor& value);
private:
    QScopedPointer<ColorEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(ColorEditorFactory);
    VSN_DISABLE_COPY(ColorEditorFactory);
};

class FontEditorFactoryPrivate;
/* FontEditorFactory */
class FontEditorFactory : public AbsEditorFactory<FontPropManager>
{
    Q_OBJECT
public:
    FontEditorFactory(QObject* parent = nullptr);
    ~FontEditorFactory();
protected:
    void connectPropertyManager(FontPropManager* manager);
    QWidget* createEditor(FontPropManager* manager, Property* property, QWidget* parent);
    void disconnectPropertyManager(FontPropManager* manager);
private Q_SLOTS:
    void slotPropertyChanged(Property* property, const QFont& value);
    void slotEditorDestroyed(QObject* object);
    void slotSetValue(const QFont& value);
private:
    QScopedPointer<FontEditorFactoryPrivate> d_ptr;
    VSN_DECLARE_PRIVATE(FontEditorFactory);
    VSN_DISABLE_COPY(FontEditorFactory);
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_EDITORFACTORY_H */
