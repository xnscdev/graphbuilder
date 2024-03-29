#include "commandlist.h"
#include "fileparser.h"

#include <QKeyEvent>

CommandList::CommandList(QWidget *parent) : QListWidget(parent) {
  setDragDropMode(QAbstractItemView::InternalMove);
  setSpacing(5);
  installEventFilter(this);
}

void CommandList::addBlock(const QString &name) {
  BlockWidget *block = FileParser::makeBlock(name);
  if (!block)
    return;
  connect(block, &BlockWidget::updated, this, &CommandList::updated);
  auto *item = new QListWidgetItem;
  addItem(item);
  item->setSizeHint(block->minimumSizeHint());
  setItemWidget(item, block);
  emit updated();
}

void CommandList::addBlock(BlockWidget *block, const BlockParams &params) {
  connect(block, &BlockWidget::updated, this, &CommandList::updated);
  auto *item = new QListWidgetItem;
  addItem(item);
  item->setSizeHint(block->minimumSizeHint());
  setItemWidget(item, block);
  block->setParams(params);
}

QList<BlockWidget *> CommandList::getBlocks() const {
  QList<BlockWidget *> blocks;
  for (int i = 0; i < count(); i++) {
    QListWidgetItem *widgetItem = item(i);
    if (widgetItem) {
      auto *block = qobject_cast<BlockWidget *>(itemWidget(widgetItem));
      if (block)
        blocks.append(block);
    }
  }
  return blocks;
}

void CommandList::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Backspace) {
    QListWidgetItem *item = currentItem();
    if (item) {
      takeItem(row(item));
      delete item;
      emit updated();
    }
  } else {
    QListWidget::keyPressEvent(event);
  }
}

bool CommandList::eventFilter(QObject *object, QEvent *event) {
  // This handles redrawing when an item is moved via drag and drop
  if (object == this && event->type() == QEvent::ChildRemoved)
    emit updated();
  return QListWidget::eventFilter(object, event);
}
