#ifndef CUSTOMCOMBOBOXITEMTEST_H
#define CUSTOMCOMBOBOXITEMTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CustomComboboxItemTest:public ::testing::Test
            {
            public:
                CustomComboboxItemTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // CUSTOMCOMBOBOXITEMTEST_H
