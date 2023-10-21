#ifndef DATA1DBLOCK_H
#define DATA1DBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledtable.h"

class Data1dBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit Data1dBlock(QWidget *t = nullptr);
  [[nodiscard]] QString getCode() const override;
  void setParams(const BlockParams &params) override;
  void paint(BuildContext &context) override;

private:
  LabeledTable *table;
};

#endif
