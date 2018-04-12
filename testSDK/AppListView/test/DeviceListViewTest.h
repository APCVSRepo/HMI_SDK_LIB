#ifndef CDEVICELISTVIEWTEST_H
#define CDEVICELISTVIEWTEST_H

#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CDeviceListViewTest:public ::testing::Test
            {
            public:
                CDeviceListViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // CDEVICELISTVIEWTEST_H
