#ifndef GEN3UI_CHOICESETTEST_H
#define GEN3UI_CHOICESETTEST_H


#include "test/MockModule.h"
#include "../ChoiceSet.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CChoiceSetTest:public ::testing::Test
            {
            public:
                CChoiceSetTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_CHOICESETTEST_H
