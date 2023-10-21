#ifndef LABELEDSPINBOX_H
#define LABELEDSPINBOX_H

#include "labeledwidget.h"

#include <QSpinBox>

class LabeledSpinBox : public LabeledWidget {
  Q_OBJECT

public:
  explicit LabeledSpinBox(const QString &label, int value = 0, int min = -99999,
                          int max = 99999, QWidget *parent = nullptr)
      : LabeledWidget(label, parent) {
    m_lineEdit = new QSpinBox();
    m_lineEdit->setMinimum(min);
    m_lineEdit->setMaximum(max);
    m_lineEdit->setValue(value);
    m_lineEdit->setSizePolicy(QSizePolicy::Policy::Expanding,
                             QSizePolicy::Policy::Ignored);
    layout->addWidget(m_lineEdit);
  }

  [[nodiscard]] QSpinBox *spinBox() const { return m_lineEdit; }

private:
  QSpinBox *m_lineEdit;
};

#endif
