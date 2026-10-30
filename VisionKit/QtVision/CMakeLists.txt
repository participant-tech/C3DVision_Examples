################################################################################
#                                                                              #
#  Copyright (c) 2025, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of C3DVision Library                                      #
#  https://c3dlabs.com, https://c3dlabs.ru/                                    #
#                                                                              #
#  Exclusive rights to C3D Vision, any copies or components (parts) thereof    #
#  and other intellectual property belong to C3D Labs, LLC (the Rightholder).  #
#  The license rights and restrictions are regulated by the Agreement between  #
#  the User and the Rightholder.                                               #
#                                                                              #
################################################################################
cmake_minimum_required(VERSION 3.15)
project(QtVision)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
include(VsnQtCoreDeploySupport)

set(C3DVision_NEED_QT5 OFF)
if (C3DVision_GUI_QT5_EXAMPLES OR C3DVision_SANDBOX)
  set(C3DVision_NEED_QT5 ON)
endif()

set(QtCore_SRC
    ./src/core/qt_eventlistener.cpp
    ./src/core/qt_eventlistener.h
    ./src/core/qt_openglwidget.cpp
    ./src/core/qt_openglwidget.h
    ./src/core/qt_openglwindow.cpp
    ./src/core/qt_openglcontext.cpp
    ./src/core/qt_licensewnd.cpp
    ./src/core/qt_cursors.cpp
    ./src/core/qt_colorbutton.cpp
    ./src/core/qt_global.cpp
    ./src/core/qt_mainwindow.cpp
    ./src/core/qt_mainwindow.h
    ./src/core/qt_sdimainwindow.cpp
    ./src/core/qt_sdimainwindow.h
    ./src/core/qt_mdimainwindow.cpp
    ./src/core/qt_mdimainwindow.h
    ./src/core/qt_icore.cpp
    ./src/core/qt_icore.h
    ./src/core/qt_icontext.cpp
    ./src/core/qt_icontext.h
    ./src/core/qt_coreconstants.h
    ./src/core/qt_application.cpp
    ./src/core/qt_application.h
    )
source_group(\\Core FILES ${QtCore_SRC})

set(QtActionmanager_SRC
    ./src/core/actionmanager/qt_actioncontainer.cpp
    ./src/core/actionmanager/qt_actioncontainer.h
    ./src/core/actionmanager/qt_actioncontainerprivate.h
    ./src/core/actionmanager/qt_actionmanager.cpp
    ./src/core/actionmanager/qt_actionmanager.h
    ./src/core/actionmanager/qt_actionmanagerprivate.h
    ./src/core/actionmanager/qt_command.cpp
    ./src/core/actionmanager/qt_command.h
    ./src/core/actionmanager/qt_commandprivate.h
    )
source_group(\\Core\\Actionmanager FILES ${QtActionmanager_SRC})

set(QtDialogs_SRC
    ./src/core/dialogs/qt_ioptionspage.cpp
    ./src/core/dialogs/qt_ioptionspage.h
    ./src/core/dialogs/qt_settingsdialog.cpp
    ./src/core/dialogs/qt_settingsdialog.h
    )
source_group(\\Core\\Dialogs FILES ${QtDialogs_SRC})

set(QtStyle_SRC
    ./src/style/qt_theme.cpp
    ./src/style/qt_theme.h
    ./src/style/qt_c3dstyle.cpp
    ./src/style/qt_c3dstyle.h
    ./src/style/qt_stylehelper.cpp
    ./src/style/qt_stylehelper.h
    )
source_group(\\Style FILES ${QtStyle_SRC})

