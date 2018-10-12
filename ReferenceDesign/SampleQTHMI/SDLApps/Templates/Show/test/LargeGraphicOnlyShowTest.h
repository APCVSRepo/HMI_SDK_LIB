#ifndef GEN3UI_LARGEGRAPHICONLYSHOWTEST_H
#define GEN3UI_LARGEGRAPHICONLYSHOWTEST_H


#include "test/MockModule.h"
#include "../LargeGraphicOnlyShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CLargeGraphicOnlyShowTest:public ::testing::Test
            {
            public:
                CLargeGraphicOnlyShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_LARGEGRAPHICONLYSHOWTEST_H
