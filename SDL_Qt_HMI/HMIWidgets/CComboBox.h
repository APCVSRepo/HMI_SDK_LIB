#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QComboBox>
#include <QResizeEvent>
#include <QSize>
class CComboBoxDelegate;
class CComboBox : public QComboBox
{
    Q_OBJECT
public:
    CComboBox(QWidget * parent = 0);

    QAbstractItemDelegate *itemDelegate() const;
    void setItemDelegate(CComboBoxDelegate *delegate);
    void setBtnStyle(const QString& style,const QSize& size);
    //overwrite
    void addItem(const QString &text, const QVariant &userData = QVariant());
    void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
    void addItems(const QStringList &texts);
    void insertItem(int index, const QString &text, const QVariant &userData = QVariant());
    void insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
    void insertItems(int index, const QStringList &texts);
    void SetIndex(int index);
    int GetIndex();
    // QWidget interface

public slots:
    void OnEditTextChanged(const QString &);
    void OnActivated(int index);
    void OnActivated(const QString &);
    void OnHighlighted(int index);
    void OnHighlighted(const QString &);
    void OnCurrentIndexChanged(int index);
    void OnCurrentIndexChanged(const QString &);
    void OnCurrentTextChanged(const QString &);

public :signals:
        void editTextChanged(int ComboBoxIndex ,const QString &);
        void activated(int ComboBoxIndex ,int index);
        void activated(int ComboBoxIndex ,const QString &);
        void highlighted(int ComboBoxIndex ,int index);
        void highlighted(int ComboBoxIndex ,const QString &);
        void currentIndexChanged(int ComboBoxIndex ,int index);
        void currentIndexChanged(int ComboBoxIndex ,const QString &);
        void currentTextChanged(int ComboBoxIndex ,const QString &);
protected:
    void resizeEvent(QResizeEvent *event);

    //this function should not be called
    void setItemDelegate(QAbstractItemDelegate *delegate);

private:
    int m_iIndex;
};



#endif // CCOMBOBOX_H
