function(add_cnoid_python_module)
  
  set(target ${ARGV0})
  string(REGEX REPLACE "^Py(.+)$" "\\1" module ${target})
  set(sources ${ARGV})
  list(REMOVE_AT sources 0)

  add_library(${target} SHARED ${sources})
    
  set_target_properties(${target} PROPERTIES
    COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY" )

  set_target_properties(${target}  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CNOID_PYTHON_SUBDIR}/cnoid
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CNOID_PYTHON_SUBDIR}/cnoid
    RUNTIME_OUTPUT_NAME ${module}
    LIBRARY_OUTPUT_NAME ${module}
    PREFIX "")

  if(ENABLE_INSTALL_RPATH)
    set_target_properties(${target} PROPERTIES INSTALL_RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
  endif()

  install(TARGETS ${target}
    RUNTIME DESTINATION ${CNOID_PYTHON_SUBDIR}/cnoid CONFIGURATIONS Release Debug RelWithDebInfo MinSizeRel
    LIBRARY DESTINATION ${CNOID_PYTHON_SUBDIR}/cnoid CONFIGURATIONS Release Debug RelWithDebInfo MinSizeRel)
endfunction()

add_subdirectory(Util)
