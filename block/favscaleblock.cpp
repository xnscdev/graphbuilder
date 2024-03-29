#include "favscaleblock.h"

#include <set>

FavScaleBlock::FavScaleBlock(QWidget *parent)
    : GraphTemplateBlock("FavScale", BlockColors::graphTemplate, parent) {
  minBox = new LabeledSpinBox("min", 0);
  maxBox = new LabeledSpinBox("max", 10);
  invertedBox = new QCheckBox("inverted");
  connect(minBox->spinBox(), &QSpinBox::valueChanged, this,
          &BlockWidget::updated);
  connect(maxBox->spinBox(), &QSpinBox::valueChanged, this,
          &BlockWidget::updated);
  connect(invertedBox, &QCheckBox::stateChanged, this, &BlockWidget::updated);
  layout->addWidget(minBox, 1, 0);
  layout->addWidget(maxBox, 1, 1);
  layout->addWidget(invertedBox, 2, 0, 1, -1);
}

QString FavScaleBlock::getCode() const {
  return QString("FavScale min=%1 max=%2 inverted=%3")
      .arg(minBox->spinBox()->value())
      .arg(maxBox->spinBox()->value())
      .arg(invertedBox->isChecked());
}

void FavScaleBlock::setParams(const BlockParams &params) {
  params.getInt("min", [&](int value) { minBox->spinBox()->setValue(value); });
  params.getInt("max", [&](int value) { maxBox->spinBox()->setValue(value); });
  params.getInt("inverted", [&](int value) { invertedBox->setChecked(value); });
}

void FavScaleBlock::paint(BuildContext &context) {
  int min = minBox->spinBox()->value();
  int max = maxBox->spinBox()->value();
  if (max <= min)
    throw BuildContextException("Max value must be greater than min value");

  context.setupGraph(this);
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
  if (invertedBox->isChecked()) {
    grad.setColorAt(0.0, Qt::red);
    grad.setColorAt(0.5, Qt::yellow);
    grad.setColorAt(1.0, Qt::green);
  } else {
    grad.setColorAt(0.0, Qt::green);
    grad.setColorAt(0.5, Qt::yellow);
    grad.setColorAt(1.0, Qt::red);
  }
  context.painter.fillRect(bar, grad);
  context.painter.drawRect(bar);
  dataStart = lineEnd + 80;
}

void FavScaleBlock::paintData(BuildContext &context,
                              const QList<QList<double>> &data,
                              const QStringList &labels) const {
  int min = minBox->spinBox()->value();
  int max = maxBox->spinBox()->value();
  QList<double> xs = data[0];
  QFontMetrics fm(context.painter.font());
  int length = static_cast<int>(xs.length());
  int fullRectPadding = fm.height() / 4;
  int pointTextPadding = fm.height() * 4 / 5;
  int pointSize = fm.height() / 3;
  auto rectComparator = [](const QRect &a, const QRect &b) {
    if (a.x() < b.x())
      return true;
    if (a.x() > b.x())
      return false;
    return a.y() < b.y();
  };
  std::set<QRect, decltype(rectComparator)> rects(rectComparator);
  for (int i = 0; i < length; i++) {
    int y = context.transformY(0.05 + 0.9 * (xs[i] - min) / (max - min));
    int x = context.transposeX(dataStart);
    QPoint point(x, y);
    QRect textRect = fm.boundingRect(labels[i]);
    textRect.moveCenter(point);
    textRect.moveLeft(point.x() + pointTextPadding);
    QRect fullRect(textRect);
    fullRect.adjust(-pointTextPadding - fullRectPadding - pointSize,
                    -fullRectPadding, fullRectPadding, fullRectPadding);
    for (auto &rect : rects) {
      if (rect.intersects(fullRect)) {
        int diff = rect.right() + fm.height() - x;
        x += diff;
        textRect.translate(diff, 0);
        fullRect.translate(diff, 0);
      }
    }

    context.painter.setBrush(Qt::black);
    context.painter.setPen(Qt::transparent);
    context.painter.drawEllipse(x, y, pointSize, pointSize);

    context.painter.setBrush(Qt::BrushStyle::NoBrush);
    context.painter.setPen(Qt::black);
    context.painter.drawText(textRect, Qt::AlignCenter, labels[i]);
    rects.insert(fullRect);
  }
}
