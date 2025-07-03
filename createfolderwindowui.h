#ifndef CREATEFOLDERWINDOWUI_H
#define CREATEFOLDERWINDOWUI_H

#include <QDialog>

class FerrumUi;
class QLineEdit;

class CreateFolderWindowUi : public QDialog
{
    Q_OBJECT
public:
    explicit CreateFolderWindowUi(FerrumUi* ferrum_ui, QDialog *parent = nullptr);

private slots:
    auto onButtonClicked() -> void;

private:
    FerrumUi* m_ferrum_ui;
    QLineEdit* m_text_line;
signals:

};
#endif // CREATEFOLDERWINDOWUI_H
