#ifndef INFOWINDOWUI_H
#define INFOWINDOWUI_H

#include <QDialog>
#include <QString>

class FerrumUi;
class QLabel;
class QFileIconProvider;
class QFileInfo;
class QString;
class QProgressDialog;
class QGridLayout;

class InfoWindowUi : public QDialog
{
    Q_OBJECT
public:
    explicit InfoWindowUi(FerrumUi* ferrum_ui, QWidget *parent = nullptr);
    QVector<qint64> x;
public slots:
    //QVector<qint64> PathInfoNoRec(const QString);
    QVector<qint64> PathInfo(const QString);
    static QString FormatSize(qint64);
    //QVector<qint64> Info0();
private slots:  
    void ChangeText(const QVector<qint64>);
private:
    FerrumUi* m_ferrum_ui;
    QLabel* ItemName;
    QLabel* ItemSizeInfo;
    QLabel* ItemItemsInfo;
    QGridLayout* gbox;
    QVector<qint64> result;
    QString ParentPath;
    bool isdir;
signals:

};

#endif // INFOWINDOWUI_H
