#ifndef CCOMBOBOXDELEGATE_H
#define CCOMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

class CComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CComboBoxDelegate(QObject *parent = 0);

    void SetRowCount(int count);
    void SetItemSize(const QSize &size);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int m_iCount;
    QSize m_size;
    int m_iTextMarginLeft;
    int m_iTextMarginRight;
};

#endif // CCOMBOBOXDELEGATE_H
