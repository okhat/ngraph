#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <string>
#include "ngraph/runtime/parameterized_tensor_view.hpp"

namespace py = pybind11;
namespace ngraph {
namespace runtime {
namespace {

template <typename ET>
static void declareParameterizedTensorView(py::module & mod, std::string const & suffix) {
    using Class = ParameterizedTensorView<ET>;
    using PyClass = py::class_<Class, std::shared_ptr<Class>, TensorView>;

    PyClass cls(mod, ("ParameterizedTensorView" + suffix).c_str());
    cls.def("write", [] (py::array_t<float, py::array::c_style> a) {
      py::buffer_info a_info = a.request();
      &Class.write(a_info.ptr, 0, a_info.ndim);
    };
}

}

PYBIND11_PLUGIN(clsParameterizedTensorView) {

    py::module mod1("clsTensorView");
    py::class_<TensorView, std::shared_ptr<TensorView>> clsTensorView(mod1, "clsTensorView");
    py::module mod("clsParameterizedTensorView");
    py::module::import("clsTraitedType");

    declareParameterizedTensorView<ngraph::element::TraitedType<float>>(mod, "F");
    //declareParameterizedTensorView<double>(mod, "D");
    //declareParameterizedTensorView<int>(mod, "I");

    return mod.ptr();
}

}}  // ngraph
