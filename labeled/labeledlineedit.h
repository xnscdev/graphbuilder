#ifndef LABELEDLINEEDIT_H
#define LABELEDLINEEDIT_H

#include "labeledwidget.h"

#include <QLineEdit>

class LabeledLineEdit : public LabeledWidget {
  Q_OBJECT

public:
  explicit LabeledLineEdit(const QString &label, QWidget *parent = nullptr)
      : LabeledWidget(label, parent) {
    m_lineEdit = new QLineEdit();
    m_lineEdit->setSizePolicy(QSizePolicy::Policy::Expanding,
                             QSizePolicy::Policy::Ignored);
    layout->addWidget(m_lineEdit);
  }

  [[nodiscard]] QLineEdit *lineEdit() const { return m_lineEdit; }

private:
  QLineEdit *m_lineEdit;
};

#endif
