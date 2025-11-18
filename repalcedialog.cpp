#include "repalcedialog.h"
#include "ui_repalcedialog.h"
#include <QMessageBox>

RepalceDialog::RepalceDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::RepalceDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;

     ui->rpDown->setChecked(true);
}

RepalceDialog::~RepalceDialog()
{
    delete ui;
}

void RepalceDialog::on_btFindNext_clicked()
{
    QString target = ui->searchText->text();

    if(target == "" || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;
    if(ui->rpDown->isChecked()){
        index = text.indexOf(target,c.position(),
                             ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index + target.length(),QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target,c.position() - text.length() -1 ,
                                 ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index + target.length());
            c.setPosition(index,QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("记事本");
        msg.setText(QString("找不到 ") + target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void RepalceDialog::on_btReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QString selText = pTextEdit->textCursor().selectedText();
        if(selText == target)
            pTextEdit->insertPlainText(to);
        on_btFindNext_clicked();
    }
}


void RepalceDialog::on_btReplaceAll_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QString text = pTextEdit->toPlainText();
        text.replace(target,to,ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive :
                                     Qt::CaseInsensitive);
        pTextEdit->clear();
        pTextEdit->insertPlainText(text);
    }
}


void RepalceDialog::on_btCancel_clicked()
{
    accept();
}

