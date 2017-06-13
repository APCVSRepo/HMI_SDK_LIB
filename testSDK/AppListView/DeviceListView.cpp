#include "DeviceListView.h"

CDeviceListView::CDeviceListView(AppListInterface * pList,QWidget *parent)
    :QWidget(parent)
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


    //QString childText[2]={"Find New App","App Setting"};
    QString appsheet_on[2] = {":/images/phonechild_on.png",
                              ":/images/listchild_on.png"};
    QString appsheet_off[2] = {":/images/phonechild_off.png",
                               ":/images/listchild_off.png"};

    QString childText[2] = {"返回","连接移动应用程序"};
    InsertDevice(0,"return",childText[0],
                   appsheet_on[0],appsheet_off[0]);
    /*
    for (int i = 0; i < 2; ++i) {
        InsertChildApp(i,funcId[i],childText[i],
                       appsheet_on[i],appsheet_off[i]);
    }*/
}

CDeviceListView::~CDeviceListView()
{
    for (int i = 0; i != m_pDevices.size(); ++i) {
        delete m_pDevices[i];
    }
    m_pDevices.clear();
}

void CDeviceListView::onDeviceSelected(std::string strId)
{
    if(strId != "return")
    {
        m_pList->OnDeviceSelect(strId);
    }
    m_pList->ShowPreviousUI();
}

void CDeviceListView::InsertDevice(int index,std::string DeviceId,QString text,
                                  QString on,QString off,bool bPaint)
{
    for (int i = index; i < m_pDevices.size(); ++i) {
        CAppButton *button = m_pDevices.at(i);
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
    newbutton->setStringId(DeviceId);
    newbutton->setIcon(on, off,bPaint);
    newbutton->setText(text);
    newbutton->show();
    connect(newbutton, SIGNAL(OnClicked(std::string)),
            SLOT(onDeviceSelected(std::string)));
    m_pDevices.insert(index, newbutton);
}

void CDeviceListView::DeleteDevice(int index)
{
    CAppButton *button = m_pDevices.at(index);
    m_pDevices.removeAt(index);
    disconnect(button,SIGNAL(OnClicked(std::string)),
               this,SLOT(onDeviceSelected(std::string)));
    delete button;
    for (int i = index;i<m_pDevices.size();++i) {
        CAppButton *button = m_pDevices.at(i);
        int r = i/4;
        int c = i%4;
        button->setGeometry(5+m_AppWidth*c,5+m_AppHeight*r,
                            m_AppWidth-10,m_AppHeight-10);
    }
}

void CDeviceListView::ClearDeviceList()
{
    for(int i = 0;i < m_pDevices.size();++i)
    {
        delete m_pDevices[i];
    }
    m_pDevices.clear();
}

void CDeviceListView::showEvent(QShowEvent * e)
{
    ClearDeviceList();

    QString appsheet_on[2] = {":/images/phonechild_on.png",
                              ":/images/listchild_on.png"};
    QString appsheet_off[2] = {":/images/phonechild_off.png",
                               ":/images/listchild_off.png"};

    QString childText[2] = {"返回","连接移动应用程序"};
    InsertDevice(0,"return",childText[0],
                   appsheet_on[0],appsheet_off[0]);

    std::vector<DeviceData> DeviceList;
    m_pList->getDeviceList(DeviceList);

    if (DeviceList.size() > 0) {
        for (int i = 0; i < DeviceList.size(); ++i) {
            InsertDevice(1+i,DeviceList[i].id,
                           DeviceList[i].name.c_str(),
                           appsheet_on[0],
                           appsheet_off[0],
                           true);
        }
    }
}
