#include "CComboBox.h"
#include <QLineEdit>
#include "CComboBoxDelegate.h"
#include "HMIFrameWork/log_interface.h"

CComboBox::CComboBox(QWidget *parent)
    :QComboBox(parent)
    ,m_iIndex(-1)
{
    //style the drop-down icon

    //style popup list
    CComboBoxDelegate *delegate = new CComboBoxDelegate;
    this->setItemDelegate(delegate);

    //style the line-edit list
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setStyleSheet("QLineEdit{background-color:#00000000; background:transparent;}");
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setTextMargins(48,0,48-36,0);
    this->setLineEdit(lineEdit);

    connect(this,SIGNAL(editTextChanged(QString)),this,SLOT(OnEditTextChanged(QString)),Qt::UniqueConnection);
    connect(this,SIGNAL(activated(int)),this,SLOT(OnActivated(int)),Qt::UniqueConnection);
    connect(this,SIGNAL(activated(QString)),this,SLOT(OnActivated(QString)),Qt::UniqueConnection);
    connect(this,SIGNAL(highlighted(int)),this,SLOT(OnHighlighted(int)),Qt::UniqueConnection);
    connect(this,SIGNAL(highlighted(QString)),this,SLOT(OnHighlighted(QString)),Qt::UniqueConnection);
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(OnCurrentIndexChanged(int)),Qt::UniqueConnection);
    connect(this,SIGNAL(currentIndexChanged(QString)),this,SLOT(OnCurrentIndexChanged(QString)),Qt::UniqueConnection);
    connect(this,SIGNAL(currentTextChanged(QString)),this,SLOT(OnCurrentTextChanged(QString)),Qt::UniqueConnection);
}

QAbstractItemDelegate *CComboBox::itemDelegate() const
{
    return QComboBox::itemDelegate();
}

void CComboBox::setItemDelegate(CComboBoxDelegate *delegate)
{
    QComboBox::setItemDelegate(delegate);
    delegate->SetRowCount(this->count());
    delegate->SetItemSize(this->size());
}

void CComboBox::setBtnStyle(const QString &style,const QSize& size,int fontsize)
{
    QString iwidth= QString::number(size.width());
    QString iheight = QString::number(size.height());
    QString iFontSize = QString::number(fontsize);
    QComboBox::setStyleSheet("QComboBox {background-color: #00000000;color:#bbffffff;font-size:"+iFontSize +"px;}\
                             QComboBox::drop-down {\
                                 subcontrol-origin: padding;\
                                 width: "+iwidth+"px;\
                                 height:"+iheight+"px;\
                                 border:none;\
                             }\
                             QComboBox:!editable:off {\
                                 background-color: #2698ff;\
                                 color:#ff0000;\
                             }\
                             QComboBox::down-arrow {\
                                 image: url("+style+");\
                             }");
}

void CComboBox::addItem(const QString &atext, const QVariant &auserData)
{
    insertItem(count(), atext, auserData);
}

void CComboBox::addItem(const QIcon &aicon, const QString &atext, const QVariant &auserData)
{
    insertItem(count(), aicon, atext, auserData);
}

void CComboBox::addItems(const QStringList &texts)
{
    insertItems(count(), texts);
}

void CComboBox::insertItem(int aindex, const QString &atext, const QVariant &auserData)
{
    insertItem(aindex, QIcon(), atext, auserData);
}

void CComboBox::insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData)
{
    QComboBox::insertItem(index, icon, text, userData);
    static_cast<CComboBoxDelegate *>(this->itemDelegate())->SetRowCount(this->count());
}

void CComboBox::insertItems(int index, const QStringList &texts)
{
    QComboBox::insertItems(index, texts);
    static_cast<CComboBoxDelegate *>(this->itemDelegate())->SetRowCount(this->count());
}

void CComboBox::SetIndex(int index)
{
    m_iIndex = index;
}

int CComboBox::GetIndex()
{
    return m_iIndex;
}

void CComboBox::OnEditTextChanged(const QString &str)
{
    emit editTextChanged(m_iIndex,str);
}

void CComboBox::OnActivated(int index)
{
    emit activated(m_iIndex,index);
}

void CComboBox::OnActivated(const QString &str)
{
    emit activated(m_iIndex,str);
}

void CComboBox::OnHighlighted(int index)
{
    emit highlighted(m_iIndex,index);
}

void CComboBox::OnHighlighted(const QString &str)
{
    emit highlighted(m_iIndex,str);
}

void CComboBox::OnCurrentIndexChanged(int index)
{
    emit currentIndexChanged(m_iIndex,index);
}

void CComboBox::OnCurrentIndexChanged(const QString &str)
{
    emit currentIndexChanged(m_iIndex,str);
}

void CComboBox::OnCurrentTextChanged(const QString &str)
{
    emit currentTextChanged(m_iIndex,str);
}

void CComboBox::resizeEvent(QResizeEvent *event)
{
    static_cast<CComboBoxDelegate *>(this->itemDelegate())->SetItemSize(event->size());
    QComboBox::resizeEvent(event);
}

void CComboBox::setItemDelegate(QAbstractItemDelegate *delegate)
{
    Q_UNUSED(delegate)
}

