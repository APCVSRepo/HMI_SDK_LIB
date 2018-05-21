#include "SDLAppsView.h"
#include <QTime>
#include "SDLApps/Templates/Config/Config.h"
#include "SDLApps/app/SDLApps.h"
SDLAppsView::SDLAppsView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,CView(SDLApps::eViewId_SDL_Main)
    ,m_bInVideoStream(false)
    ,m_bsdlStatus(false)
{
  this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
  m_pList = pList;
  int title_height = 40;
  int status_height = ui_res_width / 9;
  int center_height = ui_res_height - status_height - title_height;
  int margin = 10;
  int inter = 5;
  // setWindowFlags(Qt::FramelessWindowHint);//
  setGeometry(0, 0, ui_res_width, ui_res_height);
  this->setAutoFillBackground(true);
  QPixmap pixmap(":/images/mainmenu.png");
  QPixmap fitpixmap = pixmap.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, QBrush(fitpixmap));
  this->setPalette(palette);

  m_pIcon = new QLabel(this);
  m_pIcon->setGeometry(margin * 2, inter, title_height - inter * 2, title_height - inter * 2);
  m_pIcon->setStyleSheet(QString::fromUtf8("border-image:url(:/images/home.png)"));
  m_pTime = new QLabel(this);
  m_pTime->setGeometry(ui_res_width * 1 / 3, inter, ui_res_width / 3, title_height - inter * 2);
  m_pTime->setAlignment(Qt::AlignCenter);

  m_pTime->setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(255,255,255);background:transparent;border: 0px");
  m_pTime->setText(QTime::currentTime().toString("HH:mm"));

  m_pNetStatus = new QLabel(this);
  m_pNetStatus->setGeometry(ui_res_width - title_height - margin, inter, title_height - 2 * inter, title_height - inter * 2);
  m_pNetStatus->setStyleSheet(QString::fromUtf8("border-image:url(:/images/wifi.png)"));

  // add by fanqiang
  m_pSDLStatus = new QLabel(this);
  m_pSDLStatus->setGeometry(ui_res_width - 2 * (title_height + margin), inter, title_height - 2 * inter, title_height - inter * 2);
  //m_pSDLStatus->setStyleSheet(QString::fromUtf8("border-image:url(:/images/home.png)"));

  m_pSDLStatus->setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(255,0,0);background:transparent;border: 0px");
  m_pSDLStatus->setText("X");

  m_pCenter = new QWidget(this);
  m_pCenter->setGeometry(margin, title_height, ui_res_width - 2 * margin, center_height);
  //m_pCenter->setStyleSheet(QString::fromUtf8("border-image:url(:/images/applinkmain.png)"));

  int y = title_height + center_height;
  m_pMainMenu = new QWidget(this);
  m_pMainMenu->setGeometry(margin, y, ui_res_width - 2 * margin, status_height - inter);
  m_pMainMenu->setStyleSheet(QString::fromUtf8("border-image:url(:/images/downmenu.png)"));
  QString sheet_on[MENU_MAX] = {":/images/music_on.png", ":/images/key_on.png", ":/images/phone_on.png",
                                ":/images/link_on.png", ":/images/list_on.png",
                                ":/images/setting_on.png"
                               };
  QString sheet_off[MENU_MAX] = {":/images/music_off.png", ":/images/key_off.png", ":/images/phone_off.png",
                                 ":/images/link_off.png", ":/images/list_off.png",
                                 ":/images/setting_off.png"
                                };
  //QString text[MENU_MAX]={"Music","Keys","Phone","Navigation","AppList","Settings"};
  QString text[MENU_MAX] = {"音频", "空调", "电话", "导航", "应用程序", "设置"};
  for (int i = 0; i < MENU_MAX; ++i) {
    m_pMenuTab[i] = new MenuButton(m_pMainMenu);
    m_pMenuTab[i]->setGeometry((ui_res_width - 2 * margin) / MENU_MAX * i, 0, (ui_res_width - 2 * margin) / MENU_MAX, status_height);
    m_pMenuTab[i]->setIcon(sheet_on[i], sheet_off[i]);
    m_pMenuTab[i]->setText(text[i]);
    connect(m_pMenuTab[i], SIGNAL(clicked()), SLOT(onMenuSelected()));
  }
  m_pMenuTab[4]->setActive(true);

  m_AppWidth = (ui_res_width - 2 * margin) / 4;
  m_AppHeight = center_height / 2;
  /*
  QString appsheet_on[2]={":/images/phonechild_on.png",":/images/listchild_on.png"};
  QString appsheet_off[2]={":/images/phonechild_off.png",":/images/listchild_off.png"};
  QString childText[2]={"Find New App","App Setting"};
  int funcId[2]={-1,-2};
  for(int i=0;i<2;++i) {
      InsertChildApp(i,funcId[i],childText[i],appsheet_on[i],appsheet_off[i]);
  }
  */

  m_pTimer = new QTimer(this);
  m_pTimer->start(1000);//分钟
  connect(m_pTimer, SIGNAL(timeout()), SLOT(onUpdateTime()));

  //videoWidget = new VideoStream(ui_res_width,ui_res_height,this);
  //connect(videoWidget,SIGNAL(ClickMenuBtn()),this,SLOT(OnVideoStreamMenuBtnClicked()));
}

SDLAppsView::~SDLAppsView() {
  delete m_pIcon;
  delete m_pTime;
  delete m_pNetStatus;
  delete m_pCenter;
  delete m_pMainMenu;
  delete m_pTimer;
  delete m_pNetStatus;
  /*
  for (int i = 0; i < MENU_MAX; ++i) {
      delete m_pMenuTab[i];
  }
  */
  //delete []m_pChildApps;

    //delete videoWidget;
}

