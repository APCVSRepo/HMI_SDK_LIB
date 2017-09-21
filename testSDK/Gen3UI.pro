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

INCLUDEPATH += $$PWD/ \
               $$PWD/../include


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
    Show/MainWidget.cpp \
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
    Template/TemplateManager.cpp

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
    Show/MainWidget.h \
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
    Template/TemplateManager.h

unix {
    target.path = /usr/lib
}

RESOURCES += \
    image.qrc


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

