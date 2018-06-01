#ifndef PHONEPICKER
#define PHONEPICKER
#include <QListWidget>
#define  CODEZOOM      4


class PhonePicker : public QListWidget
{
    Q_OBJECT
public:
    explicit PhonePicker(QWidget *parent = 0);
    ~PhonePicker();

    void InsertItem(int index, const QString &text, const QSize& itemSize, int fontSize, int specifiedID = -1);
    void SetCircular(bool mode);
    QString GetItemText(int index);
    int GetItemSpecifiedID(int index);
    void SetItemCountPerPage(int count);
    void UpdateItemText(int index, const QString& qsText);

protected:
    bool eventFilter(QObject *object, QEvent *event);
    bool MouseEvent(QObject *object, QEvent *event);
signals:
    void currentIndexChanged(int index);
    void updateYear(int step,int index);
    void pressIndex(int index);
    void addPage();
    void CurrentText(int index,QString text);
    void CurrentIndex(int index);
public slots:
    void itemPressed_slot(QListWidgetItem *item);
private:
    void PChangeListItemSize(int number);
    void MChangeListItemSize(int number);
    void PmChangeListItemSize(int number);
    void MmChangeListItemSize(int number);
    void RChangeListItemSize(int number);
    void RmChangeListItemSize(int number);
private:
    int            m_nMouseDownX;
    int            m_nMouseDownY;
    int            m_nLastScrollBarValue;
    bool           m_bCircularList;
    bool           DragDiraction;
    QSize          m_sizeItem;
    int            m_nItemCountPerPage;
    int             m_SaveY;
    int             m_PressIndex;
    int             m_MoveIndex;
    int             m_RealseIndex;
    int             m_sizeH;
    int             m_textFont;
    int             m_stepSize;
    int             m_MaxViewHit;
    int             m_MinViewHit;
    bool          m_IsChangY;
    int             m_nResize;

};
#endif // PHONEPICKER

