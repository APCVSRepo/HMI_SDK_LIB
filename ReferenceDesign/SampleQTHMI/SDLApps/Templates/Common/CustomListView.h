#ifndef CUSTOMLISTVIEW_H
#define CUSTOMLISTVIEW_H

#include <string>
#include <vector>
#include <QWidget>
#include "HMIWidgets/CVListWidget.h"

class ListItemData{
public:
    ListItemData(std::string text, int id, std::string path);

    inline std::string GetText(){return m_text;}
    inline int GetID(){return m_id;}
    inline std::string GetPath(){return m_path;}

private:
    std::string m_text;
    int m_id;
    std::string m_path;
};

class CustomListView : public QWidget {
    Q_OBJECT

public:
    explicit CustomListView(int iWidth, int iHeight, int iMode = LIST, QWidget *parent = 0);
    ~CustomListView();

    enum LISTVIEWMODE {LIST = 0, ICON};

    void AddItem(std::string strText, int iId, std::string strIconPath = "");
    void ItemFilter(std::string strKey);

protected:
    void showEvent(QShowEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void ItemClicked(int iIndex);

public slots:
    void OnChoiceSelected(int iIndex);
    void OnChoiceSelected(int iIndex, int iId);

private:
    void UpdateItemShow(unsigned int iStartItemIndex = 0);

private:
    int m_iMode;

    int m_pressx;
    int m_pressy;
    int m_curpage;

    std::vector<QWidget *> *m_pItemShowVec;
    std::vector<QWidget *> m_ListItemVec;
    std::vector<QWidget *> m_FilterItemVec;

    std::vector<ListItemData> m_ListItemDataVec;
    std::vector<ListItemData> m_FilterItemDataVec;
    std::vector<ListItemData> *m_pShowItemDataVec;

    CVListWidget* m_pVlist;
    int m_AppWidth;
    int m_AppHeight;

    QWidget *m_pAppListArea;
};

#endif // CUSTOMLISTVIEW_H
