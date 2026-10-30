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
project(MfcVision)

set(MfcCore_SRC
    ./src/mfc_stdafx.cpp
    ./src/mfc_openglview.cpp
    ./src/mfc_openglwnd.cpp
    ./src/mfc_scenerenderer.cpp
    ./src/mfc_licensewnd.cpp
    ./src/mfc_exampleview.cpp
    ./src/mfc_exampletools.cpp
    )
source_group(\\Core FILES ${MfcCore_SRC})

set(MfcVision_INC
    ./include/mfc_stdafx.h
    ./include/mfc_openglview.h
    ./include/mfc_openglwnd.h
    ./include/mfc_scenerenderer.h
    ./include/mfc_scenerendererprivate.h
    ./include/mfc_exampleview.h
    ./include/mfc_exampletools.h
    ./include/mfc_licensewnd.h
    ./include/mfc_visiondef.h
    )
source_group(Include FILES ${MfcVision_INC})

set(MFC_SRC_Shared
    ${SHARED_DIR}/readwritelic.cpp
    ${SHARED_DIR}/readwritelic.h
)

if(MathTest_NAMES)
    string(REPLACE "Source" "Revisions" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
else()
    string(REPLACE "Source" "Install" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
endif()

add_definitions(
    -D_WIN32_WINNT=0X0502
)

add_definitions(
    -D_BUILDMFCVISIONDLL
    -DOGLFT_NO_SOLID
    -DNOMINMAX
    -D_AFXDLL
)

add_definitions(-DVSN_OS_WIN32 -DVSN_OS_WIN)

if(C3DVision_USING_UNICODE)
    add_definitions(
        -DUNICODE
        -D_UNICODE
    )
endif()

if(C3DVision_WITH_VLD)
    add_definitions(
        -DENABLE_VLD
    )
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W4 /MP /bigobj")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_ITERATOR_DEBUG_LEVEL=0 /Zi /W4")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE}")

add_library(
    ${MfcVision_OUTPUT}
    SHARED
    ${MfcCore_SRC}
    ${MfcVision_INC}
    ${MFC_SRC_Shared}
)

target_include_directories(${MfcVision_OUTPUT}
    PUBLIC
    Include
    PRIVATE
    ${MATH_INCLUDE_TARGET}
    ${VLD_INCLUDE_DIRS}
    ${C3D_Vision_INCLUDE_DIR}
)

target_link_libraries(
    ${MfcVision_OUTPUT}
    PRIVATE
    ${MATH_LIBRARY_TARGET}
    ${VLD_LIBRARIES}
    ${C3D_VIS_LIB}
)
if(Examples_StandaloneBuild)
    target_link_directories(${MfcVision_OUTPUT} PRIVATE "${C3D_Vision_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>")
endif()

#IF(MathTest_NAMES)
# INSTALL(TARGETS ${MfcVision_OUTPUT}
#     RUNTIME DESTINATION ${MfcVision_VERSION}/${MfcVision_PLATFORM})
# ADD_CUSTOM_COMMAND(TARGET ${MfcVision_OUTPUT}
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -DBUILD_TYPE=$<CONFIG> -P cmake_install.cmake)
#ENDIF(MathTest_NAMES)
