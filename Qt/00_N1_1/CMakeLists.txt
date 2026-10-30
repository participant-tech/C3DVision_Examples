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

project(00_N1_1)

################################################################################
# Build the Example executable
################################################################################
set(SRC_00_N1_1 ${CMAKE_CURRENT_SOURCE_DIR}/N1_1.cpp)  # или triangle.cpp

add_executable(${00_N1_1_OUTPUT} WIN32 ${MOC_Gui} ${SRC_00_N1_1})
target_link_libraries(${00_N1_1_OUTPUT} PRIVATE ${QtVision_OUTPUT} ${STDLIB})
vsn_link_with_qt_vislib_math(${00_N1_1_OUTPUT} True)

set_target_properties(${00_N1_1_OUTPUT} PROPERTIES FOLDER ${Examples_OUTPUT}/Qt)