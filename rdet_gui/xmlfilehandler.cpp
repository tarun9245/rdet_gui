#include "xmlfilehandler.h"

xmlFileHandler::xmlFileHandler()
{

}

int xmlFileHandler::open(QString file) {
    qDebug("Inside int xmlFileHandler::open(QString file)");
    if(file == "") {
        qDebug()<<"Error Meta Path can not be empty";
        return false;
    }

    QFile contentFile(file);
    qDebug()<<"file path = "<<file;
    if(!contentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Unable to open the contents.xml file..";
        return false;
    }
    xml.setContent(&contentFile);
    contentFile.close();
    return true;
    qDebug("Exiting int xmlFileHandler::open(QString file)");
}

void xmlFileHandler::extract() {
    qDebug("Inside void xmlFileHandler::extract()");
    QDomElement root = xml.documentElement();

//    qDebug()<<"root of document = "<<root.tagName();

    QDomElement comp = root.firstChild().toElement();

    while (!comp.isNull()) {
//        qDebug()<<"loop "<<comp.tagName();
        if(comp.tagName() == "product_info") {
            QDomElement child = comp.firstChild().toElement();
            extractTargetName(child);
        }
        if(comp.tagName() == "builds_flat") {
            break;
        }
        comp = comp.nextSibling().toElement();
    }
    QDomElement build = comp.firstChild().toElement();
    while (!build.isNull()) {
//        qDebug()<<build.tagName();
        QDomElement names = build.firstChild().toElement();
        if(names.text() == "apps") {
            extractAppsComponents(names);
        }else if(names.text() == "tz") {
            extractTzComponents(names);
        }else if(names.text() == "aop") {
            extractAopComponents(names);
        }else if(names.text() == "rpm") {
            extractRpmComponents(names);
        }else if(names.text() == "boot") {
            extractBootComponents(names);
        }else if(names.text() == "modem") {
            extractModemComponents(names);
        }
        build = build.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extract()");
}

void xmlFileHandler::extractAppsComponents(QDomElement &apps) {
    qDebug("Inside void xmlFileHandler::extractAppsComponents(QDomElement &apps)");
    while (!apps.isNull()) {
        if(apps.tagName() == "windows_root_path") {
            appsBasePath = apps.text();
            qDebug()<<"APPS Path = "<<appsBasePath;
        }else if(apps.tagName() == "file_ref" && apps.attribute("cmm_file_var") == "APPS_ELF") {
            QDomElement child = apps.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    qDebug()<<"File Name = "<<child.text();
                }
                else if(child.tagName() == "file_path") {
                    vmlinuxPath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<vmlinuxPath;
                }
                child = child.nextSibling().toElement();
            }
            break;
        }
        apps = apps.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractAppsComponents(QDomElement &apps)");
}

void xmlFileHandler::extractTzComponents(QDomElement &tz) {
    qDebug("Inside void xmlFileHandler::extractTzComponents(QDomElement &tz)");
    while (!tz.isNull()) {
        if(tz.tagName() == "windows_root_path") {
            tzPath = tz.text();
            qDebug()<<"TZ Path = "<<tzPath;
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "QSEE_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    qseeFileName = child.text();
                    qDebug()<<"File Name = "<<qseeFileName;
                }
                else if(child.tagName() == "file_path") {
                    qseeFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<qseeFilePath;
                }
                child = child.nextSibling().toElement();
            }
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "HYP_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    hypFileName = child.text();
                    qDebug()<<"File Name = "<<hypFileName;
                }
                else if(child.tagName() == "file_path") {
                    hypFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<hypFilePath;
                }
                child = child.nextSibling().toElement();
            }
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "MON_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    monFileName = child.text();
                    qDebug()<<"File Name = "<<monFileName;
                }
                else if(child.tagName() == "file_path") {
                    monFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<monFilePath;
                }
                child = child.nextSibling().toElement();
            }
        }
        tz = tz.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractTzComponents(QDomElement &tz)");
}

void xmlFileHandler::extractAopComponents(QDomElement &aop) {
    qDebug("Inside void xmlFileHandler::extractAopComponents(QDomElement &aop)");
    while (!aop.isNull()) {
        if(aop.tagName() == "windows_root_path") {
            aopBasePath = aop.text();
            qDebug()<<"AOP Path = "<<aopBasePath;
        }else if(aop.tagName() == "file_ref" && aop.attribute("cmm_file_var") == "AOP_ELF") {
            QDomElement child = aop.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    aopFileName = child.text();
                    qDebug()<<"File Name = "<<aopFileName;
                }
                else if(child.tagName() == "file_path") {
                    aopFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<aopFilePath;
                }
                child = child.nextSibling().toElement();
            }
            break;
        }
        aop = aop.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractAopComponents(QDomElement &aop)");

}

