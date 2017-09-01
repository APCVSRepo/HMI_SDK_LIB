#ifndef CUSTOMLISTVIEW_H
#define CUSTOMLISTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollBar>
#include <string>
#include <vector>

class CustomListView : public QWidget
{
    Q_OBJECT


public:
    explicit CustomListView(int iWidth,int iHeight,int iMode = LIST,QWidget *parent = 0);
    ~CustomListView();

    enum LISTVIEWMODE{LIST = 0,ICON};

    void AddItem(std::string strText,int iId,std::string strIconPath = "");
    void SetSpace(int iSpace);
    void SetScrollBarStyle(QString strStyle);
    void ItemFilter(std::string strKey);
protected:
    void showEvent(QShowEvent * event);
signals:
    void ItemClicked(int iIndex);
public slots:
    void OnScrollBarValueChange(int iValue);
    void OnChoiceSelected(int iIndex);
private:
    enum SCROLLBARPOS {TOP = 0,MIDDLE,BOTTOM};
    void SetScrollBarStyle(int iMode);
    void UpdateItemShow(int iStartItemIndex = 0);
    void InitScroll();
    void UpdateScrollParam(int iItemCount);

    void AddListItem(std::string strText);
    void AddIconItem(std::string strText,std::string strIconPath = "");

    int m_iMode;
    int m_iItemWidth;
    int m_iItemHeight;

    int m_iItemSpace;

    QHBoxLayout *m_pMainLayout;
    QVBoxLayout *m_pListItemLayout;

    QScrollBar *m_pScrollBar;

    std::vector<QWidget *> *m_pItemShowVec;
    std::vector<QWidget *> m_ListItemVec;
    std::vector<QWidget *> m_FilterItemVec;
};

#endif // CUSTOMLISTVIEW_H
