#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

class FerrumUi;
class QLineEdit;
class QListView;

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog(FerrumUi* ferrum_ui, QDialog *parent = nullptr);

private slots:
    //auto onButtonClicked() -> void;
    void ItemClicked();
    void HiddenChecked();
    void SetIconMode();
    void SetListMode();
    void HideStatus();
    void ShowStatus();
    void SortByName();
    void SortByType();
    void SortBySize();
    void SortByDate();
    void SortEnableReverse();
    void SortDisableReverse();
    void Close();
private:
    FerrumUi* m_ferrum_ui;
    QListView* ViewBox;
    //QLineEdit* m_text_line;
signals:

};
#endif // PREFERENCESDIALOG_H
