#ifndef CAPPBUTTONTEST_H
#define CAPPBUTTONTEST_H

#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CAppButtonTest:public ::testing::Test
            {
            public:
                CAppButtonTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // CAPPBUTTONTEST_H
