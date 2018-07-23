#include "DeviceListView.h"

CDeviceListView::CDeviceListView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_AppWidth(150)
    ,m_AppHeight(120+5+21)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pAppListArea = new QWidget(this);
    m_pAppListArea->setGeometry(85,43,630,307);

    QString appsheet_on[2] = {":/SDLApps/Source/images/return.png",
                              ""
                             };
    QString appsheet_off[2] = {":/SDLApps/Source/images/return.png",
                               ""
                              };

    QString childText[2]={"Return","App Setting"};
//    QString childText[2] = {"返回", "连接移动应用程序"};
    InsertDevice(0, "return", childText[0], appsheet_on[0], appsheet_off[0]);
}

CDeviceListView::~CDeviceListView() {
    for (int i = 0; i != m_pDevices.size(); ++i) {
        delete m_pDevices[i];
    }
    m_pDevices.clear();
}

void CDeviceListView::onDeviceSelected(std::string strId) {
    if (strId != "return") {
        m_pList->OnDeviceSelect(strId);
    }
    m_pList->ShowPreviousUI();
}

void CDeviceListView::InsertDevice(int index, std::string DeviceId, QString text,
                                   QString on, QString off, bool bPaint) {
    for (int i = index; i < m_pDevices.size(); ++i) {
        CAppButton *button = m_pDevices.at(i);
        int r = (i + 1) / 4;
        int c = (i + 1) % 4;
        button->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                            m_AppWidth, m_AppHeight);
    }
    CAppButton *newbutton = new CAppButton(m_pAppListArea);
    int r = index / 4;
    int c = index % 4;
    newbutton->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                           m_AppWidth, m_AppHeight);
    newbutton->setStringId(DeviceId);
    newbutton->setIcon(on, off, bPaint, true);
    newbutton->setText(text);
    newbutton->show();
    connect(newbutton, SIGNAL(OnClicked(std::string)),
            SLOT(onDeviceSelected(std::string)));
    m_pDevices.insert(index, newbutton);
}

void CDeviceListView::DeleteDevice(int index) {
    CAppButton *button = m_pDevices.at(index);
    m_pDevices.removeAt(index);
    disconnect(button, SIGNAL(OnClicked(std::string)),
               this, SLOT(onDeviceSelected(std::string)));
    delete button;
    for (int i = index; i < m_pDevices.size(); ++i) {
        CAppButton *button = m_pDevices.at(i);
        int r = i / 4;
        int c = i % 4;
        button->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                            m_AppWidth, m_AppHeight);
    }
}

void CDeviceListView::ClearDeviceList() {
    for (int i = 0; i < m_pDevices.size(); ++i) {
        delete m_pDevices[i];
    }
    m_pDevices.clear();
}

void CDeviceListView::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    ClearDeviceList();

    QString appsheet_on[2] = {":/SDLApps/Source/images/return.png",
                              ""
                             };
    QString appsheet_off[2] = {":/SDLApps/Source/images/return.png",
                               ""
                              };

    QString childText[2] = {"返回", "连接移动应用程序"};
    InsertDevice(0, "return", childText[0],
            appsheet_on[0], appsheet_off[0]);

    std::vector<DeviceData> DeviceList;
    m_pList->getDeviceList(DeviceList);

    if (DeviceList.size() > 0) {
        for (unsigned int i = 0; i < DeviceList.size(); ++i) {
            InsertDevice(1 + i, DeviceList[i].id,DeviceList[i].name.c_str(),"","",true);
        }
    }
}
