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

#include <qt_editorfactory.h>
#include <qt_propertybrowserutilsprivate.h>
#include <qt_editorfactoryprivate.h>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenu>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QKeySequenceEdit>
#include <QtCore/QMap>

// Q_GLOBAL_STATIC must be before #include <vsn_last.h> because the operator is overridden
Q_GLOBAL_STATIC(QtVision::CursorDatabase, cursorDatabase)

#include <vsn_last.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

namespace VSN {
namespace QtVision {

// ---
static inline void setupTreeViewEditorMargin(QLayout *lt)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        lt->setContentsMargins(DecorationMargin, 0, 0, 0);
    else
        lt->setContentsMargins(0, 0, DecorationMargin, 0);
}

// ---
static inline int calcTotalHeightHint(QWidget* parent)
{
    int height = 0;
    QSpinBox spinBox(parent);
    height = std::max(spinBox.sizeHint().height(), height);
    QLineEdit edit(parent);
    height = std::max(edit.sizeHint().height(), height);
    return height;
}

    template <class Editor>
class EditorFactoryPrivate
{
public:
    typedef QList<Editor*> EditorList;
    typedef QMap<Property*, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor*, Property*> EditorToPropertyMap;

    Editor* createEditor(Property* property, QWidget* parent);
    void initializeEditor(Property* property, Editor* e);
    void slotEditorDestroyed(QObject* object);

