#ifndef GEN3UI_CUSTOMBUTTONTEST_H
#define GEN3UI_CUSTOMBUTTONTEST_H

#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CCustomButtonTest:public ::testing::Test
            {
            public:
                CCustomButtonTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_CUSTOMBUTTONTEST_H
