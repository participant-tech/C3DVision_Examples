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

project(02_N2)

################################################################################
# Build the Tutorial/N2 executables
################################################################################
set(SRC_02_N2 ${CMAKE_CURRENT_SOURCE_DIR}/N2.cpp)

add_executable(${02_N2_OUTPUT} WIN32 ${MOC_Gui} ${SRC_02_N2})
target_link_libraries(${02_N2_OUTPUT} PRIVATE qtvision ${STDLIB})
vsn_link_with_qt_vislib_math(${02_N2_OUTPUT} True)

set_target_properties(${02_N2_OUTPUT} PROPERTIES FOLDER ${Examples_OUTPUT}/Qt)
###############################################################################