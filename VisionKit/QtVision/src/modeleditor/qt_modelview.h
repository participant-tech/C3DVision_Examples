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

///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_MODELVIEW_H
#define __QT_MODELVIEW_H

#include <qt_openglwidget.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class ModelEditor;
    
/* ModelView */
class QT_CLASS ModelView : public QtOpenGLSceneWidget
{
    Q_OBJECT
public:
    ModelView(QWidget* parent = nullptr);
    ~ModelView() override;
public:
    // Returns pointer to the model editor
    ModelEditor* modelEditor() const { return m_modelEditor; }
    void setModelEditor(ModelEditor* modelEditor) { m_modelEditor = modelEditor; }
Q_SIGNALS:
    /// \ru Инициализация Model View завершена. en Initialises Model View is complite. \~
    void afterInitializeModelView();
public:
    virtual QString currentFile() const { return QString(); }

    virtual void newFile();
    virtual bool loadFiles(const QStringList& files);
protected:
    virtual void activationView();
    virtual void deactivationView();
protected:
    /// \ru Инициализация OpenGL ресурсов. \en Initialises OpenGL resources. \~
    void initializeGL() override;
protected: 
    ModelEditor* m_modelEditor;
private:
    friend class QtMdiMainWindow;
    Q_DISABLE_COPY(ModelView);
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MODELVIEW_H */
