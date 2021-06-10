#include "metahandler.h"
#include <qdebug.h>
#include <QFile>
#include <QMessageBox>

metaHandler::metaHandler()
{

}

metaHandler::metaHandler(QString metaPath)
{
    if(metaPath == "") {
        qDebug()<<"Error Meta Path can not be empty";
        return;
    }

    QFile contentFile(metaPath +"\\contents.xml");
    qDebug()<<"file path = "<<metaPath +"\\contents.xml";
    if(!contentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Unable to open the contents.xml file..";
        isValidMetaLocation = false;
        return;
    }
    QTextStream file (&contentFile);
    while(!file.atEnd()) {
        QString line = file.readLine();
        if( line.contains( "<chipset>" )) {
            chipset = stringTrimmer(line);
            break;
        }
    }
    while (!file.atEnd()) {
        QString line = file.readLine();
        if(line.contains("windows_root_path cmm_root_path_var=\"APPS_BUILDROOT\"")) {
            appsPath = stringTrimmer(line);
            break;
        }
    }
    while (!file.atEnd()) {
        QString line = file.readLine();
        if(line.contains("APPS_ELF")) {
            line = file.readLine();
            appsFileName = stringTrimmer(line);
            line = file.readLine();
            qDebug()<<"Line = "<<line;
            QString vmlinuxPath = pathMaker(stringTrimmer(line));
            appsPath += vmlinuxPath;
            break;
        }
    }
    while (!file.atEnd()) {
        QString line = file.readLine();
        if(line.contains("windows_root_path cmm_root_path_var=\"TZ_BUILDROOT\"")) {
            tzPath = stringTrimmer(line);
            break;
        }
    }
    while (!file.atEnd()) {
        QString line = file.readLine();

        if(line.contains("QSEE_ELF")) {
            line = file.readLine();
            qseeFileName = stringTrimmer(line);
            line = file.readLine();
            line = stringTrimmer(line);
            qseeFilePath = tzPath + pathMaker(line);
            continue;
        }
        if(line.contains("HYP_ELF")) {
            line = file.readLine();
            hypFileName = stringTrimmer(line);
            line = file.readLine();
            line = stringTrimmer(line);
            hypFilePath = tzPath + pathMaker(line);
            continue;
        }
        if(line.contains("MON_ELF")) {
            line = file.readLine();
            monFileName = stringTrimmer(line);
            line = file.readLine();
            line = stringTrimmer(line);
            monFilePath = tzPath + pathMaker(line);
            break;
        }
    }
    printAll();

}

QString metaHandler::getChipSet( )
{
    return chipset;
}

QString metaHandler::getAppsPath( )
{
     return appsPath;
}

QString metaHandler::getTzPath( )
{
    return tzPath;
}

QString metaHandler::getQseeFileName() {
    return qseeFileName;
}

QString metaHandler::getQseeFilePath() {
    return qseeFilePath;
}

QString metaHandler::getMonFileName() {
    return monFileName;
}

QString metaHandler::getMonFilePath() {
    return monFilePath;
}

QString metaHandler::getHypFileName() {
    return hypFileName;
}

QString metaHandler::getHypFilePath() {
    return hypFilePath;
}

QString metaHandler::getAopFileName() {
    return aopFileName;
}

QString metaHandler::getAopFilePath() {
    return aopFilePath;
}

QString metaHandler::getRpmFileName() {
    return rpmFileName;
}

QString metaHandler::getRpmFilePath() {
    return rpmFilePath;
}

QString metaHandler::stringTrimmer(QString input)
{
    qDebug()<<"Input String ="<<input;
    int startPos = input.indexOf('>') + 1;
    int endPos = input.lastIndexOf('<');
    int length = endPos - startPos;
    qDebug()<<"Output String = "<<input.mid(startPos, length);
    return input.mid(startPos, length);
}

QString metaHandler::pathMaker(QString inputPath)
{
    qDebug()<<"Inside QString metaHandler::pathMaker(QString inputPath)";
    QString path;
    QStringList temp = inputPath.split('/');
    for(int i=0;i<temp.size();i++) {
        QString str = temp.at(i);
        if(str != "") {
            if(str.contains(':')) {
                str = str.split(':').at(1);
                str.chop(1);
            }
            path += str + "\\";
        }
    }
    qDebug()<<"Path = "<<path;
    qDebug()<<"Exiting QString metaHandler::pathMaker(QString inputPath)";
    return path;
}

void metaHandler::printAll()
{
    qDebug()<<"Printing All.........";
    qDebug()<<"Chipset = "<<chipset;
    qDebug()<<"APPS path = "<<appsPath;
    qDebug()<<"Apps file name = "<<appsFileName;
    qDebug()<<"TZ Path = "<<tzPath;
    qDebug()<<"mon file name = "<<monFileName;
    qDebug()<<"mon file path = "<<monFilePath;
    qDebug()<<"hyp file name = "<<hypFileName;
    qDebug()<<"hyp file path = "<<hypFilePath;
    qDebug()<<"qsee file name = "<<qseeFileName;
    qDebug()<<"qsee file path = "<<qseeFilePath;
    qDebug()<<"AOP file name = "<<aopFileName;
    qDebug()<<"AOP file path = "<<aopFilePath;
    qDebug()<<"RPM file name = "<<rpmFileName;
    qDebug()<<"RPM file path = "<<rpmFilePath;

}

bool metaHandler::isValidMeta() {
    return isValidMetaLocation;
}
