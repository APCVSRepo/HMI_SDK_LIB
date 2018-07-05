#ifndef GEN3UI_MEDIASHOWTEST_H
#define GEN3UI_MEDIASHOWTEST_H


#include "test/MockModule.h"
#include "../MediaShow.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CMediaShowTest:public ::testing::Test
            {
            public:
                CMediaShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_MEDIASHOWTEST_H
