#include "createfilewindowui.h"
#include "FE.h"
#include <QLineEdit>
#include <QPushButton>
CreateFileWindowUi::CreateFileWindowUi(FerrumUi* ferrum_ui, QDialog *parent)
    : QDialog{parent}, m_ferrum_ui(ferrum_ui),
     m_text_line(new QLineEdit(this))
{
    setWindowTitle("Создать файл");
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(260, 75);
    auto gbox = new QGridLayout();
    gbox->setSpacing(10);
    gbox->setColumnStretch(0, 0);
    auto CreateButton = new QPushButton(this);
    auto CancelButton = new QPushButton(this);
    auto ButtonSize = new QSize(100, 25);
    CreateButton->setFixedSize(*ButtonSize);
    CancelButton->setFixedSize(*ButtonSize);
    CreateButton->setText("Создать");
    CancelButton->setText("Отмена");
    gbox->addWidget(m_text_line, 0, 0, 1, 2);
    gbox->addWidget(CancelButton, 1, 0);
    gbox->addWidget(CreateButton, 1, 1);
    setLayout(gbox);
    connect(CreateButton, &QPushButton::clicked, this, &CreateFileWindowUi::onButtonClicked);
    connect(CancelButton, &QPushButton::clicked, this, &QDialog::close);
}
auto CreateFileWindowUi::onButtonClicked() -> void {
    m_ferrum_ui->CreateFileFE(m_text_line->text());
    close();
}
