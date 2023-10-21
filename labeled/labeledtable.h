#ifndef LABELEDTABLE_H
#define LABELEDTABLE_H

#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>

using RowCallback = std::function<void(QTableWidget *, QStringList *)>;

class LabeledTable : public QWidget {
  Q_OBJECT

public:
  LabeledTable(const QStringList &labels, int columns, RowCallback addRow,
               QWidget *parent = nullptr)
      : QWidget(parent), addRow(std::move(addRow)) {
    layout = new QGridLayout(this);
    layout->setHorizontalSpacing(4);
    layout->setVerticalSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_table = new QTableWidget(0, columns);
    m_table->setAttribute(Qt::WA_TranslucentBackground);
    m_table->setHorizontalHeaderLabels(labels);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setFixedHeight(205);
    this->addRow(m_table, nullptr);
    connect(m_table, &QTableWidget::cellChanged, this, &LabeledTable::updated);
    layout->addWidget(m_table, 0, 0, 1, -1);

    auto *addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked,
            [&]() { this->addRow(m_table, nullptr); });
    layout->addWidget(addButton, 1, 0);

    auto *deleteButton = new QPushButton("Delete");
    connect(deleteButton, &QPushButton::clicked, [&]() {
      QModelIndexList selectedIndexes =
          m_table->selectionModel()->selectedIndexes();
      QList<int> selectedRows;
      std::transform(selectedIndexes.constBegin(), selectedIndexes.constEnd(),
                     std::back_inserter(selectedRows),
                     [](const QModelIndex &index) { return index.row(); });
      std::sort(selectedRows.begin(), selectedRows.end(), std::greater<>());
      for (int row : selectedRows)
        m_table->removeRow(row);
      emit updated();
    });
    layout->addWidget(deleteButton, 1, 1);

    auto *clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, [&]() {
      m_table->setRowCount(0);
      emit updated();
    });
    layout->addWidget(clearButton, 1, 2);
  }

  [[nodiscard]] QTableWidget *table() const { return m_table; }

  void setRows(const QList<QStringList> &params) {
    int firstLength = static_cast<int>(params.first().size());
    for (auto &list : params) {
      if (list.size() != firstLength)
        return;
    }

    m_table->setRowCount(0);
    for (int i = 0; i < firstLength; i++) {
      QStringList p;
      for (auto &list : params)
        p.append(list[i]);
      addRow(m_table, &p);
    }
  }

signals:
  void updated();

private:
  QGridLayout *layout;
  QTableWidget *m_table;
  RowCallback addRow;
};

#endif
