#ifndef GEN3UI_COMMANDVIEWTEST_H
#define GEN3UI_COMMANDVIEWTEST_H

#include "test/MockModule.h"
#include "../CommandView.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CCommandViewTest:public ::testing::Test
            {
            public:
                CCommandViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_COMMANDVIEWTEST_H
