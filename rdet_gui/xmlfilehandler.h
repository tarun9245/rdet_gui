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
};

#endif // XMLFILEHANDLER_H
