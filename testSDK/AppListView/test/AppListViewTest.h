#ifndef CAPPLISTVIEWTEST_H
#define CAPPLISTVIEWTEST_H

#include "test/MockModule.h"
#include "AppListView/AppListView.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CAppListViewTest:public ::testing::Test
            {
            public:
                CAppListViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // CAPPLISTVIEWTEST_H