set(QtUtils_SRC
    ./src/utils/qt_algorithm.h
    ./src/utils/qt_aspects.cpp
    ./src/utils/qt_aspects.h
    ./src/utils/qt_commandbar.cpp
    ./src/utils/qt_commandbar.h
    ./src/utils/qt_commandbarprivate.h
    ./src/utils/qt_commandline.cpp
    ./src/utils/qt_commandline.h
    ./src/utils/qt_id.cpp
    ./src/utils/qt_id.h
    ./src/utils/qt_icon.cpp
    ./src/utils/qt_icon.h
    ./src/utils/qt_hostosinfo.cpp
    ./src/utils/qt_hostosinfo.h
    ./src/utils/qt_appmainwindow.cpp
    ./src/utils/qt_appmainwindow.h
    ./src/utils/qt_previewwidget.cpp
    ./src/utils/qt_previewwidget.h
    ./src/utils/qt_predicates.h
    ./src/utils/qt_overlaywidget.cpp
    ./src/utils/qt_overlaywidget.h
    ./src/utils/qt_progressindicator.cpp
    ./src/utils/qt_progressindicator.h
    ./src/utils/qt_processmanager.cpp
    ./src/utils/qt_processmanager.h
    ./src/utils/qt_headsuptoolbar.cpp
    ./src/utils/qt_headsuptoolbar.h
    ./src/utils/qt_orientationbar.cpp
    ./src/utils/qt_orientationbar.h
    ./src/utils/qt_sceneviewcontroller.cpp
    ./src/utils/qt_sceneviewcontroller.h
    ./src/utils/qt_proxyaction.cpp
    ./src/utils/qt_proxyaction.h
    ./src/utils/qt_stringutils.cpp
    ./src/utils/qt_stringutils.h
    ./src/utils/qt_filepath.cpp
    ./src/utils/qt_filepath.h
    ./src/utils/qt_fileutils.cpp
    ./src/utils/qt_fileutils.h
    ./src/utils/qt_savefile.cpp
    ./src/utils/qt_savefile.h
    ./src/utils/qt_osspecificaspects.h
    ./src/utils/qt_porting.h
    ./src/utils/qt_environment.cpp
    ./src/utils/qt_environment.h
    ./src/utils/qt_environmentfwd.h
    ./src/utils/qt_elidinglabel.cpp
    ./src/utils/qt_elidinglabel.h
    ./src/utils/qt_infolabel.cpp
    ./src/utils/qt_infolabel.h
    ./src/utils/qt_utilsicons.cpp
    ./src/utils/qt_utilsicons.h
    ./src/utils/qt_optional.h
    ./src/utils/qt_macroexpander.cpp
    ./src/utils/qt_macroexpander.h
    ./src/utils/qt_pathchooser.cpp
    ./src/utils/qt_pathchooser.h
    ./src/utils/qt_completinglineedit.cpp
    ./src/utils/qt_completinglineedit.h
    ./src/utils/qt_fancylineedit.cpp
    ./src/utils/qt_fancylineedit.h
    ./src/utils/qt_namevalueitem.cpp
    ./src/utils/qt_namevalueitem.h
    ./src/utils/qt_namevaluedictionary.cpp
    ./src/utils/qt_namevaluedictionary.h
    )
source_group(\\Utils FILES ${QtUtils_SRC})

set(SRC_Propbrowser
    ./src/propbrowser/qt_propbrowserwidget.cpp
    ./src/propbrowser/qt_propbrowserwidget.h
    ./src/propbrowser/qt_propertybrowser.cpp
    ./src/propbrowser/qt_propertymanager.cpp
    ./src/propbrowser/qt_propertymanagerprivate.h
    ./src/propbrowser/qt_editorfactory.cpp
    ./src/propbrowser/qt_editorfactoryprivate.h
    ./src/propbrowser/qt_variantproperty.cpp
    ./src/propbrowser/qt_treepropertybrowser.cpp
    ./src/propbrowser/qt_treepropertybrowserprivate.h
    ./src/propbrowser/qt_buttonpropertybrowser.cpp
    ./src/propbrowser/qt_groupboxpropertybrowser.cpp
    ./src/propbrowser/qt_propertybrowserutils.cpp
    ./src/propbrowser/qt_propertybrowserutilsprivate.h
    ./src/propbrowser/qt_editorfactory.h
    )
source_group(PropBrowser FILES ${SRC_Propbrowser})

set(SRC_Projectexplorer
    ./src/projectexplorer/qt_modelnodes.cpp
    ./src/projectexplorer/qt_modelnodes.h
    ./src/projectexplorer/qt_modeltreewidget.cpp
    ./src/projectexplorer/qt_modeltreewidget.h
    ./src/projectexplorer/qt_treemodel.cpp
    ./src/projectexplorer/qt_treemodel.h
    ./src/projectexplorer/qt_projectmodels.cpp
    ./src/projectexplorer/qt_projectmodels.h
    ./src/projectexplorer/qt_project.cpp
    ./src/projectexplorer/qt_project.h
    )
source_group(ProjectExplorer FILES ${SRC_Projectexplorer})

set(SRC_PropEditor
    ./src/propeditor/qt_materialprop.cpp
    ./src/propeditor/qt_materialprop.h
    )
source_group(PropEditor FILES ${SRC_PropEditor})

set(SRC_ModPrjManager
    ./src/modprjmanager/qt_createnodetreebuilder.cpp
    ./src/modprjmanager/qt_createnodetreebuilder.h
    ./src/modprjmanager/qt_createprjnodes.cpp
    ./src/modprjmanager/qt_createprjnodes.h
    )
source_group(ModPrjManager FILES ${SRC_ModPrjManager})

