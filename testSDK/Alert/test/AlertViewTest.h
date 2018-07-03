#ifndef GEN3UI_ALERTVIEWTEST_H
#define GEN3UI_ALERTVIEWTEST_H

#include "test/MockModule.h"
#include "Alert/AlertView.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class AlertViewTest:public ::testing::Test
            {
            public:
                AlertViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_ALERTVIEWTEST_H
