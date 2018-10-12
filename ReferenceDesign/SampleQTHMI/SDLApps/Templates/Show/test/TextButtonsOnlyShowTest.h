#ifndef GEN3UI_TEXTBUTTONSONLYSHOWTEST_H
#define GEN3UI_TEXTBUTTONSONLYSHOWTEST_H


#include "test/MockModule.h"
#include "../TextButtonsOnlyShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CTextButtonsOnlyShowTest:public ::testing::Test
            {
            public:
                CTextButtonsOnlyShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_TEXTBUTTONSONLYSHOWTEST_H
