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
#project(Examples)

add_subdirectory(MbVision)
if(C3DVision_GUI_MFC_EXAMPLES)
    add_subdirectory(MfcVision)
endif()

if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_GUI_QT6_EXAMPLES OR C3DVision_SANDBOX)
    add_definitions(-D__USE_QT__)
    add_definitions(-DQT_NO_DEPRECATED_WARNINGS)
    set(QtVision_OUTPUT "qtvision")
    add_subdirectory(QtVision)
endif()



