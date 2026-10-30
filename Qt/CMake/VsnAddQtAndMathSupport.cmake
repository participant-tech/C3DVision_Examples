function(vsn_link_with_qt_vislib_math
  target_name
  require_math_support)

  if(C3DVision_GUI_QT5_EXAMPLES OR C3DVision_SANDBOX)
    target_link_libraries(${target_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)
  elseif(C3DVision_GUI_QT6_EXAMPLES)
    target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets Qt6::OpenGL)
  endif()

  if(require_math_support)
    if(MATH_LIBRARY_TARGET STREQUAL "" OR MATH_INCLUDE_TARGET STREQUAL "")
      message(FATAL_ERROR
        "MATH_LIBRARY_TARGET (${MATH_LIBRARY_TARGET}) and MATH_INCLUDE_TARGET (${MATH_INCLUDE_TARGET}) variables should be defined!")
    endif()

    # If conan build, link with c3d::c3d CMake target,
    # if standalone build, link with c3d kernel library directly
    target_link_libraries(${target_name} PRIVATE ${MATH_LIBRARY_TARGET} ${VLD_LIBRARIES})

    target_include_directories(${target_name} PRIVATE ${MATH_INCLUDE_TARGET} ${VLD_INCLUDE_DIRS})
  endif()

  # Link with c3dvision
  target_link_libraries(${target_name} PRIVATE ${C3D_VIS_LIB})
  target_include_directories(${target_name} PRIVATE ${C3D_Vision_INCLUDE_DIR})
  if(Examples_StandaloneBuild)
    target_link_directories(${target_name} PRIVATE "${C3D_Vision_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>")
  endif()
endfunction()
