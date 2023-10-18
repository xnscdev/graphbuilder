#include "blockwidget.h"
#include "labeled/translucentlabel.h"

const QStringList BlockWidget::blockNames {
    "SetFont",
    "FavScale"
};

BlockWidget::BlockWidget(const QString &name, const QColor &color,
                         QWidget *parent)
    : QFrame(parent), name(name) {
  layout = new QGridLayout(this);
  layout->setHorizontalSpacing(20);
  layout->setVerticalSpacing(4);
  layout->setContentsMargins(5, 5, 5, 5);
  setLayout(layout);
  setStyleSheet(QString("QFrame { background-color: %1; border-radius: 5px; }")
                    .arg(color.name(QColor::NameFormat::HexArgb)));

  auto *nameLabel = new TranslucentLabel(name, this);
  QFont boldFont;
  boldFont.setBold(true);
  nameLabel->setFont(boldFont);
  layout->addWidget(nameLabel, 0, 0, 1, -1);
}
