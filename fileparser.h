#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "block/blockwidget.h"

#include <QQueue>
#include <QString>

class FileParserException : public std::exception {
public:
  explicit FileParserException(QString msg) : msg(std::move(msg)) {}
  [[nodiscard]] QString getMessage() const { return msg; }

private:
  QString msg;
};

class FileParser {
public:
  explicit FileParser(const QString &str);
  [[nodiscard]] bool hasNext() const { return !lines.isEmpty(); }
  QPair<BlockWidget *, BlockParams> parseNext();
  static QString encodeString(const QString &str);
  static BlockWidget *makeBlock(const QString &name);

private:
  void beginParse();
  QString decodeString();

  QQueue<QString> lines;
  QString str;
  int pos = 0;
};

#endif
