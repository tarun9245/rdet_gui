#include "rdetlogshandler.h"
#include <QDebug>
#include <QDateTime>
#include <QHostInfo>

RdetLogsHandler::RdetLogsHandler()
{

}

RdetLogsHandler::RdetLogsHandler(QString filePath)
{
    file.setFileName(filePath + "\\RDET_Logs.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug()<<"Unable to create RDET logs file at given loation. "<<file.fileName();
        return;
    }
}

void RdetLogsHandler:: setLogFilePath(QString path)
{
    file.setFileName(path + "\\RDET_Logs.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug()<<"Unable to create RDET logs file at given loation. "<<file.fileName();
        return;
    }
}

void RdetLogsHandler::save()
{
    file.close();
}

void RdetLogsHandler::insertLine(QString line)
{
    QTextStream out(&file);
    out<<line<<endl;
}

void RdetLogsHandler::insertFile(QString fileToCopy)
{
    QTextStream out(&file);
    QFile temp(fileToCopy);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Unable to open given file. "<<temp.fileName();
        return;
    }
    QTextStream read(&temp);
    while(!read.atEnd()) {
        QString line = read.readLine();
        out<<line<<endl;
    }

}

void RdetLogsHandler::formatLogFile()
{
    QTextStream out(&file);
    out<<"\n======Begin RDET Logs=====\n";
    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();
    QString host = QHostInfo::localHostName();
    qDebug()<<"Host Name: "<<host<<endl;
    qDebug()<<"today date is "<<date<<" and time is "<<time;
    out<<"Starting RDET at "<<time<<" on "<<date<<endl;
    out<<"Host Name: "<<host<<endl;
}
