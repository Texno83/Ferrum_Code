#ifndef UI_H
#define UI_H
#include <QApplication>
#include <QGridLayout>
#include <QUrl>
#include <QMainWindow>
#include <QFileInfo>

class QListWidget;
class QMouseEvent;
class QPushButton;
class QGridLayout;
class QScrollArea;
class QListView;
class QFileSystemModel;
class QTreeView;
class QString;
class QApplication;
class QClipboard;
class QUrl;
class QTextEdit;
class QSize;
class QStandardItem;
class QDirModel;
class QProgressDialog;
class QWidget;
class QStatusBar;
class QLabel;

class FerrumUi : public QMainWindow {
    Q_OBJECT
public:
    FerrumUi(QWidget *parent = nullptr);
    ~FerrumUi();
public slots:
    void PathDisplayContextMenu();
    void CopyAddress();
    void PickOne();
    void PickTwo();
    void PickThree();
    void PickFour();
    void TreePickOne();
    void TreePickTwo();
    void TreePickThree();
    void TreePickFour();
    void dragMoveEvent(QDragMoveEvent*);
    void dropEvent(QDropEvent*);
    void startDrag(Qt::DropActions SupportedActions);
    void dragEnterEvent(QDragEnterEvent*);
    Qt::DropAction supportedDropActions();
    void SetupGbox(QGridLayout*);
    void SetupTreeView(QTreeView*);
    QListView* SetupFileBox();
    void PreferencesMenu();
    void DirContextMenu();
    bool RightMenu(QPoint const& pos);
    void GetNumberOfFields(qint64);
    void GenerateDesign();
    void GoLeft();
    void GoRight();
    void GoUp();
    void Reload();
    QString GenerateLocalPath(QString const& ItemText);
    QVector<QFileInfo> GeneratePathFileInfo();
    void Open();
    void Open1(QFileInfo);
    void MoveFileToClipBoard(QString const& Fullpath);
    void MoveFolderToClipBoard(QString const& Fullpath);
    void Copy();
    void WriteFolderToPaste(QString const& FullPath);
    void Cut();
    void CopyDir(QString const& SourceDir, QString const& DestinationDir);
    void Paste();
    void RemoveDir(QString const& DirToRemove);
    void Remove();
    void RenameSlot();
    void Rename(QString const& name);
    void CreateFileFE();
    void CreateFileFE(QString const& name);
    void CreateFolder();
    void CreateFolder(QString const& name);
    void CreateSymlink();
    void Update();
    void GenerateItems(QString LocalPath);
    void Info();
    QVector<QFileInfo> Info1();
    void SetIconView();
    void SetListView();
    void SortByName();
    void SortByType();
    void SortBySize();
    void SortByDate();
    void SortEnableReverse();
    void SortDisableReverse();
    bool SendToHidBox();
    void GetFromHidBox(bool);
    void GetName1();
    void GetName2();
    void GetName3();
    void GetName4();
    void HideStatusBar();
    void ShowStatusBar();
private:
    bool ShowHidden = true;
    bool SortOrderReversed = false;
    QString SortType = "Name";
    QString path = "C:/";
    QVector<QString> History;
    qint64 HistoryIndex = 0;
    QVector<QPushButton*> ButtonsList;
    QGridLayout* gbox;
    QListView* FileBox;
    QListView* FileBox2;
    QListView* FileBox3;
    QListView* FileBox4;
    QFileSystemModel* TreeFileBox;
    QTreeView* TreeFolderBox;
    QTreeView* TreeFolderBox2;
    QTreeView* TreeFolderBox3;
    QTreeView* TreeFolderBox4;
    QVector<QString> dirs, FullDirs;
    QVector<QUrl> urls, CutUrlsToPaste;
    QClipboard* clipboard = QApplication::clipboard();
    QTextEdit* PathDisplay;
    QSize FileBoxItemSize;
    QSize FileBoxItemSize2;
    QSize FileBoxItemSize3;
    QSize FileBoxItemSize4;
    QProgressDialog* PasteProgress;
    qint64 PasteProgressValue = 0;
    qint64 NumberOfFields = 1;
    qint64 CurrentFileBox = 1;
    auto onCustomContextMenuRequested(QPoint const& pos) -> void;
    QWidget* wdg;
    QWidget* wdg2;
    QWidget* wdg3;
    QWidget* wdg4;
    QString path1 = "C:/";
    QString path2 = "C:/";
    QString path3 = "C:/";
    QString path4 = "C:/";
    QStatusBar* StatusBar;
    QLabel* FilesCount;
    QLabel* DirsCount;
    QLabel* SelectedItem;
    QLabel* ItemSize;
};
#endif // UI_H
