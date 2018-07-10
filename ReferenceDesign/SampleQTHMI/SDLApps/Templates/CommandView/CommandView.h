#ifndef COMMANDVIEW_H
#define COMMANDVIEW_H

#include <QWidget>
#include "app_list_interface.h"
#include "HMIWidgets/TopNavigateWidget.h"
#include "HMIWidgets/CVListWidget.h"

typedef struct CommandInformation {
    std::string strCmd;
    int iParentId;
    // 如果是Menu则是MenuID，如果是Command则是CommandID
    int iId;
    bool bMenu;
    std::string strImagePath;
    std::vector<CommandInformation> CmdVec;

    CommandInformation() {
        iParentId = 0;
        iId = 0;
        bMenu = false;
        strCmd.clear();
        strImagePath.clear();
    }
} tagCmdInf;

class CCommandView : public QWidget {
    Q_OBJECT

public:
    explicit CCommandView(AppListInterface *pList, QWidget *parent = 0);
    ~CCommandView();

protected:
    virtual void showEvent(QShowEvent *e);

signals:

public slots:
    void OnReturnBtnClicked();
    void OnListItemClicked(int index);

private:
    void AddCommand(int iCmdId, std::string strName, std::string strImagePath);
    void AddMenu(int iMenuId, std::string strName);
    void AddSubCommand(int iParentId, int iCmdId, std::string strName, std::string strImagePath);

    void RefreshCommandList(tagCmdInf *pMenu = NULL);

private:
    AppListInterface *m_pList;

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    //cmd list
    tagCmdInf *m_pCurrentMenu;
    std::vector<tagCmdInf> m_CmdVec;
    CVListWidget* m_pVlist;
};

#endif // COMMANDVIEW_H
