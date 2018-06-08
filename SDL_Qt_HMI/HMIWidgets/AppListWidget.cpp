#include "AppListWidget.h"

AppListWidget::AppListWidget(QWidget *parent)
    :QWidget(parent)
    ,m_AppWidth(150)
    ,m_AppHeight(120+5+21)
    ,m_pressx(0)
    ,m_pressy(0)
    ,m_curpage(1)
{
    if (parent) {
        this->setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pAppListArea = new QWidget(this);
//    m_pAppListArea->setGeometry(85,43,630,307);
    m_pAppListArea->setGeometry(0,0,630,307);

//    QString appsheet_on[2] = {":/SDLApps/Source/images/add_a_device.png",
//                              ":/SDLApps/Source/images/find_mobile_apps.png"
//                             };
//    QString appsheet_off[2] = {":/SDLApps/Source/images/add_a_device.png",
//                               ":/SDLApps/Source/images/find_mobile_apps.png"
//                              };
    //QString childText[2]={"Add a Device","Find Mobile Apps"};
//    QString childText[2] = {"添加设备", "查找移动应用程序"};
//    int funcId[2] = {-1, -2};
//    for (int i = 0; i < 2; ++i) {
//        InsertChildApp(i, funcId[i], childText[i], appsheet_on[i], appsheet_off[i]);
//    }
}

AppListWidget::~AppListWidget()
{
    for (int i = 0; i != m_pChildApps.size(); ++i) {
        delete m_pChildApps[i];
    }
    m_pChildApps.clear();
}

void AppListWidget::onChildAppSelected(int funcId) {
//    if (-1 == funcId) {
//        m_pList->OnStartDeviceDiscovery();
//        m_pList->OnShowDeviceList();
//    } else if (-2 == funcId) {

//    } else {
//        m_pList->OnAppActivated(funcId);
//    }

    emit appSelected(funcId);
}

void AppListWidget::InsertChildApp(int index, int appId, QString text,
                                  QString on, QString off, bool bPaint) {
    CAppButton *newbutton = new CAppButton(m_pAppListArea);
    int r = index / 4;
    int c = index % 4;
    newbutton->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                           m_AppWidth, m_AppHeight);

    newbutton->setFuncId(appId);
    newbutton->setIcon(on, off, bPaint, true);
    newbutton->setText(text);
    newbutton->show();
    connect(newbutton, SIGNAL(clickedWitchFuncId(int)),
            SLOT(onChildAppSelected(int)));
    m_pChildApps.insert(index, newbutton);
}

void AppListWidget::DeleteChildApp(int index) {
    CAppButton *button = m_pChildApps.at(index);
    m_pChildApps.removeAt(index);
    disconnect(button, SIGNAL(clickedWitchFuncId(int)),
               this, SLOT(onChildAppSelected(int)));
    delete button;
}

void AppListWidget::RemoveAll()
{
    while (m_pChildApps.size() > 0) {
        DeleteChildApp(0);
    }
}

void AppListWidget::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
//    std::vector<int> vAppIDs;
//    std::vector<std::string> vAppNames;
//    std::vector<std::string> vIconPath;
//    m_pList->getAppList(vAppIDs, vAppNames, vIconPath);
//    int count = m_pChildApps.size();
//    for (int i = 2; i < count; ++i) {
//        DeleteChildApp(2);
//    }
//    m_curpage = 1;
//    if (vAppIDs.size() > 0) {
//        for (unsigned int i = 0; i < vAppIDs.size(); ++i) {
//            InsertChildApp(2 + i, vAppIDs.at(i),
//                           vAppNames.at(i).c_str(),
//                           vIconPath.at(i).c_str(),
//                           vIconPath.at(i).c_str(),
//                           true);
//        }
//    }

    UpdateItemShow(0);
}

void AppListWidget::UpdateItemShow(unsigned int iStartItemIndex) {
    for (unsigned int i = 0; i != m_pChildApps.size(); ++i) {
        m_pChildApps[i]->hide();
    }

    int r = 0, c = 0;
    if (iStartItemIndex < m_pChildApps.size()) {
        for (unsigned int i = iStartItemIndex; i != m_pChildApps.size() && i < ICON_PAGE + iStartItemIndex; ++i) {
            r = (i / 4) % 2;
            c = i % 4;
            m_pChildApps[i]->show();
            m_pChildApps[i]->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                                         m_AppWidth, m_AppHeight);
        }
    }

    repaint();
}

void AppListWidget::mousePressEvent(QMouseEvent *e) {
    m_pressx = e->x();
    m_pressy = e->y();
}

void AppListWidget::mouseReleaseEvent(QMouseEvent *e) {
    int x = e->x();
    int page = (m_pChildApps.size() + (ICON_PAGE - 1)) / ICON_PAGE;
    if ((m_pressx - x) > 30 && page > m_curpage) {
        // next page
        UpdateItemShow(m_curpage * ICON_PAGE);
        m_curpage++;
    } else if ((x - m_pressx) > 30 && m_curpage > 1) {
        // previous page
        UpdateItemShow((m_curpage - 2)*ICON_PAGE);
        m_curpage--;
    }
}
