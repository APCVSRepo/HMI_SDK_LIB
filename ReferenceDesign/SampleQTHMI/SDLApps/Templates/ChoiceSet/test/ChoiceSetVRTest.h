#ifndef GEN3UI_CHOICESETVRTEST_H
#define GEN3UI_CHOICESETVRTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CChoiceSetVRTest:public ::testing::Test
            {
            public:
                CChoiceSetVRTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}
#endif // GEN3UI_CHOICESETVRTEST_H
