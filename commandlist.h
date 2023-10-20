#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "block/blockwidget.h"

#include <QListWidget>

class CommandList : public QListWidget {
  Q_OBJECT

public:
  explicit CommandList(QWidget *parent = nullptr);
  void addBlock(const QString &name);
  QList<BlockWidget *> getBlocks();

signals:
  void updated();

protected:
  void keyPressEvent(QKeyEvent *event) override;
  bool eventFilter(QObject *object, QEvent *event) override;

private:
  static BlockWidget *makeBlock(const QString &name);
};

#endif
