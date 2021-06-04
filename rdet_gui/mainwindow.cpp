#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include "settings.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rdetPath = setting->getRdetPath();
//    ui->pushButtonSettings->setIcon(QIcon("C:/Users/tarkum/Downloads/GitProject/rdet_gui/rdet_gui/settings_png.png"));
//    ui->pushButtonSettings->setIconSize(QSize(50,50));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSettings_clicked()
{
    qDebug()<<"Inside void MainWindow::on_pushButtonSettings_clicked()";
    setting = new settings();
    setting->show();

    qDebug()<<"Exiting void MainWindow::on_pushButtonSettings_clicked()";
}

QString MainWindow::getDumpsPath()
{
    qDebug()<<"Inside QString MainWindow::getDumpsPath()";
    QString str = ui->lineEditDumpPath->text();
    qDebug()<<"Str = "<<str;

    qDebug()<<"Exiting QString MainWindow::getDumpsPath()";
    return str;
}

QString MainWindow::getMetaPath()
{
    qDebug()<<"Inside QString MainWindow::getMetaPath()";
    QString str = ui->lineEditMetaPath->text();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getMetaPath()";
    return str;
}

QString MainWindow::getAppsPath()
{
    qDebug()<<"Inside QString MainWindow::getAppsPath()";
    QString str = ui->lineEditAppsPath->text();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getAppsPath()";
    return str;
}

void MainWindow::runCommand(QString cmd)
{
    qDebug()<<"Inside void MainWindow::runCommand(QString cmd)";
    qDebug()<<"cmd to run = "<<cmd;
    system(cmd.toUtf8().data());
    system("pause>nil");
    qDebug()<<"Exiting void MainWindow::runCommand(QString cmd)";
}


QString MainWindow::rdetCmd()
{
    qDebug()<<"inside QString MainWindow::rdetCmd(QString metaPath, QString dumpsPath, QString appsPath, QString options)";
    QString cmd = "perl " + rdetPath + "\\rdet.pl " + dumpsPath + " " + metaPath;
    if(appsPath != "") {
        cmd += " --apps " + appsPath;
    }
    if(options != "") {
        cmd +=  " " + options;
    }

    qDebug()<<"rdet cmd is "<<cmd;

    qDebug()<<"inside QString MainWindow::rdetCmd(QString metaPath, QString dumpsPath, QString appsPath, QString options)";
    return cmd;
}

void MainWindow::on_pushButtonSubmit_clicked()
{
    qDebug()<<"Inside void MainWindow::on_pushButtonSubmit_clicked()";
    rdetPath = setting->getRdetPath();
    metaPath = ui->lineEditMetaPath->text();
    dumpsPath = ui->lineEditDumpPath->text();
    appsPath = ui->lineEditAppsPath->text();
    if(metaPath == "" || dumpsPath == "") {
        QMessageBox::warning(this,tr("Error"), tr("Dump or Meta location cannot be Empty!"));
        return;
    }
    QString cmd = rdetCmd();
    runCommand(cmd);
    qDebug()<<"Exiting void MainWindow::on_pushButtonSubmit_clicked()";
}
