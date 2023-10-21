#include "setfontblock.h"
#include "fileparser.h"

SetFontBlock::SetFontBlock(QWidget *parent)
    : BlockWidget("SetFont", BlockColors::setup, parent) {
  fontPicker = new LabeledFontPicker("font");
  connect(fontPicker, &LabeledFontPicker::updated, this, &BlockWidget::updated);
  layout->addWidget(fontPicker, 1, 0);
}

QString SetFontBlock::getCode() const {
  return QString("SetFont font=%1")
      .arg(FileParser::encodeString(fontPicker->selectedFont().toString()));
}

void SetFontBlock::setParams(const BlockParams &params) {
  params.getString("font", [&](const QString &fontData) {
    QFont font;
    if (!font.fromString(fontData))
      throw FileParserException("Invalid font description");
    fontPicker->setSelectedFont(font);
  });
}

void SetFontBlock::paint(BuildContext &context) {
  context.painter.setFont(fontPicker->selectedFont());
}
