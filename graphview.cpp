#include "graphview.h"

#include <QPainter>

void GraphView::rebuild(const QList<BlockWidget *> &blocks_list) {
  blocks = blocks_list;
  update();
}

void GraphView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  BuildContext context(painter, width(), height());
  try {
    for (auto *block : blocks) {
      block->paint(context);
      context.currBlockId++;
    }
  } catch (const BuildContextException &ex) {
    QString msg =
        QString("Block %1: %2")
            .arg(QString::number(context.currBlockId), ex.getMessage());
    emit statusUpdated(msg);
  }
}
