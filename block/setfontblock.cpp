#include "setfontblock.h"

SetFontBlock::SetFontBlock(QWidget *parent)
    : BlockWidget("SetFont", BlockColors::graphSetup, parent) {
}

QString SetFontBlock::getCode() {
  return "SetFont";
}
