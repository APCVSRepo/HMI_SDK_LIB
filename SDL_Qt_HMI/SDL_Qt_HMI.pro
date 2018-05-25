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
    SDLApps/Templates/Alert/AlertView.cpp \
    SDLApps/Templates/AppListView/AppListView.cpp \
    SDLApps/Templates/AppListView/CAppButton.cpp \
    SDLApps/Templates/AppListView/DeviceListView.cpp \
    SDLApps/Templates/AudioPassThru/AudioPassView.cpp \
    SDLApps/Templates/ChoiceSet/ChoiceSet.cpp \
    SDLApps/Templates/ChoiceSet/ChoiceSetVR.cpp \
    SDLApps/Templates/CommandView/CommandView.cpp \
    SDLApps/Templates/CommandView/CustomCombobox.cpp \
    SDLApps/Templates/CommandView/CustomComboboxItem.cpp \
    SDLApps/Templates/Common/AppBase.cpp \
    SDLApps/Templates/Common/Button.cpp \
    SDLApps/Templates/Common/CustomButton.cpp \
    SDLApps/Templates/Common/CustomListView.cpp \
    SDLApps/Templates/Common/MenuButton.cpp \
    SDLApps/Templates/Common/ScrollBar.cpp \
    SDLApps/Templates/Config/Config.cpp \
    SDLApps/Templates/ScrollableMessage/ScollMsgView.cpp \
    SDLApps/Templates/Show/GraphicSoftButtonShow.cpp \
    #SDLApps/Templates/Show/MainWidget.cpp \
    SDLApps/Templates/Show/MediaShow.cpp \
    SDLApps/Templates/SliderView/SliderView.cpp \
    SDLApps/Templates/Template/TemplateImp.cpp \
    SDLApps/Templates/Template/TemplateManager.cpp \
    SDLApps/Templates/utils/VideoStream/CeVideoStream.cpp \
    HMIFrameWork/AppManager.cpp \
    HMIFrameWork/log_interface.cpp \
    HMIFrameWork/App.cpp \
    MainWindow.cpp \
    HMIFrameWork/HMIFrameWork.cpp \
    HMIFrameWork/CView.cpp \
    HMIFrameWork/ViewFactory.cpp \
    HMIFrameWork/GstPlayerMessage.cpp \
    HMIFrameWork/GstPlayer.cpp \
    HMIWidgets/CCButton.cpp \
    HMIWidgets/CListWidgetItem.cpp \
    HMIWidgets/CPushButton.cpp \
    HMIWidgets/CVListWidget.cpp \
    HMIWidgets/DateTimePicker.cpp \
    HMIWidgets/ListDelegate.cpp \
    HMIWidgets/ListScroller.cpp \
    HMIWidgets/Picker.cpp \
    HMIWidgets/ScrollText.cpp \
    HMIWidgets/SliderSelect.cpp \
    HMIWidgets/CComboBox.cpp \
    HMIWidgets/CComboBoxDelegate.cpp \
    HMIWidgets/CRotationWidget.cpp \
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
    AppLayer.cpp \
    SDLApps/Templates/UIManager.cpp

unix {
    SOURCES += SDLApps/Templates/utils/VideoStream/gst_player.cpp
}



HEADERS  +=  \
    #mainwindow.h \
    SDLApps/Templates/Alert/AlertView.h \
    SDLApps/Templates/AppListView/AppListView.h \
    SDLApps/Templates/AppListView/CAppButton.h \
    SDLApps/Templates/AppListView/DeviceListView.h \
    SDLApps/Templates/AudioPassThru/AudioPassView.h \
    SDLApps/Templates/ChoiceSet/ChoiceSet.h \
    SDLApps/Templates/ChoiceSet/ChoiceSetVR.h \
    SDLApps/Templates/CommandView/CommandView.h \
    SDLApps/Templates/CommandView/CustomCombobox.h \
    SDLApps/Templates/CommandView/CustomComboboxItem.h \
    SDLApps/Templates/Common/AppBase.h \
    SDLApps/Templates/Common/Button.h \
    SDLApps/Templates/Common/CustomButton.h \
    SDLApps/Templates/Common/CustomListView.h \
    SDLApps/Templates/Common/MenuButton.h \
    SDLApps/Templates/Common/ScrollBar.h \
    SDLApps/Templates/Config/Config.h \
    SDLApps/Templates/ScrollableMessage/ScollMsgView.h \
    SDLApps/Templates/Show/GraphicSoftButtonShow.h \
    #SDLApps/Templates/Show/MainWidget.h \
    SDLApps/Templates/Show/MediaShow.h \
    SDLApps/Templates/SliderView/SliderView.h \
    SDLApps/Templates/Template/TemplateImp.h \
    SDLApps/Templates/Template/TemplateManager.h \
    SDLApps/Templates/utils/VideoStream/CeVideoStream.h \
    main.h \
    HMIFrameWork/AppConfig.h \
    HMIFrameWork/AppManager.h \
    HMIFrameWork/log_interface.h \
    HMIFrameWork/Interface.h \
    HMIFrameWork/App.h \
    HMIFrameWork/GstPlayerMessage.h \
    HMIFrameWork/GstPlayer.h \
    MainWindow.h \
    HMIFrameWork/HMIFrameWork.h \
    HMIFrameWork/CView.h \
    HMIFrameWork/ViewFactory.h \
    HMIWidgets/CCButton.h \
    HMIWidgets/CListWidgetItem.h \
    HMIWidgets/CPushButton.h \
    HMIWidgets/CVListWidget.h \
    HMIWidgets/DateTimePicker.h \
    HMIWidgets/ListDelegate.h \
    HMIWidgets/ListScroller.h \
    HMIWidgets/Picker.h \
    HMIWidgets/ScrollText.h \
    HMIWidgets/SliderSelect.h \
    HMIWidgets/WidgetsCommon.h \
    HMIWidgets/CComboBox.h \
    HMIWidgets/CComboBoxDelegate.h \
    HMIWidgets/CRotationWidget.h \
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
    AppLayer.h \
    SDLApps/Templates/UIManager.h



unix {
    HEADERS += SDLApps/Templates/utils/VideoStream/gst_player.h
}

unix {
    target.path = /usr/lib
}


RESOURCES += \
    SDLApps/Templates/image.qrc \
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

