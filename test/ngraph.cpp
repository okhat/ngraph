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

#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <dlfcn.h>

#include "gtest/gtest.h"
#include "ngraph.hpp"
#include "log.hpp"

using namespace std;

TEST(NGraph, loadTest)
{
    // load the triangle library
    void* ngraphImplLib = dlopen("../src/libngraph.so", RTLD_LAZY);
    if (!ngraphImplLib)
    {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        ASSERT_FALSE(true);
    }

    // reset errors
    dlerror();

    // Get the symbols
    auto createPfn =
        reinterpret_cast<CreateNGraphObjPfn>(dlsym(ngraphImplLib, "create_ngraph_object"));
    ASSERT_FALSE(createPfn == nullptr);

    auto destroyPfn =
        reinterpret_cast<DestroyNGraphObjPfn>(dlsym(ngraphImplLib, "destroy_ngraph_object"));
    ASSERT_FALSE(destroyPfn == nullptr);

    NGraph* nGraphObj = createPfn();

    INFO << "Call a method on the Object";
    ASSERT_EQ("NGraph Implementation Object", nGraphObj->get_name());
    INFO << "Object Name: " << nGraphObj->get_name();

    // Add some parameters
    const vector<string> TEST_PARAMS = {"param-1", "param-2", "param-3"};

    nGraphObj->add_params(TEST_PARAMS);

    // Get the list of params
    auto& storedParams = nGraphObj->get_params();
    EXPECT_EQ(TEST_PARAMS.size(), storedParams.size());
    for (int i = 0; i < TEST_PARAMS.size(); i++)
    {
        EXPECT_EQ(TEST_PARAMS[i], storedParams[i]);
    }

    INFO << "Destroy the NGraph Object";
    destroyPfn(nGraphObj);

    dlclose(ngraphImplLib);
}