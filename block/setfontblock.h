#ifndef SETFONTBLOCK_H
#define SETFONTBLOCK_H

#include "blockwidget.h"
#include "labeled/labeledfontpicker.h"

class SetFontBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit SetFontBlock(QWidget *parent = nullptr)
      : BlockWidget("SetFont", BlockColors::graphSetup, parent) {
    fontPicker = new LabeledFontPicker("font");
    connect(fontPicker, &LabeledFontPicker::updated, this,
            &BlockWidget::updated);
    layout->addWidget(fontPicker, 1, 0);
  }

  [[nodiscard]] QString getCode() const override {
    return QString("SetFont font=%1")
        .arg(encodeString(fontPicker->selectedFont().family()));
  }

private:
  LabeledFontPicker *fontPicker;
};

#endif
