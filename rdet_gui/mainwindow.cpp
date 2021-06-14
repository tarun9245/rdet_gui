#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include "settings.h"
#include <QMessageBox>
#include "metahandler.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include "rdetlogshandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rdetPath = setting->getRdetPath();
    on_checkBox_ramparser_stateChanged(0);
//    ui->pushButtonSettings->setIcon(QIcon("C:/Users/tarkum/Downloads/GitProject/rdet_gui/rdet_gui/settings_png.png"));
//    ui->pushButtonSettings->setIconSize(QSize(50,50));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSettings_clicked()
{
    qDebug()<<"Inside void MainWindow::on_pushButtonSettings_clicked()";
    setting = new settings();
    setting->show();

    qDebug()<<"Exiting void MainWindow::on_pushButtonSettings_clicked()";
}

QString MainWindow::getDumpsPath()
{
    qDebug()<<"Inside QString MainWindow::getDumpsPath()";
    QString str = ui->lineEditDumpPath->text().trimmed();
    qDebug()<<"Str = "<<str;

    qDebug()<<"Exiting QString MainWindow::getDumpsPath()";
    return str;
}

QString MainWindow::getMetaPath()
{
    qDebug()<<"Inside QString MainWindow::getMetaPath()";
    QString str = ui->lineEditMetaPath->text().trimmed();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getMetaPath()";
    return str;
}

QString MainWindow::getAppsPath()
{
    qDebug()<<"Inside QString MainWindow::getAppsPath()";
    QString str = ui->lineEditAppsPath->text().trimmed();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getAppsPath()";
    return str;
}

void MainWindow::runCommand(QString cmd)
{
    qDebug()<<"Inside void MainWindow::runCommand(QString cmd)";
    logHandler.insertLine("\n\nExecuting the subscript with command " +cmd);
    cmd += " > log.txt";
    qDebug()<<"cmd to run = "<<cmd;
    system(cmd.toUtf8().data());
    logHandler.insertFile("log.txt");
    qDebug()<<"Exiting void MainWindow::runCommand(QString cmd)";
}


QString MainWindow::rdetCmd()
{
    qDebug()<<"inside QString MainWindow::rdetCmd(QString metaPath, QString dumpsPath, QString appsPath, QString options)";
    QString cmd = "perl " + rdetPath + "\\rdet.pl " + dumpsPath + " " + metaPath;
    if(appsPath != "") {
        cmd += " --apps " + appsPath;
    }
    if(options != "") {
        cmd +=  " " + options;
    }

    qDebug()<<"rdet cmd is "<<cmd;

    qDebug()<<"inside QString MainWindow::rdetCmd(QString metaPath, QString dumpsPath, QString appsPath, QString options)";
    return cmd;
}

void MainWindow::readingMeta()
{
    metaHandler meta(metaPath);
    if(!meta.isValidMeta()) {
        QMessageBox::warning(this,tr("Error"), tr("Unable to open contents.xml file at given META location.."));
        return;
    }
    if(appsPath == "") {
        qDebug()<<"Using APPS symbol from Meta.";
        appsPath = meta.getAppsPath();
    }else {
        if(appsPath.at(appsPath.length() - 1) != '\\') {
            appsPath += "\\";
        }
    }
    targetName = meta.getChipSet();
    qseeFileName = meta.getQseeFileName();
    qseeFilePath = meta.getQseeFilePath();
    monFileName = meta.getMonFileName();
    monFilePath = meta.getMonFilePath();
    hypFileName = meta.getHypFileName();
    hypFilePath = meta.getHypFilePath();
    aopFileName = meta.getAopFileName();
    aopFilePath = meta.getAopFilePath();
    rpmFileName = meta.getRpmFileName();
    rpmFilePath = meta.getRpmFilePath();
}

