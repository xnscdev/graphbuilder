#include "setfontblock.h"

SetFontBlock::SetFontBlock(QWidget *parent)
    : BlockWidget("SetFont", BlockColors::graphSetup, parent) {
  fontPicker = new LabeledFontPicker("font");
  connect(fontPicker, &LabeledFontPicker::updated, this, &BlockWidget::updated);
  layout->addWidget(fontPicker, 1, 0);
}

QString SetFontBlock::getCode() const {
  return QString("SetFont font=%1")
      .arg(encodeString(fontPicker->selectedFont().toString()));
}

void SetFontBlock::paint(BuildContext &context) const {
  context.painter.setFont(fontPicker->selectedFont());
}
