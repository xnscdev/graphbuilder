#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include "buildcontext.h"

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

class BlockWidget : public QFrame {
  Q_OBJECT

public:
  BlockWidget(const QString &name, const QColor &color,
              QWidget *parent = nullptr);
  virtual ~BlockWidget() = default;
  [[nodiscard]] virtual QString getCode() const = 0;
  virtual void paint(BuildContext &context) const = 0;

  static const QStringList blockNames;

signals:
  void updated();

protected:
  static QString encodeString(const QString &str) {
    if (str.contains(' '))
      return QString("\"%1\"").arg(str);
    return str;
  }

  QGridLayout *layout;

private:
  QString name;
};

namespace BlockColors {
const QColor graphSetup(79, 89, 232, 100);
const QColor graphTemplate(0, 255, 0, 100);
} // namespace BlockColors

#endif