void MainWindow::on_pushButtonSubmit_clicked()
{
    qDebug()<<"Inside void MainWindow::on_pushButtonSubmit_clicked()";
    rdetPath = setting->getRdetPath();
    metaPath = ui->lineEditMetaPath->text().trimmed();
    dumpsPath = ui->lineEditDumpPath->text().trimmed();
    appsPath = ui->lineEditAppsPath->text().trimmed();
    outputPath = dumpsPath;
    if(metaPath == "" || dumpsPath == "") {
        QMessageBox::warning(this,tr("Error"), tr("Dump or Meta location cannot be Empty!"));
        return;
    }

    readingMeta();
    updatingMetaInfoToLogsFile();
    runSubScripts();
    logHandler.save();
    qDebug()<<"Exiting void MainWindow::on_pushButtonSubmit_clicked()";
}

void MainWindow::updatingMetaInfoToLogsFile()
{
    logHandler.setLogFilePath(outputPath);
    logHandler.formatLogFile();
    logHandler.insertLine("Input RAM dump directory: " + dumpsPath);
    logHandler.insertLine("Output directory: " + outputPath);
    logHandler.insertLine("META Build Location: " + metaPath);
    logHandler.insertLine("Chip Name: " +targetName);
    logHandler.insertLine("APPS Path: " + appsPath);
    if(qseeFileName != "") {
        logHandler.insertLine("QSEE ELF: " + qseeFilePath + qseeFileName);
    }
    if(monFileName != "")
        logHandler.insertLine("MON ELF: "+ monFilePath + monFileName);
    if(hypFileName != "")
        logHandler.insertLine("HYP ELF: " + hypFilePath + hypFileName);
    if(aopFileName != "")
        logHandler.insertLine("AOP Path: " +aopFilePath + aopFileName);
    if(rpmFileName != "")
        logHandler.insertLine("RPM Path: " +rpmFilePath + rpmFileName);
    logHandler.insertLine("");
    logHandler.insertLine("");
}

void MainWindow::runSubScripts()
{
    QString cmd;
    QString hardware = getHardwareName(targetName);
    if(hardware == "") {
        QString msg = targetName + " Target Support is Not added to RDET.";
        QMessageBox::warning(this,tr("Error"), tr(msg.toUtf8().constData()));
        return;
    }

    if(ui->checkBox_module_symbol->checkState() == Qt::Checked) {
        cmd = module_symbolCmd();
        runCommand(cmd);
    }
    if(ui->checkBox_ramparser->checkState() == Qt::Checked) {
        cmd = ramparserCmd(hardware);
        runCommand(cmd);
    }
    if(ui->checkBox_ramparser_svm->checkState() == Qt::Checked) {
        //cmd = ramparser_svmCmd();
        //runCommand(cmd);
    }
    if(ui->checkBox_dcc_wrapper->checkState() == Qt::Checked) {
        cmd = dcc_wrapperCmd();
        runCommand(cmd);
    }
    if(ui->checkBox_task_stats->checkState() == Qt::Checked) {
        cmd = task_statsCmd();
        runCommand(cmd);
    }
    if(ui->checkBox_DDRCookies->checkState() == Qt::Checked) {
        cmd = ddrCookiesCmd();
        runCommand(cmd);
    }
    if(ui->checkBox_read_power_collapse_cnt->checkState() == Qt::Checked) {
        runCommand(cmd);
    }
    if(ui->checkBox_excessive_logging->checkState() == Qt::Checked) {
        cmd = excessive_loggingCmd();
        runCommand(cmd);
    }
    if(ui->checkBox_Rdet_attachment->checkState() == Qt::Checked) {
        cmd = rdet_html_genCmd();
        runCommand(cmd);
    }
}

