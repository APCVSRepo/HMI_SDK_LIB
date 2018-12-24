#ifndef GEN3UI_TEXTWITHGRAPHICTEST_H
#define GEN3UI_TEXTWITHGRAPHICTEST_H


#include "test/MockModule.h"
#include "../TextWithGraphicShow.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CTextWithGraphicShowTest:public ::testing::Test
            {
            public:
                CTextWithGraphicShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_TEXTWITHGRAPHICTEST_H
