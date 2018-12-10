#ifndef GEN3UI_GRAPHICWITHTEXTANDSOFTBUTTONSSHOWTEST_H
#define GEN3UI_GRAPHICWITHTEXTANDSOFTBUTTONSSHOWTEST_H


#include "test/MockModule.h"
#include "../GraphicWithTextAndSoftbuttonsShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CGraphicWithTextAndSoftbuttonsShowTest:public ::testing::Test
            {
            public:
                CGraphicWithTextAndSoftbuttonsShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_GRAPHICWITHTEXTANDSOFTBUTTONSSHOWTEST_H
