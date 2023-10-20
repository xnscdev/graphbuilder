#ifndef FAVSCALEBLOCK_H
#define FAVSCALEBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledspinbox.h"

class FavScaleBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit FavScaleBlock(QWidget *parent = nullptr);
  [[nodiscard]] QString getCode() const override;
  void paint(BuildContext &context) const override;

private:
  LabeledSpinBox *minBox;
  LabeledSpinBox *maxBox;
};

#endif
