#include "Gen3UIManager.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QDialog>
#include <QTimer>
#include "Common/AppBase.h"

CGen3UIManager *g_pUIManager;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);
#else
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
#endif

  g_pUIManager = new CGen3UIManager;
  QTimer::singleShot(500, g_pUIManager, SLOT(loadsdk()));

  QDialog diaStart;
#ifdef ANDROID
  diaStart.setGeometry(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height() - 30);
#else
  diaStart.setGeometry((1280 - SCREEN_WIDTH) / 2, (800 - SCREEN_HEIGHT) / 2, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif
  diaStart.setStyleSheet("border-image:url(:/images/Screen.png);");
  QObject::connect(g_pUIManager, SIGNAL(finishLoadSDK()), &diaStart, SLOT(accept()));

  // 启动画面，等待HMISDK初始化完成
  diaStart.exec();

  g_pUIManager->onAppShow(ID_MAIN);
  g_pUIManager->onAppShow(ID_APPLINK);

  return a.exec();
}
