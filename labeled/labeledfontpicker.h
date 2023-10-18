#ifndef LABELEDFONTPICKER_H
#define LABELEDFONTPICKER_H

#include "labeledwidget.h"

#include <QFontDialog>
#include <QPushButton>

class LabeledFontPicker : public LabeledWidget {
  Q_OBJECT

public:
  explicit LabeledFontPicker(const QString &label, QWidget *parent = nullptr)
      : LabeledWidget(label, parent) {
    auto *button = new QPushButton("Choose");
    connect(button, &QPushButton::clicked, [&]() {
      bool ok;
      m_selectedFont =
          QFontDialog::getFont(&ok, fontLabel->font(), nullptr, "Select Font");
      if (ok) {
        fontLabel->setFont(m_selectedFont);
        fontLabel->setText(m_selectedFont.family());
        emit updated();
      }
    });
    layout->addWidget(button);
    fontLabel = new TranslucentLabel("None selected");
    fontLabel->setSizePolicy(QSizePolicy::Policy::Expanding,
                             QSizePolicy::Policy::Ignored);
    layout->addWidget(fontLabel);
  }

  [[nodiscard]] QFont selectedFont() const { return m_selectedFont; }

signals:
  void updated();

private:
  QLabel *fontLabel;
  QFont m_selectedFont;
};

#endif
