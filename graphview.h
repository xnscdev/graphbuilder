#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include "block/blockwidget.h"

#include <QWidget>

class GraphView : public QWidget {
  Q_OBJECT

public:
  explicit GraphView(QWidget *parent = nullptr) : QWidget(parent) {}
  void rebuild(const QList<BlockWidget *> &blocks);

protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif
