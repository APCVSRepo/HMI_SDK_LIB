#ifndef GEN3UI_TEMPLATEMANAGERTEST_H
#define GEN3UI_TEMPLATEMANAGERTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class TemplateManagerTest:public ::testing::Test
            {
            public:
                TemplateManagerTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // TEMPLATEMANAGERTEST_H
