#ifndef RENAMEDIALOGUI_H
#define RENAMEDIALOGUI_H

#include <QDialog>

class FerrumUi;
class QLineEdit;

class RenameDialogUi : public QDialog
{
    Q_OBJECT
public:
    explicit RenameDialogUi(FerrumUi* ferrum_ui, QDialog *parent = nullptr);

private slots:
    auto onButtonClicked() -> void;

private:
    FerrumUi* m_ferrum_ui;
    QLineEdit* m_text_line;
signals:

};

#endif // RENAMEDIALOGUI_H