set(SRC_ModelEditor
    ./src/modeleditor/qt_modeleditor.cpp
    ./src/modeleditor/qt_modeleditor.h
    ./src/modeleditor/qt_modelview.cpp
    ./src/modeleditor/qt_modelview.h
    ./src/modeleditor/qt_modeldocument.cpp
    ./src/modeleditor/qt_modeldocument.h
    )
source_group(ModelEditor FILES ${SRC_ModelEditor})

set(MOC_Files
    ./Include/qt_openglwindow.h
    ./Include/qt_licensewnd.h
    ./Include/qt_colorbutton.h

    ./Include/qt_propertybrowser.h
    ./Include/qt_propertymanager.h
    ./Include/qt_variantproperty.h

    ./Include/qt_treepropertybrowser.h
    ./Include/qt_groupboxpropertybrowser.h

    ./src/core/qt_mainwindow.h
    ./src/core/qt_openglwidget.h
    ./src/core/qt_sdimainwindow.h
    ./src/core/qt_mdimainwindow.h
    ./src/core/qt_icore.h
    ./src/core/actionmanager/qt_actioncontainer.h
    ./src/core/actionmanager/qt_actionmanager.h
    ./src/core/actionmanager/qt_command.h
    ./src/core/dialogs/qt_ioptionspage.h

    ./src/propbrowser/qt_buttonpropertybrowser.h
    ./src/propeditor/qt_materialprop.h

    ./src/style/qt_theme.h
    ./src/style/qt_c3dstyle.h
    ./src/utils/qt_headsuptoolbar.h
    ./src/utils/qt_orientationbar.h
    ./src/utils/qt_sceneviewcontroller.h
    ./src/utils/qt_appmainwindow.h
    ./src/utils/qt_processmanager.h
    ./src/utils/qt_aspects.h
    ./src/utils/qt_savefile.h
    ./src/utils/qt_fancylineedit.h
    ./src/utils/qt_completinglineedit.h
    ./src/utils/qt_elidinglabel.h
    ./src/utils/qt_pathchooser.h
)
vsn_qt_wrap_cpp(MOC_Gui ${MOC_Files})

set(MOC_FilesPrivate
    ./src/projectexplorer/qt_modeltreewidget.h
    ./src/projectexplorer/qt_treemodel.h
    ./src/projectexplorer/qt_projectmodels.h

    ./src/propbrowser/qt_propbrowserwidget.h
    ./src/propbrowser/qt_editorfactory.h
    ./src/propbrowser/qt_editorfactoryprivate.h
    ./src/propbrowser/qt_treepropertybrowserprivate.h
    ./src/propbrowser/qt_propertymanagerprivate.h
    ./src/propbrowser/qt_propertybrowserutilsprivate.h

    ./src/core/actionmanager/qt_actionmanagerprivate.h
    ./src/core/actionmanager/qt_actioncontainerprivate.h
    ./src/core/actionmanager/qt_commandprivate.h

    ./src/modeleditor/qt_modeleditor.h
    ./src/modeleditor/qt_modelview.h
    ./src/modeleditor/qt_modeldocument.h

    ./src/utils/qt_commandbar.h
    ./src/utils/qt_previewwidget.h
    ./src/utils/qt_proxyaction.h
    ./src/utils/qt_completionshortcut.h
)
vsn_qt_wrap_cpp(MOC_GUIPrivate ${MOC_FilesPrivate})

set(RCC_Files_Vision 
    ./src/qt_openglwidget.qrc
    ./src/propbrowser/qt_propertybrowser.qrc
)
vsn_qt_add_resources(RCC_Gui ${RCC_Files_Vision})

set(QtVision_INC
    ./Include/qt_id.h
    ./Include/qt_propbrowserwidget.h
    ./Include/qt_openglwidget.h
    ./Include/qt_openglcontext.h
    ./Include/qt_openglwindow.h
    ./Include/qt_resstream.h
    ./Include/qt_licensewnd.h
    ./Include/qt_cursors.h
    ./Include/qt_headsuptoolbar.h
    ./Include/qt_colorbutton.h
    ./Include/qt_global.h
    ./Include/qt_osspecificaspects.h
    ./Include/qt_mainwindow.h
    ./Include/qt_application.h
    ./Include/qt_materialprop.h
    ./Include/qt_sceneviewcontroller.h
    ./Include/qt_orientationbar.h
    ./Include/qt_vision.h
    )
source_group(Include FILES ${QtVision_INC})

set(QT_SRC_Shared
    ${SHARED_DIR}/readwritelic.cpp
    ${SHARED_DIR}/readwritelic.h
    )

