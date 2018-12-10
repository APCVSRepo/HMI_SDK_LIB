#ifndef GEN3UI_GRAPHICSOFTBUTTONSHOWTEST_H
#define GEN3UI_GRAPHICSOFTBUTTONSHOWTEST_H


#include "test/MockModule.h"
#include "../TilesWithGraphicShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CTilesWithGraphicShowTest:public ::testing::Test
            {
            public:
                CTilesWithGraphicShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_GRAPHICSOFTBUTTONSHOWTEST_H
