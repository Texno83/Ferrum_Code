#include "FE.h"
#include "qlabel.h"
#include "renamedialogui.h"
#include "infowindowui.h"
#include "createfolderwindowui.h"
#include "createfilewindowui.h"
#include "preferencesdialog.h"
#include <QApplication>
#include <QListWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>
#include <QDir>
#include <QFileIconProvider>
#include <QListView>
#include <QStandardItem>
#include <QListView>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>
#include <QClipboard>
#include <QMimeData>
#include <QMimeType>
#include <QUrl>
#include <QThread>
#include <QDesktopServices>
#include <QToolBar>
#include <QTextEdit>
#include <QFile>
#include <QModelIndex>
#include <QScrollBar>
#include <QHeaderView>
#include <QStringLiteral>
#include <QMessageBox>
#include <QCursor>
#include <QThread>
#include <QProgressDialog>
#include <QTimer>
#include <QComboBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QShortcut>
#include <QKeySequence>
FerrumUi::FerrumUi(QWidget *parent)
    : QMainWindow(parent), gbox(new QGridLayout()), FileBox(new QListView()),
    FileBox2(new QListView()), FileBox3(new QListView()), FileBox4(new QListView()),
    TreeFileBox(new QFileSystemModel()), TreeFolderBox(new QTreeView()), TreeFolderBox2(new QTreeView()),
    TreeFolderBox3(new QTreeView()), TreeFolderBox4(new QTreeView()), PathDisplay(new QTextEdit()),
    wdg(new QWidget()), wdg2(new QWidget()), wdg3(new QWidget()), wdg4(new QWidget()),
    StatusBar(new QStatusBar()), FilesCount(new QLabel()), DirsCount(new QLabel()), SelectedItem(new QLabel()),
    ItemSize(new QLabel())
{
    setWindowTitle("Ferrum");
    setWindowIcon(QIcon("FE.ico"));
    adjustSize();
    resize(800, 600);
    StatusBar->setFixedHeight(20);
    StatusBar->addWidget(FilesCount);
    StatusBar->addWidget(DirsCount);
    StatusBar->addWidget(SelectedItem);
    StatusBar->addWidget(ItemSize);
    setStatusBar(StatusBar);
    FileBoxItemSize = QSize(24, 24);
    FileBoxItemSize2 = QSize(24, 24);
    FileBoxItemSize3 = QSize(24, 24);
    FileBoxItemSize4 = QSize(24, 24);
    SetupTreeView(TreeFolderBox);
    SetupTreeView(TreeFolderBox2);
    SetupTreeView(TreeFolderBox3);
    SetupTreeView(TreeFolderBox4);
    TreeFileBox->setRootPath("C:/");
    FileBox = SetupFileBox();
    FileBox2 = SetupFileBox();
    FileBox3 = SetupFileBox();
    FileBox4 = SetupFileBox();
    PathDisplay->setText(path);
    PathDisplay->setFixedHeight(26);
    auto GoLeftAction = new QAction(this);
    auto GoRightAction = new QAction(this);
    auto GoUpAction = new QAction(this);
    auto UpdateAction = new QAction(this);
    auto ParamsMenuAction = new QAction(this);
    auto ParamsAction = new QAction(this);
    GoUpAction->setIcon(QIcon("GoUp.svg"));
    GoRightAction->setIcon(QIcon("GoRight.svg"));
    GoLeftAction->setIcon(QIcon("GoLeft.svg"));
    UpdateAction->setIcon(QIcon("Update.svg"));
    ParamsMenuAction->setIcon(QIcon("Menu.svg"));
    ParamsAction->setIcon(QIcon("PreferencesMenu.svg"));
    auto ToolBar = new QToolBar(this);
    gbox->setMenuBar(ToolBar);
    ToolBar->addAction(GoLeftAction);
    ToolBar->addAction(GoRightAction);
    ToolBar->addAction(GoUpAction);
    ToolBar->addWidget(PathDisplay);
    ToolBar->addAction(UpdateAction);
    ToolBar->addSeparator();
    ToolBar->addAction(ParamsMenuAction);
    ToolBar->addAction(ParamsAction);
    gbox->addWidget(TreeFolderBox,  0, 0);
    gbox->addWidget(FileBox,  0, 1);
    wdg->setLayout(gbox);
    setCentralWidget(wdg);
    setContextMenuPolicy(Qt::CustomContextMenu);
    PathDisplay->setContextMenuPolicy(Qt::CustomContextMenu);




    connect(TreeFolderBox, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(TreeFolderBox, &QTreeView::doubleClicked, this, &FerrumUi::TreePickOne);
    connect(FileBox, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(FileBox, &QListView::doubleClicked, this, &FerrumUi::TreePickOne);
    connect(FileBox, &QListView::clicked, this, &FerrumUi::PickOne);
    connect(TreeFolderBox, &QTreeView::clicked, this, &FerrumUi::PickOne);
    auto OpenShortCut = new QShortcut(QKeySequence::Open, FileBox);
    auto CopyShortCut = new QShortcut(QKeySequence::Copy, FileBox);
    auto CutShortCut = new QShortcut(QKeySequence::Cut, FileBox);
    auto PasteShortCut = new QShortcut(QKeySequence::Paste, FileBox);
    auto RemoveShortCut = new QShortcut(QKeySequence::Delete, FileBox);
    auto RenameShortCut = new QShortcut(QKeySequence::Replace, FileBox);
    auto InfoShortCut = new QShortcut(QKeySequence::Print, FileBox);
    auto TreeOpenShortCut = new QShortcut(QKeySequence::Open, TreeFolderBox);
    auto TreeCopyShortCut = new QShortcut(QKeySequence::Copy, TreeFolderBox);
    auto TreeCutShortCut = new QShortcut(QKeySequence::Cut, TreeFolderBox);
    auto TreePasteShortCut = new QShortcut(QKeySequence::Paste, TreeFolderBox);
    auto TreeRemoveShortCut = new QShortcut(QKeySequence::Delete, TreeFolderBox);
    auto TreeRenameShortCut = new QShortcut(QKeySequence::Replace, TreeFolderBox);
    auto TreeInfoShortCut = new QShortcut(QKeySequence::Print, TreeFolderBox);
    connect(OpenShortCut, &QShortcut::activated, this, &FerrumUi::Open);
    connect(CopyShortCut, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(CutShortCut, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(PasteShortCut, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(RemoveShortCut, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(RenameShortCut, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(InfoShortCut, &QShortcut::activated, this, &FerrumUi::Info);
    connect(TreeOpenShortCut, &QShortcut::activated, this, &FerrumUi::Open);
    connect(TreeCopyShortCut, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(TreeCutShortCut, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(TreePasteShortCut, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(TreeRemoveShortCut, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(TreeRenameShortCut, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(TreeInfoShortCut, &QShortcut::activated, this, &FerrumUi::Info);

    TreeFolderBox2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(TreeFolderBox2, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(TreeFolderBox2, &QTreeView::doubleClicked, this, &FerrumUi::TreePickTwo);
    connect(FileBox2, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(FileBox2, &QListView::doubleClicked, this, &FerrumUi::TreePickTwo);
    connect(FileBox2, &QListView::clicked, this, &FerrumUi::PickTwo);
    connect(TreeFolderBox2, &QTreeView::clicked, this, &FerrumUi::PickTwo);
    auto OpenShortCut2 = new QShortcut(QKeySequence::Open, FileBox2);
    auto CopyShortCut2 = new QShortcut(QKeySequence::Copy, FileBox2);
    auto CutShortCut2 = new QShortcut(QKeySequence::Cut, FileBox2);
    auto PasteShortCut2 = new QShortcut(QKeySequence::Paste, FileBox2);
    auto RemoveShortCut2 = new QShortcut(QKeySequence::Delete, FileBox2);
    auto RenameShortCut2 = new QShortcut(QKeySequence::Replace, FileBox2);
    auto InfoShortCut2 = new QShortcut(QKeySequence::Print, FileBox2);
    auto TreeOpenShortCut2 = new QShortcut(QKeySequence::Open, TreeFolderBox2);
    auto TreeCopyShortCut2 = new QShortcut(QKeySequence::Copy, TreeFolderBox2);
    auto TreeCutShortCut2 = new QShortcut(QKeySequence::Cut, TreeFolderBox2);
    auto TreePasteShortCut2 = new QShortcut(QKeySequence::Paste, TreeFolderBox2);
    auto TreeRemoveShortCut2 = new QShortcut(QKeySequence::Delete, TreeFolderBox2);
    auto TreeRenameShortCut2 = new QShortcut(QKeySequence::Replace, TreeFolderBox2);
    auto TreeInfoShortCut2 = new QShortcut(QKeySequence::Print, TreeFolderBox2);
    connect(OpenShortCut2, &QShortcut::activated, this, &FerrumUi::Open);
    connect(CopyShortCut2, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(CutShortCut2, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(PasteShortCut2, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(RemoveShortCut2, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(RenameShortCut2, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(InfoShortCut2, &QShortcut::activated, this, &FerrumUi::Info);
    connect(TreeOpenShortCut2, &QShortcut::activated, this, &FerrumUi::Open);
    connect(TreeCopyShortCut2, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(TreeCutShortCut2, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(TreePasteShortCut2, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(TreeRemoveShortCut2, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(TreeRenameShortCut2, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(TreeInfoShortCut2, &QShortcut::activated, this, &FerrumUi::Info);

    TreeFolderBox3->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(TreeFolderBox3, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(TreeFolderBox3, &QTreeView::doubleClicked, this, &FerrumUi::TreePickThree);
    connect(FileBox3, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(FileBox3, &QListView::doubleClicked, this, &FerrumUi::TreePickThree);
    connect(FileBox3, &QListView::clicked, this, &FerrumUi::PickThree);
    connect(TreeFolderBox3, &QTreeView::clicked, this, &FerrumUi::PickThree);
    auto OpenShortCut3 = new QShortcut(QKeySequence::Open, FileBox3);
    auto CopyShortCut3 = new QShortcut(QKeySequence::Copy, FileBox3);
    auto CutShortCut3 = new QShortcut(QKeySequence::Cut, FileBox3);
    auto PasteShortCut3 = new QShortcut(QKeySequence::Paste, FileBox3);
    auto RemoveShortCut3 = new QShortcut(QKeySequence::Delete, FileBox3);
    auto RenameShortCut3 = new QShortcut(QKeySequence::Replace, FileBox3);
    auto InfoShortCut3 = new QShortcut(QKeySequence::Print, FileBox3);
    auto TreeOpenShortCut3 = new QShortcut(QKeySequence::Open, TreeFolderBox3);
    auto TreeCopyShortCut3 = new QShortcut(QKeySequence::Copy, TreeFolderBox3);
    auto TreeCutShortCut3 = new QShortcut(QKeySequence::Cut, TreeFolderBox3);
    auto TreePasteShortCut3 = new QShortcut(QKeySequence::Paste, TreeFolderBox3);
    auto TreeRemoveShortCut3 = new QShortcut(QKeySequence::Delete, TreeFolderBox3);
    auto TreeRenameShortCut3 = new QShortcut(QKeySequence::Replace, TreeFolderBox3);
    auto TreeInfoShortCut3 = new QShortcut(QKeySequence::Print, TreeFolderBox3);
    connect(OpenShortCut3, &QShortcut::activated, this, &FerrumUi::Open);
    connect(CopyShortCut3, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(CutShortCut3, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(PasteShortCut3, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(RemoveShortCut3, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(RenameShortCut3, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(InfoShortCut3, &QShortcut::activated, this, &FerrumUi::Info);
    connect(TreeOpenShortCut3, &QShortcut::activated, this, &FerrumUi::Open);
    connect(TreeCopyShortCut3, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(TreeCutShortCut3, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(TreePasteShortCut3, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(TreeRemoveShortCut3, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(TreeRenameShortCut3, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(TreeInfoShortCut3, &QShortcut::activated, this, &FerrumUi::Info);

    TreeFolderBox4->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(TreeFolderBox4, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(TreeFolderBox4, &QTreeView::doubleClicked, this, &FerrumUi::TreePickFour);
    connect(FileBox4, &QWidget::customContextMenuRequested,
        this, &FerrumUi::onCustomContextMenuRequested);
    connect(FileBox4, &QListView::doubleClicked, this, &FerrumUi::TreePickFour);
    connect(FileBox4, &QListView::clicked, this, &FerrumUi::PickFour);
    connect(TreeFolderBox4, &QTreeView::clicked, this, &FerrumUi::PickFour);
    auto OpenShortCut4 = new QShortcut(QKeySequence::Open, FileBox4);
    auto CopyShortCut4 = new QShortcut(QKeySequence::Copy, FileBox4);
    auto CutShortCut4 = new QShortcut(QKeySequence::Cut, FileBox4);
    auto PasteShortCut4 = new QShortcut(QKeySequence::Paste, FileBox4);
    auto RemoveShortCut4 = new QShortcut(QKeySequence::Delete, FileBox4);
    auto RenameShortCut4 = new QShortcut(QKeySequence::Replace, FileBox4);
    auto InfoShortCut4 = new QShortcut(QKeySequence::Print, FileBox4);
    auto TreeOpenShortCut4 = new QShortcut(QKeySequence::Open, TreeFolderBox4);
    auto TreeCopyShortCut4 = new QShortcut(QKeySequence::Copy, TreeFolderBox4);
    auto TreeCutShortCut4 = new QShortcut(QKeySequence::Cut, TreeFolderBox4);
    auto TreePasteShortCut4 = new QShortcut(QKeySequence::Paste, TreeFolderBox4);
    auto TreeRemoveShortCut4 = new QShortcut(QKeySequence::Delete, TreeFolderBox4);
    auto TreeRenameShortCut4 = new QShortcut(QKeySequence::Replace, TreeFolderBox4);
    auto TreeInfoShortCut4 = new QShortcut(QKeySequence::Print, TreeFolderBox4);
    connect(OpenShortCut4, &QShortcut::activated, this, &FerrumUi::Open);
    connect(CopyShortCut4, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(CutShortCut4, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(PasteShortCut4, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(RemoveShortCut4, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(RenameShortCut4, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(InfoShortCut4, &QShortcut::activated, this, &FerrumUi::Info);
    connect(TreeOpenShortCut4, &QShortcut::activated, this, &FerrumUi::Open);
    connect(TreeCopyShortCut4, &QShortcut::activated, this, &FerrumUi::Copy);
    connect(TreeCutShortCut4, &QShortcut::activated, this, &FerrumUi::Cut);
    connect(TreePasteShortCut4, &QShortcut::activated, this, &FerrumUi::Paste);
    connect(TreeRemoveShortCut4, &QShortcut::activated, this, &FerrumUi::Remove);
    connect(TreeRenameShortCut4, &QShortcut::activated, this, &FerrumUi::RenameSlot);
    connect(TreeInfoShortCut4, &QShortcut::activated, this, &FerrumUi::Info);

    connect(GoUpAction, &QAction::triggered, this, &FerrumUi::GoUp);
    connect(GoLeftAction, &QAction::triggered, this, &FerrumUi::GoLeft);
    connect(GoRightAction, &QAction::triggered, this, &FerrumUi::GoRight);
    connect(UpdateAction, &QAction::triggered, this, &FerrumUi::Reload);
    connect(ParamsMenuAction, &QAction::triggered, this, &FerrumUi::DirContextMenu);
    connect(ParamsAction, &QAction::triggered, this, &FerrumUi::PreferencesMenu);
    connect(PathDisplay, &QWidget::customContextMenuRequested, this, &FerrumUi::PathDisplayContextMenu);
    History.push_back(path);
    Update();
    StatusBar->clearMessage();
}
FerrumUi::~FerrumUi() {}
void FerrumUi::PathDisplayContextMenu() {
    auto menu = new QMenu();
    QAction* CopyOption = new QAction("Копировать", this);
    QAction* RemoveOption = new QAction("Удалить", this);
    menu->addAction(CopyOption);
    menu->addAction(RemoveOption);
    QAction* SelectedOption = menu->exec(QCursor::pos());
    if (SelectedOption == CopyOption) FerrumUi::CopyAddress();
    else if (SelectedOption == RemoveOption) { PathDisplay->clear(); }
}
void FerrumUi::CopyAddress() { clipboard->setText(PathDisplay->toPlainText(), QClipboard::Clipboard); }
auto FerrumUi::onCustomContextMenuRequested(QPoint const& pos) -> void {
    QModelIndexList indexes = FileBox->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        indexes = TreeFolderBox->selectionModel()->selectedIndexes();      
        if (indexes.size() == 0) {
            if (NumberOfFields == 1) DirContextMenu();
            else {
                indexes = FileBox2->selectionModel()->selectedIndexes();
                if (indexes.size() == 0) {
                    indexes = TreeFolderBox2->selectionModel()->selectedIndexes();
                    if (indexes.size() == 0) {
                        if (NumberOfFields == 2) DirContextMenu();
                        else {
                            indexes = FileBox3->selectionModel()->selectedIndexes();
                            if (indexes.size() == 0) {
                                indexes = TreeFolderBox3->selectionModel()->selectedIndexes();
                                if (indexes.size() == 0) {
                                    if (NumberOfFields == 3) DirContextMenu();
                                    else {
                                        indexes = FileBox4->selectionModel()->selectedIndexes();
                                        if (indexes.size() == 0) {
                                            indexes = TreeFolderBox4->selectionModel()->selectedIndexes();
                                            if (indexes.size() == 0) DirContextMenu();
                                            else { RightMenu(pos); TreeFolderBox4->clearSelection(); }
                                        }
                                        else { RightMenu(pos); FileBox4->clearSelection(); }
                                    }
                                }
                                else { RightMenu(pos); TreeFolderBox3->clearSelection(); }
                            }
                            else { RightMenu(pos); FileBox3->clearSelection(); }
                        }
                    }
                    else { RightMenu(pos); TreeFolderBox2->clearSelection(); }
                }
                else { RightMenu(pos); FileBox2->clearSelection(); }
            }
        }
        else { RightMenu(pos); TreeFolderBox->clearSelection(); }
    }
    else { RightMenu(pos); FileBox->clearSelection(); }
}
void FerrumUi::GetName1() {
    QModelIndexList indexes = FileBox->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        indexes = TreeFolderBox->selectionModel()->selectedIndexes();
        if (indexes.size() == 0) {
            if (NumberOfFields == 1) { SelectedItem->clear(); ItemSize->clear(); }
        }
        else {
            SelectedItem->setText("Выбрано элементов: 1");
            ItemSize->setText(InfoWindowUi::FormatSize(QFileInfo(TreeFileBox->filePath(indexes[0])).size()));
        }
    }
    else {
        SelectedItem->setText("Выбрано элементов: " + QString::number(indexes.size()));
        qint64 size = 0;
        for (int i = 0; i < indexes.size(); i++)
            size += QFileInfo(FerrumUi::GenerateLocalPath(
                indexes[i].data(Qt::DisplayRole).toString())).size();
        ItemSize->setText(InfoWindowUi::FormatSize(size));
    }
}
void FerrumUi::GetName2() {
    QModelIndexList indexes = FileBox2->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        indexes = TreeFolderBox2->selectionModel()->selectedIndexes();
        if (indexes.size() == 0) {
            if (NumberOfFields == 1) { SelectedItem->clear(); ItemSize->clear(); }
        }
        else {
            SelectedItem->setText("Выбрано элементов: 1");
            ItemSize->setText(InfoWindowUi::FormatSize(QFileInfo(TreeFileBox->filePath(indexes[0])).size()));
        }
    }
    else {
        SelectedItem->setText("Выбрано элементов: " + QString::number(indexes.size()));
        qint64 size = 0;
        for (int i = 0; i < indexes.size(); i++)
            size += QFileInfo(FerrumUi::GenerateLocalPath(
                indexes[i].data(Qt::DisplayRole).toString())).size();
        ItemSize->setText(InfoWindowUi::FormatSize(size));
    }
}
void FerrumUi::GetName3() {
    QModelIndexList indexes = FileBox3->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        indexes = TreeFolderBox3->selectionModel()->selectedIndexes();
        if (indexes.size() == 0) {
            if (NumberOfFields == 1) { SelectedItem->clear(); ItemSize->clear(); }
        }
        else {
            SelectedItem->setText("Выбрано элементов: 1");
            ItemSize->setText(InfoWindowUi::FormatSize(QFileInfo(TreeFileBox->filePath(indexes[0])).size()));
        }
    }
    else {
        SelectedItem->setText("Выбрано элементов: " + QString::number(indexes.size()));
        qint64 size = 0;
        for (int i = 0; i < indexes.size(); i++)
            size += QFileInfo(FerrumUi::GenerateLocalPath(
                indexes[i].data(Qt::DisplayRole).toString())).size();
        ItemSize->setText(InfoWindowUi::FormatSize(size));
    }
}
void FerrumUi::GetName4() {
    QModelIndexList indexes = FileBox4->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        indexes = TreeFolderBox4->selectionModel()->selectedIndexes();
        if (indexes.size() == 0) {
            if (NumberOfFields == 1) { SelectedItem->clear(); ItemSize->clear(); }
        }
        else {
            SelectedItem->setText("Выбрано элементов: 1");
            ItemSize->setText(InfoWindowUi::FormatSize(QFileInfo(TreeFileBox->filePath(indexes[0])).size()));
        }
    }
    else {
        SelectedItem->setText("Выбрано элементов: " + QString::number(indexes.size()));
        qint64 size = 0;
        for (int i = 0; i < indexes.size(); i++)
            size += QFileInfo(FerrumUi::GenerateLocalPath(
                indexes[i].data(Qt::DisplayRole).toString())).size();
        ItemSize->setText(InfoWindowUi::FormatSize(size));
    }
}
void FerrumUi::PickOne() { CurrentFileBox = 1; path = path1; GetName1(); }
void FerrumUi::PickTwo() { CurrentFileBox = 2; path = path2; GetName2(); }
void FerrumUi::PickThree() { CurrentFileBox = 3; path = path3; GetName3(); }
void FerrumUi::PickFour() { CurrentFileBox = 4; path = path4; GetName4(); }
void FerrumUi::TreePickOne() { PickOne(); Open(); }
void FerrumUi::TreePickTwo() { PickTwo(); Open(); }
void FerrumUi::TreePickThree() { PickThree(); Open(); }
void FerrumUi::TreePickFour() { PickFour(); Open(); }


void FerrumUi::dragMoveEvent(QDragMoveEvent* event) {
    Copy();
    qDebug() << event;
}
void FerrumUi::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasUrls()) {
        QVector<QString> links;
        for (QUrl url: event->mimeData()->urls()) {
            links.push_back(url.toString());
        }
        emit(SIGNAL("dropped"), links);
        event->acceptProposedAction();
    }
    else dropEvent(event);
}
void FerrumUi::startDrag(Qt::DropActions SupportedActions) { qDebug() << SupportedActions; }
void FerrumUi::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
    else dragEnterEvent(event);
}
Qt::DropAction FerrumUi::supportedDropActions() {return Qt::MoveAction; }


void FerrumUi::SetupTreeView(QTreeView* Sample) {
    Sample->setModel(TreeFileBox);
    Sample->setAnimated(true);
    Sample->setSortingEnabled(true);
    Sample->isSortingEnabled();
    Sample->setFixedWidth(200);
    Sample->hideColumn(1);
    Sample->hideColumn(2);
    Sample->hideColumn(3);
    Sample->hideColumn(4);
    Sample->setHeaderHidden(true);
    Sample->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    Sample->horizontalScrollBar()->setEnabled(true);
    Sample->resizeColumnToContents(1);
    Sample->header()->resizeContentsPrecision();
    Sample->header()->setStretchLastSection(true);
    Sample->setDragEnabled(true);
    Sample->setAcceptDrops(true);
    Sample->setDragDropMode(QAbstractItemView::InternalMove);
    Sample->setContextMenuPolicy(Qt::CustomContextMenu);
}
QListView* FerrumUi::SetupFileBox() {
    QListView* Sample = new QListView();
    Sample->setSpacing(0);
    FileBoxItemSize = QSize(24, 24);
    Sample->setViewMode(QListView::ListMode);
    Sample->setFlow(QListView::TopToBottom);
    Sample->setSelectionMode(QAbstractItemView::ExtendedSelection);
    Sample->setContextMenuPolicy(Qt::CustomContextMenu);
    Sample->setDragEnabled(true);
    Sample->setAcceptDrops(true);
    Sample->setDropIndicatorShown(true);
    Sample->setDragDropMode(QAbstractItemView::InternalMove);
    Sample->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    Sample->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    auto OpenShortCut = new QShortcut(QKeySequence::Open, Sample);
    connect(OpenShortCut, &QShortcut::activated, this, &FerrumUi::Open);
    return Sample;
}
void FerrumUi::PreferencesMenu() {
    auto PrefsDialog = new PreferencesDialog(this);
    PrefsDialog->exec();
    PrefsDialog->deleteLater();
}
void FerrumUi::DirContextMenu() {
    auto menu = new QMenu();
    QMenu* SortMenu = new QMenu("Сортировка", this);
    QAction* SortOptionName = new QAction("Имя", this);
    QAction* SortOptionType = new QAction("Тип", this);
    QAction* SortOptionSize = new QAction("Размер", this);
    QAction* SortOptionDate = new QAction("Дата изменения", this);
    QAction* SortOptionNoReverse = new QAction("По возрастанию", this);
    QAction* SortOptionDoReverse = new QAction("По убыванию", this);
    QMenu* ViewMenu = new QMenu("Вид", this);
    QAction* ViewOptionIcons = new QAction("Значки", this);
    QAction* ViewOptionList = new QAction("Список", this);
    QAction* UpdateOption = new QAction("Обновить", this);
    QAction* PasteOption = new QAction("Вставить", this);
    QAction* CreateFileOption = new QAction("Создать файл", this);
    QAction* CreateFolderOption = new QAction("Создать папку", this);
    QAction* InfoOption = new QAction("Свойства", this);
    menu->addMenu(ViewMenu);
    menu->addMenu(SortMenu);
    menu->addAction(UpdateOption);
    menu->addSeparator();
    menu->addAction(PasteOption);
    menu->addSeparator();
    menu->addAction(CreateFileOption);
    menu->addAction(CreateFolderOption);
    menu->addSeparator();
    menu->addAction(InfoOption);
    ViewMenu->addAction(ViewOptionIcons);
    ViewMenu->addAction(ViewOptionList);
    SortMenu->addAction(SortOptionName);
    SortMenu->addAction(SortOptionType);
    SortMenu->addAction(SortOptionSize);
    SortMenu->addAction(SortOptionDate);
    SortMenu->addSeparator();
    SortMenu->addAction(SortOptionNoReverse);
    SortMenu->addAction(SortOptionDoReverse);
    QAction* SelectedOption = menu->exec(QCursor::pos());
    if (SelectedOption == ViewOptionIcons) FerrumUi::SetIconView();
    else if (SelectedOption == ViewOptionList) FerrumUi::SetListView();
    else if (SelectedOption == SortOptionName) FerrumUi::SortByName();
    else if (SelectedOption == SortOptionType) FerrumUi::SortByType();
    else if (SelectedOption == SortOptionSize) FerrumUi::SortBySize();
    else if (SelectedOption == SortOptionDate) FerrumUi::SortByDate();
    else if (SelectedOption == SortOptionNoReverse) FerrumUi::SortDisableReverse();
    else if (SelectedOption == SortOptionDoReverse) FerrumUi::SortEnableReverse();
    else if (SelectedOption == UpdateOption) FerrumUi::Update();
    else if (SelectedOption == PasteOption) FerrumUi::Paste();
    else if (SelectedOption == CreateFileOption) FerrumUi::CreateFileFE();
    else if (SelectedOption == CreateFolderOption) FerrumUi::CreateFolder();
    else if (SelectedOption == InfoOption) FerrumUi::Info();
}
bool FerrumUi::RightMenu(QPoint const& pos) {
    auto menu = new QMenu();
    QAction* OpenOption = new QAction("Открыть", this);
    QAction* CopyOption = new QAction("Копировать", this);
    QAction* CutOption = new QAction("Вырезать", this);
    QAction* PasteOption = new QAction("Вставить", this);
    QAction* RemoveOption = new QAction("Удалить", this);
    QAction* RenameOption = new QAction("Переименовать", this);
    QAction* CreateSymlink = new QAction("Создать ярлык", this);
    QAction* InfoOption = new QAction("Свойства", this);
    menu->addAction(OpenOption);
    menu->addAction(CopyOption);
    menu->addAction(CutOption);
    menu->addAction(PasteOption);
    menu->addAction(RemoveOption);
    menu->addAction(RenameOption);
    menu->addAction(CreateSymlink);
    menu->addAction(InfoOption);
    QAction* SelectedOption = menu->exec(QCursor::pos());
    if (SelectedOption == OpenOption) FerrumUi::Open();
    else if (SelectedOption == CopyOption) FerrumUi::Copy();
    else if (SelectedOption == CutOption) FerrumUi::Cut();
    else if (SelectedOption == PasteOption) FerrumUi::Paste();
    else if (SelectedOption == RemoveOption) FerrumUi::Remove();
    else if (SelectedOption == RenameOption) FerrumUi::RenameSlot();
    else if (SelectedOption == CreateSymlink) FerrumUi::CreateSymlink();
    else if (SelectedOption == InfoOption) FerrumUi::Info();
    return true;
}
void FerrumUi::GetNumberOfFields(qint64 x) { NumberOfFields = x; }
void FerrumUi::GenerateDesign() {
    qDebug() << NumberOfFields << Qt::endl;
    switch (NumberOfFields) {
    case 1: {
        gbox->removeWidget(TreeFolderBox2);
        gbox->removeWidget(FileBox2);
        TreeFolderBox2->hide();
        FileBox2->hide();
        gbox->removeWidget(TreeFolderBox3);
        gbox->removeWidget(FileBox3);
        TreeFolderBox3->hide();
        FileBox3->hide();
        gbox->removeWidget(TreeFolderBox4);
        gbox->removeWidget(FileBox4);
        TreeFolderBox4->hide();
        FileBox4->hide();
        gbox->update();
        path = path1;
        Update();
        repaint();
        QApplication::processEvents();
        break;
        }
    case 2: {
        Update();
        gbox->removeWidget(TreeFolderBox3);
        gbox->removeWidget(FileBox3);
        TreeFolderBox3->hide();
        FileBox3->hide();
        gbox->removeWidget(TreeFolderBox4);
        gbox->removeWidget(FileBox4);
        TreeFolderBox4->hide();
        FileBox4->hide();
        gbox->addWidget(TreeFolderBox2, 0, 3);
        gbox->addWidget(FileBox2, 0, 4);
        TreeFolderBox2->show();
        FileBox2->show();
        CurrentFileBox = 2;
        path = path2;
        Update();
        update();
        break;
        }
    case 3: {
        Update();
        gbox->removeWidget(TreeFolderBox4);
        gbox->removeWidget(FileBox4);
        TreeFolderBox4->hide();
        FileBox4->hide();
        gbox->addWidget(TreeFolderBox2, 0, 3);
        gbox->addWidget(FileBox2, 0, 4);
        TreeFolderBox2->show();
        FileBox2->show();
        CurrentFileBox = 2;
        path = path2;
        Update();
        gbox->addWidget(TreeFolderBox3, 1, 0);
        gbox->addWidget(FileBox3, 1, 1, 1, 4);
        TreeFolderBox3->show();
        FileBox3->show();
        CurrentFileBox = 3;
        path = path3;
        Update();
        update();
        break;
    }
    case 4: {
        Update();
        gbox->addWidget(TreeFolderBox2, 0, 3);
        gbox->addWidget(FileBox2, 0, 4);
        TreeFolderBox2->show();
        FileBox2->show();
        CurrentFileBox = 2;
        Update();
        gbox->addWidget(TreeFolderBox3, 1, 0);
        gbox->addWidget(FileBox3, 1, 1, 1, 2);
        TreeFolderBox3->show();
        FileBox3->show();
        gbox->addWidget(TreeFolderBox4, 1, 3);
        gbox->addWidget(FileBox4, 1, 4);
        CurrentFileBox = 3;
        path = path3;
        Update();
        TreeFolderBox4->show();
        FileBox4->show();
        CurrentFileBox = 4;
        path = path4;
        Update();
        update();
        break;
    }
    default:
        break;
    }
}
void FerrumUi::SetupGbox(QGridLayout* x) {
    x = new QGridLayout();
    x->setSpacing(0);
    x->setColumnStretch(0, 0);
}
void FerrumUi::GoLeft() {
    if (HistoryIndex == 1) { HistoryIndex -= 1; path = History[HistoryIndex]; Update(); }
    else if (HistoryIndex >= 2) { HistoryIndex -= 2; path = History[HistoryIndex]; Update(); }
}
void FerrumUi::GoRight() {
    if (HistoryIndex < History.length() - 1) { HistoryIndex += 1; path = History[HistoryIndex]; Update(); }
}
void FerrumUi::GoUp() {
    path = QFileInfo(path).absolutePath();
    switch(CurrentFileBox) {
        case 1: { path1 = path; break; }
        case 2: { path2 = path; break; }
        case 3: { path3 = path; break; }
        case 4: { path4 = path; break; }
        default: break;
    }
    History.push_back(path);
    HistoryIndex = History.length();
    Update();
}
void FerrumUi::Reload() {
    QFileInfo PathFileInfo(PathDisplay->toPlainText());
    if (PathFileInfo.isDir() && PathFileInfo.exists()) { path = PathFileInfo.absoluteFilePath(); Update(); }
    else if (PathFileInfo.isFile() && PathFileInfo.exists())
        QDesktopServices::openUrl(QUrl(QString::fromStdString("file:///")
        + PathFileInfo.absoluteFilePath(),
        QUrl::TolerantMode));
    else QMessageBox::critical(this, "Ошибка", "Нет такого файла или каталога!");
}
QString FerrumUi::GenerateLocalPath(QString const& ItemText) {
    QString LocalPath;
    if (path.length() < 4) LocalPath = path + ItemText;
    else LocalPath = path + '/' + ItemText;
    return LocalPath;
}
QVector<QFileInfo> FerrumUi::GeneratePathFileInfo() {
    QVector<QString> FullPath; QVector<QFileInfo> PathFileInfo;
    QModelIndexList FileBoxIndex = FileBox->selectionModel()->selectedIndexes();
    if (FileBoxIndex.size() == 0) {
        QModelIndexList TreeFolderBoxIndex = TreeFolderBox->selectionModel()->selectedIndexes();
        if (TreeFolderBoxIndex.size() > 0) {
            CurrentFileBox = 1;
            path1 = path;
            FullPath.push_back(TreeFileBox->filePath(TreeFolderBoxIndex[0]));
        }
        else {
            if (NumberOfFields == 1) FullPath = {path};
            else {
                FileBoxIndex = FileBox2->selectionModel()->selectedIndexes();
                if (FileBoxIndex.size() == 0) {
                    TreeFolderBoxIndex = TreeFolderBox2->selectionModel()->selectedIndexes();
                    if (TreeFolderBoxIndex.size() > 0) {
                        CurrentFileBox = 2;
                        path2 = path;
                        FullPath.push_back(TreeFileBox->filePath(TreeFolderBoxIndex[0]));
                    }
                    else {
                        if (NumberOfFields == 2) FullPath = {path};
                        else {
                            FileBoxIndex = FileBox3->selectionModel()->selectedIndexes();
                            if (FileBoxIndex.size() == 0) {
                                TreeFolderBoxIndex = TreeFolderBox3->selectionModel()->selectedIndexes();
                                if (TreeFolderBoxIndex.size() > 0) {
                                    CurrentFileBox = 3;
                                    path3 = path;
                                    FullPath.push_back(TreeFileBox->filePath(TreeFolderBoxIndex[0]));
                                }
                                else {
                                    if (NumberOfFields == 3) FullPath = {path};
                                    else {
                                        FileBoxIndex = FileBox4->selectionModel()->selectedIndexes();
                                        if (FileBoxIndex.size() == 0) {
                                            TreeFolderBoxIndex = TreeFolderBox4->selectionModel()->selectedIndexes();
                                            if (TreeFolderBoxIndex.size() > 0) {
                                                CurrentFileBox = 4;
                                                path4 = path;
                                                FullPath.push_back(TreeFileBox->filePath(TreeFolderBoxIndex[0]));
                                            }
                                            else {  FullPath = {path}; }
                                        }
                                        else {
                                            path4 = path;
                                            CurrentFileBox = 4;
                                            for (int i = 0; i < FileBoxIndex.size(); i++)
                                                FullPath.push_back(FerrumUi::GenerateLocalPath(
                                                FileBoxIndex[i].data(Qt::DisplayRole).toString()));
                                        }
                                    }
                                }
                            }
                            else {
                                path3 = path;
                                CurrentFileBox = 3;
                                for (int i = 0; i < FileBoxIndex.size(); i++)
                                    FullPath.push_back(FerrumUi::GenerateLocalPath(
                                    FileBoxIndex[i].data(Qt::DisplayRole).toString()));
                            }
                        }
                    }
                }
                else {
                    path2 = path;
                    CurrentFileBox = 2;
                    for (int i = 0; i < FileBoxIndex.size(); i++)
                        FullPath.push_back(FerrumUi::GenerateLocalPath(
                       FileBoxIndex[i].data(Qt::DisplayRole).toString()));
                }
            }
        }
    }
    else {
       CurrentFileBox = 1;
        path1 = path;
        for (int i = 0; i < FileBoxIndex.size(); i++)
            FullPath.push_back(FerrumUi::GenerateLocalPath(
            FileBoxIndex[i].data(Qt::DisplayRole).toString()));
    }
    for (QString Path : FullPath) PathFileInfo.push_back(QFileInfo(Path));
    TreeFolderBox->clearSelection();
    TreeFolderBox2->clearSelection();
    FileBox->clearSelection();
    FileBox2->clearSelection();
    TreeFolderBox3->clearSelection();
    TreeFolderBox4->clearSelection();
    FileBox3->clearSelection();
    FileBox4->clearSelection();
    return PathFileInfo;
}
void FerrumUi::Open() {
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        if (PathFileInfo.isSymLink()) Open1(QFileInfo(PathFileInfo.symLinkTarget()));
        else Open1(PathFileInfo);
    }
}
void FerrumUi::Open1(QFileInfo PathFileInfo) {
    qDebug() << PathFileInfo << Qt::endl;
    if (PathFileInfo.isFile()) {
        QDesktopServices::openUrl(QUrl(QString::fromStdString("file:///")
            + PathFileInfo.absoluteFilePath(),
                QUrl::TolerantMode));
    }
    else if (PathFileInfo.isDir() && PathFileInfo.exists()) {
        path = PathFileInfo.absoluteFilePath();
        History.push_back(path);
        HistoryIndex = History.length();
        Update();
    }
    switch(CurrentFileBox) {
        case 1: { path1 = path; break; }
        case 2: { path2 = path; break; }
        case 3: { path3 = path; break; }
        case 4: { path4 = path; break; }
        default: break;
    }

}
void FerrumUi::MoveFileToClipBoard(QString const& FullPath) {urls.push_back(QUrl::fromLocalFile(FullPath));}
void FerrumUi::MoveFolderToClipBoard(QString const& FullPath) {
    GenerateItems(FullPath);
    for (int i = 0; i < dirs.size(); i++) {
        QFileInfo PathFileInfo(FullPath);
        QString s = PathFileInfo.absoluteFilePath();
        if (PathFileInfo.isDir() and not urls.contains(QUrl::fromLocalFile(s))) {
        urls.push_back(QUrl::fromLocalFile(s)); MoveFolderToClipBoard(s);  GenerateItems(FullPath);}
    }
}
void FerrumUi::Copy() {
    urls.clear();
    CutUrlsToPaste.clear();
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        if (PathFileInfo.isFile()) MoveFileToClipBoard(PathFileInfo.absoluteFilePath());
        else if (PathFileInfo.isDir()) MoveFolderToClipBoard(PathFileInfo.absoluteFilePath());
        QMimeData* mimeData = new QMimeData();
        mimeData->setUrls({urls});
        clipboard->setMimeData(mimeData);
        #if defined(Q_OS_LINUX)
            QThread::msleep(1);
        #endif
    }
}
void FerrumUi::WriteFolderToPaste(QString const& FullPath) {
    GenerateItems(FullPath);
    for (int i = 0; i < dirs.size(); i++) {
        QFileInfo PathFileInfo(FullPath);
        QString s = PathFileInfo.absoluteFilePath();
        if (not CutUrlsToPaste.contains(QUrl::fromLocalFile(s))) {
        CutUrlsToPaste.push_back(QUrl::fromLocalFile(s)); GenerateItems(FullPath);}
    }
}
void FerrumUi::Cut() {
    urls.clear();
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        QString FullPath = PathFileInfo.absoluteFilePath();
        if (PathFileInfo.isFile()) {
            MoveFileToClipBoard(FullPath);
            CutUrlsToPaste.push_back(QUrl::fromLocalFile(FullPath));
        }
        else if (PathFileInfo.isDir()) {
            MoveFolderToClipBoard(FullPath);
            WriteFolderToPaste(FullPath);
        }
        QMimeData* mimeData = new QMimeData();
        mimeData->setUrls({CutUrlsToPaste});
        clipboard->setMimeData(mimeData);
        #if defined(Q_OS_LINUX)
            QThread::msleep(1);
        #endif
    }
    Update();
}
void FerrumUi::CopyDir(QString const& SourceDir, QString const& DestinationDir) {
    QDir dir(SourceDir);
    //QApplication::processEvents();
    QVector<QFileInfo> dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot
    | QDir::Hidden | QDir::System);
    for (int i = 0; i < dirs.length(); i++) {
        QString DirName = dirs[i].fileName();
        QString DestinatonPath = DestinationDir + QDir::separator() + DirName;
        //QApplication::processEvents();
        dir.mkpath(DestinatonPath);
        //QApplication::processEvents();
        CopyDir(SourceDir + QDir::separator() + DirName, DestinatonPath);
        //QApplication::processEvents();
        Update();
        PasteProgress->setValue(PasteProgressValue);
        PasteProgressValue++;
        //QApplication::processEvents();
    }
    QVector<QFileInfo> files = dir.entryInfoList(QDir::Files | QDir::Hidden
    | QDir::System);
    for (int i = 0; i < files.length(); i++) {
        QString FileName = files[i].fileName();
        //QApplication::processEvents();
        QFile::copy(SourceDir + QDir::separator() + FileName, DestinationDir +
        QDir::separator() + FileName);
        //QApplication::processEvents();
        Update();
        PasteProgress->setValue(PasteProgressValue);
        PasteProgressValue++;
        //QApplication::processEvents();
    }
    //QApplication::processEvents();
}
void FerrumUi::Paste() {
    //QApplication::processEvents();
    QVector<QUrl> UrlsToPaste;
    if (CutUrlsToPaste.length() > 0) UrlsToPaste = CutUrlsToPaste;
    else {
        const QMimeData* mimeData = clipboard->mimeData();
        UrlsToPaste = mimeData->urls();
    }
    QVector<QString> DirsToPaste;
    for (int i = 0; i < UrlsToPaste.length(); i++) DirsToPaste.push_back(UrlsToPaste[i].toLocalFile());
    PasteProgress = new QProgressDialog("Копирование директории. Пожалуйста подождите...",
        "Отмена", 0, 0, this);
    PasteProgress->setValue(0);
    PasteProgress->setWindowModality(Qt::WindowModal);
    for (int i = 0; i < DirsToPaste.length(); i++) {
        QFileInfo DirToPaste(DirsToPaste[i]);
        DirToPaste.absolutePath();
        if (DirToPaste.isDir()) { CopyDir(DirToPaste.absoluteFilePath(),
            GenerateLocalPath("") + DirToPaste.fileName()); Update(); }
        else if (DirToPaste.isFile()) { QFile::copy(DirToPaste.absoluteFilePath(),
            GenerateLocalPath("") + DirToPaste.fileName()); Update();}
        PasteProgress->setValue(PasteProgressValue);
        PasteProgressValue++;
    }
    PasteProgress->close();
    PasteProgress->setValue(PasteProgressValue++);
    if (not CutUrlsToPaste.isEmpty()) {
        for (int i = 0; i < CutUrlsToPaste.length(); i++) {
            QFileInfo PathFileInfo(CutUrlsToPaste[i].toLocalFile());
            QString FullPath = PathFileInfo.absoluteFilePath();
            if (PathFileInfo.isFile()) QFile::remove(FullPath);
            else if (PathFileInfo.isDir()) RemoveDir(FullPath);
        }
    }
    Update();
    UrlsToPaste.clear();
    DirsToPaste.clear();
}
void FerrumUi::RemoveDir(QString const& DirToRemove) {
    QDir dir(DirToRemove);
    dir.removeRecursively();
}
void FerrumUi::Remove() {
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        if (PathFileInfo.isFile() or PathFileInfo.isSymLink())
            QFile::remove(PathFileInfo.absoluteFilePath());
        else if (PathFileInfo.isDir()) RemoveDir(PathFileInfo.absoluteFilePath());
    }
    Update();
}
void FerrumUi::RenameSlot() {
    auto RenameDialogUiWindow = new RenameDialogUi(this);
    RenameDialogUiWindow->exec();
    RenameDialogUiWindow->deleteLater();
}
void FerrumUi::Rename(QString const& name) {
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        QString FullPath = PathFileInfo.absoluteFilePath();
        QString Path = PathFileInfo.path();
        if (path.length() >= 4) Path += '/';
        if (PathFileInfo.isFile()) QFile::rename(FullPath, Path + name + '.' + PathFileInfo.completeSuffix());
        else if (PathFileInfo.isDir()) {
            QDir dir(FullPath);
            auto Source = QDir::cleanPath(dir.filePath("."));
            auto Destination = QDir::cleanPath(dir.filePath(QStringLiteral("..%1%2").arg(QDir::separator()).arg(name)));
            auto rc = QFile::rename(Source, Destination);
            if (rc) dir.setPath(Destination);
        }
    }
    Update();
}
void FerrumUi::CreateFileFE() {
    auto CreateFileDialogUiWindow = new CreateFileWindowUi(this);
    CreateFileDialogUiWindow->exec();
    CreateFileDialogUiWindow->deleteLater();
}
void FerrumUi::CreateFileFE(QString const& name) {
    QFile file(GenerateLocalPath(name));
    file.open(QIODevice::WriteOnly);
    Update();
}
void FerrumUi::CreateFolder() {
    auto CreateFolderDialogUiWindow = new CreateFolderWindowUi(this);
    CreateFolderDialogUiWindow->exec();
    CreateFolderDialogUiWindow->deleteLater();
}
void FerrumUi::CreateFolder(QString const& name) {
    QDir().mkdir(GenerateLocalPath(name));
    Update();
}
void FerrumUi::CreateSymlink() {
    QVector<QFileInfo> PathFileInfoList = GeneratePathFileInfo();
    for (QFileInfo PathFileInfo : PathFileInfoList) {
        QString FullPath = PathFileInfo.absoluteFilePath();
        QFile(FullPath).link(FullPath.append(".lnk"));
    }
    Update();
}// Текущий каталог: C:/ количество файлов - x количество папок - y Выбранныый элемент - Qt Размер - z
void FerrumUi::Update() {
    PathDisplay->setPlainText(path);
    FileBox->clearSelection();
    GenerateItems(path);
    auto FileModel = new QStandardItemModel();
    QSize FileBoxItemSizeLocal;
    switch(CurrentFileBox) {
        case 1: { FileBox->setModel(FileModel); FileBoxItemSizeLocal = FileBoxItemSize; break; }
        case 2: { FileBox2->setModel(FileModel); FileBoxItemSizeLocal = FileBoxItemSize2; break; }
        case 3: { FileBox3->setModel(FileModel); FileBoxItemSizeLocal = FileBoxItemSize3; break; }
        case 4: { FileBox4->setModel(FileModel); FileBoxItemSizeLocal = FileBoxItemSize4; break; }
        default: break;
    }
    SelectedItem->clear();
    ItemSize->clear();
    for (qint64 i = 0; i < dirs.size(); i++) {
        auto FileDirInfo = new QFileInfo(GenerateLocalPath(dirs[i]));
        auto IconProvider = new QFileIconProvider();
        auto FileDirIcon = new QIcon(IconProvider->icon(*FileDirInfo));
        auto item = new QStandardItem(*FileDirIcon, dirs[i]);
        item->setSizeHint(FileBoxItemSizeLocal);
        FileModel->appendRow(item);
        FileModel->setSortRole(1);
    }
}
void FerrumUi::GenerateItems(QString LocalPath) {
    QDir dir(LocalPath); dirs.clear(), FullDirs.clear();
    QVector<QFileInfo> DirList, FileList;
    if (ShowHidden) dir.setFilter(QDir::Hidden | QDir::System);
    if (!SortOrderReversed) {
        if (SortType == "Name") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
            FileList = dir.entryInfoList(QDir::Files, QDir::Name);
        }
        else if (SortType == "Type") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Type);
            FileList = dir.entryInfoList(QDir::Files, QDir::Type);
        }
        else if (SortType == "Size") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Size);
            FileList = dir.entryInfoList(QDir::Files, QDir::Size);
        }
        else if (SortType == "Date") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Time);
            FileList = dir.entryInfoList(QDir::Files, QDir::Time);
        }
    }
    else {
        if (SortType == "Name") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name | QDir::Reversed);
            FileList = dir.entryInfoList(QDir::Files, QDir::Name);
        }
        else if (SortType == "Type") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Type | QDir::Reversed);
            FileList = dir.entryInfoList(QDir::Files, QDir::Type);
        }
        else if (SortType == "Size") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Size | QDir::Reversed);
            FileList = dir.entryInfoList(QDir::Files, QDir::Size);
        }
        else if (SortType == "Date") {
            DirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Time | QDir::Reversed);
            FileList = dir.entryInfoList(QDir::Files, QDir::Time);
        }
    }
    for (const QFileInfo &file: DirList) {
        dirs.push_back(file.fileName());
        if (LocalPath.length() < 4)  FullDirs.push_back(file.absolutePath());
        else FullDirs.push_back(file.absolutePath() + '/');
    }
    for (const QFileInfo &file: FileList) {
        dirs.push_back(file.fileName());
        if (LocalPath.length() < 4)  FullDirs.push_back(file.absolutePath());
        else FullDirs.push_back(file.absolutePath() + '/');
    }
    FilesCount->setText("Файлов: " + QString::number(FileList.size()));
    DirsCount->setText("Каталогов: " + QString::number(DirList.size()));
}
void FerrumUi::Info() {
    auto InfoWindowUiWindow = new InfoWindowUi(this);
    InfoWindowUiWindow->exec();
    InfoWindowUiWindow->deleteLater();
}
QVector<QFileInfo> FerrumUi::Info1() { return GeneratePathFileInfo(); }
void FerrumUi::SetIconView() {
    switch(CurrentFileBox) {
        case 1: {
            FileBox->setResizeMode(QListView::Adjust);
            FileBox->setSpacing(8);
            FileBoxItemSize = QSize(64, 64);
            FileBox->setViewMode(QListView::IconMode);
            FileBox->setMovement(QListView::Snap);
            FileBox->setFlow(QListView::LeftToRight);
            break;
        }
        case 2: {
            FileBox2->setResizeMode(QListView::Adjust);
            FileBox2->setSpacing(8);
            FileBoxItemSize2 = QSize(64, 64);
            FileBox2->setViewMode(QListView::IconMode);
            FileBox2->setMovement(QListView::Snap);
            FileBox2->setFlow(QListView::LeftToRight);
            break;
        }
        case 3: {
            FileBox3->setResizeMode(QListView::Adjust);
            FileBox3->setSpacing(8);
            FileBoxItemSize3 = QSize(64, 64);
            FileBox3->setViewMode(QListView::IconMode);
            FileBox3->setMovement(QListView::Snap);
            FileBox3->setFlow(QListView::LeftToRight);
            break;
        }
        case 4: {
            FileBox4->setResizeMode(QListView::Adjust);
            FileBox4->setSpacing(8);
            FileBoxItemSize4 = QSize(64, 64);
            FileBox4->setViewMode(QListView::IconMode);
            FileBox4->setMovement(QListView::Snap);
            FileBox4->setFlow(QListView::LeftToRight);
            break;
        }
    }
    Update();
}
void FerrumUi::SetListView() {
    switch (CurrentFileBox) {
        case 1: {
            FileBox->setSpacing(0);
            FileBoxItemSize = QSize(24, 24);
            FileBox->setViewMode(QListView::ListMode);
            FileBox->setFlow(QListView::TopToBottom);
            break;
        }
        case 2: {
            FileBox2->setSpacing(0);
            FileBoxItemSize2 = QSize(24, 24);
            FileBox2->setViewMode(QListView::ListMode);
            FileBox2->setFlow(QListView::TopToBottom);
            break;
        }
        case 3: {
            FileBox3->setSpacing(0);
            FileBoxItemSize3 = QSize(24, 24);
            FileBox3->setViewMode(QListView::ListMode);
            FileBox3->setFlow(QListView::TopToBottom);
            break;
        }
        case 4: {
            FileBox4->setSpacing(0);
            FileBoxItemSize4 = QSize(24, 24);
            FileBox4->setViewMode(QListView::ListMode);
            FileBox4->setFlow(QListView::TopToBottom);
            break;
        }
    }
    Update();
}
void FerrumUi::SortByName() { SortType = "Name"; Update(); }
void FerrumUi::SortByType() { SortType = "Type"; Update(); }
void FerrumUi::SortBySize() { SortType = "Size"; Update(); }
void FerrumUi::SortByDate() { SortType = "Date"; Update(); }
void FerrumUi::SortEnableReverse() { SortOrderReversed = true; Update(); }
void FerrumUi::SortDisableReverse() { SortOrderReversed = false; Update(); }
bool FerrumUi::SendToHidBox() { return ShowHidden; }
void FerrumUi::GetFromHidBox(bool x) { ShowHidden = x; }
void FerrumUi::HideStatusBar() { StatusBar->hide(); }
void FerrumUi::ShowStatusBar() { StatusBar->show(); }
