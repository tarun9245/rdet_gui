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
            qDebug()<<"BOOT Path = "<<boot.text();
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
            qDebug()<<"Modem Path = "<<modem.text();
        }else if(modem.tagName() == "file_ref" && modem.attribute("cmm_file_var") == "ORIG_MPSSPROC_ELF") {
            QDomElement child = modem.firstChild().toElement();
            while(!child.isNull()) {
                if(child.tagName() == "file_name")
                    qDebug()<<"File Name = "<<child.text();
                else if(child.tagName() == "file_path")
                    qDebug()<<"File Path = "<<child.text();
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
            qDebug()<<"Target Name = "<<target.text();
        }
        target = target.nextSibling().toElement();
    }
    qDebug("Exiting void xmlFileHandler::extractTargetName(QDomElement target)");
}


//============================= Interface =====================================
