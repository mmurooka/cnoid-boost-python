set(target PyOpenRTMPlugin)
link_directories(${OPENRTM_LIBRARY_DIRS})
add_cnoid_python_module(${target} PyOpenRTMPlugin.cpp)
target_link_libraries(${target} CnoidOpenRTMPlugin CnoidPyBase)