void MainWindow::on_checkBox_ramparser_stateChanged(int arg1)
{
    qDebug()<<"Inside void MainWindow::on_checkBox_ramparser_stateChanged(int arg1)";
    qDebug()<<"arg1 = "<<arg1;
    ui->checkBox_parse_debug_image->setEnabled(arg1);
    ui->checkBox_wdog->setEnabled(arg1);
    ui->checkBox_qtf->setEnabled(arg1);
    ui->checkBox_slabsummary->setEnabled(arg1);
    ui->checkBox_print_ionbuffer->setEnabled(arg1);
    ui->checkBox_print_pagetypeinfo->setEnabled(arg1);
    ui->checkBox_print_memory_info->setEnabled(arg1);
    ui->checkBox_print_pagetracking->setEnabled(arg1);
    ui->checkBox_print_memstat->setEnabled(arg1);
    ui->checkBox_print_lsof->setEnabled(arg1);
    ui->checkBox_slabinfo->setEnabled(arg1);
    ui->checkBox_cpr3_info->setEnabled(arg1);
    ui->checkBox_print_vmalloc->setEnabled(arg1);
    ui->checkBox_dtb->setEnabled(arg1);
    ui->checkBox_print_tasks->setEnabled(arg1);
    ui->checkBox_dump_ftrace->setEnabled(arg1);
    ui->checkBox_sched_info->setEnabled(arg1);
    ui->checkBox_print_irqs->setEnabled(arg1);
    ui->checkBox_print_workqueues->setEnabled(arg1);
    ui->checkBox_print_kconfig->setEnabled(arg1);
    ui->checkBox_print_rtb->setEnabled(arg1);
    ui->checkBox_timer_list->setEnabled(arg1);
    ui->checkBox_print_tasks_timestamps->setEnabled(arg1);
    ui->checkBox_print_runqueues->setEnabled(arg1);
    ui->checkBox_print_softirq_stat->setEnabled(arg1);
    ui->checkBox_print_iommu_pg_tables->setEnabled(arg1);
    ui->checkBox_print_filetracking->setEnabled(arg1);
    ui->checkBox_logcat->setEnabled(arg1);
    qDebug()<<"Exiting void MainWindow::on_checkBox_ramparser_stateChanged(int arg1)";
}

QString MainWindow::ramparserCmd(QString hardware)
{
    qDebug()<<"Inside QString MainWindow::ramparserCmd()";
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\ramparse\\ramparse_handler.py --vmlinux ";
    cmd += appsPath + "vmlinux" + " --auto-dump " + dumpsPath;
    cmd += " --force-hardware " + hardware;
    cmd += " --dmesg --t32launcher --ddr-compare --clock-dump --check-for-panic --print-reserved-mem";
    cmd += " --lpm --regulator --ipc_logging --ipa --hotplug --kbootlog --wakeup";

    if(ui->checkBox_parse_debug_image->checkState() == Qt::Checked)
        cmd += " --parse-debug-image";
    if(ui->checkBox_wdog->checkState() == Qt::Checked)
        cmd += " --watchdog";
    if(ui->checkBox_qtf->checkState() == Qt::Checked)
        cmd += " --qtf";
    if(ui->checkBox_slabsummary->checkState() == Qt::Checked)
        cmd += " --slabsummary";
    if(ui->checkBox_print_ionbuffer->checkState() == Qt::Checked)
        cmd += " --print-ionbuffer";
    if(ui->checkBox_print_pagetypeinfo->checkState() == Qt::Checked)
        cmd += " --print-pagetypeinfo";
    if(ui->checkBox_print_memory_info->checkState() == Qt::Checked)
        cmd += " --print-memory-info";
    if(ui->checkBox_print_pagetracking->checkState() == Qt::Checked)
        cmd += " --print-pagetracking";
    if(ui->checkBox_print_memstat->checkState() == Qt::Checked)
        cmd += " --print-memstat";
    if(ui->checkBox_print_lsof->checkState() == Qt::Checked)
        cmd += " --print-lsof";
    if(ui->checkBox_slabinfo->checkState() == Qt::Checked)
        cmd += " --slabinfo";
    if(ui->checkBox_cpr3_info->checkState() == Qt::Checked)
        cmd += " --cpr3-info";
    if(ui->checkBox_print_vmalloc->checkState() == Qt::Checked)
        cmd += " --print-vmalloc";
    if(ui->checkBox_dtb->checkState() == Qt::Checked)
        cmd += " --dtb";
    if(ui->checkBox_print_tasks->checkState() == Qt::Checked)
        cmd += " --print-tasks";
    if(ui->checkBox_dump_ftrace->checkState() == Qt::Checked)
        cmd += " --dump-ftrace";
    if(ui->checkBox_sched_info->checkState() == Qt::Checked)
        cmd += " --sched-info";
    if(ui->checkBox_print_irqs->checkState() == Qt::Checked)
        cmd += " --print-irqs";
    if(ui->checkBox_print_workqueues->checkState() == Qt::Checked)
        cmd += " --print-workqueues";
    if(ui->checkBox_print_kconfig->checkState() == Qt::Checked)
        cmd += " --print-kconfig";
    if(ui->checkBox_print_rtb->checkState() == Qt::Checked)
        cmd += " --print-rtb";
    if(ui->checkBox_timer_list->checkState() == Qt::Checked)
        cmd += " --timer-list";
    if(ui->checkBox_print_tasks_timestamps->checkState() == Qt::Checked)
        cmd += " --print-tasks-timestamps";
    if(ui->checkBox_print_runqueues->checkState() == Qt::Checked)
        cmd += " --print-runqueues";
    if(ui->checkBox_print_softirq_stat->checkState() == Qt::Checked)
        cmd += " --print-softirq-stat";
    if(ui->checkBox_print_iommu_pg_tables->checkState() == Qt::Checked)
        cmd += " --print-iommu-pg-tables";
    if(ui->checkBox_print_filetracking->checkState() == Qt::Checked)
        cmd += " --print-filetracking";
    if(ui->checkBox_logcat->checkState() == Qt::Checked)
        cmd += " --logcat";

    cmd += " -o " + outputPath;
    if(hypFileName != "") {
        cmd += " --hyp " + hypFilePath + hypFileName;
    }
    qDebug()<<"ramparser cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ramparserCmd()";
    return cmd;
}

