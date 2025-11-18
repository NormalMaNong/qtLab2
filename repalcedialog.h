#ifndef REPALCEDIALOG_H
#define REPALCEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class RepalceDialog;
}

class RepalceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepalceDialog(QWidget *parent = nullptr, QPlainTextEdit *textEdit = nullptr);
    ~RepalceDialog();

private slots:
    void on_btFindNext_clicked();

    void on_btReplace_clicked();

    void on_btReplaceAll_clicked();

    void on_btCancel_clicked();

private:
    Ui::RepalceDialog *ui;
    QPlainTextEdit *pTextEdit;
};

#endif // REPALCEDIALOG_H
