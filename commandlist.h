#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "block/blockwidget.h"

#include <QListWidget>

class CommandList : public QListWidget {
  Q_OBJECT

public:
  explicit CommandList(QWidget *parent = nullptr);
  void addBlock(const QString &name);
  void addBlock(BlockWidget *block, const BlockParams &params);
  [[nodiscard]] QList<BlockWidget *> getBlocks() const;

signals:
  void updated();

protected:
  void keyPressEvent(QKeyEvent *event) override;
  bool eventFilter(QObject *object, QEvent *event) override;
};

#endif
