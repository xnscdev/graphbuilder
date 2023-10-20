#ifndef BLOCKPARAMS_H
#define BLOCKPARAMS_H

#include <QMap>
#include <QStringList>

class BlockParams : public QMap<QString, QStringList> {
public:
  void getString(const QString &param,
                 const std::function<void(const QString &)> &setter) const;
  void getInt(const QString &param,
              const std::function<void(int)> &setter) const;

private:
  [[nodiscard]] QString readValue(const QString &param) const;
};

#endif
