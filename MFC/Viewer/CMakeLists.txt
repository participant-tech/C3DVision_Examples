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
project(Viewer)

################################################################################
# Build the Example/Mdi executables
################################################################################
# MFC_MDI_Example
add_executable(${Viewer_OUTPUT} WIN32
    ../Viewer/stdafx.cpp
    ../Viewer/stdafx.h
    ../Viewer/viewerapplication.cpp
    ../Viewer/viewerapplication.h
    ../Viewer/viewerapplication.rc
    ../Viewer/mainfrm.cpp
    ../Viewer/mainfrm.h
    ../Viewer/childfrm.cpp
    ../Viewer/childfrm.h
    ../Viewer/viewerview.cpp
    ../Viewer/viewerview.h
    ../Viewer/viewerdoc.cpp
    ../Viewer/viewerdoc.h
    ../Viewer/classview.cpp
    ../Viewer/classview.h
    ../Viewer/viewtree.cpp
    ../Viewer/viewtree.h
    ../Viewer/propertieswnd.cpp
    ../Viewer/propertieswnd.h
    ../Viewer/resource.h
    ${SRC_Shared})

target_link_libraries(
    ${Viewer_OUTPUT}
    PRIVATE
    ${MATH_LIBRARY_TARGET}
    ${C3D_VIS_LIB}
    ${MfcVision_OUTPUT}
    mbvision
)

set_target_properties(${Viewer_OUTPUT} PROPERTIES COMPILE_FLAGS -D_AFXDLL FOLDER ${Examples_MFC_OUTPUT})

if(C3DVision_USING_UNICODE)
    set_target_properties(${Viewer_OUTPUT} PROPERTIES LINK_FLAGS /ENTRY:wWinMainCRTStartup)
endif()
###############################################################################
