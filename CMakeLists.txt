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
project(C3DVision_Examples)

###
### CMake options
###

option(Examples_StandaloneBuildByConan "Build source code in Examples folder by conanfile-examples-usage recipe" OFF)

if(NOT DEFINED C3DVision_KERNEL_PKG_DIRECT_LINKAGE)
    # Option is defined to enable the possibility of Examples standalone built
    option(C3DVision_KERNEL_PKG_DIRECT_LINKAGE "Link with c3d kernel by direct linkage" ON)
    if(NOT Examples_StandaloneBuildByConan)
        set(Examples_StandaloneBuild True CACHE BOOL "True for standalone build of Examples folder without conan")
    endif()
    message(STATUS "Selected standalone build of Examples")  # via CMakeLists.txt in Examples dir
endif()

set(C3DVision_STANDARD_CXX 2017 CACHE STRING "C++ standard version")
string(SUBSTRING ${C3DVision_STANDARD_CXX} 2 3 CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W4 /MP /bigobj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_ITERATOR_DEBUG_LEVEL=0 /W4")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_ITERATOR_DEBUG_LEVEL=0 -Wno-deprecated-declarations -fno-operator-names")
endif()
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE}")

option(C3DVision_USING_UNICODE "Enable Unicode support" ON)

option(C3DVision_GUI_QT5_EXAMPLES "Build Qt examples with Qt5 support" ON)
option(C3DVision_GUI_QT6_EXAMPLES "Build Qt examples with Qt6 support" OFF)

if(NOT UNIX)
    option(C3DVision_GUI_MFC_EXAMPLES "Build with MFC support" ON)
endif()

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
  set_property(CACHE CMAKE_CONFIGURATION_TYPES PROPERTY VALUE "Debug;RelWithDebInfo;Release")
endif()


###
### c3dvision library: set linkage method for Examples standalone builds
###

