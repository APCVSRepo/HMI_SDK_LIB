#ifndef GEN3UI_SCOLLMSGVIEWTEST_H
#define GEN3UI_SCOLLMSGVIEWTEST_H


#include "test/MockModule.h"
#include "../ScollMsgView.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CScollMsgViewTest:public ::testing::Test
            {
            public:
                CScollMsgViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };
        }
    }
}

#endif // GEN3UI_SCOLLMSGVIEWTEST_H
