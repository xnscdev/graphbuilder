#include "favscaleblock.h"

FavScaleBlock::FavScaleBlock(QWidget *parent)
    : BlockWidget("FavScale", BlockColors::graphTemplate, parent) {
  minBox = new LabeledSpinBox("min", 0);
  maxBox = new LabeledSpinBox("max", 10);
  connect(minBox->spinBox(), &QSpinBox::valueChanged, this,
          &BlockWidget::updated);
  connect(maxBox->spinBox(), &QSpinBox::valueChanged, this,
          &BlockWidget::updated);
  layout->addWidget(minBox, 1, 0);
  layout->addWidget(maxBox, 1, 1);
}

QString FavScaleBlock::getCode() const {
  return QString("FavScale min=%1 max=%2")
      .arg(minBox->spinBox()->value())
      .arg(maxBox->spinBox()->value());
}

void FavScaleBlock::paint(BuildContext &context) const {
  int min = minBox->spinBox()->value();
  int max = maxBox->spinBox()->value();
  if (max <= min)
    throw BuildContextException("Max value must be greater than min value");

  context.setupGraph();
  context.painter.setPen(QPen(Qt::black, 1));

  int increment = BuildContext::axisIncrement(min, max);
  QFontMetrics fm(context.painter.font());
  int longest = 0;
  // Attempting to draw an interval line marker above this boundary will fail
  // since it would overlap with the line marker for the max value
  int yBoundary = context.transformY(0.95) +
                  fm.tightBoundingRect(QString::number(max)).height() + 3;
  // Create a line marker at each increment, and also a final one at max
  // even if max isn't a multiple of the increment
  QList<GraphTickInfo> lines;
  for (int i = min; i <= max;
       i = i < max && i + increment > max ? max : i + increment) {
    double y = 0.05 + (i - min) * 0.9 / (max - min);
    QString label = QString::number(i);
    QRect textRect = fm.tightBoundingRect(label);
    textRect.moveCenter(context.getPointTransformedY(0, y));
    if (i < max && textRect.center().y() < yBoundary)
      continue;
    lines.append({textRect, label, y});
    longest = qMax(longest, textRect.width());
  }
  int lineStart = longest + fm.height() / 2;
  int lineEnd = lineStart + fm.height();
  for (auto &line : lines) {
    QRect textRect = line.rect;
    textRect.moveRight(context.transposeX(longest));
    int ds = fm.height() / 4;
    textRect.adjust(-ds, -ds, ds, ds);
    context.painter.drawText(textRect, Qt::AlignCenter, line.label);
    context.painter.drawLine(context.getPointTransformedY(lineStart, line.y),
                             context.getPointTransformedY(lineEnd, line.y));
  }

  // Draw the color bar
  context.painter.setPen(QPen(Qt::black, 3));
  QRect bar = context.getRectTransformedY(lineEnd, 0, 40, 1);
  QLinearGradient grad(0, 0, 0, bar.height());
  grad.setColorAt(0.0, Qt::green);
  grad.setColorAt(0.5, Qt::yellow);
  grad.setColorAt(1.0, Qt::red);
  context.painter.fillRect(bar, grad);
  context.painter.drawRect(bar);
}