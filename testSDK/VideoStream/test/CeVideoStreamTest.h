#ifndef CEVIDEOSTREAMTEST_H
#define CEVIDEOSTREAMTEST_H


#include "test/MockModule.h"

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

#endif // CEVIDEOSTREAMTEST_H
