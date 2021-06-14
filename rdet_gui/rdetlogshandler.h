#ifndef RDETLOGSHANDLER_H
#define RDETLOGSHANDLER_H
#include <QString>
#include<QFile>
#include <QTextStream>

class RdetLogsHandler
{
    QFile file;
public:
    RdetLogsHandler();
    RdetLogsHandler(QString filePath);
    void setLogFilePath(QString path);
    void insertLine(QString line);
    void insertFile(QString fileToCopy);
    void formatLogFile();
    void save();
};

#endif // RDETLOGSHANDLER_H
