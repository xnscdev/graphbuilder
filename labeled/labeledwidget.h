#ifndef LABELEDWIDGET_H
#define LABELEDWIDGET_H

#include "translucentlabel.h"

#include <QHBoxLayout>

class LabeledWidget : public QWidget {
  Q_OBJECT

public:
  explicit LabeledWidget(const QString &label, QWidget *parent = nullptr)
      : QWidget(parent) {
    layout = new QHBoxLayout(this);
    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    layout->addWidget(new TranslucentLabel(label));
  }

protected:
  QHBoxLayout *layout;
};

#endif
