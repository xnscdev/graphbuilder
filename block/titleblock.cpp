#include "titleblock.h"
#include "fileparser.h"

TitleBlock::TitleBlock(QWidget *parent)
    : BlockWidget("Title", BlockColors::graphTemplate, parent) {
  textEdit = new LabeledLineEdit("text");
  connect(textEdit->lineEdit(), &QLineEdit::textChanged, this,
          &BlockWidget::updated);
  layout->addWidget(textEdit, 1, 0);
}

QString TitleBlock::getCode() const {
  return QString("Title text=%1")
      .arg(FileParser::encodeString(textEdit->lineEdit()->text()));
}

void TitleBlock::setParams(const BlockParams &params) {
  params.getString("text", [&](const QString &value) {
    textEdit->lineEdit()->setText(value);
  });
}

void TitleBlock::paint(BuildContext &context) {
  QString text = textEdit->lineEdit()->text();
  QFontMetrics fm(context.painter.font());
  int height = fm.height() * 3 / 2;
  QRect rect(0, context.currHeight, context.getWidth(), height);
  context.painter.setPen(Qt::black);
  context.painter.drawText(rect, Qt::AlignCenter, text);
  context.currHeight += height;
}
