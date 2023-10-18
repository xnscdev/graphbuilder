#ifndef SETFONTBLOCK_H
#define SETFONTBLOCK_H

#include "blockwidget.h"

class SetFontBlock : public BlockWidget {
  Q_OBJECT

public:
  explicit SetFontBlock(QWidget *parent = nullptr);
  QString getCode() override;
};

#endif
