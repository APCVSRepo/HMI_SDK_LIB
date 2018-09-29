#ifndef GEN3UI_GRAPHICWITHTEXTBUTTONSSHOWTEST_H
#define GEN3UI_GRAPHICWITHTEXTBUTTONSSHOWTEST_H


#include "test/MockModule.h"
#include "../GraphicWithTextButtonsShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CGraphicWithTextButtonsShowTest:public ::testing::Test
            {
            public:
                CGraphicWithTextButtonsShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_GRAPHICWITHTEXTBUTTONSSHOWTEST_H
