/*!
  @author Shin'ichiro Nakaoka
*/

#include "../PythonSimScriptItem.h"
#include <cnoid/PyBase>

using namespace cnoid;

BOOST_PYTHON_MODULE(PythonSimScriptPlugin)
{
    boost::python::class_<
        PythonSimScriptItem, PythonSimScriptItemPtr, boost::python::bases<SimulationScriptItem>>
        ("PythonSimScriptItem")
        .def("setScriptFilename", &PythonSimScriptItem::setScriptFilename);

    boost::python::implicitly_convertible<PythonSimScriptItemPtr, SimulationScriptItemPtr>();
    PyItemList<PythonSimScriptItem>("PythonSimScriptItemList");
};
