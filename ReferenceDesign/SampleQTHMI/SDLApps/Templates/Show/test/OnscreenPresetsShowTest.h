#ifndef GEN3UI_ONSCREENPRESETSSHOWTEST_H
#define GEN3UI_ONSCREENPRESETSSHOWTEST_H


#include "test/MockModule.h"
#include "../OnscreenPresetsShow.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class COnscreenPresetsShowTest:public ::testing::Test
            {
            public:
                COnscreenPresetsShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_ONSCREENPRESETSSHOWTEST_H
