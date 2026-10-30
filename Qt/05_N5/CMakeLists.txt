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

project(05_N5)

################################################################################
# Build the Example/N5 executables
################################################################################
set(SRC_05_N5 ${CMAKE_CURRENT_SOURCE_DIR}/N5.cpp)

add_executable(${05_N5_OUTPUT} WIN32 ${MOC_Gui} ${SRC_05_N5})
target_link_libraries(${05_N5_OUTPUT} PRIVATE ${QtVision_OUTPUT} ${STDLIB})
vsn_link_with_qt_vislib_math(${05_N5_OUTPUT} True)

set_target_properties(${05_N5_OUTPUT} PROPERTIES FOLDER ${Examples_OUTPUT}/Qt)
###############################################################################