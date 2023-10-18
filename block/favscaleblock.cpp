#include "favscaleblock.h"

FavScaleBlock::FavScaleBlock(QWidget *parent)
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

QString FavScaleBlock::getCode() {
  return QString("FavScale min=%1 max=%2")
      .arg(minBox->spinBox()->value())
      .arg(maxBox->spinBox()->value());
}
