#ifndef TRANSLUCENTLABEL_H
#define TRANSLUCENTLABEL_H

#include <QLabel>

class TranslucentLabel : public QLabel {
  Q_OBJECT

public:
  explicit TranslucentLabel(QWidget *parent = nullptr) : QLabel(parent) {
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Ignored);
  }

  explicit TranslucentLabel(const QString &text, QWidget *parent = nullptr)
      : QLabel(text, parent) {
    setAttribute(Qt::WA_TranslucentBackground);
  }
};

#endif
