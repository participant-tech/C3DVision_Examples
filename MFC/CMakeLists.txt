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

################################################################################
# Build the Example/Test executables
################################################################################

if(C3DVision_GUI_MFC_EXAMPLES)
    ###############################################################################

    # MFC_Example
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        Common
        ${MATH_INCLUDE_TARGET}
        ${VLD_LIBRARIES}
        ${C3D_Vision_INCLUDE_DIR})

    if(C3DVision_USING_UNICODE)
        add_definitions(-DUNICODE -D_UNICODE)
    endif()

    ###############################################################################
    # Cube
    set(Cube_OUTPUT "Cube")
    add_subdirectory(Cube)
    ###############################################################################
    # Viewer
    set(Viewer_OUTPUT "Viewer")
    add_subdirectory(Viewer)
    ###############################################################################
endif()



