#include "graphview.h"

#include <QPainter>

void GraphView::rebuild(const QList<BlockWidget *> &blocks) {
  qDebug() << "LIST OF BLOCKS";
  for (auto *block : blocks) {
    qDebug() << block->getCode();
  }
}

void GraphView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setPen(Qt::red);
  painter.drawRect(20, 20, 50, 50);
}
