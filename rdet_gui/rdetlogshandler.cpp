#include "rdetlogshandler.h"
#include <QDebug>
#include <QDateTime>
#include <QHostInfo>

RdetLogsHandler::RdetLogsHandler()
{

}

RdetLogsHandler::RdetLogsHandler(QString filePath)
{
    qDebug()<<"Inside RdetLogsHandler::RdetLogsHandler(QString filePath)";
    file.setFileName(filePath + "\\RDET_Logs.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug()<<"Unable to create RDET logs file at given loation. "<<file.fileName();
        return;
    }
    qDebug()<<"Exiting RdetLogsHandler::RdetLogsHandler(QString filePath)";
}

void RdetLogsHandler:: setLogFilePath(QString path)
{
    qDebug()<<"Inside void RdetLogsHandler:: setLogFilePath(QString path)";
    file.setFileName(path + "\\RDET_Logs.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug()<<"Unable to create RDET logs file at given loation. "<<file.fileName();
        return;
    }
    qDebug()<<"Exiting void RdetLogsHandler:: setLogFilePath(QString path)";
}

void RdetLogsHandler::save()
{
    insertLine("\n===== END RDET Logs ====\n");

    file.close();
}

void RdetLogsHandler::insertLine(QString line)
{
    qDebug()<<"Inside void RdetLogsHandler::insertLine(QString line)";
    QTextStream out(&file);
    out<<line<<endl;
    qDebug()<<"Exiting void RdetLogsHandler::insertLine(QString line)";
}

void RdetLogsHandler::insertFile(QString fileToCopy)
{
    qDebug()<<"Inside void RdetLogsHandler::insertFile(QString fileToCopy)";
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
    qDebug()<<"Exiting void RdetLogsHandler::insertFile(QString fileToCopy)";
}

void RdetLogsHandler::formatLogFile()
{
    qDebug()<<"Inside void RdetLogsHandler::formatLogFile()";
    QTextStream out(&file);
    out<<"\n====== Begin RDET Logs =====\n";
    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();
    QString host = QHostInfo::localHostName();
    qDebug()<<"Host Name: "<<host<<endl;
    qDebug()<<"today date is "<<date<<" and time is "<<time;
    out<<"Starting RDET at "<<time<<" on "<<date<<endl;
    out<<"Host Name: "<<host<<endl;
    qDebug()<<"Exiting void RdetLogsHandler::formatLogFile()";
}
