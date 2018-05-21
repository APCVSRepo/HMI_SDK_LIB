#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QScrollBar>

class ScrollBar : public QScrollBar {
  Q_OBJECT
 public:
  explicit ScrollBar(QWidget *parent = 0);
  ~ScrollBar();
  static QString cssString();
  void init(int h);
  void flushScroll(int page, int currentNo, int totalNum);

 signals:

 public slots:

 private:
};

#endif // SCROLLBAR_H
