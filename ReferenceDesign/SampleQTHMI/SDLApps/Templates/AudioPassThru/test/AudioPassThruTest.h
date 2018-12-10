#ifndef GEN3UI_CAUDIOPASSTHRUTEST_H
#define GEN3UI_CAUDIOPASSTHRUTEST_H

#include "test/MockModule.h"
#include "../AudioPassThru.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CAudioPassThruTest:public ::testing::Test
            {
            public:
                CAudioPassThruTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();
            };

        }

    }
}

#endif // GEN3UI_CAUDIOPASSTHRUTEST_H
