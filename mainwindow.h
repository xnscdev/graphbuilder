#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private slots:
  void rebuild();
  void updateStatus(const QString &msg);
  void doOpen();
  void doSave();
  void doSaveAs();

private:
  void addBlock();
  void saveFile(const QString &path);

  Ui::MainWindow *ui;
  QString openFile;
};

#endif
