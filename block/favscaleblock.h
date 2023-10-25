#ifndef FAVSCALEBLOCK_H
#define FAVSCALEBLOCK_H

#include "graphtemplateblock.h"
#include "labeled/labeledspinbox.h"

#include <QCheckBox>

class FavScaleBlock : public GraphTemplateBlock {
  Q_OBJECT

public:
  explicit FavScaleBlock(QWidget *parent = nullptr);
  [[nodiscard]] QString getCode() const override;
  void setParams(const BlockParams &params) override;
  void paint(BuildContext &context) override;
  [[nodiscard]] DataType dataType() const override { return DataType::Data1d; }
  void paintData(BuildContext &context, const QList<QList<double>> &data,
                 const QStringList &labels) const override;

private:
  LabeledSpinBox *minBox;
  LabeledSpinBox *maxBox;
  QCheckBox *invertedBox;
  int dataStart = 0;
};

#endif
