#ifndef GEN3UI_CEVIDEOSTREAMTEST_H
#define GEN3UI_CEVIDEOSTREAMTEST_H


#include "test/MockModule.h"
#include "../CeVideoStream.h"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CeVideoStreamTest:public ::testing::Test
            {
            public:
                CeVideoStreamTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_CEVIDEOSTREAMTEST_H
