#ifndef CUSTOMCOMBOBOXITEM_H
#define CUSTOMCOMBOBOXITEM_H

#include <QListWidgetItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <string>

class CustomComboboxItem : public QLabel
{
    Q_OBJECT
public:
    explicit CustomComboboxItem(int w,int h,QWidget *parent = 0);
    ~CustomComboboxItem();

    void setText(QString text);

    void setIsMenu(bool isMenu);

    void SetBkPic(QString strNormalPicPath,QString strPressPicPath,QString strHoverPicPath);
    enum BkState{NORMAL_STATE = 0,PRESS_STATE,HOVER_STATE};
    void ChangeBkPic(int iFlag);

    QString GetItemText();    
    void SetIndex(int iIndex);
    void SetLeftIcon(std::string strIcon);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void ItemClicked(CustomComboboxItem *pItem);
    void ItemClicked(int iIndex);
private:
    QLabel *m_pIconLab;
    QLabel *m_pMenuArrowLab;
    QLabel *m_pTextLab;
    QHBoxLayout *m_pMainLayout;

    QString m_strNormalBk;
    QString m_strHoverBk;
    QString m_strPressBk;

    int m_iBkState;
    int m_iIndex;
};

#endif // CUSTOMCOMBOBOXITEM_H
