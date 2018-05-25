#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QStyledItemDelegate>
#include "CVListWidget.h"
#include <QTimer>

class ListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ListDelegate(CVListWidget* listWidget = 0);
    ~ListDelegate();

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const;

    void DrawBackgroundPixmap(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void DrawText(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void DrawIcon(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void DrawButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void DrawIndicator(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void DrawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

public slots:

private:
    CVListWidget*        m_pVListWidget;
};

#endif // LISTDELEGATE_H