    PropertyToEditorListMap  m_createdEditors;
    EditorToPropertyMap m_editorToProperty;
};

template <class Editor>
Editor* EditorFactoryPrivate<Editor>::createEditor(Property* property, QWidget* parent)
{
    Editor* editor = new Editor(parent);
    initializeEditor(property, editor);
    return editor;
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeEditor(Property* property, Editor* editor)
{
    typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        it = m_createdEditors.insert(property, EditorList());
    it.value().append(editor);
    m_editorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject* object)
{
    const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
    for (typename EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor) 
    {
        if (itEditor.key() == object) 
        {
            Editor *editor = itEditor.key();
            Property *property = itEditor.value();
            const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
            if (pit != m_createdEditors.end()) 
            {
                pit.value().removeAll(editor);
                if (pit.value().isEmpty())
                    m_createdEditors.erase(pit);
            }
            m_editorToProperty.erase(itEditor);
            return;
        }
    }
}

/* SpinBoxFactoryPrivate */
class SpinBoxFactoryPrivate : public EditorFactoryPrivate<QSpinBox>
{
    SpinBoxFactory* q_ptr;
    VSN_DECLARE_PUBLIC(SpinBoxFactory);
public:
    void slotPropertyChanged(Property* property, int value);
    void slotRangeChanged(Property* property, int min, int max);
    void slotSingleStepChanged(Property* property, int step);
    void slotSetValue(int value);
};

void SpinBoxFactoryPrivate::slotPropertyChanged(Property* property, int value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QSpinBox* editor : it.value()) 
    {
        if (editor->value() != value) 
        {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void SpinBoxFactoryPrivate::slotRangeChanged(Property* property, int min, int max)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    IntPropManager* manager = q_ptr->propertyManager(property);
    if (!manager)
        return;
    for (QSpinBox* editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void SpinBoxFactoryPrivate::slotSingleStepChanged(Property* property, int step)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QSpinBox* editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void SpinBoxFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QSpinBox*, Property*>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QSpinBox*, Property*>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor !=  ecend; ++itEditor) 
    {
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            IntPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/* SpinBoxFactory */
SpinBoxFactory::SpinBoxFactory(QObject* parent)
    : AbsEditorFactory<IntPropManager>(parent), d_ptr(new SpinBoxFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

SpinBoxFactory::~SpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void SpinBoxFactory::connectPropertyManager(IntPropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    connect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

QWidget* SpinBoxFactory::createEditor(IntPropManager* manager, Property* property, QWidget* parent)
{
    QSpinBox* editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void SpinBoxFactory::disconnectPropertyManager(IntPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    disconnect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    disconnect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

void SpinBoxFactory::slotPropertyChanged(Property* property, int value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void SpinBoxFactory::slotRangeChanged(Property* property, int min, int max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void SpinBoxFactory::slotSingleStepChanged(Property* property, int step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void SpinBoxFactory::slotSetValue(int value)
{
    d_ptr->slotSetValue(value);
}

void SpinBoxFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* SliderFactoryPrivate */
class SliderFactoryPrivate : public EditorFactoryPrivate<QSlider>
{
    SliderFactory* q_ptr;
    VSN_DECLARE_PUBLIC(SliderFactory);
public:
    void slotPropertyChanged(Property* property, int value);
    void slotRangeChanged(Property* property, int min, int max);
    void slotSingleStepChanged(Property* property, int step);
    void slotSetValue(int value);
};

void SliderFactoryPrivate::slotPropertyChanged(Property *property, int value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QSlider *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void SliderFactoryPrivate::slotRangeChanged(Property *property, int min, int max)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    IntPropManager* manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QSlider* editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void SliderFactoryPrivate::slotSingleStepChanged(Property* property, int step)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QSlider* editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void SliderFactoryPrivate::slotSetValue(int value)
{
    QObject* object = q_ptr->sender();
    const QMap<QSlider*, Property*>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QSlider*, Property*>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor ) 
    {
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            IntPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/* SliderFactory */
SliderFactory::SliderFactory(QObject* parent)
    : AbsEditorFactory<IntPropManager>(parent)
    , d_ptr(new SliderFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

SliderFactory::~SliderFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void SliderFactory::connectPropertyManager(IntPropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    connect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

QWidget* SliderFactory::createEditor(IntPropManager* manager, Property* property, QWidget* parent)
{
    QSlider* editor = new QSlider(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void SliderFactory::disconnectPropertyManager(IntPropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    disconnect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    disconnect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

void SliderFactory::slotPropertyChanged(Property* property, int value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void SliderFactory::slotRangeChanged(Property* property, int min, int max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void SliderFactory::slotSingleStepChanged(Property* property, int step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void SliderFactory::slotSetValue(int value)
{
    d_ptr->slotSetValue(value);
}

void SliderFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* ScrollBarFactoryPrivate */
class ScrollBarFactoryPrivate : public  EditorFactoryPrivate<QScrollBar>
{
    ScrollBarFactory *q_ptr;
    VSN_DECLARE_PUBLIC(ScrollBarFactory);
public:
    void slotPropertyChanged(Property* property, int value);
    void slotRangeChanged(Property *property, int min, int max);
    void slotSingleStepChanged(Property *property, int step);
    void slotSetValue(int value);
};

void ScrollBarFactoryPrivate::slotPropertyChanged(Property* property, int value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    for (QScrollBar *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void ScrollBarFactoryPrivate::slotRangeChanged(Property* property, int min, int max)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    IntPropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QScrollBar *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void ScrollBarFactoryPrivate::slotSingleStepChanged(Property* property, int step)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QScrollBar *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void ScrollBarFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QScrollBar *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QScrollBar *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            IntPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* ScrollBarFactory */
ScrollBarFactory::ScrollBarFactory(QObject *parent)
    : AbsEditorFactory<IntPropManager>(parent), d_ptr(new ScrollBarFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

ScrollBarFactory::~ScrollBarFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void ScrollBarFactory::connectPropertyManager(IntPropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    connect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    connect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

QWidget *ScrollBarFactory::createEditor(IntPropManager *manager, Property *property,
        QWidget *parent)
{
    QScrollBar *editor = new QScrollBar(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void ScrollBarFactory::disconnectPropertyManager(IntPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    disconnect(manager, SIGNAL(rangeChanged(Property*,int,int)), this, SLOT(slotRangeChanged(Property*,int,int)));
    disconnect(manager, SIGNAL(singleStepChanged(Property*,int)), this, SLOT(slotSingleStepChanged(Property*,int)));
}

void ScrollBarFactory::slotPropertyChanged(Property* property, int value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void ScrollBarFactory::slotRangeChanged(Property* property, int min, int max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void ScrollBarFactory::slotSingleStepChanged(Property* property, int step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void ScrollBarFactory::slotSetValue(int value)
{
    d_ptr->slotSetValue(value);
}

void ScrollBarFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* CheckBoxFactoryPrivate */
class CheckBoxFactoryPrivate : public EditorFactoryPrivate<BoolEdit>
{
    CheckBoxFactory *q_ptr;
    VSN_DECLARE_PUBLIC(CheckBoxFactory);
public:
    void slotPropertyChanged(Property* property, bool value);
    void slotSetValue(bool value);
};

void CheckBoxFactoryPrivate::slotPropertyChanged(Property* property, bool value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    for (BoolEdit *editor : it.value()) {
        editor->blockCheckBoxSignals(true);
        editor->setChecked(value);
        editor->blockCheckBoxSignals(false);
    }
}

void CheckBoxFactoryPrivate::slotSetValue(bool value)
{
    QObject *object = q_ptr->sender();

    const QMap<BoolEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<BoolEdit *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            BoolPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* CheckBoxFactory */
CheckBoxFactory::CheckBoxFactory(QObject* parent)
    : AbsEditorFactory<BoolPropManager>(parent)
    , d_ptr(new CheckBoxFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

CheckBoxFactory::~CheckBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void CheckBoxFactory::connectPropertyManager(BoolPropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,bool)), this, SLOT(slotPropertyChanged(Property*,bool)));
}

QWidget* CheckBoxFactory::createEditor(BoolPropManager* manager, Property* property, QWidget* parent)
{
    BoolEdit *editor = d_ptr->createEditor(property, parent);
    editor->setChecked(manager->value(property));

    connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetValue(bool)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void CheckBoxFactory::disconnectPropertyManager(BoolPropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,bool)), this, SLOT(slotPropertyChanged(Property*,bool)));
}

void CheckBoxFactory::slotPropertyChanged(Property* property, bool value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void CheckBoxFactory::slotSetValue(bool value)
{
    d_ptr->slotSetValue(value);
}

void CheckBoxFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* DoubleSpinBoxFactoryPrivate */
class DoubleSpinBoxFactoryPrivate : public EditorFactoryPrivate<QDoubleSpinBox>
{
    DoubleSpinBoxFactory *q_ptr;
    VSN_DECLARE_PUBLIC(DoubleSpinBoxFactory);
public:
    void slotPropertyChanged(Property* property, double value);
    void slotRangeChanged(Property* property, double min, double max);
    void slotSingleStepChanged(Property* property, double step);
    void slotDecimalsChanged(Property* property, int prec);
    void slotSetValue(double value);
};

void DoubleSpinBoxFactoryPrivate::slotPropertyChanged(Property* property, double value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;
    for (QDoubleSpinBox *editor : it.value()) 
    {
        if (editor->value() != value) 
        {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void DoubleSpinBoxFactoryPrivate::slotRangeChanged(Property* property, double min, double max)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    DoublePropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QDoubleSpinBox *editor : it.value()) {
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void DoubleSpinBoxFactoryPrivate::slotSingleStepChanged(Property* property, double step)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.cend())
        return;

    DoublePropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QDoubleSpinBox *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void DoubleSpinBoxFactoryPrivate::slotDecimalsChanged(Property* property, int prec)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    DoublePropManager* manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QDoubleSpinBox *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setDecimals(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void DoubleSpinBoxFactoryPrivate::slotSetValue(double value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleSpinBox *, Property *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QDoubleSpinBox *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) 
    {
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            DoublePropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/* DoubleSpinBoxFactory */
DoubleSpinBoxFactory::DoubleSpinBoxFactory(QObject* parent)
    : AbsEditorFactory<DoublePropManager>(parent), d_ptr(new DoubleSpinBoxFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

DoubleSpinBoxFactory::~DoubleSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void DoubleSpinBoxFactory::connectPropertyManager(DoublePropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,double)), this, SLOT(slotPropertyChanged(Property*,double)));
    connect(manager, SIGNAL(rangeChanged(Property*,double,double)), this, SLOT(slotRangeChanged(Property*,double,double)));
    connect(manager, SIGNAL(singleStepChanged(Property*,double)), this, SLOT(slotSingleStepChanged(Property*,double)));
    connect(manager, SIGNAL(decimalsChanged(Property*,int)), this, SLOT(slotDecimalsChanged(Property*,int)));
}

QWidget* DoubleSpinBoxFactory::createEditor(DoublePropManager* manager,
        Property* property, QWidget* parent)
{
    QDoubleSpinBox* editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setDecimals(manager->decimals(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);

    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void DoubleSpinBoxFactory::disconnectPropertyManager(DoublePropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,double)), this, SLOT(slotPropertyChanged(Property*,double)));
    disconnect(manager, SIGNAL(rangeChanged(Property*,double,double)), this, SLOT(slotRangeChanged(Property*,double,double)));
    disconnect(manager, SIGNAL(singleStepChanged(Property*,double)), this, SLOT(slotSingleStepChanged(Property*,double)));
    disconnect(manager, SIGNAL(decimalsChanged(Property*,int)), this, SLOT(slotDecimalsChanged(Property*,int)));
}

void DoubleSpinBoxFactory::slotPropertyChanged(Property* property, double value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void DoubleSpinBoxFactory::slotRangeChanged(Property* property, double min, double max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void DoubleSpinBoxFactory::slotSingleStepChanged(Property* property, double step)
{
    d_ptr->slotSingleStepChanged(property, step);
}

void DoubleSpinBoxFactory::slotDecimalsChanged(Property* property, int prec)
{
    d_ptr->slotDecimalsChanged(property, prec);
}

void DoubleSpinBoxFactory::slotSetValue(double value)
{
    d_ptr->slotSetValue(value);
}

void DoubleSpinBoxFactory::slotEditorDestroyed(QObject* object) 
{
    d_ptr->slotEditorDestroyed(object);
}

/* LineEditFactoryPrivate */
class LineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit>
{
    LineEditFactory *q_ptr;
    VSN_DECLARE_PUBLIC(LineEditFactory);
public:
    void slotPropertyChanged(Property* property, const QString& value);
    void slotRegExpChanged(Property* property, const QRegularExpression& regExp);
    void slotSetValue(const QString& value);
};

void LineEditFactoryPrivate::slotPropertyChanged(Property* property, const QString& value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (QLineEdit *editor : it.value()) 
    {
        if (editor->text() != value)
            editor->setText(value);
    }
}

void LineEditFactoryPrivate::slotRegExpChanged(Property* property, const QRegularExpression& regExp)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    StringPropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QLineEdit* editor : it.value()) 
    {
        editor->blockSignals(true);
        const QValidator* oldValidator = editor->validator();
        QValidator* newValidator = nullptr;
        if (regExp.isValid()) 
            newValidator = new QRegularExpressionValidator(regExp, editor);

        editor->setValidator(newValidator);
        if (oldValidator)
            delete oldValidator;
        editor->blockSignals(false);
    }
}

void LineEditFactoryPrivate::slotSetValue(const QString& value)
{
    QObject *object = q_ptr->sender();
    const QMap<QLineEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QLineEdit *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            StringPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* LineEditFactory */
LineEditFactory::LineEditFactory(QObject* parent)
    : AbsEditorFactory<StringPropManager>(parent), d_ptr(new LineEditFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

LineEditFactory::~LineEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void LineEditFactory::connectPropertyManager(StringPropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QString)), this, SLOT(slotPropertyChanged(Property*,QString)));
    connect(manager, SIGNAL(regExpChanged(Property*, QRegularExpression)), this, SLOT(slotRegExpChanged(Property*, QRegularExpression)));
}

QWidget* LineEditFactory::createEditor(StringPropManager* manager, Property* property, QWidget* parent)
{
    QLineEdit* editor = d_ptr->createEditor(property, parent);
    QRegularExpression regExp = manager->regExp(property);
    if (regExp.isValid()) 
    {
        QValidator *validator = new QRegularExpressionValidator(regExp, editor);
        editor->setValidator(validator);
    }
    editor->setText(manager->value(property));

    connect(editor, SIGNAL(textEdited(QString)), this, SLOT(slotSetValue(QString)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void LineEditFactory::disconnectPropertyManager(StringPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QString)), this, SLOT(slotPropertyChanged(Property*,QString)));
    disconnect(manager, SIGNAL(regExpChanged(Property*, QRegularExpression)), this, SLOT(slotRegExpChanged(Property*, QRegularExpression)));
}

void LineEditFactory::slotPropertyChanged(Property* property, const QString& str)
{
    d_ptr->slotPropertyChanged(property, str);
}

void LineEditFactory::slotRegExpChanged(Property* property, const QRegularExpression& regExp)
{
    d_ptr->slotRegExpChanged(property, regExp);
}

void LineEditFactory::slotSetValue(const QString& value)
{
    d_ptr->slotSetValue(value);
}

void LineEditFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* DateEditFactoryPrivate */
class DateEditFactoryPrivate : public EditorFactoryPrivate<QDateEdit>
{
    DateEditFactory *q_ptr;
    VSN_DECLARE_PUBLIC(DateEditFactory);
public:
    void slotPropertyChanged(Property *property, const QDate& value);
    void slotRangeChanged(Property *property, const QDate &min, const QDate &max);
    void slotSetValue(const QDate &value);
};

void DateEditFactoryPrivate::slotPropertyChanged(Property *property, const QDate& value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;
    for (QDateEdit *editor : it.value()) {
        editor->blockSignals(true);
        editor->setDate(value);
        editor->blockSignals(false);
    }
}

void DateEditFactoryPrivate::slotRangeChanged(Property *property, const QDate &min, const QDate &max)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    DatePropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    for (QDateEdit *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setDateRange(min, max);
        editor->setDate(manager->value(property));
        editor->blockSignals(false);
    }
}

void DateEditFactoryPrivate::slotSetValue(const QDate &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDateEdit*, Property *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QDateEdit*, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            DatePropManager* manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* DateEditFactory */
DateEditFactory::DateEditFactory(QObject* parent)
    : AbsEditorFactory<DatePropManager>(parent), d_ptr(new DateEditFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

DateEditFactory::~DateEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void DateEditFactory::connectPropertyManager(DatePropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QDate)), this, SLOT(slotPropertyChanged(Property*,QDate)));
    connect(manager, SIGNAL(rangeChanged(Property*,QDate,QDate)), this, SLOT(slotRangeChanged(Property*,QDate,QDate)));
}

QWidget *DateEditFactory::createEditor(DatePropManager* manager, Property* property,
        QWidget *parent)
{
    QDateEdit *editor = d_ptr->createEditor(property, parent);
    editor->setDisplayFormat(PropBrowserUtils::dateFormat());
    editor->setCalendarPopup(true);
    editor->setDateRange(manager->minimum(property), manager->maximum(property));
    editor->setDate(manager->value(property));

    connect(editor, SIGNAL(dateChanged(QDate)), this, SLOT(slotSetValue(QDate)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void DateEditFactory::disconnectPropertyManager(DatePropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QDate)), this, SLOT(slotPropertyChanged(Property*,QDate)));
    disconnect(manager, SIGNAL(rangeChanged(Property*,QDate,QDate)), this, SLOT(slotRangeChanged(Property*,QDate,QDate)));
}

void DateEditFactory::slotPropertyChanged(Property* property, const QDate& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void DateEditFactory::slotRangeChanged(Property* property, const QDate& min, const QDate& max)
{
    d_ptr->slotRangeChanged(property, min, max);
}

void DateEditFactory::slotSetValue(const QDate&)
{
}

void DateEditFactory::slotEditorDestroyed(QObject*)
{
}

/* TimeEditFactoryPrivate */
class TimeEditFactoryPrivate : public EditorFactoryPrivate<QTimeEdit>
{
    TimeEditFactory *q_ptr;
    VSN_DECLARE_PUBLIC(TimeEditFactory);
public:
    void slotPropertyChanged(Property *property, const QTime &value);
    void slotSetValue(const QTime &value);
};

void TimeEditFactoryPrivate::slotPropertyChanged(Property *property, const QTime &value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;
    for (QTimeEdit *editor : it.value()) {
        editor->blockSignals(true);
        editor->setTime(value);
        editor->blockSignals(false);
    }
}

void TimeEditFactoryPrivate::slotSetValue(const QTime& value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QTimeEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QTimeEdit *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            TimePropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* TimeEditFactory */
TimeEditFactory::TimeEditFactory(QObject* parent)
    : AbsEditorFactory<TimePropManager>(parent), d_ptr(new TimeEditFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

TimeEditFactory::~TimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void TimeEditFactory::connectPropertyManager(TimePropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QTime)), this, SLOT(slotPropertyChanged(Property*,QTime)));
}

QWidget *TimeEditFactory::createEditor(TimePropManager* manager, Property* property, QWidget* parent)
{
    QTimeEdit* editor = d_ptr->createEditor(property, parent);
    editor->setDisplayFormat(PropBrowserUtils::timeFormat());
    editor->setTime(manager->value(property));

    connect(editor, SIGNAL(timeChanged(QTime)), this, SLOT(slotSetValue(QTime)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void TimeEditFactory::disconnectPropertyManager(TimePropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QTime)), this, SLOT(slotPropertyChanged(Property*,QTime)));
}

void TimeEditFactory::slotPropertyChanged(Property* property, const QTime& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void TimeEditFactory::slotSetValue(const QTime& value)
{
    d_ptr->slotSetValue(value);
}

void TimeEditFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* DateTimeEditFactoryPrivate */
class DateTimeEditFactoryPrivate : public EditorFactoryPrivate<QDateTimeEdit>
{
    DateTimeEditFactory *q_ptr;
    VSN_DECLARE_PUBLIC(DateTimeEditFactory);
public:
    void slotPropertyChanged(Property *property, const QDateTime &value);
    void slotSetValue(const QDateTime &value);
};

void DateTimeEditFactoryPrivate::slotPropertyChanged(Property *property,
            const QDateTime &value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (QDateTimeEdit *editor : it.value()) 
    {
        editor->blockSignals(true);
        editor->setDateTime(value);
        editor->blockSignals(false);
    }
}

void DateTimeEditFactoryPrivate::slotSetValue(const QDateTime& value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QDateTimeEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QDateTimeEdit *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            DateTimePropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* DateTimeEditFactory */
DateTimeEditFactory::DateTimeEditFactory(QObject* parent)
    : AbsEditorFactory<DateTimePropManager>(parent), d_ptr(new DateTimeEditFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

DateTimeEditFactory::~DateTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void DateTimeEditFactory::connectPropertyManager(DateTimePropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QDateTime)), this, SLOT(slotPropertyChanged(Property*,QDateTime)));
}

QWidget* DateTimeEditFactory::createEditor(DateTimePropManager* manager,
        Property* property, QWidget* parent)
{
    QDateTimeEdit *editor =  d_ptr->createEditor(property, parent);
    editor->setDisplayFormat(PropBrowserUtils::dateTimeFormat());
    editor->setDateTime(manager->value(property));

    connect(editor, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(slotSetValue(QDateTime)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void DateTimeEditFactory::disconnectPropertyManager(DateTimePropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QDateTime)), this, SLOT(slotPropertyChanged(Property*,QDateTime)));
}

void DateTimeEditFactory::slotPropertyChanged(Property* property, const QDateTime& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void DateTimeEditFactory::slotSetValue(const QDateTime& value)
{
    d_ptr->slotSetValue(value);
}

void DateTimeEditFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* KeySequenceEditorFactoryPrivate */
class KeySequenceEditorFactoryPrivate : public EditorFactoryPrivate<QKeySequenceEdit>
{
    KeySequenceEditorFactory *q_ptr;
    VSN_DECLARE_PUBLIC(KeySequenceEditorFactory);
public:

    void slotPropertyChanged(Property *property, const QKeySequence &value);
    void slotSetValue(const QKeySequence &value);
};

void KeySequenceEditorFactoryPrivate::slotPropertyChanged(Property *property, const QKeySequence &value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (QKeySequenceEdit *editor : it.value()) {
        editor->blockSignals(true);
        editor->setKeySequence(value);
        editor->blockSignals(false);
    }
}

void KeySequenceEditorFactoryPrivate::slotSetValue(const QKeySequence &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QKeySequenceEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QKeySequenceEdit *, Property *>::ConstIterator itEditor =  m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            Property *property = itEditor.value();
            KeySequencePropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* KeySequenceEditorFactory */
KeySequenceEditorFactory::KeySequenceEditorFactory(QObject *parent)
    : AbsEditorFactory<KeySequencePropManager>(parent), d_ptr(new KeySequenceEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

KeySequenceEditorFactory::~KeySequenceEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void KeySequenceEditorFactory::connectPropertyManager(KeySequencePropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QKeySequence)), this, SLOT(slotPropertyChanged(Property*,QKeySequence)));
}

QWidget* KeySequenceEditorFactory::createEditor(KeySequencePropManager* manager, Property* property, QWidget* parent)
{
    QKeySequenceEdit *editor = d_ptr->createEditor(property, parent);
    editor->setKeySequence(manager->value(property));

    connect(editor, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(slotSetValue(QKeySequence)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void KeySequenceEditorFactory::disconnectPropertyManager(KeySequencePropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QKeySequence)), this, SLOT(slotPropertyChanged(Property*,QKeySequence)));
}

void KeySequenceEditorFactory::slotPropertyChanged(Property* property, const QKeySequence& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void KeySequenceEditorFactory::slotSetValue(const QKeySequence& value)
{
    d_ptr->slotSetValue(value);
}

void KeySequenceEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* QtCharEdit */
QtCharEdit::QtCharEdit(QWidget *parent)
    : QWidget(parent),  m_lineEdit(new QLineEdit(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->setContentsMargins(QMargins());
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setFocusProxy(this);
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
}

bool QtCharEdit::eventFilter(QObject* o, QEvent* e)
{
    if (o == m_lineEdit && e->type() == QEvent::ContextMenu) 
    {
        QContextMenuEvent* c = static_cast<QContextMenuEvent*>(e);
        QMenu* menu = m_lineEdit->createStandardContextMenu();
        const auto actions = menu->actions();
        for (QAction *action : actions) 
        {
            action->setShortcut(QKeySequence());
            QString actionString = action->text();
            const int pos = actionString.lastIndexOf(QLatin1Char('\t'));
            if (pos > 0)
                actionString = actionString.remove(pos, actionString.length() - pos);
            action->setText(actionString);
        }
        QAction *actionBefore = 0;
        if (actions.count() > 0)
            actionBefore = actions[0];
        QAction *clearAction = new QAction(tr("Clear Char"), menu);
        menu->insertAction(actionBefore, clearAction);
        menu->insertSeparator(actionBefore);
        clearAction->setEnabled(!m_value.isNull());
        connect(clearAction, SIGNAL(triggered()), this, SLOT(slotClearChar()));
        menu->exec(c->globalPos());
        delete menu;
        e->accept();
        return true;
    }

    return QWidget::eventFilter(o, e);
}

void QtCharEdit::slotClearChar()
{
    if (m_value.isNull())
        return;
    setValue(QChar());
    emit valueChanged(m_value);
}

void QtCharEdit::handleKeyEvent(QKeyEvent *e)
{
    const int key = e->key();
    switch (key) {
    case Qt::Key_Control:
    case Qt::Key_Shift:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_Super_L:
    case Qt::Key_Return:
        return;
    default:
        break;
    }

    const QString text = e->text();
    if (text.count() != 1)
        return;

    const QChar c = text.at(0);
    if (!c.isPrint())
        return;

    if (m_value == c)
        return;

    m_value = c;
    const QString str = m_value.isNull() ? QString() : QString(m_value);
    m_lineEdit->setText(str);
    e->accept();
    emit valueChanged(m_value);
}

void QtCharEdit::setValue(const QChar &value)
{
    if (value == m_value)
        return;

    m_value = value;
    QString str = value.isNull() ? QString() : QString(value);
    m_lineEdit->setText(str);
}

QChar QtCharEdit::value() const
{
    return m_value;
}

void QtCharEdit::focusInEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    m_lineEdit->selectAll();
    QWidget::focusInEvent(e);
}

void QtCharEdit::focusOutEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void QtCharEdit::keyPressEvent(QKeyEvent *e)
{
    handleKeyEvent(e);
    e->accept();
}

void QtCharEdit::keyReleaseEvent(QKeyEvent *e)
{
    m_lineEdit->event(e);
}

bool QtCharEdit::event(QEvent *e)
{
    switch(e->type()) {
    case QEvent::Shortcut:
    case QEvent::ShortcutOverride:
    case QEvent::KeyRelease:
        e->accept();
        return true;
    default:
        break;
    }
    return QWidget::event(e);
}

/* CharEditorFactoryPrivate */
class CharEditorFactoryPrivate : public EditorFactoryPrivate<QtCharEdit>
{
    CharEditorFactory *q_ptr;
    VSN_DECLARE_PUBLIC(CharEditorFactory);
public:
    void slotPropertyChanged(Property* property, const QChar& value);
    void slotSetValue(const QChar& value);
};

void CharEditorFactoryPrivate::slotPropertyChanged(Property *property, const QChar &value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (QtCharEdit *editor : it.value()) {
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void CharEditorFactoryPrivate::slotSetValue(const QChar& value)
{
    QObject *object = q_ptr->sender();
    const QMap<QtCharEdit *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QtCharEdit *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            CharPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* CharEditorFactory */
CharEditorFactory::CharEditorFactory(QObject* parent)
    : AbsEditorFactory<CharPropManager>(parent), d_ptr(new CharEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;

}

CharEditorFactory::~CharEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void CharEditorFactory::connectPropertyManager(CharPropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QChar)), this, SLOT(slotPropertyChanged(Property*,QChar)));
}

QWidget *CharEditorFactory::createEditor(CharPropManager* manager, Property* property, QWidget* parent)
{
    QtCharEdit *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(QChar)), this, SLOT(slotSetValue(QChar)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void CharEditorFactory::disconnectPropertyManager(CharPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QChar)), this, SLOT(slotPropertyChanged(Property*,QChar)));
}

void CharEditorFactory::slotPropertyChanged(Property* property, const QChar& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void CharEditorFactory::slotSetValue(const QChar& value)
{
    d_ptr->slotSetValue(value);
}

void CharEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* EnumEditorFactoryPrivate */
class EnumEditorFactoryPrivate : public EditorFactoryPrivate<QComboBox>
{
    EnumEditorFactory* q_ptr;
    VSN_DECLARE_PUBLIC(EnumEditorFactory);
public:
    void slotPropertyChanged(Property *property, int value);
    void slotEnumNamesChanged(Property *property, const QStringList &);
    void slotEnumIconsChanged(Property *property, const QMap<int, QIcon> &);
    void slotSetValue(int value);
};

void EnumEditorFactoryPrivate::slotPropertyChanged(Property *property, int value)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (QComboBox *editor : it.value()) {
        editor->blockSignals(true);
        editor->setCurrentIndex(value);
        editor->blockSignals(false);
    }
}

void EnumEditorFactoryPrivate::slotEnumNamesChanged(Property *property, const QStringList &enumNames)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    EnumPropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QMap<int, QIcon> enumIcons = manager->enumIcons(property);

    for (QComboBox *editor : it.value()) {
        editor->blockSignals(true);
        editor->clear();
        editor->addItems(enumNames);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void EnumEditorFactoryPrivate::slotEnumIconsChanged(Property *property, const QMap<int, QIcon> &enumIcons)
{
    const auto it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    EnumPropManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    const QStringList enumNames = manager->enumNames(property);
    for (QComboBox *editor : it.value()) {
        editor->blockSignals(true);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void EnumEditorFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QComboBox *, Property *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QComboBox *, Property *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property* property = itEditor.value();
            EnumPropManager* manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* EnumEditorFactory */
EnumEditorFactory::EnumEditorFactory(QObject *parent)
    : AbsEditorFactory<EnumPropManager>(parent), d_ptr(new EnumEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

EnumEditorFactory::~EnumEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void EnumEditorFactory::connectPropertyManager(EnumPropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    connect(manager, SIGNAL(enumNamesChanged(Property*,QStringList)), this, SLOT(slotEnumNamesChanged(Property*,QStringList)));
}

QWidget* EnumEditorFactory::createEditor(EnumPropManager* manager, Property* property, QWidget* parent)
{
    QComboBox* editor = d_ptr->createEditor(property, parent);
    editor->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    editor->setMinimumHeight(calcTotalHeightHint(parent));
    editor->view()->setTextElideMode(Qt::ElideRight);
    QStringList enumNames = manager->enumNames(property);
    editor->addItems(enumNames);
    QMap<int, QIcon> enumIcons = manager->enumIcons(property);
    const int enumNamesCount = enumNames.count();
    for (int i = 0; i < enumNamesCount; i++)
        editor->setItemIcon(i, enumIcons.value(i));
    editor->setCurrentIndex(manager->value(property));

    connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void EnumEditorFactory::disconnectPropertyManager(EnumPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,int)), this, SLOT(slotPropertyChanged(Property*,int)));
    disconnect(manager, SIGNAL(enumNamesChanged(Property*,QStringList)), this, SLOT(slotEnumNamesChanged(Property*,QStringList)));
}

void EnumEditorFactory::slotPropertyChanged(Property* property, int value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void EnumEditorFactory::slotEnumNamesChanged(Property* property, const QStringList& enumNames)
{
    d_ptr->slotEnumNamesChanged(property, enumNames);
}

void EnumEditorFactory::slotEnumIconsChanged(Property* property, const QMap<int, QIcon>& enumIcons)
{
    d_ptr->slotEnumIconsChanged(property, enumIcons);
}

void EnumEditorFactory::slotSetValue(int value)
{
    d_ptr->slotSetValue(value);
}

void EnumEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* CursorEditorFactoryPrivate */
class CursorEditorFactoryPrivate
{
    CursorEditorFactory *q_ptr;
    VSN_DECLARE_PUBLIC(CursorEditorFactory);
public:
    CursorEditorFactoryPrivate();

    void slotPropertyChanged(Property *property, const QCursor &cursor);
    void slotEnumChanged(Property *property, int value);
    void slotEditorDestroyed(QObject *object);

    EnumEditorFactory *m_enumEditorFactory;
    EnumPropManager *m_enumPropertyManager;

    QMap<Property*, Property*> m_propertyToEnum;
    QMap<Property*, Property*> m_enumToProperty;
    QMap<Property*, QWidgetList> m_enumToEditors;
    QMap<QWidget*, Property*>  m_editorToEnum;
    bool m_updatingEnum;
};

/* CursorEditorFactoryPrivate */
CursorEditorFactoryPrivate::CursorEditorFactoryPrivate()
    : m_updatingEnum(false)
{
}

void CursorEditorFactoryPrivate::slotPropertyChanged(Property* property, const QCursor& cursor)
{
    Property *enumProp = m_propertyToEnum.value(property);
    if (!enumProp)
        return;

    m_updatingEnum = true;
    m_enumPropertyManager->setValue(enumProp, cursorDatabase()->cursorToValue(cursor));
    m_updatingEnum = false;
}

void CursorEditorFactoryPrivate::slotEnumChanged(Property* property, int value)
{
    if (m_updatingEnum)
        return;
    // update cursor property
    Property *prop = m_enumToProperty.value(property);
    if (!prop)
        return;
    CursorPropManager *cursorManager = q_ptr->propertyManager(prop);
    if (!cursorManager)
        return;
#ifndef QT_NO_CURSOR
    cursorManager->setValue(prop, QCursor(cursorDatabase()->valueToCursor(value)));
#endif
}

void CursorEditorFactoryPrivate::slotEditorDestroyed(QObject* object)
{
    const  QMap<QWidget*, Property*>::ConstIterator ecend = m_editorToEnum.constEnd();
    for (QMap<QWidget*, Property*>::ConstIterator itEditor = m_editorToEnum.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            QWidget *editor = itEditor.key();
            Property *enumProp = itEditor.value();
            m_editorToEnum.remove(editor);
            m_enumToEditors[enumProp].removeAll(editor);
            if (m_enumToEditors[enumProp].isEmpty()) 
            {
                m_enumToEditors.remove(enumProp);
                Property *property = m_enumToProperty.value(enumProp);
                m_enumToProperty.remove(enumProp);
                m_propertyToEnum.remove(property);
                delete enumProp;
            }
            return;
        }
}

/* CursorEditorFactory */
CursorEditorFactory::CursorEditorFactory(QObject *parent)
    : AbsEditorFactory<CursorPropManager>(parent), d_ptr(new CursorEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;

    d_ptr->m_enumEditorFactory = new EnumEditorFactory(this);
    d_ptr->m_enumPropertyManager = new EnumPropManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(Property*,int)),
                this, SLOT(slotEnumChanged(Property*,int)));
    d_ptr->m_enumEditorFactory->appendPropertyManager(d_ptr->m_enumPropertyManager);
}

CursorEditorFactory::~CursorEditorFactory()
{
}

void CursorEditorFactory::connectPropertyManager(CursorPropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QCursor)), this, SLOT(slotPropertyChanged(Property*,QCursor)));
}

QWidget* CursorEditorFactory::createEditor(CursorPropManager* manager, Property* property, QWidget* parent)
{
    Property *enumProp = 0;
    if (d_ptr->m_propertyToEnum.contains(property)) {
        enumProp = d_ptr->m_propertyToEnum[property];
    } else {
        enumProp = d_ptr->m_enumPropertyManager->addProperty(property->propertyName());
        d_ptr->m_enumPropertyManager->setEnumNames(enumProp, cursorDatabase()->cursorShapeNames());
        d_ptr->m_enumPropertyManager->setEnumIcons(enumProp, cursorDatabase()->cursorShapeIcons());
#ifndef QT_NO_CURSOR
        d_ptr->m_enumPropertyManager->setValue(enumProp, cursorDatabase()->cursorToValue(manager->value(property)));
#endif
        d_ptr->m_propertyToEnum[property] = enumProp;
        d_ptr->m_enumToProperty[enumProp] = property;
    }
    AbsEditorFactoryBase *af = d_ptr->m_enumEditorFactory;
    QWidget *editor = af->createEditor(enumProp, parent);
    d_ptr->m_enumToEditors[enumProp].append(editor);
    d_ptr->m_editorToEnum[editor] = enumProp;
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void CursorEditorFactory::disconnectPropertyManager(CursorPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QCursor)), this, SLOT(slotPropertyChanged(Property*,QCursor)));
}

void CursorEditorFactory::slotPropertyChanged(Property* property, const QCursor& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void CursorEditorFactory::slotEnumChanged(Property* property, int value)
{
    d_ptr->slotEnumChanged(property, value);
}

void CursorEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

/* ColorEditWidget */
ColorEditWidget::ColorEditWidget(QWidget* parent) 
    : QWidget(parent)
    , m_pixmapLabel(new QLabel)
    , m_label(new QLabel)
    , m_button(new QToolButton)
{
    QHBoxLayout* lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(10);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

    QString str(tr("..."));
    QFontMetrics fm = m_button->fontMetrics();
    QRect rc = fm.boundingRect(str);
    m_button->setFixedWidth(/*20*/rc.width() + fm.xHeight() * 2 + 1);
    setFocusProxy(m_button);

    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(str);
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(PropBrowserUtils::brushValuePixmap(QBrush(m_color)));
    m_label->setText(PropBrowserUtils::colorValueText(m_color));
}

void ColorEditWidget::setValue(const QColor& c)
{
    if (m_color != c) 
    {
        m_color = c;
        m_pixmapLabel->setPixmap(PropBrowserUtils::brushValuePixmap(QBrush(c)));
        m_label->setText(PropBrowserUtils::colorValueText(c));
    }
}

void ColorEditWidget::buttonClicked()
{
    const QColor newColor = QColorDialog::getColor(m_color, this, QString(), QColorDialog::ShowAlphaChannel);
    if (newColor.isValid() && newColor != m_color) 
    {
        setValue(newColor);
        emit valueChanged(m_color);
    }
}

bool ColorEditWidget::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == m_button) 
    {
        switch (ev->type()) 
        {
            case QEvent::KeyPress:
            case QEvent::KeyRelease:  // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            {
                switch (static_cast<const QKeyEvent*>(ev)->key()) 
                {
                    case Qt::Key_Escape:
                    case Qt::Key_Enter:
                    case Qt::Key_Return:
                        ev->ignore();
                        return true;
                    default:
                        break;
                }
            }
                break;
            default:
                break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

/* ColorEditorFactoryPrivate */
class ColorEditorFactoryPrivate : public EditorFactoryPrivate<ColorEditWidget>
{
    ColorEditorFactory* q_ptr;
    VSN_DECLARE_PUBLIC(ColorEditorFactory);
public:
    void slotPropertyChanged(Property* property, const QColor& value);
    void slotSetValue(const QColor& value);
};

void ColorEditorFactoryPrivate::slotPropertyChanged(Property* property, const QColor& value)
{
    const PropertyToEditorListMap::const_iterator it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (ColorEditWidget* e : it.value())
        e->setValue(value);
}

void ColorEditorFactoryPrivate::slotSetValue(const QColor& value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) 
        {
            Property *property = itEditor.value();
            ColorPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* ColorEditorFactory */
ColorEditorFactory::ColorEditorFactory(QObject* parent) :
    AbsEditorFactory<ColorPropManager>(parent),
    d_ptr(new ColorEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

ColorEditorFactory::~ColorEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void ColorEditorFactory::connectPropertyManager(ColorPropManager* manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QColor)),
            this, SLOT(slotPropertyChanged(Property*,QColor)));
}

QWidget* ColorEditorFactory::createEditor(ColorPropManager* manager,
        Property* property, QWidget* parent)
{
    ColorEditWidget* editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QColor)), this, SLOT(slotSetValue(QColor)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void ColorEditorFactory::disconnectPropertyManager(ColorPropManager* manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*, QColor)), this, SLOT(slotPropertyChanged(Property*, QColor)));
}

void ColorEditorFactory::slotPropertyChanged(Property* property, const QColor& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void ColorEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

void ColorEditorFactory::slotSetValue(const QColor& value)
{
    d_ptr->slotSetValue(value);
}

/* FontEditWidget */
FontEditWidget::FontEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
    QHBoxLayout* lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(PropBrowserUtils::fontValuePixmap(m_font));
    m_label->setText(PropBrowserUtils::fontValueText(m_font));
}

void FontEditWidget::setValue(const QFont &f)
{
    if (m_font != f) {
        m_font = f;
        m_pixmapLabel->setPixmap(PropBrowserUtils::fontValuePixmap(f));
        m_label->setText(PropBrowserUtils::fontValueText(f));
    }
}

void FontEditWidget::buttonClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this, tr("Select Font"));
    if (ok && newFont != m_font) 
    {
        QFont f = m_font;
        // prevent mask for unchanged attributes, don't change other attributes (like kerning, etc...)
        if (m_font.family() != newFont.family())
            f.setFamily(newFont.family());
        if (m_font.pointSize() != newFont.pointSize())
            f.setPointSize(newFont.pointSize());
        if (m_font.bold() != newFont.bold())
            f.setBold(newFont.bold());
        if (m_font.italic() != newFont.italic())
            f.setItalic(newFont.italic());
        if (m_font.underline() != newFont.underline())
            f.setUnderline(newFont.underline());
        if (m_font.strikeOut() != newFont.strikeOut())
            f.setStrikeOut(newFont.strikeOut());
        setValue(f);
        emit valueChanged(m_font);
    }
}

bool FontEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: {
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

/* FontEditorFactoryPrivate */
class FontEditorFactoryPrivate : public EditorFactoryPrivate<FontEditWidget>
{
    FontEditorFactory* q_ptr;
    VSN_DECLARE_PUBLIC(FontEditorFactory);
public:

    void slotPropertyChanged(Property *property, const QFont &value);
    void slotSetValue(const QFont& value);
};

void FontEditorFactoryPrivate::slotPropertyChanged(Property* property, const QFont& value)
{
    const PropertyToEditorListMap::const_iterator it = m_createdEditors.constFind(property);
    if (it == m_createdEditors.constEnd())
        return;

    for (FontEditWidget *e : it.value())
        e->setValue(value);
}

void FontEditorFactoryPrivate::slotSetValue(const QFont& value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            Property *property = itEditor.value();
            FontPropManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/* FontEditorFactory */
FontEditorFactory::FontEditorFactory(QObject *parent) :
    AbsEditorFactory<FontPropManager>(parent),
    d_ptr(new FontEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

FontEditorFactory::~FontEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
}

void FontEditorFactory::connectPropertyManager(FontPropManager *manager)
{
    connect(manager, SIGNAL(valueChanged(Property*,QFont)),
            this, SLOT(slotPropertyChanged(Property*,QFont)));
}

QWidget *FontEditorFactory::createEditor(FontPropManager *manager,
        Property *property, QWidget *parent)
{
    FontEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QFont)), this, SLOT(slotSetValue(QFont)));
    connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    return editor;
}

void FontEditorFactory::disconnectPropertyManager(FontPropManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(Property*,QFont)), this, SLOT(slotPropertyChanged(Property*,QFont)));
}

void FontEditorFactory::slotPropertyChanged(Property* property, const QFont& value)
{
    d_ptr->slotPropertyChanged(property, value);
}

void FontEditorFactory::slotEditorDestroyed(QObject* object)
{
    d_ptr->slotEditorDestroyed(object);
}

void FontEditorFactory::slotSetValue(const QFont& value)
{
    d_ptr->slotSetValue(value);
}

} // namespace QtVision
} // namespace VSN

