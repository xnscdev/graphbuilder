#ifndef SETFONTBLOCK_H
#define SETFONTBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledfontpicker.h"

class SetFontBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit SetFontBlock(QWidget *parent = nullptr);
  [[nodiscard]] QString getCode() const override;
  void paint(BuildContext &context) const override;

private:
  LabeledFontPicker *fontPicker;
};

#endif
