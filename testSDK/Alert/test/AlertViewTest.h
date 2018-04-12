#ifndef ALERTVIEWTEST_H
#define ALERTVIEWTEST_H

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

#endif // ALERTVIEWTEST_H
