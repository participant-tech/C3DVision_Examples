///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_CURSORS_H
#define __QT_CURSORS_H

#include <QCursor>
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

QT_FUNC(QCursor) findCursor(const QWidget* pWidget);

} // namespace QtVision

} // namespace VSN

#endif /* __QT_CURSORS_H */
