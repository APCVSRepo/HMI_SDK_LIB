#include "AppListView.h"
//#include "Notify/Notify.h"

CAppListView::CAppListView(AppListInterface * pList,QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    if (parent){
        setGeometry(0,0,parent->width(),parent->height());
        m_AppWidth = parent->width() / 4;
        m_AppHeight = parent->height() / 2;
    }

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/applinkmain.png");
    pixmap = pixmap.scaled(width(),height(),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    m_pList = pList;

    QString appsheet_on[2] = {":/images/phonechild_on.png",
                              ":/images/listchild_on.png"};
    QString appsheet_off[2] = {":/images/phonechild_off.png",
                               ":/images/listchild_off.png"};
    //QString childText[2]={"Find New App","App Setting"};
    QString childText[2] = {"连接设备","连接移动应用程序"};
    int funcId[2] = {-1,-2};
    for (int i = 0; i < 2; ++i) {
        InsertChildApp(i,funcId[i],childText[i],
                       appsheet_on[i],appsheet_off[i]);
    }
}

CAppListView::~CAppListView()
{
    for (int i = 0; i != m_pChildApps.size(); ++i) {
        delete m_pChildApps[i];
    }
    m_pChildApps.clear();
}


void CAppListView::onChildAppSelected(int funcId)
{
    if (-1 == funcId) {
        m_pList->OnStartDeviceDiscovery();
        m_pList->OnShowDeviceList();
    }else if (-2 == funcId) {

    } else {
         m_pList->OnAppActivated(funcId);
    }
}

void CAppListView::InsertChildApp(int index,int appId,QString text,
                                  QString on,QString off,bool bPaint)
{
    for (int i = index; i < m_pChildApps.size(); ++i) {
        CAppButton *button = m_pChildApps.at(i);
        int r = (i+1)/4;
        int c = (i+1)%4;
        button->setGeometry(5+m_AppWidth*c,5+m_AppHeight*r,
                            m_AppWidth-10,m_AppHeight-10);
    }
    CAppButton *newbutton = new CAppButton(this);
    int r = index/4;
    int c = index%4;
    newbutton->setGeometry(5 + m_AppWidth*c, 5 + m_AppHeight*r,
                           m_AppWidth - 10, m_AppHeight - 10);
    newbutton->setFuncId(appId);
    newbutton->setIcon(on, off,bPaint);
    newbutton->setText(text);
    newbutton->show();
    connect(newbutton, SIGNAL(clickedWitchFuncId(int)),
            SLOT(onChildAppSelected(int)));
    m_pChildApps.insert(index, newbutton);
}

void CAppListView::DeleteChildApp(int index)
{
    CAppButton *button = m_pChildApps.at(index);
    m_pChildApps.removeAt(index);
    disconnect(button,SIGNAL(clickedWitchFuncId(int)),
               this,SLOT(onChildAppSelected(int)));
    delete button;
    for (int i = index;i<m_pChildApps.size();++i) {
        CAppButton *button = m_pChildApps.at(i);
        int r = i/4;
        int c = i%4;
        button->setGeometry(5+m_AppWidth*c,5+m_AppHeight*r,
                            m_AppWidth-10,m_AppHeight-10);
    }
}

void CAppListView::showEvent(QShowEvent * e)
{
    std::vector<int> vAppIDs;
    std::vector<std::string> vAppNames;
    std::vector<std::string> vIconPath;
    m_pList->getAppList(vAppIDs, vAppNames,vIconPath);
    int count = m_pChildApps.size();
    for (int i = 2; i < count; ++i) {
        DeleteChildApp(2);
    }
    if (vAppIDs.size() > 0) {
        for (int i = 0; i < vAppIDs.size(); ++i) {
            InsertChildApp(2+i,vAppIDs.at(i),
                           vAppNames.at(i).c_str(),
                           vIconPath.at(i).c_str(),
                           vIconPath.at(i).c_str(),
                           true);
        }
    }
}
