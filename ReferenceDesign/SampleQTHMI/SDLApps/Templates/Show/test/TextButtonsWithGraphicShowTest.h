#ifndef GEN3UI_TEXTBUTTONSWITHGRAPHICSHOWTEST_H
#define GEN3UI_TEXTBUTTONSWITHGRAPHICSHOWTEST_H


#include "test/MockModule.h"
#include "../TextButtonsWithGraphicShow.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CTextButtonsWithGraphicShowTest:public ::testing::Test
            {
            public:
                CTextButtonsWithGraphicShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GEN3UI_TEXTBUTTONSWITHGRAPHICSHOWTEST_H
