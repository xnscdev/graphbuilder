#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include "block/blockwidget.h"

#include <QWidget>

class GraphView : public QWidget {
  Q_OBJECT

public:
  explicit GraphView(QWidget *parent = nullptr) : QWidget(parent) {}
  void rebuild(const QList<BlockWidget *> &blocks_list);

signals:
  void statusUpdated(const QString &msg);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QList<BlockWidget *> blocks;
};

#endif
