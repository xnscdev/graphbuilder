#include "data1dblock.h"
#include "fileparser.h"
#include "graphtemplateblock.h"

Data1dBlock::Data1dBlock(QWidget *parent)
    : BlockWidget("Data1d", BlockColors::data, parent) {
  QStringList headers;
  headers << "x"
          << "labels";
  table =
      new LabeledTable(headers, 2, [&](QTableWidget *t, QStringList *params) {
        auto *spinBox = new QDoubleSpinBox;
        spinBox->setMinimum(-99999);
        spinBox->setMaximum(99999);
        if (params) {
          bool ok;
          QString str = params->value(0);
          double spinValue = str.toDouble(&ok);
          if (!ok)
            throw FileParserException(
                QString("Value in vector must be a double, got '%1'").arg(str));
          spinBox->setValue(spinValue);
        }
        connect(spinBox, &QDoubleSpinBox::valueChanged, this,
                &BlockWidget::updated);
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
    QTableWidgetItem *labelItem = table->table()->item(i, 1);
    xs.append(QString::number(spinBox->value()));
    labels.append(FileParser::encodeString(labelItem->text()));
  }
  return QString("Data1d x=%1 labels=%2").arg(xs.join(','), labels.join(','));
}

void Data1dBlock::setParams(const BlockParams &params) {
  if (!params.contains("x") || !params.contains("labels"))
    return;
  table->setRows({params["x"], params["labels"]});
}

void Data1dBlock::paint(BuildContext &context) {
  const GraphTemplateBlock *graphBlock = context.getGraphBlock();
  if (!graphBlock)
    return;
  if (graphBlock->dataType() != DataType::Data1d)
    throw BuildContextException(
        "The selected graph template does not support one-dimensional data");

  QList<double> xs;
  QStringList labels;
  for (int i = 0; i < table->table()->rowCount(); i++) {
    auto *spinBox =
        qobject_cast<QDoubleSpinBox *>(table->table()->cellWidget(i, 0));
    QTableWidgetItem *labelItem = table->table()->item(i, 1);
    xs.append(spinBox->value());
    labels.append(labelItem->text());
  }
  graphBlock->paintData(context, {xs}, labels);
}
