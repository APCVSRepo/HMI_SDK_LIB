#ifndef GEN3UI_TILESONLYSHOWTEST_H
#define GEN3UI_TILESONLYSHOWTEST_H


#include "test/MockModule.h"
#include "../TilesOnlyShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CTilesOnlyShowTest:public ::testing::Test
            {
            public:
                CTilesOnlyShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_TILESONLYSHOWTEST_H
