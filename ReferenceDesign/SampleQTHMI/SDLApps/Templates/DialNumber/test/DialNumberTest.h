#ifndef GEN3UI_CDIALNUMBERTEST_H
#define GEN3UI_CDIALNUMBERTEST_H

#include "test/MockModule.h"
#include "../DialNumber.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CDialNumberTest:public ::testing::Test
            {
            public:
                CDialNumberTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();
            };

        }

    }
}

#endif // GEN3UI_CDIALNUMBERTEST_H
