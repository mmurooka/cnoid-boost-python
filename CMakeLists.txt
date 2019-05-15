option(BUILD_BOOST_PYTHON_WRAPPERS "Building Boost.Python version Python Wrappers" OFF)
if(NOT BUILD_BOOST_PYTHON_WRAPPERS)
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

install(DIRECTORY ${PROJECT_BINARY_DIR}/${CNOID_PYTHON_SUBDIR} DESTINATION ${CNOID_PLUGIN_SUBDIR}
  FILES_MATCHING PATTERN "*.py")

add_subdirectory(src)
