#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T16:06:45
#
#-------------------------------------------------

QT += widgets network
greaterThan(QT_MAJOR_VERSION, 4): QT +=multimedia

TARGET = Gen3UI
TEMPLATE = app

DEFINES += HMIUI_LIBRARY __STDC_CONSTANT_MACROS

#CONFIG  += wince
CONFIG  += unix x86

INCLUDEPATH += $$PWD/ \
               $$PWD/../include \
               $$PWD/../hmi_sdk/gstplayer/include
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

SOURCES += \
    main.cpp \
    Gen3UIManager.cpp \
    MainWindow/MainWindow.cpp \
    AppListView/AppListView.cpp \
    AppListView/CAppButton.cpp \
    Common/MenuButton.cpp \
    CommandView/CommandView.cpp \
    CommandView/CustomCombobox.cpp \
    CommandView/CustomComboboxItem.cpp \
    Common/Button.cpp \
    Common/ScrollBar.cpp \
    Common/AppBase.cpp \
    Common/CustomButton.cpp \
    #Show/MainWidget.cpp \
    Show/MediaShow.cpp \
    Config/Config.cpp \
    Alert/AlertView.cpp \
    Common/CustomListView.cpp \
    ChoiceSet/ChoiceSet.cpp \
    ChoiceSet/ChoiceSetVR.cpp \
    ScrollableMessage/ScollMsgView.cpp \
    SliderView/SliderView.cpp \
    AudioPassThru/AudioPassView.cpp \
    VideoStream/CeVideoStream.cpp \
    AppListView/DeviceListView.cpp \
    Template/TemplateImp.cpp \
    Template/TemplateManager.cpp \
    Show/GraphicSoftButtonShow.cpp \
    Alert/test/AlertViewTest.cpp \
    test/StartTest.cpp \
    AppListView/test/AppListViewTest.cpp \
    AppListView/test/CAppButtonTest.cpp \
    AppListView/test/DeviceListViewTest.cpp \
    ChoiceSet/test/ChoiceSetTest.cpp \
    ChoiceSet/test/ChoiceSetVRTest.cpp \
    CommandView/test/CommandViewTest.cpp \
    CommandView/test/CustomComboboxTest.cpp \
    CommandView/test/CustomComboboxItemTest.cpp \
    Common/test/AppBaseTest.cpp \
    Common/test/ButtonTest.cpp \
    Common/test/CustomButtonTest.cpp \
    Common/test/CustomListViewTest.cpp \
    Common/test/MenuButtonTest.cpp \
    Common/test/ScrollBarTest.cpp \
    Config/test/ConfigTest.cpp \
    MainWindow/test/MainWindowTest.cpp \
    ScrollableMessage/test/ScollMsgViewTest.cpp \
    Show/test/GraphicSoftButtonShowTest.cpp \
    Show/test/MediaShowTest.cpp \
    SliderView/test/SliderViewTest.cpp \
    Template/test/TemplateImpTest.cpp \
    Template/test/TemplateManagerTest.cpp \
    AudioPassThru/test/AudioPassViewTest.cpp \
    VideoStream/test/CeVideoStreamTest.cpp

unix {
    SOURCES += VideoStream/gst_player.cpp
}

HEADERS += \
    Gen3UIManager.h \
    MainWindow/MainWindow.h \
    AppListView/AppListView.h \
    AppListView/CAppButton.h \
    Common/MenuButton.h \
    CommandView/CommandView.h \
    CommandView/CustomCombobox.h \
    CommandView/CustomComboboxItem.h \
    Common/Button.h \
    Common/ScrollBar.h \
    Common/AppBase.h \
    Common/CustomButton.h \
    #Show/MainWidget.h \
    Show/MediaShow.h \
    Config/Config.h \
    main.h \
    Alert/AlertView.h \
    Common/CustomListView.h \
    ChoiceSet/ChoiceSet.h \
    ChoiceSet/ChoiceSetVR.h \
    ScrollableMessage/ScollMsgView.h \
    SliderView/SliderView.h \
    AudioPassThru/AudioPassView.h \
    VideoStream/CeVideoStream.h \
    AppListView/DeviceListView.h \
    Library/android/sdl/main.h \
    Template/TemplateImp.h \
    Template/TemplateManager.h \
    Show/GraphicSoftButtonShow.h \
    Alert/test/AlertViewTest.h \
    test/MockModule.h \
    test/StartTest.h \
    AppListView/test/AppListViewTest.h \
    AppListView/test/CAppButtonTest.h \
    AppListView/test/DeviceListViewTest.h \
    ChoiceSet/test/ChoiceSetTest.h \
    ChoiceSet/test/ChoiceSetVRTest.h \
    CommandView/test/CommandViewTest.h \
    CommandView/test/CustomComboboxTest.h \
    CommandView/test/CustomComboboxItemTest.h \
    Common/test/AppBaseTest.h \
    Common/test/ButtonTest.h \
    Common/test/CustomButtonTest.h \
    Common/test/CustomListViewTest.h \
    Common/test/MenuButtonTest.h \
    Common/test/ScrollBarTest.h \
    Config/test/ConfigTest.h \
    MainWindow/test/MainWindowTest.h \
    ScrollableMessage/test/ScollMsgViewTest.h \
    Show/test/GraphicSoftButtonShowTest.h \
    Show/test/MediaShowTest.h \
    SliderView/test/SliderViewTest.h \
    Template/test/TemplateImpTest.h \
    Template/test/TemplateManagerTest.h \
    AudioPassThru/test/AudioPassViewTest.h \
    VideoStream/test/CeVideoStreamTest.h

unix {
    SOURCES += VideoStream/gst_player.h
}

unix {
    target.path = /usr/lib
}

RESOURCES += \
    image.qrc

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

###############################for test
unix{

DEFINES += HMI_TEST

INCLUDEPATH += $$PWD/../googletest/include \
               $$PWD/../hmi_sdk/connect/include \
               $$PWD/../hmi_sdk/app_data/include

DEPENDPATH += $$PWD/../googletest/include

unix:!macx: LIBS += -L$$PWD/../googletest/lib/ -lgmock -lgmock_main -lgtest -lgtest_main -ljsoncpp

unix:!macx: PRE_TARGETDEPS += $$PWD/../googletest/lib/libgmock.a

unix:!macx: PRE_TARGETDEPS += $$PWD/../googletest/lib/libgmock_main.a

unix:!macx: PRE_TARGETDEPS += $$PWD/../googletest/lib/libgtest.a

unix:!macx: PRE_TARGETDEPS += $$PWD/../googletest/lib/libgtest_main.a

unix:!macx: PRE_TARGETDEPS += $$PWD/../googletest/lib/libjsoncpp.a

unix:!macx: LIBS += -L$$PWD/../googletest/bin/ -lhmi_sdk


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
