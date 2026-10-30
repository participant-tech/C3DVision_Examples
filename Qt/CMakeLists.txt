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
project(Examples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
include(VsnAddQtAndMathSupport)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../VisionKit/QtVision/CMake")
include(VsnQtCoreDeploySupport)


################################################################################
# Build the Example/Test executables
################################################################################
if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_GUI_QT6_EXAMPLES)
    ###############################################################################
    # ElementarySolid1
    set(00_N1_1_OUTPUT "00_N1_1")
    add_subdirectory(00_N1_1)
    ###############################################################################
    # ElementarySolid2
    set(01_N1_2_OUTPUT "01_N1_2")
    add_subdirectory(01_N1_2)
    ###############################################################################
    # Union
    set(02_N2_OUTPUT "02_N2")
    add_subdirectory(02_N2)
    ###############################################################################
    # Fillet
    set(03_N3_OUTPUT "03_N3")
    add_subdirectory(03_N3)
    ###############################################################################
    # MbMesh
    set(04_N4_OUTPUT "04_N4")
    add_subdirectory(04_N4)
    ###############################################################################
    # MbPolyMesh
    set(05_N5_OUTPUT "05_N5")
    add_subdirectory(05_N5)
endif()
