#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

class BlockWidget : public QFrame {
  Q_OBJECT

public:
  BlockWidget(const QString &name, const QColor &color, QWidget *parent = nullptr);
  virtual ~BlockWidget() = default;
  virtual QString getCode() = 0;

  static const QStringList blockNames;

signals:
  void updated();

protected:
  QGridLayout *layout;

private:
  QString name;
};

namespace BlockColors {
const QColor graphSetup(79, 89, 232, 100);
const QColor graphTemplate(0, 255, 0, 100);
}

#endif
