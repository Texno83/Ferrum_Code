#include "preferencesdialog.h"
#include "FE.h"
#include <QApplication>
#include <QTabWidget>
#include <QWidget>
#include <QGridLayout>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QIcon>
#include <QSize>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
PreferencesDialog::PreferencesDialog(FerrumUi* ferrum_ui, QDialog *parent) :
QDialog{parent}, m_ferrum_ui(ferrum_ui), ViewBox(new QListView)
{
    setWindowTitle("Настройки");
    auto CloseButton = new QPushButton(this);
    auto MainGbox = new QGridLayout(this);
    auto TabWidget = new QTabWidget(this);
    auto wgd1 = new QWidget(this);
    auto gbox1 = new QGridLayout(this);
    auto HidCheck = new QCheckBox(this);
    auto ViewLab = new QLabel(this);
    auto ViewFrame = new QGroupBox(this);
    auto ViewLayout = new QGridLayout(this);
    auto IconModeButton = new QRadioButton(this);
    auto ListModeButton = new QRadioButton(this);
    auto StatusLab = new QLabel(this);
    auto StatusFrame = new QGroupBox(this);
    auto StatusLayout = new QGridLayout(this);
    auto HideStatusButton = new QRadioButton(this);
    auto ShowStatusButton = new QRadioButton(this);

    auto gbox2 = new QGridLayout(this);
    auto wgd2 = new QWidget(this);
    auto SortLab = new QLabel(this);
    auto SortFrame = new QGroupBox(this);
    auto SortLayout = new QGridLayout(this);
    auto NameSortButton = new QRadioButton(this);
    auto TypeSortButton = new QRadioButton(this);
    auto DateSortButton = new QRadioButton(this);
    auto SizeSortButton = new QRadioButton(this);
    auto ReverseLab = new QLabel(this);
    auto ReverseFrame = new QGroupBox(this);
    auto ReverseLayout = new QGridLayout(this);
    auto ReverseOnButton = new QRadioButton(this);
    auto ReverseOffButton = new QRadioButton(this);

    CloseButton->setText("Закрыть");
    ViewLab->setText("Отображение");
    IconModeButton->setText("Иконки");
    ListModeButton->setText("Список");
    ListModeButton->setChecked(true);
    StatusLab->setText("Статус");
    HideStatusButton->setText("Скрыть");
    ShowStatusButton->setText("Показать");
    ShowStatusButton->setChecked(true);
    HidCheck->setChecked(true);
    HidCheck->setText("Показывать скрытые файлы");
    ViewBox->setFixedWidth(262);
    ViewBox->setFixedHeight(50);
    ViewBox->setSpacing(0);
    ViewBox->setUniformItemSizes(true);
    ViewBox->setViewMode(QListView::IconMode);
    ViewBox->setMovement(QListView::Snap);
    ViewBox->setFlow(QListView::LeftToRight);
    SortLab->setText("Тип сортировки");
    ReverseLab->setText("Реверсивная сортировка");
    NameSortButton->setChecked(true);
    NameSortButton->setText("Имя");
    TypeSortButton->setText("Тип");
    SizeSortButton->setText("Размер");
    DateSortButton->setText("Дата изменения");
    ReverseOnButton->setText("Включить");
    ReverseOffButton->setChecked(true);
    ReverseOffButton->setText("Выключить");
    auto ViewModel = new QStandardItemModel();
    ViewBox->setModel(ViewModel);
    auto item1 = new QStandardItem(QIcon("OneFieldMode.svg"), "1");
    item1->setSizeHint(QSize(60, 45));
    auto item2 = new QStandardItem(QIcon("TwoFieldMode.svg"), "2");
    item2->setSizeHint(QSize(60, 45));
    auto item3 = new QStandardItem(QIcon("ThreeFieldMode.svg"), "3");
    item3->setSizeHint(QSize(60, 45));
    auto item4 = new QStandardItem(QIcon("FourFieldMode.svg"), "4");
    item4->setSizeHint(QSize(60, 45));
    ViewModel->appendRow(item1);
    ViewModel->appendRow(item2);
    ViewModel->appendRow(item3);
    ViewModel->appendRow(item4);
    ViewModel->setSortRole(1);
    ViewBox->setResizeMode(QListView::Adjust);
    ViewBox->setContextMenuPolicy(Qt::CustomContextMenu);
    ViewLayout->addWidget(IconModeButton);
    ViewLayout->addWidget(ListModeButton);
    ViewFrame->setLayout(ViewLayout);
    StatusLayout->addWidget(ShowStatusButton);
    StatusLayout->addWidget(HideStatusButton);
    StatusFrame->setLayout(StatusLayout);
    SortLayout->addWidget(NameSortButton);
    SortLayout->addWidget(TypeSortButton);
    SortLayout->addWidget(SizeSortButton);
    SortLayout->addWidget(DateSortButton);
    SortFrame->setLayout(SortLayout);
    ReverseLayout->addWidget(ReverseOnButton);
    ReverseLayout->addWidget(ReverseOffButton);
    ReverseFrame->setLayout(ReverseLayout);
    gbox1->addWidget(ViewBox);
    gbox1->addWidget(HidCheck);
    gbox1->addWidget(ViewLab);
    gbox1->addWidget(ViewFrame);
    gbox1->addWidget(StatusLab);
    gbox1->addWidget(StatusFrame);
    gbox2->addWidget(SortLab);
    gbox2->addWidget(SortFrame);
    gbox2->addWidget(ReverseLab);
    gbox2->addWidget(ReverseFrame);
    wgd1->setLayout(gbox1);
    wgd2->setLayout(gbox2);
    TabWidget->addTab(wgd1, "Внешний вид");
    TabWidget->addTab(wgd2, "Сортировка");
    MainGbox->addWidget(TabWidget);
    MainGbox->addWidget(CloseButton, 1, 0, Qt::AlignCenter);
    setLayout(MainGbox);
    connect(CloseButton, &QPushButton::clicked, this, &PreferencesDialog::Close);
    connect(ViewBox, &QListView::clicked, this, &PreferencesDialog::ItemClicked);
    connect(HidCheck, &QCheckBox::isChecked, this, &PreferencesDialog::HiddenChecked);
    connect(IconModeButton, &QRadioButton::clicked, this, &PreferencesDialog::SetIconMode);
    connect(ListModeButton, &QRadioButton::clicked, this, &PreferencesDialog::SetListMode);
    connect(ShowStatusButton, &QRadioButton::clicked, this, &PreferencesDialog::ShowStatus);
    connect(HideStatusButton, &QRadioButton::clicked, this, &PreferencesDialog::HideStatus);
    connect(NameSortButton,  &QRadioButton::clicked, this, &PreferencesDialog::SortByName);
    connect(TypeSortButton,  &QRadioButton::clicked, this, &PreferencesDialog::SortByType);
    connect(SizeSortButton,  &QRadioButton::clicked, this, &PreferencesDialog::SortBySize);
    connect(DateSortButton,  &QRadioButton::clicked, this, &PreferencesDialog::SortByDate);
    connect(ReverseOnButton, &QRadioButton::clicked, this, &PreferencesDialog::SortEnableReverse);
    connect(ReverseOffButton, &QRadioButton::clicked, this, &PreferencesDialog::SortDisableReverse);
}
void PreferencesDialog::ItemClicked() {
    m_ferrum_ui->GetNumberOfFields(ViewBox->selectionModel()
        ->selectedIndexes()[0].data(Qt::DisplayRole).toInt());
    m_ferrum_ui->GenerateDesign();
}
void PreferencesDialog::HiddenChecked() { m_ferrum_ui->GetFromHidBox(!m_ferrum_ui->SendToHidBox()); }
void PreferencesDialog::SetIconMode() { m_ferrum_ui->SetIconView(); }
void PreferencesDialog::SetListMode() { m_ferrum_ui->SetListView(); }
void PreferencesDialog::Close() { close(); }
void PreferencesDialog::ShowStatus() { m_ferrum_ui->ShowStatusBar(); }
void PreferencesDialog::HideStatus() { m_ferrum_ui->HideStatusBar(); }
void PreferencesDialog::SortByName() { m_ferrum_ui->SortByName(); }
void PreferencesDialog::SortByType() { m_ferrum_ui->SortByType(); }
void PreferencesDialog::SortBySize() { m_ferrum_ui->SortBySize(); }
void PreferencesDialog::SortByDate() { m_ferrum_ui->SortByDate(); }
void PreferencesDialog::SortEnableReverse() { m_ferrum_ui->SortEnableReverse(); }
void PreferencesDialog::SortDisableReverse() { m_ferrum_ui->SortDisableReverse(); }
