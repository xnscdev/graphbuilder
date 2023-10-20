#include "mainwindow.h"
#include "block/blockwidget.h"
#include "ui_mainwindow.h"

#include <QCompleter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto *completer = new QCompleter(BlockWidget::blockNames, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->blockEdit->setCompleter(completer);
  connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
          this, &MainWindow::addBlock);
  connect(ui->blockEdit, &QLineEdit::returnPressed, this,
          &MainWindow::addBlock);
  connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
          ui->blockEdit, &QLineEdit::clear, Qt::QueuedConnection);
  connect(ui->commandList, &CommandList::updated, this, &MainWindow::rebuild);
  connect(ui->graphView, &GraphView::statusUpdated, this,
          &MainWindow::updateStatus);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::rebuild() {
  ui->graphView->rebuild(ui->commandList->getBlocks());
}

void MainWindow::updateStatus(const QString &msg) {
  ui->statusBar->showMessage(msg, 3000);
}

void MainWindow::addBlock() {
  QString name = ui->blockEdit->text();
  if (!BlockWidget::blockNames.contains(name))
    return;
  ui->commandList->addBlock(name);
  ui->blockEdit->clear();
}
