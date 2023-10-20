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
      m_selectedFont = QFontDialog::getFont(
          &ok, fontLabel->font(), nullptr, "Select Font",
          QFontDialog::FontDialogOption::DontUseNativeDialog);
      if (ok) {
        updateLabel();
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

  void setSelectedFont(const QFont &font) {
    m_selectedFont = font;
    updateLabel();
  }

signals:
  void updated();

private:
  void updateLabel() {
    fontLabel->setText(QString("%1 %2 %3")
                           .arg(m_selectedFont.family(),
                                m_selectedFont.styleName(),
                                QString::number(m_selectedFont.pointSize())));
  }

  QLabel *fontLabel;
  QFont m_selectedFont;
};

#endif
