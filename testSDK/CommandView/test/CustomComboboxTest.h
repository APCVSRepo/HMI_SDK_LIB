#ifndef CUSTOMCOMBOBOXTEST_H
#define CUSTOMCOMBOBOXTEST_H

#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CustomComboboxTest:public ::testing::Test
            {
            public:
                CustomComboboxTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // CUSTOMCOMBOBOXTEST_H
