#include "settings.h"
#include "ui_settings.h"
#include "qdebug.h"
#include <qfile.h>

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->lineEdit->clear();
    ui->lineEdit->setText(getRdetPath());
}

settings::~settings()
{
    delete ui;
}


void settings::setRdetPath(QString path)
{
    qDebug()<<"Inside void settings::setRdetPath(QString path)";
    qDebug()<<"RDET Path ="<<path;
    QFile file("rdetPath.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"unable to Open/Create file";
        return;
    }
    QTextStream out(&file);
    out << path;
    file.close();
    qDebug()<<"Exiting void rdetSelection::setRdetPath(QString path)";
}

QString settings::getRdetPath()
{
    QString path = "";
    qDebug()<<"Inside QString settings::getRdetPath()";
    QFile file("rdetPath.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Unable to open the rdetPath file.";
    }
    else {
        QTextStream in(&file);
        path = in.readLine();
        qDebug()<<"RDET Path = "<<path;
    }
    file.close();
    qDebug()<<"Exiting QString settings::getRdetPath()";
    return path;
}

void settings::on_pushButton_clicked()
{
    qDebug()<<"Inside void settings::on_pushButton_clicked()";
    QString path = ui->lineEdit->text();
    if(path != "")
    {
        qDebug()<<"path = "<<path;
        setRdetPath(path);
    }
    this->close();
    qDebug()<<"Exiting void settings::on_pushButton_clicked()";
}
