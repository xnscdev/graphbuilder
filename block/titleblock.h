#ifndef TITLEBLOCK_H
#define TITLEBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledlineedit.h"

class TitleBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit TitleBlock(QWidget *parent = nullptr);
  [[nodiscard]] QString getCode() const override;
  void setParams(const BlockParams &params) override;
  void paint(BuildContext &context) override;

private:
  LabeledLineEdit *textEdit;
};

#endif
