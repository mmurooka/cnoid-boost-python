option(BUILD_BOOST_PYTHON_MODULES "Building Boost.Python version Python Wrappers" OFF)
if(NOT BUILD_BOOST_PYTHON_MODULES)
  return()
endif()

unset(PYTHON_INCLUDE_DIR CACHE)
unset(PYTHON_LIBRARY CACHE)
unset(PYTHON_LIBRARY_DEBUG CACHE)
find_package(PythonLibs 2 REQUIRED)
find_package(Boost 1.54.0 REQUIRED COMPONENTS python)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Release>:BOOST_DISABLE_ASSERTS>)

set(CNOID_PYTHON_SUBDIR ${CNOID_PLUGIN_SUBDIR}/python)

set(init_py "${PROJECT_BINARY_DIR}/${CNOID_PYTHON_SUBDIR}/cnoid/__init__.py")
file(WRITE ${init_py} "")
install(FILES ${init_py} DESTINATION ${CNOID_PYTHON_SUBDIR}/cnoid
  CONFIGURATIONS Release Debug RelWithDebInfo MinSizeRel)

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

install(DIRECTORY ${PROJECT_BINARY_DIR}/${CNOID_PYTHON_SUBDIR} DESTINATION ${CNOID_PLUGIN_SUBDIR}
  FILES_MATCHING PATTERN "*.py")

add_subdirectory(src)
