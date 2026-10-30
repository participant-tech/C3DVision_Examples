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
project(MbVision)

# C3D Model eXtension files are shared for all examples.
set(MbModex_SRC
#        utest_model_extension.cpp
    ./src/modex/mx_brep_model.cpp
    ./src/modex/mx_brep_model.h
    ./src/modex/mx_dimension.cpp
    ./src/modex/mx_dimension.h
    ./src/modex/mx_model_extension.cpp
    ./src/modex/mx_model_extension.h
    ./src/modex/mx_model_routines.cpp
    ./src/modex/mx_model_routines.h
    ./src/modex/mx_model_tree.cpp
    ./src/modex/mx_model_tree.h
    ./src/modex/mx_types.h
    )
source_group(\\Modex FILES ${MbModex_SRC})

set(MbCommon_SRC
    ./src/common/mb_scenegenerator.cpp
    ./src/common/mb_scenegenerator.h
    ./src/common/mb_progressbuild.cpp
    ./src/common/mb_progressbuild.h
    )
source_group(\\Common FILES ${MbCommon_SRC})

set(MbExt_SRC
    ./src/ext/mb_pointcloud.cpp
    ./src/ext/mb_pointcloud.h
)
source_group(\\Ext FILES ${MbExt_SRC})

set(MbVision_INC
    ./include/mb_scenegenerator.h
    ./include/mx_model_tree.h
    ./include/mx_model_extension.h
    ./include/mx_model_routines.h
    ./include/mb_visiondef.h
    ./include/mx_types.h
    ./include/mb_pointcloud.h
    )
source_group(Include FILES ${MbVision_INC})


if(MathTest_NAMES)
    string(REPLACE "Source" "Revisions" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
else()
    string(REPLACE "Source" "Install" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
endif()

add_definitions(
    -D_WIN32_WINNT=0X0502
)

add_definitions(
    -D_BUILDMBVISIONDLL
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

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W4 /MP /bigobj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_ITERATOR_DEBUG_LEVEL=0 /W4")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -std=c++11 -D_DEBUG -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -std=c++11 -D_ITERATOR_DEBUG_LEVEL=0 -Wno-deprecated-declarations -fno-operator-names")
endif()
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE}")

# метод сборки библиотеки
# set(MbVisionBuildMethod SHARED)
# if(?)  # TODO
#     add_definitions(
#         -DMB_VISION_STATIC
#         -DMB_VISION_EXPORT
#     )
#     set(MbVisionBuildMethod STATIC)
# endif()

add_library(mbvision ${MbVisionBuildMethod}
    ${MbModex_SRC} ${MbCommon_SRC} ${MbExt_SRC} ${MbVision_INC})
set_property(TARGET mbvision PROPERTY POSITION_INDEPENDENT_CODE TRUE)

# add linked libs
target_link_libraries(mbvision
    PRIVATE
    ${MATH_LIBRARY_TARGET}
    ${VLD_LIBRARIES}
    ${C3D_VIS_LIB}
)
if(Examples_StandaloneBuild)
    target_link_directories(mbvision PUBLIC "${C3D_Vision_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>")
endif()

target_include_directories(mbvision
    PRIVATE
    src/common
    src/modex
    src/ext
    ${MATH_INCLUDE_TARGET}
    ${VLD_INCLUDE_DIRS}
    PUBLIC
    include
    ${C3D_Vision_INCLUDE_DIR}
)
