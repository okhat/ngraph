/*******************************************************************************
* Copyright 2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "sigmoid_mul.hpp"
#include "ngraph/log.hpp"
#include "ngraph/util.hpp"
#include "ngraph/op/tanh.hpp"
#include "ngraph/runtime/cpu/op/sigmoid.hpp"

using namespace std;
using namespace ngraph;

shared_ptr<Node> op::SigmoidMultiply::copy_with_new_args(const NodeVector& new_args) const
{
    if (new_args.size() != 2)
    {
        throw ngraph_error("SigmoidMultiply incorrect number of new arguments");
    }

    return make_shared<SigmoidMultiply>(new_args.at(0), new_args.at(1));
}
op::SigmoidMultiply::FunctionType identify_node_fucntion(shared_ptr<Node> node) {
    if (std::dynamic_pointer_cast<op::Tanh>(node) != nullptr) {
        return op::SigmoidMultiply::FunctionType::Tanh;
    }
    else if (std::dynamic_pointer_cast<op::Sigmoid>(node) != nullptr) {
        return op::SigmoidMultiply::FunctionType::Sigmoid;
    }
    else {
        throw ngraph_error("SigmoidMultiply input function type not supported: " + node->get_name());
    }
}
op::SigmoidMultiply::SigmoidMultiply(shared_ptr<Node> input_1, shared_ptr<Node> input_2)
        : RequiresTensorViewArgs("Sigmoid", {input_1, input_2})
{
    if (input_1->get_element_type() != input_2->get_element_type())
    {
        throw ngraph_error("SigmoidMultiply input element type mismatch");
    }
    if (input_1->get_shape() != input_2->get_shape()) {
        throw ngraph_error("SigmoidMultiply input shape mismatch: " + vector_to_string(input_1->get_shape()) + " != " +
        vector_to_string(input_2->get_shape()));
    }

    input_1_type = identify_node_fucntion(input_1);
    input_2_type = identify_node_fucntion(input_2);

    add_output(input_1->get_element_type(), input_1->get_shape());
}

//op::SigmoidBackprop::SigmoidBackprop(shared_ptr<Node> arg, shared_ptr<Node> delta)
//        : RequiresTensorViewArgs("SigmoidBackprop", {arg, delta})
//{
//    if (arg->get_element_type() != delta->get_element_type())
//    {
//        throw ngraph_error("Argument and delta element types for Sigmoid backprop do not match");
//    }
//    if (arg->get_shape() != delta->get_shape())
//    {
//        throw ngraph_error("Argument and delta shape for Sigmoid backprop do not match");
//    }
//    set_value_type_checked(delta->get_element_type(), delta->get_shape());
//}
//
//shared_ptr<Node> op::SigmoidBackprop::copy_with_new_args(const NodeVector& new_args) const
//{
//    if (new_args.size() != 2)
//    {
//        throw ngraph_error("Incorrect number of new arguments");
//    }
//    return make_shared<SigmoidBackprop>(new_args.at(0), new_args.at(1));
//}

void op::SigmoidMultiply::generate_adjoints(autodiff::Adjoints& adjoints, const NodeVector& deltas)
{
//    auto delta = deltas.at(0);

//    auto backprop = make_shared<op::SigmoidMultiplyBackprop>(get_argument(0), delta);
//    adjoints.add_delta(get_argument(0), backprop);
}
