#include "HomeVFactory.h"
#include "Home/app/Home.h"
#include "Home/UI/HomeView.h"
#include "HMIFrameWork/CView.h"
#include "Home/UI/Settings/SettingsDateTimeUI.h"
#include "Home/UI/Settings/SettingsMainUI.h"
#include "Home/UI/Settings/SettingsSoundUI.h"
#include "Home/UI/Settings/SettingsBTUI.h"
#include "Home/UI/Settings/SettingsWifiAddHotSpotsUI.h"
#include "Home/UI/Settings/SettingsWifiPasswordUI.h"
#include "Home/UI/Settings/SettingsWifiUI.h"
#include "Home/UI/Settings/SettingsMobileApplicationsUI.h"
#include "Home/UI/Settings/SettingsDisplayUI.h"
#include "Home/UI/Settings/SettingsEmergencyUI.h"
#include "Home/UI/Settings/SettingsRoutineSettingUI.h"
#include "Home/UI/Settings/SettingsSpeechRecognitionUI.h"
#include "Home/UI/PlayVedio/BootAnimationUI.h"
HomeVFactory::HomeVFactory()
{
}

HomeVFactory * HomeVFactory::m_pInst = NULL;

HomeVFactory *HomeVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new HomeVFactory;
    }
    return m_pInst;
}

void *HomeVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(Home::Inst()-> getMain());
    switch (viewId) {
    case Home::eViewId_Main:
    {
        HomeView* view = new HomeView(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_Main:
    {
        SettingsMainUI* view = new SettingsMainUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_DataTime:
    {
        SettingsDateTimeUI* view = new SettingsDateTimeUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_Sound:
    {
        SettingsSoundUI* view = new SettingsSoundUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_BT:
    {
        SettingsBTUI* view = new SettingsBTUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_Wifi:
    {
        SettingsWifiUI* view = new SettingsWifiUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_WifiAddHotSpots:
    {
        SettingsWifiAddHotSpotsUI* view = new SettingsWifiAddHotSpotsUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_WifiPassword:
    {
        SettingsWifiPasswordUI* view = new SettingsWifiPasswordUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_Display:
    {
        SettingsDisplayUI* view = new SettingsDisplayUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_Emergency:
    {
        SettingsEmergencyUI* view = new SettingsEmergencyUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_MobileApplications:
    {
        SettingsMobileApplicationsUI* view = new SettingsMobileApplicationsUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_RoutineSetting:
    {
        SettingsRoutineSettingUI* view = new SettingsRoutineSettingUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_Settings_SpeechRecogniton:
    {
        SettingsSpeechRecognitionUI* view = new SettingsSpeechRecognitionUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    case Home::eViewId_BootAnimation:
    {
        BootAnimationUI* view = new BootAnimationUI(mainwin);
        view->setView(dynamic_cast<QWidget*>(view));
        return  dynamic_cast<CView*>(view);
    }
    default:
        return NULL;
    }
}
