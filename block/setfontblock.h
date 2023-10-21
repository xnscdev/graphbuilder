#ifndef SETFONTBLOCK_H
#define SETFONTBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledfontpicker.h"

class SetFontBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit SetFontBlock(QWidget *parent = nullptr);
  [[nodiscard]] QString getCode() const override;
  void setParams(const BlockParams &params) override;
  void paint(BuildContext &context) override;

private:
  LabeledFontPicker *fontPicker;
};

#endif
