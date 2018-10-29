#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T18:21:09
#
#-------------------------------------------------

QT       += widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT +=multimedia

TARGET = SampleQTHMI
TEMPLATE = app

DEFINES += HMIUI_LIBRARY __STDC_CONSTANT_MACROS

#CONFIG  += wince
CONFIG  += unix x86

INCLUDEPATH += $$PWD/ \
               $$PWD/../../HMI_SDK_LIB/include \
               $$PWD/../../HMI_SDK_LIB/hmi_sdk/gstplayer/include \
               $$PWD/../../HMI_SDK_LIB/tools/jsoncpp/include/    \
               $$PWD/../../HMI_SDK_LIB/hmi_sdk/connect/include   \
               $$PWD/../../HMI_SDK_LIB/hmi_sdk/app_data/include
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
    MainWindow.cpp \
    HMIFrameWork/AppManager.cpp \
    HMIFrameWork/log_interface.cpp \
    HMIFrameWork/App.cpp \
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
    HMIWidgets/CSlider.cpp \
    HMIWidgets/AlbumCoverWidget.cpp \
    HMIWidgets/TopNavigateWidget.cpp \
    HMIWidgets/AppListWidget.cpp \
    HMIWidgets/CAppButton.cpp \
    Home/app/Home.cpp \
    Home/Factory/HomeVFactory.cpp \
    Home/UI/HomeView.cpp \
    Home/UI/HomeWindow.cpp \
    Home/UI/Settings/SettingsDateTimeUI.cpp \
    Home/UI/Settings/SettingsMainUI.cpp \
    Home/UI/Settings/SettingsSoundUI.cpp \
    Home/UI/Settings/SettingsBTUI.cpp \
    Home/UI/Settings/SettingsWifiAddHotSpotsUI.cpp \
    Home/UI/Settings/SettingsWifiPasswordUI.cpp \
    Home/UI/Settings/SettingsWifiUI.cpp \
    Home/UI/Settings/SettingsSpeechRecognitionUI.cpp \
    Home/UI/Settings/SettingsRoutineSettingUI.cpp \
    Home/UI/Settings/SettingsEmergencyUI.cpp \
    Home/UI/Settings/SettingsDisplayUI.cpp \
    Home/UI/PlayVedio/BootAnimation.cpp \
    Home/UI/PlayVedio/BootAnimationUI.cpp \
    Home/data/Settings/SettingsWifiData.cpp \
    Home/data/Settings/SettingsBTData.cpp \
    Home/data/Settings/SettingsDateTimeData.cpp \
    Home/data/Settings/SettingsRoutineSettingData.cpp \
    Home/data/Settings/SettingsDisplayData.cpp \
    Home/data/Settings/SettingsMobileApplicationsData.cpp \
    Home/UI/Settings/SettingsMobileApplicationsUI.cpp \
    Home/data/Settings/SettingsEmergencyData.cpp \
    QuickLanuch/app/QuickLanuch.cpp \
    QuickLanuch/Factory/QuickVFactory.cpp \
    QuickLanuch/UI/QuickLanuchView.cpp \
    QuickLanuch/UI/QuickLanuchWindow.cpp \
    StatusBar/app/StatusBar.cpp \
    StatusBar/Factory/StatusBarVFactory.cpp \
    StatusBar/UI/StatusBarView.cpp \
    StatusBar/UI/StatusBarWindow.cpp \
    SDLApps/Templates/Alert/AlertView.cpp \
    SDLApps/Templates/AppListView/AppListView.cpp \
    SDLApps/Templates/AppListView/DeviceListView.cpp \
    SDLApps/Templates/ChoiceSet/ChoiceSet.cpp \
    SDLApps/Templates/ChoiceSet/ChoiceSetVR.cpp \
    SDLApps/Templates/CommandView/CommandView.cpp \
    SDLApps/Templates/Common/AppBase.cpp \
    SDLApps/Templates/Common/Button.cpp \
    SDLApps/Templates/Common/CustomListView.cpp \
    SDLApps/Templates/Common/MenuButton.cpp \
    SDLApps/Templates/Config/Config.cpp \
    SDLApps/Templates/ScrollableMessage/ScollMsgView.cpp \
    SDLApps/Templates/Show/GraphicSoftButtonShow.cpp \
    SDLApps/Templates/Show/MediaShow.cpp \
    SDLApps/Templates/SliderView/SliderView.cpp \
    SDLApps/Templates/Template/TemplateImp.cpp \
    SDLApps/Templates/Template/TemplateManager.cpp \
    SDLApps/Templates/utils/VideoStream/CeVideoStream.cpp \
    SDLApps/app/SDLApps.cpp \
    SDLApps/Factory/SDLVFactory.cpp \
    SDLApps/UI/SDLAppsView.cpp \
    SDLApps/UI/SDLAppsWindow.cpp \
    SDLApps/Templates/UIManager.cpp \
    SDLApps/Data/SDLAppsData.cpp \
    PopUp/app/PopUp.cpp \
    PopUp/Factory/PopUpVFactory.cpp \
    PopUp/UI/PopUpWindow.cpp \
    PopUp/UI/PopUpViewUI.cpp \
    PopUp/UI/PopupGeneralView.cpp \
    PopUp/UI/PopUpBase.cpp \
    Prompt/app/Prompt.cpp \
    Prompt/Factory/PromptVFactory.cpp \
    Prompt/UI/PromptBase.cpp \
    Prompt/UI/PromptNavView.cpp \
    Prompt/UI/PromptViewUI.cpp \
    Prompt/UI/PromptWindow.cpp \
    HVAC/app/HVAC.cpp \
    HVAC/Factory/HVACVFactory.cpp \
    HVAC/UI/HVACWindow.cpp \
    HVAC/UI/HVACFrontView.cpp \
    HVAC/UI/HVACRearView.cpp \
    HVAC/UI/HVACFrontViewOff.cpp \
    HVAC/UI/HVACRearViewOff.cpp \
    HVAC/data/HVACData.cpp \
    Phone/app/Phone.cpp \
    Phone/Factory/PhoneVFactory.cpp \
    Phone/UI/KeyBoardView.cpp \
    Phone/UI/PhoneWindow.cpp \
    HMIWidgets/PhonePicker.cpp \
    Phone/data/PhoneData.cpp \
    Phone/UI/ContactsView.cpp \
    Phone/UI/RecentsView.cpp \
    Phone/UI/ContactsDetailsView.cpp \
    Prompt/UI/PromptMessageView.cpp \
    Phone/UI/CallingView.cpp \
    Message/app/Message.cpp \
    Message/data/MessageData.cpp \
    Message/Factory/MessageVFactory.cpp \
    Message/UI/MessagesView.cpp \
    Message/UI/MessageWindow.cpp \
    Message/UI/MessageListView.cpp \
    Navigation/app/Navigation.cpp \
    Navigation/Factory/NavigationVFactory.cpp \
    Navigation/UI/NavigationWindow.cpp \
    Navigation/UI/NavigationView.cpp \
    Media/app/Media.cpp \
    Media/Factory/MediaVFactory.cpp \
    Media/UI/MediaView.cpp \
    Media/UI/MediaWindow.cpp \
    Message/UI/MessagesNoNewInfoView.cpp \
    VR/app/VR.cpp \
    VR/Factory/VRVFactory.cpp \
    VR/UI/VRView.cpp \
    VR/UI/VRWindow.cpp \
    VR/UI/VRInteractionView.cpp \
    SDLApps/Templates/AudioPassThru/AudioPassThru.cpp




