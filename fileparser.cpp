#include "fileparser.h"
#include "block/favscaleblock.h"
#include "block/setfontblock.h"
#include "blockparams.h"

FileParser::FileParser(const QString &str) {
  for (auto &line : str.split('\n')) {
    if (!line.simplified().isEmpty())
      lines.enqueue(line);
  }
}

QPair<BlockWidget *, BlockParams> FileParser::parseNext() {
  beginParse();
  while (pos < str.length() && !str[pos].isSpace())
    pos++;
  QString name = str.left(pos);
  BlockParams params;
  while (true) {
    while (pos < str.length() && str[pos].isSpace())
      pos++;
    if (pos >= str.length())
      break;
    int paramStart = pos;
    while (pos < str.length() && str[pos] != '=')
      pos++;
    if (pos >= str.length())
      throw FileParserException("Unexpected end of file reached");
    QString paramName = str.mid(paramStart, pos - paramStart);
    pos++;
    QStringList paramValues;
    if (pos < str.length() && !str[pos].isSpace()) {
      paramValues.append(decodeString());
      while (pos < str.length() && str[pos] == ',') {
        pos++;
        paramValues.append(decodeString());
      }
      if (pos < str.length() && !str[pos].isSpace())
        throw FileParserException("Invalid parameter value");
    }
    params[paramName] = paramValues;
  }
  BlockWidget *block = makeBlock(name);
  return {block, params};
}

QString FileParser::encodeString(const QString &str) {
  QString result;
  bool needsQuoted = false;
  for (QChar c : str) {
    switch (c.toLatin1()) {
    case '\'':
      result += "\\'";
      break;
    case '"':
      result += "\\\"";
      break;
    case '\\':
      result += "\\\\";
      break;
    case '\b':
      result += "\\b";
      break;
    case '\f':
      result += "\\f";
      break;
    case '\n':
      result += "\\n";
      break;
    case '\r':
      result += "\\r";
      break;
    case '\t':
      result += "\\t";
      break;
    case '\v':
      result += "\\v";
      break;
    case ',':
    case ' ':
      needsQuoted = true;
    default:
      result += c;
    }
  }

  if (needsQuoted)
    result = QString("\"%1\"").arg(result);
  return result;
}

BlockWidget *FileParser::makeBlock(const QString &name) {
  if (name == "SetFont")
    return new SetFontBlock;
  if (name == "FavScale")
    return new FavScaleBlock;
  return nullptr;
}

void FileParser::beginParse() {
  str = lines.dequeue();
  pos = 0;
}

QString FileParser::decodeString() {
  QString result;
  bool quoted = false;
  while (quoted || (pos < str.length() && str[pos] != ',' && str[pos] != ' ')) {
    if (str[pos] == '"') {
      quoted = !quoted;
    } else if (str[pos] == '\\') {
      switch (str[++pos].toLatin1()) {
      case 'b':
        result += '\b';
        break;
      case 'f':
        result += '\f';
        break;
      case 'n':
        result += '\n';
        break;
      case 'r':
        result += '\r';
        break;
      case 't':
        result += '\t';
        break;
      case 'v':
        result += '\v';
        break;
      default:
        result += str[pos];
      }
    } else {
      result += str[pos];
    }
    pos++;
  }
  return result;
}
