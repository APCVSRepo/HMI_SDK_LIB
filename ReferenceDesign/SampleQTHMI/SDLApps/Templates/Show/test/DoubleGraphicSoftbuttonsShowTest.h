#ifndef GEN3UI_DOUBLEGRAPHICSOFTBUTTONSSHOWTEST_H
#define GEN3UI_DOUBLEGRAPHICSOFTBUTTONSSHOWTEST_H


#include "test/MockModule.h"
#include "../DoubleGraphicSoftbuttonsShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CDoubleGraphicSoftbuttonsShowTest:public ::testing::Test
            {
            public:
                CDoubleGraphicSoftbuttonsShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_DOUBLEGRAPHICSOFTBUTTONSSHOWTEST_H
