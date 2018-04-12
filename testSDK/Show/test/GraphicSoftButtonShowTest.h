#ifndef GRAPHICSOFTBUTTONSHOWTEST_H
#define GRAPHICSOFTBUTTONSHOWTEST_H


#include "test/MockModule.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CGraphicSoftButtonShowTest:public ::testing::Test
            {
            public:
                CGraphicSoftButtonShowTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}


#endif // GRAPHICSOFTBUTTONSHOWTEST_H
