# @author Shin'ichiro Nakaoka

set(target CnoidPythonSimScriptPlugin)

set(sources
  PythonSimScriptPlugin.cpp
  PythonSimScriptItem.cpp
  )

make_gettext_mofiles(${target} mofiles)
add_cnoid_plugin(${target} SHARED ${sources} ${mofiles})
target_link_libraries(${target} CnoidBodyPlugin CnoidPythonPlugin)
apply_common_setting_for_plugin(${target} "${headers}")

add_subdirectory(python)
