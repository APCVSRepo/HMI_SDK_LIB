#ifndef MENUBUTTONTEST_H
#define MENUBUTTONTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class MenuButtonTest:public ::testing::Test
            {
            public:
                MenuButtonTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // MENUBUTTONTEST_H