void xmlFileHandler::extractRpmComponents(QDomElement &rpm) {
    qDebug("Inside void xmlFileHandler::extractRpmComponents(QDomElement &rpm)");
    while (!rpm.isNull()) {
        if(rpm.tagName() == "windows_root_path") {
            rpmBasePath = rpm.text();
            qDebug()<<"RPM Path = "<<rpmBasePath;
        }else if(rpm.tagName() == "file_ref" && rpm.attribute("cmm_file_var") == "RPM_ELF") {
            QDomElement child = rpm.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    rpmFileName = pathMaker(child.text());
                    qDebug()<<"File Name = "<<rpmFileName;
                }
                else if(child.tagName() == "file_path") {
                    rpmFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<rpmFilePath;
                }
                child = child.nextSibling().toElement();
            }
            break;
        }
        rpm = rpm.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractRpmComponents(QDomElement &rpm)");
}

void xmlFileHandler::extractBootComponents(QDomElement &boot) {
    qDebug("Inside void xmlFileHandler::extractBootComponents(QDomElement &boot)");
    while (!boot.isNull()) {
        if(boot.tagName() == "windows_root_path") {
            bootBasePath = boot.text();
            qDebug()<<"BOOT Path = "<<bootBasePath;
            break;
        }
        boot = boot.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractBootComponents(QDomElement &boot)");
}

void xmlFileHandler::extractModemComponents(QDomElement &modem) {
    qDebug("Inside void xmlFileHandler::extractModemComponents(QDomElement &modem)");
    while (!modem.isNull()) {
        if(modem.tagName() == "windows_root_path") {
            modemBasePath = modem.text();
            qDebug()<<"Modem Path = "<<modemBasePath;
        }else if(modem.tagName() == "file_ref" && modem.attribute("cmm_file_var") == "ORIG_MPSSPROC_ELF") {
            QDomElement child = modem.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name") {
                    modemFileName = child.text();
                    qDebug()<<"File Name = "<<modemFileName;
                }
                else if(child.tagName() == "file_path") {
                    modemFilePath = pathMaker(child.text());
                    qDebug()<<"File Path = "<<modemFilePath;
                }
                child = child.nextSibling().toElement();
            }
            break;
        }
        modem = modem.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractModemComponents(QDomElement &modem)");
}

void xmlFileHandler::extractTargetName(QDomElement &target) {
    qDebug("Inside void xmlFileHandler::extractTargetName(QDomElement target)");
    while(!target.isNull()) {
        if(target.tagName() == "chipid" && target.attribute("cmm_var") == "CHIPID") {
            targetName = target.text();
            qDebug()<<"Target Name = "<<targetName;
            break;
        }
        target = target.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractTargetName(QDomElement target)");
}

QString xmlFileHandler::pathMaker(QString input)
{
    qDebug()<<"Inside QString metaHandler::pathMaker(QString inputPath)";
    QString path;
    QStringList temp = input.split('/');
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

//============================= Interface =====================================
QString xmlFileHandler::getTargetName() {
    return targetName;
}

QString xmlFileHandler::getAppsBasePath() {
    return appsBasePath;
}

QString xmlFileHandler::getVmlinuxPath() {
    return vmlinuxPath;
}

QString xmlFileHandler::getTzBasePath() {
    return tzPath;
}

QString xmlFileHandler::getMonFileName() {
    return monFileName;
}

QString xmlFileHandler::getMonFilePath() {
    return monFilePath;
}

QString xmlFileHandler::getHypFileName() {
    return hypFileName;
}

QString xmlFileHandler::getHypFilePath() {
    return hypFilePath;
}

QString xmlFileHandler::getQseeFileName() {
    return qseeFileName;
}

QString xmlFileHandler::getQseeFilePath() {
    return qseeFilePath;
}

QString xmlFileHandler::getAopFileName() {
    return aopFileName;
}

QString xmlFileHandler::getAopFilePath() {
    return aopFilePath;
}

QString xmlFileHandler::getRpmFileName() {
    return rpmFileName;
}

QString xmlFileHandler::getRpmFilePath() {
    return rpmFilePath;
}
