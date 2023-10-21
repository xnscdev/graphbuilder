#ifndef GRAPHTEMPLATEBLOCK_H
#define GRAPHTEMPLATEBLOCK_H

#include "blockwidget.h"

enum class DataType { Data1d, Data2d };

class GraphTemplateBlock : public BlockWidget {
  Q_OBJECT

public:
  GraphTemplateBlock(const QString &name, const QColor &color,
                     QWidget *parent = nullptr)
      : BlockWidget(name, color, parent) {}
  [[nodiscard]] virtual DataType dataType() const = 0;
  virtual void paintData(BuildContext &context,
                         const QList<QList<double>> &data,
                         const QStringList &labels) const = 0;
};

#endif
