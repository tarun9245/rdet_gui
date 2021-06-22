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

    qDebug()<<"root of document = "<<root.tagName();

    QDomElement comp = root.firstChild().toElement();

    while (!comp.isNull()) {
        qDebug()<<"loop "<<comp.tagName();
        if(comp.tagName() == "builds_flat") {
            break;
        }
        comp = comp.nextSibling().toElement();
    }
    QDomElement build = comp.firstChild().toElement();
    int i = 1;
    while (!build.isNull()) {
        qDebug()<<"itr = "<<i++;
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
        }
        build = build.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extract()");
}

void xmlFileHandler::extractAppsComponents(QDomElement &apps) {
    qDebug("Inside void xmlFileHandler::extractAppsComponents(QDomElement &apps)");
    while (!apps.isNull()) {
//        qDebug()<<"tagName = "<<apps.tagName();
//        qDebug()<<"text in tag = "<<apps.text();
        if(apps.tagName() == "windows_root_path") {
            qDebug()<<"APPS Path = "<<apps.text();
        }else if(apps.tagName() == "file_ref" && apps.attribute("cmm_file_var") == "APPS_ELF") {
            QDomElement child = apps.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
                child = child.nextSibling().toElement();
            }
        }
        apps = apps.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractAppsComponents(QDomElement &apps)");
}

void xmlFileHandler::extractTzComponents(QDomElement &tz) {
    qDebug("Inside void xmlFileHandler::extractTzComponents(QDomElement &tz)");
    while (!tz.isNull()) {
        if(tz.tagName() == "windows_root_path") {
            qDebug()<<"TZ Path = "<<tz.text();
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "QSEE_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
                child = child.nextSibling().toElement();
            }
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "HYP_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
                child = child.nextSibling().toElement();
            }
        }else if(tz.tagName() == "file_ref" && tz.attribute("cmm_file_var") == "MON_ELF") {
            QDomElement child = tz.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
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
            qDebug()<<"AOP Path = "<<aop.text();
        }else if(aop.tagName() == "file_ref" && aop.attribute("cmm_file_var") == "AOP_ELF") {
            QDomElement child = aop.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
                child = child.nextSibling().toElement();
            }
        }
        aop = aop.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractAopComponents(QDomElement &aop)");

}

void xmlFileHandler::extractRpmComponents(QDomElement &rpm) {
    qDebug("Inside void xmlFileHandler::extractRpmComponents(QDomElement &rpm)");
    while (!rpm.isNull()) {
        if(rpm.tagName() == "windows_root_path") {
            qDebug()<<"RPM Path = "<<rpm.text();
        }else if(rpm.tagName() == "file_ref" && rpm.attribute("cmm_file_var") == "RPM_ELF") {
            QDomElement child = rpm.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
                child = child.nextSibling().toElement();
            }
        }
        rpm = rpm.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractRpmComponents(QDomElement &rpm)");
}
