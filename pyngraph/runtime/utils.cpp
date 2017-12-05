// ----------------------------------------------------------------------------
// Copyright 2017 Nervana Systems Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// ----------------------------------------------------------------------------

#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>
//#include <string>
#include "ngraph/runtime/utils.hpp"
#include "pyngraph/runtime/utils.hpp"

namespace py = pybind11;

void regmodule_pyngraph_runtime_Utils(py::module m) {
    py::module mod = m.def_submodule("Utils", "module pyngraph.runtime.Utils");
    using PTVFloat32 = ngraph::runtime::ParameterizedTensorView<ngraph::element::Float32>;    

    mod.def("make_tensor", (std::shared_ptr<PTVFloat32> (*) (const ngraph::Shape&)) &make_tensor);
    mod.def("make_tensor", (std::shared_ptr<PTVFloat32> (*) (const ngraph::Shape& , const std::vector<typename ngraph::element::Float32::type>& )) &make_tensor);
}