QString MainWindow::module_symbolCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\module_symbol\\module_symbol.py ";
    qDebug()<<"Inside QString MainWindow::module_symbolCmd()";
    cmd += dumpsPath + " " + appsPath + "vmlinux --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::module_symbolCmd()";
    return cmd;
}

QString MainWindow::platform_infoCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\platform_info\\platform_info.py ";
    qDebug()<<"Inside QString MainWindow::platform_infoCmd()";
    cmd += dumpsPath + " -o " + outputPath + " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::platform_infoCmd()";
    return cmd;
}

QString MainWindow::dcc_wrapperCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\dcc_parser\\dcc_wrapper.py ";
    qDebug()<<"Inside QString MainWindow::dcc_wrapperCmd()";
    cmd += dumpsPath + " --target " + targetName + " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::dcc_wrapperCmd()";
    return cmd;
}

QString MainWindow::task_statsCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\task_stats\\task_stats.py ";
    qDebug()<<"Inside QString MainWindow::task_statsCmd()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::task_statsCmd()";
    return cmd;
}

QString MainWindow::ddrCookiesCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\DDRCookies\\DDRCookies.py ";
    qDebug()<<"Inside QString MainWindow::ddrCookiesCmd()";
    cmd += dumpsPath + " --output " + outputPath;
    cmd += " -- target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ddrCookiesCmd()";
    return cmd;
}

QString MainWindow::excessive_loggingCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\excessive_logging\\excessive_log_detection.py ";
    qDebug()<<"Inside QString MainWindow::excessive_loggingCmd()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::excessive_loggingCmd()";
    return cmd;
}

QString MainWindow::rdet_html_genCmd()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\rdet_html_gen\\rdet_html_gen.py ";
    qDebug()<<"Inside QString MainWindow::rdet_html_genCmd()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::rdet_html_genCmd()";
    return cmd;
}

QString MainWindow::getHardwareName(QString targetName)
{
    QString filePath = rdetPath + "\\lib\\common_subscripts\\cafname\\caf.json";
    QString hwName;
    qDebug()<<"Inside QString MainWindow::getHardwareName()";

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"unable to open caf.json file. path = "<<filePath;
        return hwName;
    }
    QString temp = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(temp.toUtf8());
//    qDebug()<<doc;
    QJsonObject obj = doc.object();
    hwName = obj.value(targetName.toLower()).toString();
    qDebug()<<"Value = "<<hwName;
    qDebug()<<"Exiting QString MainWindow::getHardwareName()";
    return hwName;
}
