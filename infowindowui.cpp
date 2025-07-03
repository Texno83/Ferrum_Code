#include <QApplication>
#include "infowindowui.h"
#include "FE.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QString>
#include <QPixmap>
#include <QSize>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDir>
#include <QStringList>
#include <QDirIterator>
#include <QPair>
#include <QProgressDialog>
InfoWindowUi::InfoWindowUi(FerrumUi* ferrum_ui, QWidget *parent)
    : QDialog{parent}, m_ferrum_ui(ferrum_ui), ItemName(new QLabel()),
     ItemSizeInfo(new QLabel()), ItemItemsInfo(new QLabel()), gbox(new QGridLayout())
{
    setWindowTitle("Свойства");
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(400, 500);
    auto ItemIcon = new QLabel(this);
    auto ItemType = new QLabel(this);
    auto ItemTypeInfo = new QLabel(this);
    auto ItemPath = new QLabel(this);
    auto ItemPathInfo = new QLabel(this);
    auto ItemSize = new QLabel(this);
    auto ItemSizeInfo = new QLabel(this);
    auto ItemCreated = new QLabel(this);
    auto ItemCreatedInfo = new QLabel(this);
    auto ItemModified = new QLabel(this);
    auto ItemModifiedInfo = new QLabel(this);
    auto ItemItems = new QLabel(this);
    auto ItemItemsInfo = new QLabel(this);
    QVector<QFileInfo> PathFileInfoList;
    //PathFileInfoList.resize(m_ferrum_ui->Info1().size());

    for (QFileInfo PathFileInfo : m_ferrum_ui->Info1()) PathFileInfoList.push_back(PathFileInfo);
    qDebug() << PathFileInfoList.length() << "Длина вектора" << Qt::endl;
    //qDebug() << m_ferrum_ui->Info1().length() << "Vekotor" << Qt::endl;
    qDebug() << PathFileInfoList << "вектор" << Qt::endl;
    //for (QFileInfo PathFileInfo : PathFileInfoList)
    QVector<QString> FullPathList;
    for (QFileInfo PathFileInfo : PathFileInfoList) FullPathList.push_back(PathFileInfo.absoluteFilePath());
    //QFileInfo PathFileInfo = m_ferrum_ui->Info1();
    //QString FullPath = PathFileInfo.absoluteFilePath();
    if (PathFileInfoList.size() > 1) {
        //qDebug() << PathFileInfoList << Qt::endl;
        //qDebug() << FullPathList << Qt::endl;
        ItemType->setText("Тип:");
        ItemTypeInfo->setText("Разные типы");
        ItemPath->setText("Путь:");
        ItemPathInfo->setText(PathFileInfoList[0].absolutePath());
        ItemSize->setText("Размер:");
        ItemItems->setText("Размер:");
        gbox->addWidget(ItemType, 1, 0);
        gbox->addWidget(ItemTypeInfo, 1, 1);
        gbox->addWidget(ItemPath, 2, 0);
        gbox->addWidget(ItemPathInfo, 2, 1);
        gbox->addWidget(ItemSize, 3, 0);
        gbox->addWidget(ItemSizeInfo, 3, 1);
        gbox->addWidget(ItemItems, 4, 0);
        gbox->addWidget(ItemItemsInfo, 4, 1);
        x.resize(4);
        x = {0, 0, 0, 0};
        isdir = true;
        for (QString FullPath : FullPathList)
            QMetaObject::invokeMethod(this, "PathInfo", Qt::QueuedConnection, Q_ARG(QString, FullPath));
        //qDebug() << FullPath << Qt::endl;

    }
    else {
        if (PathFileInfoList[0].isDir()) isdir = true;
        else isdir = false;
        x = {0, 0, 0, 0};
        x.resize(4);
        qDebug() << PathFileInfoList[0] << Qt::endl;
        ItemName->setText(PathFileInfoList[0].fileName());
        ItemIcon->setPixmap(QIcon(QFileIconProvider().icon(PathFileInfoList[0])).pixmap(QSize(64, 64)));
        ItemType->setText("Тип:");
        ItemPath->setText("Путь:");
        ItemPathInfo->setText(FullPathList[0]);
        ItemSize->setText("Размер:");
        ItemCreated->setText("Создан:");
        ItemCreatedInfo->setText(PathFileInfoList[0].birthTime().toString("hh:mm:ss dd-MM-yyyy"));
        ItemModified->setText("Изменён:");
        ItemModifiedInfo->setText(PathFileInfoList[0].lastModified().toString("hh:mm:ss dd-MM-yyyy"));
        if (PathFileInfoList[0].isDir()) {
            ItemTypeInfo->setText("Папка");
            ItemItems->setText("Содержит:");
            gbox->addWidget(ItemIcon, 0, 0);
            gbox->addWidget(ItemName, 0, 1);
            gbox->addWidget(ItemType, 1, 0);
            gbox->addWidget(ItemTypeInfo, 1, 1);
            gbox->addWidget(ItemPath, 2, 0);
            gbox->addWidget(ItemPathInfo, 2, 1);
            gbox->addWidget(ItemSize, 3, 0);
            gbox->addWidget(ItemSizeInfo, 3, 1);
            gbox->addWidget(ItemItems, 4, 0);
            gbox->addWidget(ItemItemsInfo, 4, 1);
            gbox->addWidget(ItemCreated, 5, 0);
            gbox->addWidget(ItemCreatedInfo, 5, 1);
            gbox->addWidget(ItemModified, 6, 0);
            gbox->addWidget(ItemModifiedInfo, 6, 1);
            QMetaObject::invokeMethod(this, "PathInfo", Qt::QueuedConnection,
                Q_ARG(QString, FullPathList[0]));
        }
        else if (PathFileInfoList[0].isFile()) {
            ItemTypeInfo->setText("." + PathFileInfoList[0].completeSuffix());
            ItemSizeInfo->setText(FormatSize(PathFileInfoList[0].size()));
            gbox->addWidget(ItemIcon, 0, 0);
            gbox->addWidget(ItemName, 0, 1);
            gbox->addWidget(ItemType, 1, 0);
            gbox->addWidget(ItemTypeInfo, 1, 1);
            gbox->addWidget(ItemPath, 2, 0);
            gbox->addWidget(ItemPathInfo, 2, 1);
            gbox->addWidget(ItemSize, 3, 0);
            gbox->addWidget(ItemSizeInfo, 3, 1);
            gbox->addWidget(ItemCreated, 4, 0);
            gbox->addWidget(ItemCreatedInfo, 4, 1);
            gbox->addWidget(ItemModified, 5, 0);
            gbox->addWidget(ItemModifiedInfo, 5, 1);
        }
    }
    gbox->setSpacing(8);
    gbox->setColumnStretch(1, 1);
    setLayout(gbox);
}
QVector<qint64> InfoWindowUi::PathInfo(const QString FullPath) {
    auto PathFileInfo = QFileInfo(FullPath);
    if (PathFileInfo.isFile() or QFileInfo(PathFileInfo.symLinkTarget()).isFile()) {
        x[0] += PathFileInfo.size();
        x[2]++;
        ChangeText(x);
        return {PathFileInfo.size(), 0, x[2]}; }
    else {
        qint64 size = 0;
        QDir dir(FullPath), file(FullPath);
        dir.setFilter( QDir::AllDirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden);
        file.setFilter( QDir::Files | QDir::System | QDir::Hidden);
        qint64 dirs = dir.count(), files = file.count();
        QVector<qint64> info1 = {size, dirs, files};
        QVector<qint64> res;
        res.resize(3);
        for (QString Path : file.entryList()) { info1[0] += QFileInfo(FullPath + "/" + Path).size(); }
        for (QString Path : dir.entryList()) { res = PathInfo(FullPath + "/" + Path); }
        x[0] += info1[0]; x[1] += info1[1]; x[2] += info1[2];
        ChangeText(x);
        return info1;
    }
}
void InfoWindowUi::ChangeText(const QVector<qint64> info) {
    gbox->removeWidget(ItemSizeInfo);
    ItemSizeInfo->setText(FormatSize(info[0]));
    gbox->addWidget(ItemSizeInfo, 3, 1);
    if (isdir) {
        gbox->removeWidget(ItemItemsInfo);
        ItemItemsInfo->setText("Файлов: " + QString::number(info[2]) + " Папок: " + QString::number(info[1]));
        gbox->addWidget(ItemItemsInfo, 4, 1);
    }
    gbox->update();
    QApplication::processEvents();
    repaint(); update();
}
QString InfoWindowUi::FormatSize(qint64 size) {
    if (size < 1024 ) return QString::number(size) + " Б";
    else {
        QStringList formats = {"Б", "КБ", "МБ", "ГБ", "ТБ", "ПБ", "ЭБ", "ЗБ", "ЙБ", "РБ", "КБ"};
        float output = size;
        int i = 0;
        for (i = 1; i < formats.size() - 1; i++) {
            output /= 1024;
            if (output < 1024) return QString::number(output) + ' ' +
                formats[i] + " (" + QString::number(size) + " Б)";
        }
        return QString::number(output) + ' ' + formats[i] + " (" + QString::number(size) + " Б)";
    }
}

