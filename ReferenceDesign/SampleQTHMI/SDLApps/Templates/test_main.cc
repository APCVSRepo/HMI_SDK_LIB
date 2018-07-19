#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <QApplication>
#include "UIManager.h"

int main(int argc, char** argv) {

    QApplication a(argc, argv);

   UIManager *m_pUIManager = new UIManager;
   m_pUIManager->loadsdk();

//  testing::GTEST_FLAG(output) = "xml:";
  testing::InitGoogleMock(&argc, argv);
  const int result = RUN_ALL_TESTS();
  return result;
}
