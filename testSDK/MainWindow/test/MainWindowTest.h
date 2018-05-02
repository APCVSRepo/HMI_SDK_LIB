#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class MainWindowTest:public ::testing::Test
            {
            public:
                MainWindowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }
    }
}

#endif // MAINWINDOWTEST_H