if(MathTest_NAMES)
    string(REPLACE "Source" "Revisions" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
else()
    string(REPLACE "Source" "Install" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
endif()

if(MSVC)
    add_definitions(
        -D_WIN32_WINNT=0X0502
    )
endif()

add_definitions(
    -D_BUILDQTVISIONDLL
    -DOGLFT_NO_QT
    -DOGLFT_NO_SOLID
    -DNOMINMAX
)

if(UNIX)
    add_definitions(
        -DVSN_OS_UNIX
    )
    #  ADD_DEFINITIONS(-D_GLIBCXX_USE_CXX11_ABI=0)
else()
    add_definitions(
        -DVSN_OS_WIN32
        -DVSN_OS_WIN
    )
endif()

if(MSVC)
    if(C3DVision_USING_UNICODE)
        add_definitions(
            -DUNICODE
            -D_UNICODE
        )
    endif()
endif()

if(C3DVision_WITH_VLD)
    add_definitions(
        -DENABLE_VLD
    )
endif()

#ADD_DEFINITIONS(
#    -D__USE_QT__
#)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W4 /MP /bigobj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_ITERATOR_DEBUG_LEVEL=0 /Zi /W4")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -std=c++11 -D_DEBUG -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -std=c++11 -D_ITERATOR_DEBUG_LEVEL=0 -Wno-deprecated-declarations -fno-operator-names")
endif()
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE}")

# метод сборки библиотеки
set(QtVisionBuildMethod SHARED)
# if(?)  # TODO
    # add_definitions(
    #     -DQT_VISION_STATIC
    #     -DQT_VISION_EXPORT
    # )
    # set(QtVisionBuildMethod STATIC)
# endif()

add_library(${QtVision_OUTPUT} ${QtVisionBuildMethod}
    ${QtCore_SRC}
    ${QtActionmanager_SRC}
    ${QtDialogs_SRC}
    ${QtStyle_SRC}
    ${QtUtils_SRC}
    ${SRC_Propbrowser}
    ${SRC_Projectexplorer}
    ${SRC_ModPrjManager}
    ${SRC_PropEditor}
    ${SRC_ModelEditor}
    ${QtVision_INC}
    ${MOC_Gui}
    ${MOC_GUIPrivate}
    ${RCC_Gui}
    ${QT_SRC_Shared}
    )

target_include_directories(${QtVision_OUTPUT}
    PRIVATE
    ${MATH_INCLUDE_TARGET}
    ${VLD_INCLUDE_DIRS}
    PUBLIC
    ${C3D_Vision_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/actionmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/dialogs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/style
    ${CMAKE_CURRENT_SOURCE_DIR}/src/projectexplorer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modprjmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/src/propbrowser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modeleditor
    ${CMAKE_CURRENT_SOURCE_DIR}/src/propeditor
)

if(C3DVision_GUI_QT5_EXAMPLES)
    set(C3DVision_GUI_QT6_EXAMPLES OFF)
    cmake_dependent_option(C3DVision_GUI_QT6_EXAMPLES
        C3DVision_GUI_QT5_EXAMPLES ON
        C3DVision_GUI_QT6_EXAMPLES OFF
        )
elseif(C3DVision_GUI_QT6_EXAMPLES)
    set(C3DVision_GUI_QT5_EXAMPLES OFF)
    cmake_dependent_option(C3DVision_GUI_QT5_EXAMPLES
        C3DVision_GUI_QT6_EXAMPLES ON
        C3DVision_GUI_QT5_EXAMPLES OFF
        )
endif()

if(C3DVision_NEED_QT5)
    target_link_libraries(${QtVision_OUTPUT} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)
elseif(C3DVision_GUI_QT6_EXAMPLES)
    target_link_libraries(${QtVision_OUTPUT} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
endif()

if(UNIX)
    set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

target_link_libraries(
    ${QtVision_OUTPUT}
    PUBLIC
    mbvision
    PRIVATE
    ${MATH_LIBRARY_TARGET}
    ${VLD_LIBRARIES}
)
if(Examples_StandaloneBuild)
    target_link_directories(${QtVision_OUTPUT} PRIVATE "${C3D_Vision_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>")
endif()

# Make optional since Examples folder is packaged and distributed in-source separately.
include(strip_debug_symbols_support OPTIONAL RESULT_VARIABLE _strip_debug_symbols_module)
if(_strip_debug_symbols_module)
    message(STATUS "Module ${_strip_debug_symbols_module} was found")
    # Strip debug symbols before installation
    strip_debug_symbols(${QtVision_OUTPUT} True ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
else()
    message(STATUS "Module \'strip_debug_symbols_support\' was skipped")
endif()

message(STATUS "${QtVision_OUTPUT} Compile C++ Flags (Debug): " ${CMAKE_CXX_FLAGS_DEBUG})
message(STATUS "${QtVision_OUTPUT} Compile C++ Flags (Release): " ${CMAKE_CXX_FLAGS_RELEASE})
