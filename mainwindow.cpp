#include "mainwindow.h"
#include "block/blockwidget.h"
#include "fileparser.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Use a completer with block names and add a block when the completer runs
  auto *completer = new QCompleter(BlockWidget::blockNames, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->blockEdit->setCompleter(completer);
  connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
          this, &MainWindow::addBlock);
  connect(ui->blockEdit, &QLineEdit::returnPressed, this,
          &MainWindow::addBlock);
  connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
          ui->blockEdit, &QLineEdit::clear, Qt::QueuedConnection);

  // Rebuild the graph when the command list changes
  connect(ui->commandList, &CommandList::updated, this, &MainWindow::rebuild);

  // Update the status bar with the error message when the graph has errors
  connect(ui->graphView, &GraphView::statusUpdated, this,
          &MainWindow::updateStatus);

  // Connect menu actions
  connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::doOpen);
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::doSave);
  connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::doSaveAs);
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

void MainWindow::doOpen() {
  QFileDialog::getOpenFileContent(
      tr("GraphBuilder Graphs (*.txt *.dat)"),
      [&](const QString &name, const QByteArray &content) {
        QString str(content);
        FileParser parser(str);
        try {
          ui->commandList->clear();
          while (parser.hasNext()) {
            auto pair = parser.parseNext();
            ui->commandList->addBlock(pair.first, pair.second);
          }
          openFile = name;
          rebuild();
        } catch (FileParserException &ex) {
          ui->statusBar->showMessage(
              QString("Error loading file: %1").arg(ex.getMessage()));
        }
      });
}

void MainWindow::doSave() {
  if (openFile.isEmpty()) {
    doSaveAs();
    return;
  }
  saveFile(openFile);
}

void MainWindow::doSaveAs() {
  QString name =
      QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                   tr("GraphBuilder Graphs (*.txt *.dat)"));
  if (!name.isEmpty())
    saveFile(name);
}

void MainWindow::addBlock() {
  QString name = ui->blockEdit->text();
  if (!BlockWidget::blockNames.contains(name))
    return;
  ui->commandList->addBlock(name);
  ui->blockEdit->clear();
}

void MainWindow::saveFile(const QString &path) {
  QFile file(path);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream stream(&file);
    for (auto *block : ui->commandList->getBlocks())
      stream << block->getCode() << '\n';
    file.close();
    ui->statusBar->showMessage(QString("Saved graph code to %1").arg(path),
                               3000);
  } else {
    ui->statusBar->showMessage(
        QString("Error saving file: %1").arg(file.errorString()), 3000);
  }
}
