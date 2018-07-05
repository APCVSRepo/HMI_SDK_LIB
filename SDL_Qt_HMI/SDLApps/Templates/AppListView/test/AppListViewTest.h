#ifndef GEN3UI_CAPPLISTVIEWTEST_H
#define GEN3UI_CAPPLISTVIEWTEST_H

#include "test/MockModule.h"
#include "../AppListView.h"
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

#endif // GEN3UI_CAPPLISTVIEWTEST_H
