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

project(03_N3)

################################################################################
# Build the Tutorial/N3 executables
################################################################################
set(SRC_03_N3 ${CMAKE_CURRENT_SOURCE_DIR}/N3.cpp)

add_executable(${03_N3_OUTPUT} WIN32 ${MOC_Gui} ${SRC_03_N3})
target_link_libraries(${03_N3_OUTPUT} PRIVATE ${QtVision_OUTPUT} ${STDLIB})
vsn_link_with_qt_vislib_math(${03_N3_OUTPUT} False)

set_target_properties(${03_N3_OUTPUT} PROPERTIES FOLDER ${Examples_OUTPUT}/Qt)
###############################################################################