unix {
    SOURCES += SDLApps/Templates/utils/VideoStream/gst_player.cpp
}



HEADERS  +=  \
    main.h \
    MainWindow.h \
    HMIFrameWork/AppConfig.h \
    HMIFrameWork/AppManager.h \
    HMIFrameWork/log_interface.h \
    HMIFrameWork/Interface.h \
    HMIFrameWork/App.h \
    HMIFrameWork/GstPlayerMessage.h \
    HMIFrameWork/GstPlayer.h \
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
    HMIWidgets/CSlider.h \
    HMIWidgets/AlbumCoverWidget.h \
    HMIWidgets/TopNavigateWidget.h \
    HMIWidgets/AppListWidget.h \
    HMIWidgets/CAppButton.h \
    Home/app/Home.h \
    Home/Factory/HomeVFactory.h \
    Home/UI/HomeView.h \
    Home/UI/HomeWindow.h \
    Home/UI/Settings/SettingsDateTimeUI.h \
    Home/UI/Settings/SettingsMainUI.h \
    Home/UI/Settings/SettingsSoundUI.h \
    Home/UI/Settings/SettingsBTUI.h \
    Home/UI/Settings/SettingsWifiAddHotSpotsUI.h \
    Home/UI/Settings/SettingsWifiPasswordUI.h \
    Home/UI/Settings/SettingsWifiUI.h \
    Home/UI/Settings/SettingsSpeechRecognitionUI.h \
    Home/UI/Settings/SettingsRoutineSettingUI.h \
    Home/UI/Settings/SettingsEmergencyUI.h \
    Home/UI/Settings/SettingsDisplayUI.h \
    Home/UI/PlayVedio/BootAnimation.h \
    Home/UI/PlayVedio/BootAnimationUI.h \
    Home/data/Settings/SettingsWifiData.h \
    Home/data/Settings/SettingsBTData.h \
    Home/data/Settings/SettingsDateTimeData.h \
    Home/data/Settings/SettingsRoutineSettingData.h \
    Home/data/Settings/SettingsDisplayData.h \
    Home/data/Settings/SettingsMobileApplicationsData.h \
    Home/UI/Settings/SettingsMobileApplicationsUI.h \
    Home/data/Settings/SettingsEmergencyData.h \
    QuickLanuch/app/QuickLanuch.h \
    QuickLanuch/Factory/QuickVFactory.h \
    QuickLanuch/UI/QuickLanuchView.h \
    QuickLanuch/UI/QuickLanuchWindow.h \
    StatusBar/app/StatusBar.h \
    StatusBar/Factory/StatusBarVFactory.h \
    StatusBar/UI/StatusBarView.h \
    StatusBar/UI/StatusBarWindow.h \
    SDLApps/app/SDLApps.h \
    SDLApps/Factory/SDLVFactory.h \
    SDLApps/UI/SDLAppsView.h \
    SDLApps/UI/SDLAppsWindow.h \
    SDLApps/Templates/UIManager.h \
    SDLApps/Templates/Alert/AlertView.h \
    SDLApps/Templates/AppListView/AppListView.h \
    SDLApps/Templates/AppListView/DeviceListView.h \
    SDLApps/Templates/ChoiceSet/ChoiceSet.h \
    SDLApps/Templates/ChoiceSet/ChoiceSetVR.h \
    SDLApps/Templates/CommandView/CommandView.h \
    SDLApps/Templates/Common/AppBase.h \
    SDLApps/Templates/Common/Button.h \
    SDLApps/Templates/Common/CustomListView.h \
    SDLApps/Templates/Common/MenuButton.h \
    SDLApps/Templates/Config/Config.h \
    SDLApps/Templates/ScrollableMessage/ScollMsgView.h \
    SDLApps/Templates/Show/GraphicSoftButtonShow.h \
    SDLApps/Templates/Show/MediaShow.h \
    SDLApps/Templates/SliderView/SliderView.h \
    SDLApps/Templates/Template/TemplateImp.h \
    SDLApps/Templates/Template/TemplateManager.h \
    SDLApps/Templates/utils/VideoStream/CeVideoStream.h \
    SDLApps/Data/SDLAppsData.h \
    PopUp/app/PopUp.h \
    PopUp/Factory/PopUpVFactory.h \
    PopUp/UI/PopUpWindow.h \
    PopUp/UI/PopUpViewUI.h \
    PopUp/UI/PopupGeneralView.h \
    PopUp/UI/PopUpBase.h \
    Prompt/app/Prompt.h \
    Prompt/Factory/PromptVFactory.h \
    Prompt/UI/PromptBase.h \
    Prompt/UI/PromptNavView.h \
    Prompt/UI/PromptViewUI.h \
    Prompt/UI/PromptWindow.h \
    HVAC/app/HVAC.h \
    HVAC/Factory/HVACVFactory.h \
    HVAC/UI/HVACWindow.h \
    HVAC/UI/HVACFrontView.h \
    HVAC/UI/HVACRearView.h \
    HVAC/UI/HVACFrontViewOff.h \
    HVAC/UI/HVACRearViewOff.h \
    HVAC/data/HVACData.h \
    Phone/app/Phone.h \
    Phone/Factory/PhoneVFactory.h \
    Phone/UI/KeyBoardView.h \
    Phone/UI/PhoneWindow.h \
    HMIWidgets/PhonePicker.h \
    Phone/data/PhoneData.h \
    Phone/UI/ContactsView.h \
    Phone/UI/RecentsView.h \
    Phone/UI/ContactsDetailsView.h \
    Prompt/UI/PromptMessageView.h \
    Phone/UI/CallingView.h \
    Message/app/Message.h \
    Message/data/MessageData.h \
    Message/Factory/MessageVFactory.h \
    Message/UI/MessagesView.h \
    Message/UI/MessageWindow.h \
    Message/UI/MessageListView.h \
    Navigation/app/Navigation.h \
    Navigation/Factory/NavigationVFactory.h \
    Navigation/UI/NavigationWindow.h \
    Navigation/UI/NavigationView.h \
    Media/app/Media.h \
    Media/Factory/MediaVFactory.h \
    Media/UI/MediaView.h \
    Media/UI/MediaWindow.h \ 
    Message/UI/MessagesNoNewInfoView.h \
    VR/app/VR.h \
    VR/Factory/VRVFactory.h \
    VR/UI/VRView.h \
    VR/UI/VRWindow.h \
    VR/UI/VRInteractionView.h \
    SDLApps/Templates/AudioPassThru/AudioPassThru.h