void SDLAppsView::viewAction(int state)
{

}

void SDLAppsView::HideAllComponent() {
  if (m_pIcon) {
    m_pIcon->hide();
  }

  if (m_pTime) {
    m_pTime->hide();
  }

  if (m_pSDLStatus) {
    m_pSDLStatus->hide();
  }

  if (m_pNetStatus) {
    m_pNetStatus->hide();
  }

  if (m_pCenter) {
    m_pCenter->hide();
  }
}

void SDLAppsView::ShowAllComponent() {
  if (m_pIcon) {
    m_pIcon->show();
  }

  if (m_pTime) {
    m_pTime->show();
  }

  if (m_pSDLStatus) {
    m_pSDLStatus->show();
  }

  if (m_pNetStatus) {
    m_pNetStatus->show();
  }

  if (m_pCenter) {
    m_pCenter->show();
  }
}

void SDLAppsView::HideMenuBar() {
  m_pMainMenu->hide();
}

void SDLAppsView::ShowMenuBar() {
    m_pMainMenu->show();
}

QWidget *SDLAppsView::CenterWidget() {
  return m_pCenter;
}
void SDLAppsView::onMenuSelected() {
  MenuButton *button = static_cast<MenuButton *>(sender());
  if (NULL == button)
    return;
  for (int i = 0; i < MENU_MAX; ++i) {
    if (button == m_pMenuTab[i]) {
      m_pMenuTab[i]->setActive(true);
      if(i == 0)
      {
          m_pList->OnAppActivated(ID_COMMAND);

      }
    } else {
      m_pMenuTab[i]->setActive(false);
    }
  }
}
/*
void SDLAppsView::onChildAppSelected(int funcId)
{
    if (funcId==-1) {
        Notify n(this);
        n.showDlg();
    }
    else if (funcId==-2) {

    }
    else
    {
         m_pList->OnAppActivated(funcId);
    }
}
*/


void SDLAppsView::onUpdateTime() {
  m_pTime->setText(QTime::currentTime().toString("HH:mm"));

  if (m_bsdlStatus) {

    m_pSDLStatus->setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(0,255,0);background:transparent;border: 0px");
    m_pSDLStatus->setText("H");
  } else {
    m_pSDLStatus->setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(255,0,0);background:transparent;border: 0px");
    m_pSDLStatus->setText("X");
  }
}

/*
void SDLAppsView::InsertChildApp(int index,int appId,QString text,QString on,QString off)
{
    for(int i=index;i<m_pChildApps.size();++i) {
        CAppButton *button=m_pChildApps.at(i);
        int r=(i+1)/4;
        int c=(i+1)%4;
        button->setGeometry(5+m_AppWidth*c,5+m_AppHeight*r,m_AppWidth-10,m_AppHeight-10);
    }
    CAppButton *newbutton=new CAppButton(m_pCenter);
    int r=index/4;
    int c=index%4;
	newbutton->setGeometry(5 + m_AppWidth*c, 5 + m_AppHeight*r, m_AppWidth - 10, m_AppHeight - 10);
	newbutton->setFuncId(appId);
	newbutton->setIcon(on, off);
	newbutton->setText(text);
    newbutton->show();
    connect(newbutton, SIGNAL(clickedWitchFuncId(int)), SLOT(onChildAppSelected(int)));
	m_pChildApps.insert(index, newbutton);
}

void SDLAppsView::DeleteChildApp(int index)
{
    CAppButton *button=m_pChildApps.at(index);
    m_pChildApps.removeAt(index);
    disconnect(button,SIGNAL(clickedWitchFuncId(int)),this,SLOT(onChildAppSelected(int)));
    delete button;
    for(int i=index;i<m_pChildApps.size();++i) {
        CAppButton *button=m_pChildApps.at(i);
        int r=i/4;
        int c=i%4;
        button->setGeometry(5+m_AppWidth*c,5+m_AppHeight*r,m_AppWidth-10,m_AppHeight-10);
    }
}
*/


void SDLAppsView::showEvent(QShowEvent *e) {
  Q_UNUSED(e);
  /*
  std::vector<int> vAppIDs;
  std::vector<std::string> vAppNames;
  std::vector<std::string> vIconPath;
  m_pList->getAppList(vAppIDs, vAppNames,vIconPath);
  int count=m_pChildApps.size();
  for(int i=2;i<count;++i) {
      DeleteChildApp(2);
  }

  if (vAppIDs.size()>0) {

      for(int i=0;i<vAppIDs.size();++i) {
          InsertChildApp(2+i,vAppIDs.at(i),vAppNames.at(i).c_str(),vIconPath.at(i).c_str(),vIconPath.at(i).c_str());
      }
  }
  this->show();
  */
}

void SDLAppsView::StartVideoStream(const char *url) {
  Q_UNUSED(url);
  //videoWidget->setUrl(url);
  //videoWidget->startStream();
}

void SDLAppsView::StopVideoStream() {
  //videoWidget->stopStream();
}

void SDLAppsView::OnVideoStreamMenuBtnClicked() {
  //videoWidget->hide();
  //m_bInVideoStream = true;
  //AppControl->OnShowCommand();
}

void SDLAppsView::BackToVideoStream() {
  /*
  if (m_bInVideoStream)
  {
      m_bInVideoStream = false;
      videoWidget->show();

  }
  */
}

void SDLAppsView::SetSDLStatus(bool bConnect) {
  m_bsdlStatus = bConnect;
}

bool SDLAppsView::InVideoStream() {
  return m_bInVideoStream;
}
