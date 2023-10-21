#include "data1dblock.h"
#include "fileparser.h"

Data1dBlock::Data1dBlock(QWidget *parent)
    : BlockWidget("Data1d", BlockColors::data, parent) {
  QStringList headers;
  headers << "x"
          << "labels";
  table =
      new LabeledTable(headers, 2, [](QTableWidget *t, QStringList *params) {
        auto *spinBox = new QDoubleSpinBox;
        if (params) {
          bool ok;
          QString str = params->value(0);
          double spinValue = str.toDouble(&ok);
          if (!ok)
            throw FileParserException(
                QString("Value in vector must be a double, got '%1'").arg(str));
          spinBox->setValue(spinValue);
        }
        auto *spinBoxItem = new QTableWidgetItem;
        int row = t->rowCount();
        t->insertRow(row);
        t->setItem(row, 0, spinBoxItem);
        t->setCellWidget(row, 0, spinBox);
        auto *labelItem =
            new QTableWidgetItem(params ? params->value(1) : QString());
        t->setItem(row, 1, labelItem);
      });
  connect(table, &LabeledTable::updated, this, &BlockWidget::updated);
  layout->addWidget(table, 1, 0);
}

QString Data1dBlock::getCode() const {
  QStringList xs;
  QStringList labels;
  for (int i = 0; i < table->table()->rowCount(); i++) {
    auto *spinBox =
        qobject_cast<QDoubleSpinBox *>(table->table()->cellWidget(i, 0));
    double x = spinBox->value();
    QTableWidgetItem *labelItem = table->table()->item(i, 1);
    QString labelText = FileParser::encodeString(labelItem->text());
    xs.append(QString::number(x));
    labels.append(labelText);
  }
  return QString("Data1d x=%1 labels=%2").arg(xs.join(','), labels.join(','));
}

void Data1dBlock::setParams(const BlockParams &params) {
  if (!params.contains("x") || !params.contains("labels"))
    return;
  table->setRows({params["x"], params["labels"]});
}

void Data1dBlock::paint(BuildContext &context) const {
  qDebug() << "REPAINT";
  for (int i = 0; i < table->table()->rowCount(); i++) {
    auto *spinBox =
        qobject_cast<QDoubleSpinBox *>(table->table()->cellWidget(i, 0));
    double x = spinBox->value();
    QTableWidgetItem *labelItem = table->table()->item(i, 1);
    QString labelText = labelItem->text();
    qDebug() << "Row" << i << ": x =" << x << ", labels =" << labelText;
  }
}