unix {
    HEADERS += SDLApps/Templates/utils/VideoStream/gst_player.h
}

unix {
    target.path = /usr/lib
}


RESOURCES += \
    Home/Source/HomeImages.qrc \
    QuickLanuch/Source/QuickLanuchImages.qrc \
    Home/Source/images/Settings/SettingsSource.qrc \
    StatusBar/Source/StatusBarImages.qrc \
    PopUp/Source/PopUpImages.qrc \
    HVAC/Source/HVACImages.qrc \
    Phone/Source/PhoneImages.qrc \
    Prompt/Source/PromptImages.qrc \
    Message/Source/MessageImages.qrc \
    SDLApps/Source/SDLAppsImages.qrc \
    Navigation/Source/NavigationImages.qrc \
    Media/Source/MediaImages.qrc \
    VR/Source/VRImages.qrc

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
INCLUDEPATH += $$PWD/../../HMI_SDK_LIB/include \
               $$PWD/../../HMI_SDK_LIB/include/wince

DEFINES += OS_WIN32
DEFINES += SDL_SUPPORT_LIB
}


################################for android
android{
QT += androidextras
DEFINES +=ANDROID \
          SDL_SUPPORT_LIB

ANDROID_EXTRA_LIBS = $$PWD/../../HMI_SDK_LIB/lib/android/libhmi_sdk.so \
    $$PWD/../../HMI_SDK_LIB/lib/android/libsmartDeviceLinkCore.so

}

FORMS += \
    MainWindow.ui

