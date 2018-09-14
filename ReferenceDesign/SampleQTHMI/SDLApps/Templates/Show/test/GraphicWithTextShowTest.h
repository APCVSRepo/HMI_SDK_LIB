#ifndef GEN3UI_GRAPHICWITHTEXTTEST_H
#define GEN3UI_GRAPHICWITHTEXTTEST_H


#include "test/MockModule.h"
#include "../GraphicWithTextShow.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CGraphicWithTextShowTest:public ::testing::Test
            {
            public:
                CGraphicWithTextShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_GRAPHICWITHTEXTTEST_H
