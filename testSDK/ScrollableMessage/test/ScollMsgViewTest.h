#ifndef SCOLLMSGVIEWTEST_H
#define SCOLLMSGVIEWTEST_H


#include "test/MockModule.h"

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

#endif // SCOLLMSGVIEWTEST_H
