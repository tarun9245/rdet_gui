#ifndef METAHANDLER_H
#define METAHANDLER_H
#include <QString>
#include <QFile>

class metaHandler
{

private:
    QString appsFileName,qseeFileName,monFileName,hypFileName,aopFileName,rpmFileName;
    QString chipset,appsPath,tzPath,aopFilePath,rpmFilePath, monFilePath,hypFilePath,qseeFilePath;
    bool isValidMetaLocation = true;
public:
    metaHandler();
    metaHandler(QString);
    QString getChipSet();
    QString getAppsPath();
    QString getTzPath();
    QString getMonFilePath();
    QString getMonFileName();
    QString getQseeFileName();
    QString getQseeFilePath();
    QString getHypFileName();
    QString getHypFilePath();
    QString getAopFileName();
    QString getAopFilePath();
    QString getRpmFileName();
    QString getRpmFilePath();
    QString stringTrimmer(QString);
    QString pathMaker(QString inputPath);
    void printAll();
    bool isValidMeta();

};

#endif // METAHANDLER_H
