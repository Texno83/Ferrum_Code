#ifndef CREATEFILEWINDOWUI_H
#define CREATEFILEWINDOWUI_H

#include <QDialog>

class FerrumUi;
class QLineEdit;

class CreateFileWindowUi : public QDialog
{
    Q_OBJECT
public:
    explicit CreateFileWindowUi(FerrumUi* ferrum_ui, QDialog *parent = nullptr);

private slots:
    auto onButtonClicked() -> void;

private:
    FerrumUi* m_ferrum_ui;
    QLineEdit* m_text_line;
signals:

};
#endif // CREATEFILEWINDOWUI_H
