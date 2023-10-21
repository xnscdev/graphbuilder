#include "blockparams.h"
#include "fileparser.h"

QString BlockParams::readValue(const QString &param) const {
  const QStringList &list = value(param);
  if (list.isEmpty())
    throw FileParserException(
        QString("Expected a value for parameter '%1'").arg(param));
  return list[0];
}

void BlockParams::getString(
    const QString &param,
    const std::function<void(const QString &)> &setter) const {
  if (!contains(param))
    return;
  QString str = readValue(param);
  setter(str);
}

void BlockParams::getInt(const QString &param,
                         const std::function<void(int)> &setter) const {
  if (!contains(param))
    return;
  QString str = readValue(param);
  bool ok;
  int paramValue = str.toInt(&ok);
  if (!ok)
    throw FileParserException(
        QString("Value for parameter '%1' must be an integer, got '%2'")
            .arg(param, str[0]));
  setter(paramValue);
}
