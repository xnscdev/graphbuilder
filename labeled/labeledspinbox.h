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
    m_spinBox = new QSpinBox();
    m_spinBox->setMinimum(min);
    m_spinBox->setMaximum(max);
    m_spinBox->setValue(value);
    m_spinBox->setSizePolicy(QSizePolicy::Policy::Expanding,
                             QSizePolicy::Policy::Ignored);
    layout->addWidget(m_spinBox);
  }

  [[nodiscard]] QSpinBox *spinBox() const { return m_spinBox; }

private:
  QSpinBox *m_spinBox;
};

#endif
