#ifndef GEN3UI_SLIDERVIEWTEST_H
#define GEN3UI_SLIDERVIEWTEST_H


#include "test/MockModule.h"
#include "../SliderView.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class CSliderViewTest:public ::testing::Test
            {
            public:
                CSliderViewTest();
                static void SetUpTestCase();
                static void TearDownTestCase();
                virtual void SetUp();
                virtual void TearDown();

            };

        }

    }
}

#endif // GEN3UI_SLIDERVIEWTEST_H
