#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qlabel.h>
#include "Common/AppBase.h"
#include "Common/Button.h"



class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(AppListInterface * pList, QWidget *parent = 0);
    ~MainWidget();

    void SetAppName(QString strName);
protected:
    virtual void showEvent(QShowEvent * e);
signals:
    void ExitApp();
    void CommandClick(int iCmdId);
public slots:
    // 菜单点击相应槽
    void BtnMenuClickedSlots();
    // 软按键点击相应槽
    void SoftBtnClickedSlot(int iSoftBtnID);
private:
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

    //void AddCommand(int iCmdId,std::string strName);
    //void AddMenu(int iMenuId,std::string strName);
    //void AddSubCommand(int iParentId,int iCmdId,std::string strName);
    // 如果pMenu为nullptr表示主菜单
    //void RefreshCommandList(tagCmdInf *pMenu);
    // 隐藏command列表
    //void HideCommandList();

    //std::vector<tagCmdInf> m_CmdVec;

    // 4个文字show
    QLabel m_pShowLine[4];

    QLabel *m_pAppNameLab;
    QLabel *m_pMainTitleLab;
    QLabel *m_pIconLab;
    CButton *m_pMenuBtn;
    // 三个软按键
    CButton m_pSoftBtn[3];

    AppListInterface *m_pList;

    QVBoxLayout *m_pMainLayout;
};

#endif // MAINWIDGET_H