set(Examples_OUTPUT "Examples")
if(Examples_StandaloneBuildByConan)
    find_package(c3dvision REQUIRED)
    message(STATUS "c3dvision library linkage mode: linking with c3dvision conan package")
    if(c3dvision_FOUND)
        set(C3D_VIS_LIB c3dvision::c3dvision)
        get_property(C3D_Vision_INCLUDE_DIR
            TARGET c3dvision::headers
            PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    endif()
else()
    if(NOT C3D_Vision_DIR OR NOT C3D_Vision_INCLUDE_DIR)
        message(STATUS "c3dvision library linkage mode: linking directly with the binary")
        set(C3D_Vision_DIR "${CMAKE_SOURCE_DIR}/../Vision" CACHE STRING "Folder with Debug/ and Release/ prebuilt 'c3dvision' library targets")
        set(C3D_Vision_INCLUDE_DIR "${C3D_Vision_DIR}/Include" CACHE STRING "Folder with 'c3dvision' library public 'include' files")
    endif()
endif()

if(NOT C3D_VIS_LIB)
    set(C3D_VIS_LIB "${Vision_OUTPUT}")  # May be defined by root-level CMakeLists.txt
    if(NOT C3D_VIS_LIB)
        set(C3D_VIS_LIB "c3dvision")
    endif()
endif()


###
### C3D kernel library: linkage mode selection
###

if(Examples_StandaloneBuild OR Examples_StandaloneBuildByConan)
    if(C3DVision_KERNEL_PKG_DIRECT_LINKAGE AND NOT Examples_StandaloneBuildByConan)
        # Variables below are used when kernel is provided not by conan package, but directly (folder with prebuild artifacts)
        message(STATUS "c3d kernel library linkage mode: linking directly with the binary")
        if(NOT C3D_MATH_DIR)
            set(C3D_MATH_DIR "$ENV{C3D_MATH_DIR}")
        endif()

        if(NOT C3D_MATH_DIR)
            set(C3D_MATH_DIR "${CMAKE_SOURCE_DIR}/../Kernel")
        endif()
        message(STATUS "C3D_MATH_DIR: '${C3D_MATH_DIR}'")

        if(NOT C3D_MATH_INCLUDE_DIR)
            set(C3D_MATH_INCLUDE_DIR "${C3D_MATH_DIR}/Include" "${C3D_MATH_DIR}/include" "${C3D_MATH_DIR}/include/c3d")
        endif()

        if(UNIX)
            if(APPLE)
                set(C3D_MATH_NAME libc3d.dylib)
            else()
                set(C3D_MATH_NAME libc3d.so)
            endif()
        else()
            set(C3D_MATH_NAME c3d.lib)
        endif()

        set(Math_OUTPUT optimized "${C3D_MATH_DIR}/Release/${C3D_MATH_NAME}" debug "${C3D_MATH_DIR}/Debug/${C3D_MATH_NAME}")
        unset(C3D_MATH_NAME)
    else()
        find_package(c3d REQUIRED)
        message(STATUS "c3d kernel library linkage mode: linking with c3d conan package")
        if(c3d_FOUND)
            set(c3d_lib c3d::c3d)
            get_property(c3d_headers
                TARGET c3d::headers
                PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
        endif()
    endif()
    set(MATH_LIBRARY_TARGET ${c3d_lib} "${Math_OUTPUT}" CACHE STRING "Folder with Debug/ and Release/ prebuilt 'c3d' kernel library targets")
    set(MATH_INCLUDE_TARGET ${c3d_headers} "${C3D_MATH_INCLUDE_DIR}" CACHE STRING "Folder with 'c3d' kernel library public 'include' files")
    unset(Math_OUTPUT)
    unset(C3D_MATH_INCLUDE_DIR)
endif()


if(NOT C3D_CONVERTER_PLUGIN_DIR)
    set(C3D_CONVERTER_PLUGIN_DIR "${CMAKE_SOURCE_DIR}/../Plugins")
endif()

###
### Output folder selection
###

set(EXAMPLES_BIN "${CMAKE_BINARY_DIR}/bin/")
if(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(EXAMPLES_BIN "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EXAMPLES_BIN}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EXAMPLES_BIN}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXAMPLES_BIN}")
if(MSVC)
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${EXAMPLES_BIN}")
endif()

# Shared auxiliary files for all examples.
set(SHARED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shared")

if(C3DVision_USING_UNICODE)
    add_definitions(
        -DUNICODE
        -D_UNICODE
    )
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SHARED_DIR}
)

if(UNIX)
    add_definitions(-std=c++17)
    set(STDLIB stdc++)
else()
    set(STDLIB "")
endif()

if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_SANDBOX OR C3DVision_GUI_QT6_EXAMPLES OR C3DVision_GUI_MFC_EXAMPLES)
    if(MSVC)
        set(debug_suffix "Debug")
        set(release_suffix "Release")
        set(release_suffix_2 "RelWithDebInfo")
    endif()
    if(NOT Examples_StandaloneBuildByConan AND C3DVision_KERNEL_PKG_DIRECT_LINKAGE)
        message(STATUS "Copying c3d kernel binaries subdirs from '${C3D_MATH_DIR}' to '${CMAKE_RUNTIME_OUTPUT_DIRECTORY}'...")
        if(EXISTS "${C3D_MATH_DIR}/Debug")
            file(COPY "${C3D_MATH_DIR}/Debug/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${debug_suffix}")
        endif()
        if(EXISTS "${C3D_MATH_DIR}/Release")
            file(COPY "${C3D_MATH_DIR}/Release/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix}")
            file(COPY "${C3D_MATH_DIR}/Release/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix_2}")
        endif()
    endif()

    if(EXISTS "${C3D_CONVERTER_PLUGIN_DIR}")
        if(EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
            file(COPY "${C3D_CONVERTER_PLUGIN_DIR}/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${debug_suffix}")
        endif()
        if(EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
            file(COPY "${C3D_CONVERTER_PLUGIN_DIR}/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix}")
            file(COPY "${C3D_CONVERTER_PLUGIN_DIR}/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix_2}")
        endif()
        add_definitions(-D_USE_PLUGINS_)
    endif()
    
    if(NOT Examples_StandaloneBuildByConan AND NOT C3D_Vision_DIR STREQUAL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        message(STATUS "Copying c3dvision binaries subdirs from '${C3D_Vision_DIR}' to '${CMAKE_RUNTIME_OUTPUT_DIRECTORY}'...")
        if(EXISTS "${C3D_Vision_DIR}/Debug")
            file(COPY "${C3D_Vision_DIR}/Debug/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${debug_suffix}")
        endif()
        if(EXISTS "${C3D_Vision_DIR}/Release")
            file(COPY "${C3D_Vision_DIR}/Release/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix}")
            file(COPY "${C3D_Vision_DIR}/Release/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${release_suffix_2}")
        endif()
    endif()
endif()


###############################################################################
#  QT Examples
###############################################################################

# Append CMAKE_PREFIX_PATH for QtX builds
if(Examples_StandaloneBuild)  # otherwise set by conan_provider module
    if(DEFINED ENV{QT_PATH})  # Path to Qt distribution folder with 'lib' subfolder
        list(FIND CMAKE_PREFIX_PATH "$ENV{QT_PATH}" idx_of_qt)
        if(idx_of_qt EQUAL -1)
            list(PREPEND CMAKE_PREFIX_PATH "$ENV{QT_PATH}")
            message(STATUS "Expanding CMAKE_PREFIX_PATH with QT_PATH: '${CMAKE_PREFIX_PATH}'")
        endif()
        unset(idx_of_qt)
    else()
        message(WARNING "QT_PATH env variable pointing to QT distribution folder is not set")
    endif()
endif()

if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_SANDBOX)
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)
elseif(C3DVision_GUI_QT6_EXAMPLES)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets OpenGL)
endif()

if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_GUI_QT6_EXAMPLES OR C3DVision_SANDBOX)
    add_definitions(-D__USE_QT__)
    add_definitions(-DQT_NO_DEPRECATED_WARNINGS)
    set(QtVision_OUTPUT "qtvision")
endif()

if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_GUI_QT6_EXAMPLES)
    set(Examples_Qt_OUTPUT ${Examples_OUTPUT}/Qt)

    include_directories(
        ${MATH_INCLUDE_TARGET}
        ${C3D_Vision_INCLUDE_DIR}
        ${QtVision_SOURCE_DIR}/Include)
    add_definitions(-DQT_NO_DEPRECATED_WARNINGS)
    add_subdirectory(Qt)
    add_definitions(-DNOMINMAX)
endif()

###############################################################################
#  MFC Examples
###############################################################################
if(C3DVision_GUI_MFC_EXAMPLES)
    set(MfcVision_OUTPUT "mfcvision")
    set(Examples_MFC_OUTPUT ${Examples_OUTPUT}/MFC/)
    add_subdirectory(MFC)
endif()

###############################################################################
#  MB Examples
###############################################################################
add_subdirectory(VisionKit)
