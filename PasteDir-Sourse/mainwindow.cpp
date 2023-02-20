#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <random>
#include <QFileSystemModel>
#include <string>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //здесь создавать папку с файлами if not exist
    titlegen();
    QDir dir;
    if (!dir.exists("pastestorage")) {
        dir.mkdir("pastestorage");
      }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::titlegen(){
    srand (time(0));
    int seed = rand() % 1000+1;
    QString tmp;
    ui->FileTitle->setText("defaultitle"+tmp.setNum(seed));
}

//нужно добавить опцию new,и уже там генерировать новое название,а по умолчанию открывать последнюю,но это на потом

void MainWindow::on_SaveButton_clicked() //saving a new file
{
   QString text = ui->TextSpace->toPlainText();
   QString title = ui->FileTitle->text();
   QFile file("pastestorage/"+title+".txt"); //можно сделать выбор формата
   if (file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       QTextStream out(&file);
       out << text;
       file.close();
   }
   QMessageBox::information(this,"Info","Saved!");
}


void MainWindow::on_actionDelete_triggered()
{
    QString path = "pastestorage/" + ui->FileTitle->text() + ".txt";
    const char* cpath = 0;
    std::string spath = path.toStdString();
    cpath=spath.c_str();
    if(!remove(cpath)){
        QMessageBox::warning(this,"","File deleted!");
    }
    else QMessageBox::critical(this,"","No file with such title");
    ui->TextSpace->clear();
    titlegen();
}



void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory("pastestorage");
    dialog.setNameFilter("Text files (*.txt);;All files (*.*)");
    if (dialog.exec() == QDialog::Accepted) {
        QString filePath = dialog.selectedFiles().first();
        QFile file(filePath);
        QString text;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QFileInfo fileinfo(file);
            text = in.readAll();
            ui->TextSpace->setPlainText(text);
            ui->FileTitle->setText(fileinfo.completeBaseName());
            file.close();
        }
    }


}

