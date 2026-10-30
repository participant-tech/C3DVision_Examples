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
project(Cube)

################################################################################
# Build the Example/Cube executables
################################################################################
add_executable(${Cube_OUTPUT} WIN32
    ../Common/stdafx.cpp
    ../Common/stdafx.h
    ../Cube/cube.cpp
    ../Cube/cubeview.cpp
    ../Cube/cubeview.h)

target_link_libraries(
    ${Cube_OUTPUT}
    PRIVATE
    ${MATH_LIBRARY_TARGET}
    ${C3D_VIS_LIB}
    ${MfcVision_OUTPUT}
)
if(Examples_StandaloneBuild)
    target_link_directories(${Cube_OUTPUT} PRIVATE "${C3D_Vision_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>")
endif()

set_target_properties(${Cube_OUTPUT} PROPERTIES COMPILE_FLAGS -D_AFXDLL FOLDER ${Examples_MFC_OUTPUT})
if(C3DVision_USING_UNICODE)
    set_target_properties(${Cube_OUTPUT} PROPERTIES LINK_FLAGS /ENTRY:wWinMainCRTStartup)
endif()
###############################################################################
