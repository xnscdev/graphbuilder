#ifndef FAVSCALEBLOCK_H
#define FAVSCALEBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledspinbox.h"

class FavScaleBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit FavScaleBlock(QWidget *parent = nullptr)
      : BlockWidget("FavScale", BlockColors::graphTemplate, parent) {
    minBox = new LabeledSpinBox("min", 0);
    maxBox = new LabeledSpinBox("max", 10);
    connect(minBox->spinBox(), &QSpinBox::valueChanged, this,
            &BlockWidget::updated);
    connect(maxBox->spinBox(), &QSpinBox::valueChanged, this,
            &BlockWidget::updated);
    layout->addWidget(minBox, 1, 0);
    layout->addWidget(maxBox, 1, 1);
  }

  [[nodiscard]] QString getCode() const override {
    return QString("FavScale min=%1 max=%2")
        .arg(minBox->spinBox()->value())
        .arg(maxBox->spinBox()->value());
  }

private:
  LabeledSpinBox *minBox;
  LabeledSpinBox *maxBox;
};

#endif
