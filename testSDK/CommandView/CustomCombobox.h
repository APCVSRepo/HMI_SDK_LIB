#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QListWidget>
#include "Common/ScrollBar.h"
#include "CustomComboboxItem.h"

class CustomCombobox : public QListWidget
{
    Q_OBJECT
public:
    explicit CustomCombobox(int iMaxHeight,bool bUp = false,QWidget *parent = NULL);
    //explicit CustomCombobox(int iStartX,int iStartY,int iWidth,int iMaxHeight,bool bUp = true,QWidget *parent = NULL);
    ~CustomCombobox();

    static QString cssString();

    void AddListItem(QString strText,bool bMenu,std::string strImagePath = "");
    // 根据朝向设定窗体位置
    void SetPos(int iStartX,int iStartY,int iWidth,int iHeight);

    // 清空所有项
    void ClearAllItem();

signals:
    void ItemClickedSignal(QListWidgetItem *pItem);
public slots:
    void OnTimeOutSlot();

    void OnScrollBarValueChange(int iValue);

    void OnItemClicked(CustomComboboxItem *pItem);
private:
    enum SCROLLBARPOS {TOP = 0,MIDDLE,BOTTOM};
    void SetScrollBarStyle(int iMode);

    // 定时检查鼠标位置，给悬停的选项高亮
    QTimer *m_pTimer;
    void SetScrollParams(int page,int range);

    QVector<CustomComboboxItem*> m_itemList;
    int m_iOldHoverItemIndex;

    ScrollBar m_scrollWidget;
    // 起始点
    int m_iStartX;
    int m_iStartY;
    // 宽度
    int m_iWidth;
    // 高度
    int m_iHeight;
    // 最大高度
    int m_iMaxHeight;
    // true表示向上，false表示朝下
    bool m_bUp;


    //void mouseMoveEvent(QMouseEvent *event);
};

#endif // CUSTOMCOMBOBOX_H
