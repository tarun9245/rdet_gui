#ifndef XMLFILEHANDLER_H
#define XMLFILEHANDLER_H
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDebug>

class xmlFileHandler
{
private:
    QDomDocument xml;
    QString targetName, appsBasePath,vmlinuxPath;
    QString tzPath,monFileName, monFilePath;
    QString hypFileName, hypFilePath;
    QString qseeFileName, qseeFilePath;
    QString rpmBasePath,rpmFileName, rpmFilePath;
    QString aopBasePath,aopFileName, aopFilePath;
    QString modemBasePath,modemFileName, modemFilePath;
    QString bootBasePath;
public:
    xmlFileHandler();
    int open(QString file);
    void extract();
    void extractAppsComponents(QDomElement &apps);
    void extractTzComponents(QDomElement &tz);
    void extractAopComponents(QDomElement &aop);
    void extractRpmComponents(QDomElement &rpm);
    void extractModemComponents(QDomElement &modem);
    void extractBootComponents(QDomElement &boot);
    void extractTargetName(QDomElement &target);
    QString pathMaker(QString input);

    /// Interface Functions ///
    QString getTargetName();
    QString getAppsBasePath();
    QString getVmlinuxPath();
    QString getTzBasePath();
    QString getMonFilePath();
    QString getMonFileName();
    QString getHypFileName();
    QString getHypFilePath();
    QString getQseeFileName();
    QString getQseeFilePath();
    QString getAopFileName();
    QString getAopFilePath();
    QString getRpmFileName();
    QString getRpmFilePath();


};

#endif // XMLFILEHANDLER_H
