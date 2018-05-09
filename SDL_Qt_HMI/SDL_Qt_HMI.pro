#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T18:21:09
#
#-------------------------------------------------

QT       += widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT +=multimedia

TARGET = SDL_Qt_HMI
TEMPLATE = app

DEFINES += HMIUI_LIBRARY __STDC_CONSTANT_MACROS

#CONFIG  += wince
CONFIG  += unix x86

INCLUDEPATH += $$PWD/ \
               $$PWD/../include \
               $$PWD/../hmi_sdk/gstplayer/include \
               $$PWD/../tools/jsoncpp/include/    \
               $$PWD/../hmi_sdk/connect/include   \
               $$PWD/../hmi_sdk/app_data/include
unix {
  DEFINES += OS_LINUX
  x86 {
  INCLUDEPATH += /usr/include/glib-2.0 \
                 /usr/include/gstreamer-1.0 \
                 /usr/lib/x86_64-linux-gnu/ \
                 /usr/lib/x86_64-linux-gnu/glib-2.0/include \
                 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
  DEFINES += ARCH_X86
  }

  armhf {
  INCLUDEPATH += /usr/arm-linux-gnueabihf/include \
                 /usr/arm-linux-gnueabihf/include/glib-2.0 \
                 /usr/arm-linux-gnueabihf/include/gstreamer-1.0 \
                 /usr/arm-linux-gnueabihf/lib/glib-2.0/include
  DEFINES += ARCH_ARMHF
  }
}

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj
DESTDIR=bin

SOURCES += main.cpp\
       # mainwindow.cpp \
    SDLApps/Alert/AlertView.cpp \
    SDLApps/AppListView/AppListView.cpp \
    SDLApps/AppListView/CAppButton.cpp \
    SDLApps/AppListView/DeviceListView.cpp \
    SDLApps/AudioPassThru/AudioPassView.cpp \
    SDLApps/ChoiceSet/ChoiceSet.cpp \
    SDLApps/ChoiceSet/ChoiceSetVR.cpp \
    SDLApps/CommandView/CommandView.cpp \
    SDLApps/CommandView/CustomCombobox.cpp \
    SDLApps/CommandView/CustomComboboxItem.cpp \
    SDLApps/Common/AppBase.cpp \
    SDLApps/Common/Button.cpp \
    SDLApps/Common/CustomButton.cpp \
    SDLApps/Common/CustomListView.cpp \
    SDLApps/Common/MenuButton.cpp \
    SDLApps/Common/ScrollBar.cpp \
    SDLApps/Config/Config.cpp \
    SDLApps/ScrollableMessage/ScollMsgView.cpp \
    SDLApps/Show/GraphicSoftButtonShow.cpp \
    #SDLApps/Show/MainWidget.cpp \
    SDLApps/Show/MediaShow.cpp \
    SDLApps/SliderView/SliderView.cpp \
    SDLApps/Template/TemplateImp.cpp \
    SDLApps/Template/TemplateManager.cpp \
    SDLApps/VideoStream/CeVideoStream.cpp \
    SDLApps/Gen3UIManager.cpp \
    HMIFrameWork/AppManager.cpp \
    HMIFrameWork/log_interface.cpp \
    HMIFrameWork/App.cpp \
    MainWindow.cpp \
    HMIFrameWork/HMIFrameWork.cpp \
    HMIFrameWork/CView.cpp \
    HMIFrameWork/ViewFactory.cpp \
    HMIWidgets/CCButton.cpp \
    Home/app/Home.cpp \
    Home/Factory/HomeVFactory.cpp \
    Home/UI/HomeView.cpp \
    Home/UI/HomeWindow.cpp \
    QuickLanuch/app/QuickLanuch.cpp \
    QuickLanuch/Factory/QuickVFactory.cpp \
    QuickLanuch/UI/QuickLanuchView.cpp \
    QuickLanuch/UI/QuickLanuchWindow.cpp \
    SDLApps/app/SDLApps.cpp \
    SDLApps/Factory/SDLVFactory.cpp \
    SDLApps/UI/SDLAppsView.cpp \
    SDLApps/UI/SDLAppsWindow.cpp \
    AppLayer.cpp

unix {
    SOURCES += SDLApps/VideoStream/gst_player.cpp
}



