#include <QApplication>
#include "renamedialogui.h"
#include "FE.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSize>
#include <QFileInfo>
#include <QDebug>
RenameDialogUi::RenameDialogUi(FerrumUi* ferrum_ui, QDialog *parent)
    : QDialog{parent}, m_ferrum_ui(ferrum_ui), m_text_line(new QLineEdit(this))
{
    setWindowTitle("Переименовать");
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(260, 75);
    auto gbox = new QGridLayout();
    gbox->setSpacing(10);
    gbox->setColumnStretch(0, 0);
    auto RenameButton = new QPushButton(this);
    auto CancelButton = new QPushButton(this);
    auto ButtonSize = new QSize(100, 25);
    RenameButton->setFixedSize(*ButtonSize);
    CancelButton->setFixedSize(*ButtonSize);
    RenameButton->setText("Переименовать");
    CancelButton->setText("Закрыть");
    gbox->addWidget(m_text_line, 0, 0, 1, 2);
    gbox->addWidget(CancelButton, 1, 0);
    gbox->addWidget(RenameButton, 1, 1);
    setLayout(gbox);
    connect(RenameButton, &QPushButton::clicked, this, &RenameDialogUi::onButtonClicked);
    connect(CancelButton, &QPushButton::clicked, this, &QDialog::close);
}

auto RenameDialogUi::onButtonClicked() -> void
{
    m_ferrum_ui->Rename(m_text_line->text());
    close();
}