HEADERS  +=  \
    #mainwindow.h \
    SDLApps/Alert/AlertView.h \
    SDLApps/AppListView/AppListView.h \
    SDLApps/AppListView/CAppButton.h \
    SDLApps/AppListView/DeviceListView.h \
    SDLApps/AudioPassThru/AudioPassView.h \
    SDLApps/ChoiceSet/ChoiceSet.h \
    SDLApps/ChoiceSet/ChoiceSetVR.h \
    SDLApps/CommandView/CommandView.h \
    SDLApps/CommandView/CustomCombobox.h \
    SDLApps/CommandView/CustomComboboxItem.h \
    SDLApps/Common/AppBase.h \
    SDLApps/Common/Button.h \
    SDLApps/Common/CustomButton.h \
    SDLApps/Common/CustomListView.h \
    SDLApps/Common/MenuButton.h \
    SDLApps/Common/ScrollBar.h \
    SDLApps/Config/Config.h \
    SDLApps/ScrollableMessage/ScollMsgView.h \
    SDLApps/Show/GraphicSoftButtonShow.h \
    #SDLApps/Show/MainWidget.h \
    SDLApps/Show/MediaShow.h \
    SDLApps/SliderView/SliderView.h \
    SDLApps/Template/TemplateImp.h \
    SDLApps/Template/TemplateManager.h \
    SDLApps/VideoStream/CeVideoStream.h \
    SDLApps/Gen3UIManager.h \
    main.h \
    HMIFrameWork/AppConfig.h \
    HMIFrameWork/AppManager.h \
    HMIFrameWork/log_interface.h \
    HMIFrameWork/Interface.h \
    HMIFrameWork/App.h \
    MainWindow.h \
    HMIFrameWork/HMIFrameWork.h \
    HMIFrameWork/CView.h \
    HMIFrameWork/ViewFactory.h \
    HMIWidgets/CCButton.h \
    Home/app/Home.h \
    Home/Factory/HomeVFactory.h \
    Home/UI/HomeView.h \
    Home/UI/HomeWindow.h \
    QuickLanuch/app/QuickLanuch.h \
    QuickLanuch/Factory/QuickVFactory.h \
    QuickLanuch/UI/QuickLanuchView.h \
    QuickLanuch/UI/QuickLanuchWindow.h \
    SDLApps/app/SDLApps.h \
    SDLApps/Factory/SDLVFactory.h \
    SDLApps/UI/SDLAppsView.h \
    SDLApps/UI/SDLAppsWindow.h \
    AppLayer.h



unix {
    HEADERS += SDLApps/VideoStream/gst_player.h
}

unix {
    target.path = /usr/lib
}


RESOURCES += \
    SDLApps/image.qrc \
    Home/Source/HomeImages.qrc \
    QuickLanuch/Source/QuickLanuchImages.qrc

unix {
  x86 {
  LIBS += /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so \
          /usr/lib/x86_64-linux-gnu/libgobject-2.0.so   \
          /usr/lib/x86_64-linux-gnu/libglib-2.0.so      \
          /usr/lib/x86_64-linux-gnu/libgstvideo-1.0.so
  }

  armhf {
  LIBS += /usr/arm-linux-gnueabihf/lib/libgstreamer-1.0.so \
          /usr/arm-linux-gnueabihf/lib/libgobject-2.0.so   \
          /usr/arm-linux-gnueabihf/lib/libglib-2.0.so      \
          /usr/arm-linux-gnueabihf/lib/libgstvideo-1.0.so  \
          /usr/arm-linux-gnueabihf/lib/libffi.so.6         \
          /usr/arm-linux-gnueabihf/lib/libgmodule-2.0.so.0 \
          /lib/arm-linux-gnueabihf/libpcre.so.3        \
          /usr/arm-linux-gnueabihf/lib/libgstbase-1.0.so.0 \
          /usr/arm-linux-gnueabihf/lib/liborc-0.4.so.0
  }
}

###############################for windows
win32:!wince{
DEFINES +=WIN32 \
          OS_WIN32
}

################################for linux
unix:!android{

}

################################for wince
wince{
HEADERS += \
    include/global_first.h
INCLUDEPATH += $$PWD/../include \
               $$PWD/../include/wince

DEFINES += OS_WIN32
DEFINES += SDL_SUPPORT_LIB
}


################################for android
android{
QT += androidextras
DEFINES +=ANDROID \
          SDL_SUPPORT_LIB

ANDROID_EXTRA_LIBS = $$PWD/../lib/android/libhmi_sdk.so \
    $$PWD/../lib/android/libsmartDeviceLinkCore.so

}

FORMS += \
    MainWindow.ui

