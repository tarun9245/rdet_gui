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
    cmd += " > ";
    cmd += outputPath + "\\temp.txt";
    qDebug()<<"cmd to run = "<<cmd;
    system(cmd.toUtf8().data());
    logHandler.insertFile(outputPath + "\\temp.txt");
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
    tzPath = meta.getTzPath();
    //aopDir = meta.getAopDir();
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
    qDebug()<<"Inside void MainWindow::updatingMetaInfoToLogsFile()";
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
    qDebug()<<"Exiting void MainWindow::updatingMetaInfoToLogsFile()";
}

void MainWindow::runSubScripts()
{
    qDebug()<<"Inside void MainWindow::runSubScripts()";
    QString cmd;
    hardware = getHardwareName(targetName);
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
    qDebug()<<"Exiting void MainWindow::runSubScripts()";
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

QString MainWindow::read_power_collapse_cnt()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\read_power_collapse_cnt\\read_power_collapse_cnt.py ";
    qDebug()<<"Inside QString MainWindow::read_power_collapse_cnt()";
    cmd += dumpsPath + " --tz " + tzPath;
    cmd += " --target " + targetName;
    cmd += " --outdir " + outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::read_power_collapse_cnt()";
    return cmd;
}

QString MainWindow::tme_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\tme_parser\\tme_parser.py ";
    qDebug()<<"Inside QString MainWindow::tme_parser()";
    cmd += "-a " + dumpsPath + " --meta " + metaPath;
    cmd += " --everything -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::tme_parser()";
    return cmd;
}

QString MainWindow::tme_debugging()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\tme_parser\\tme_debugging.py ";
    qDebug()<<"Inside QString MainWindow::tme_debugging()";
    cmd += dumpsPath + " -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::tme_debugging()";
    return cmd;
}

QString MainWindow::scandump_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\scandump\\scandump_parser_helper.py ";
    qDebug()<<"Inside QString MainWindow::scandump_parser()";
    cmd += dumpsPath + " -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::scandump_parser()";
    return cmd;
}

QString MainWindow::instr_fetcher()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\instr_fetcher\\instr_fetcher.py ";
    qDebug()<<"Inside QString MainWindow::instr_fetcher()";
    cmd += dumpsPath + " --o " + outputPath;
    cmd += " " + qseeFilePath + qseeFileName;
    cmd += " " + monFilePath + monFileName;
    cmd += " " + hypFilePath + hypFileName;
    cmd += " " + appsPath + "\\vmlinux";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::instr_fetcher()";
    return cmd;
}

QString MainWindow::bus_error_decoder()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\bus_error_decoder.py ";
    qDebug()<<"Inside QString MainWindow::bus_error_decoder()";
    cmd += dumpsPath + " --o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::bus_error_decoder()";
    return cmd;
}

QString MainWindow::smmu_fault_decoder()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\smmu_fault_decoder.py ";
    qDebug()<<"Inside QString MainWindow::smmu_fault_decoder()";
    cmd += outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::smmu_fault_decoder()";
    return cmd;
}

QString MainWindow::parse_panic_regs()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\parse_panic_regs\\create_panic_regs_cmm.py ";
    qDebug()<<"Inside QString MainWindow::parse_panic_regs()";
    cmd += dumpsPath + " " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::parse_panic_regs()";
    return cmd;
}

QString MainWindow::edit_t32_shortcut()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\edit_t32_shortcut.py ";
    qDebug()<<"Inside QString MainWindow::edit_t32_shortcut()";
    cmd += outputPath;
    cmd += " " + qseeFilePath + qseeFileName;
    cmd += " " + monFilePath + monFileName;
    cmd += " " + hypFilePath + hypFileName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::edit_t32_shortcut()";
    return cmd;
}

QString MainWindow::watchdog_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\watchdog_parser\\watchdog.py ";
    qDebug()<<"Inside QString MainWindow::watchdog_parser()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::watchdog_parser()";
    return cmd;
}

QString MainWindow::ion_buf_analyzer()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\IONMem_parser\\ion_buf_analyzer.py ";
    qDebug()<<"Inside QString MainWindow::ion_buf_analyzer()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ion_buf_analyzer()";
    return cmd;
}

QString MainWindow::wa_log()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\wa_log\\wa_log.pl ";
    qDebug()<<"Inside QString MainWindow::wa_log()";
    cmd += dumpsPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::wa_log()";
    return cmd;
}

QString MainWindow::lockup_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\lockup_parser\\lockup.py ";
    qDebug()<<"Inside QString MainWindow::lockup_parser()";
    cmd += dumpsPath + " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::lockup_parser()";
    return cmd;
}

QString MainWindow::rtb_schedstat()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\RTB_Parser\\rtb_schedstat.py ";
    qDebug()<<"Inside QString MainWindow::rtb_schedstat()";
    cmd += outputPath + " --top=20";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::rtb_schedstat()";
    return cmd;
}

QString MainWindow::memory_corruption()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\memory_corruption\\memory_corruption.py ";
    qDebug()<<"Inside QString MainWindow::memory_corruption()";
    cmd += dumpsPath + " --target " + hardware;
    cmd += " " + appsPath + "\\vmlinux -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::memory_corruption()";
    return cmd;
}

QString MainWindow::iommu_pagetable()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\iommu_pagetable\\iommu_pagetable.py ";
    qDebug()<<"Inside QString MainWindow::iommu_pagetable()";
    cmd += dumpsPath + " --target " + hardware;
    cmd += " " + appsPath + "\\vmlinux -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::iommu_pagetable()";
    return cmd;
}

QString MainWindow::vidc_parse()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\vidc_parse\\vidc_parse.py ";
    qDebug()<<"Inside QString MainWindow::vidc_parse()";
    cmd += dumpsPath + " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::vidc_parse()";
    return cmd;
}

QString MainWindow::smmu_test_bus_decoding()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\bus_error_decoders\\smmu_test_bus_decoding.py ";
    qDebug()<<"Inside QString MainWindow::smmu_test_bus_decoding()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::smmu_test_bus_decoding()";
    return cmd;
}

QString MainWindow::memory_summarize()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\memory_summarize\\memory_summarize.py ";
    qDebug()<<"Inside QString MainWindow::memory_summarize()";
    cmd += dumpsPath + " " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::memory_summarize()";
    return cmd;
}

QString MainWindow::tz_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\tz_parser\\tz_parser.py ";
    qDebug()<<"Inside QString MainWindow::tz_parser()";
    cmd += "--vmlinux " + appsPath + "\\vmlinux";
    cmd += " --qsee " + qseeFilePath + qseeFileName;
    cmd += " --mon " + monFilePath + monFileName;
    cmd += " --hyp " + hypFilePath + hypFileName;
    cmd += " --auto-dump " + dumpsPath;
    cmd += " --force-hardware " + hardware;
    cmd += " --everything -o " + outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::tz_parser()";
    return cmd;
}

QString MainWindow::aop_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\aop_parser\\aop_parser.py ";
    qDebug()<<"Inside QString MainWindow::aop_parser()";
    cmd += "--aop " + aopFilePath + aopFileName;
    cmd += " -i " + dumpsPath;
    cmd += " --everything -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::aop_parser()";
    return cmd;
}

QString MainWindow::cpucp_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\cpucp_parser\\cpucp_parser.py ";
    qDebug()<<"Inside QString MainWindow::cpucp_parser()";
    cmd += "-i " + dumpsPath;
    cmd += " --meta " + metaPath;
    cmd += " --everything -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::cpucp_parser()";
    return cmd;
}

QString MainWindow::aop_script()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\aop_files_gen\\aop_script.py ";
    qDebug()<<"Inside QString MainWindow::aop_script()";
    cmd += dumpsPath + " --o " + outputPath;
    cmd += " --aop " + aopDir;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::aop_script()";
    return cmd;
}

QString MainWindow::merge_logs()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\merge_logs\\merge_logs.py ";
    qDebug()<<"Inside QString MainWindow::merge_logs()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::merge_logs()";
    return cmd;
}

QString MainWindow::ddr_freq_switch()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\ddr_freq_switch\\ddr_freq_switch.py ";
    qDebug()<<"Inside QString MainWindow::ddr_freq_switch()";
    cmd += dumpsPath + " --o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ddr_freq_switch()";
    return cmd;
}

QString MainWindow::arc_stuck_debug()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\arc_stuck\\arc_stuck_debug.py ";
    qDebug()<<"Inside QString MainWindow::arc_stuck_debug()";
    cmd += dumpsPath + " " + metaPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::arc_stuck_debug()";
    return cmd;
}

QString MainWindow::split_tasks()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\split_tasks\\split_tasks.py ";
    qDebug()<<"Inside QString MainWindow::split_tasks()";
    cmd += dumpsPath + " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::split_tasks()";
    return cmd;
}

QString MainWindow::hypvm_traces()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\hymvm_traces\\hyp_parser.py ";
    qDebug()<<"Inside QString MainWindow::hypvm_traces()";
    cmd += "--meta " + metaPath;
    cmd += " --hyp " + hypFilePath + hypFileName;
    cmd += " --auto-dump " + dumpsPath;
    cmd += " --64-bit --target " + targetName;
    cmd += " -o " + outputPath;
    cmd += " --reduceddump N";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::hypvm_traces()";
    return cmd;
}

QString MainWindow::edac_decoder()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\edac_decoder\\edac_decoder.py ";
    qDebug()<<"Inside QString MainWindow::edac_decoder()";
    cmd += dumpsPath + " -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::edac_decoder()";
    return cmd;
}

QString MainWindow::ddr_data()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\ddr_data\\ddr_data.py ";
    qDebug()<<"Inside QString MainWindow::ddr_data()";
    cmd += dumpsPath + " -o " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ddr_data()";
    return cmd;
}

QString MainWindow::consolidated_core_summary()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\consolidated_core_summary\\consolidated_core_summary.py ";
    qDebug()<<"Inside QString MainWindow::consolidated_core_summary()";
    cmd += dumpsPath + " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::consolidated_core_summary()";
    return cmd;
}

QString MainWindow::issue_signature_detector()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\issue_signature_detector\\issue_signature_detector.py ";
    qDebug()<<"Inside QString MainWindow::issue_signature_detector()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::issue_signature_detector()";
    return cmd;
}

QString MainWindow::lpm_merge()
{
    QString cmd = "py -3 " + rdetPath + "\\lib\\support_scripts\\lpm_merge\\lpm_merge.py ";
    qDebug()<<"Inside QString MainWindow::lpm_merge()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::lpm_merge()";
    return cmd;
}

// =============== Extensions functions =================== //

QString MainWindow::run_qtf()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\run_qtf\\run_qtf.py ";
    qDebug()<<"Inside QString MainWindow::run_qtf()";
    cmd += dumpsPath + " --json --target " + targetName;
    cmd += " -o " + outputPath;
    cmd += " --metapath " + metaPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::run_qtf()";
    return cmd;
}

QString MainWindow::dcc_wrapper()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\dcc_parser\\dcc_wrapper.py ";
    qDebug()<<"Inside QString MainWindow::dcc_wrapper()";
    cmd += dumpsPath + " -a " + outputPath + "\\qtf.json";
    cmd += " --target " + targetName;
    cmd += " -o " + outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::dcc_wrapper()";
    return cmd;
}

QString MainWindow::delete_qtf_json()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\run_qtf\\delete_qtf_json.py ";
    qDebug()<<"Inside QString MainWindow::delete_qtf_json()";
    cmd += outputPath;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::delete_qtf_json()";
    return cmd;
}

QString MainWindow::register_dump_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\dcc_parser\\register_dump_parser.py ";
    qDebug()<<"Inside QString MainWindow::register_dump_parser()";
    cmd += dumpsPath + " " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::register_dump_parser()";
    return cmd;
}

QString MainWindow::cpuss_dump_parser()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\cpuss_dump_parser\\cpuss_dump_parser.py ";
    qDebug()<<"Inside QString MainWindow::cpuss_dump_parser()";
    cmd += dumpsPath + " " + outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::cpuss_dump_parser()";
    return cmd;
}

QString MainWindow::system_parameters_wrapper()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\system_parameters\\system_parms_wrapper.py ";
    qDebug()<<"Inside QString MainWindow::system_parameters_wrapper()";
    cmd += dumpsPath + " " + metaPath + " --o " + outputPath;
    cmd += " --target " + targetName + " --hw_version Y";
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::system_parameters_wrapper()";
    return cmd;
}

QString MainWindow::dcc_gladiator_parser_v2()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\dcc_gladiator_parser\\dcc_gladiator_parser_v2.py ";
    qDebug()<<"Inside QString MainWindow::dcc_gladiator_parser_v2()";
    cmd += outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::dcc_gladiator_parser_v2()";
    return cmd;
}

QString MainWindow::ddr_debugging()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\ddr_debugging\\ddr_debugging.py ";
    qDebug()<<"Inside QString MainWindow::ddr_debugging()";
    cmd += outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ddr_debugging()";
    return cmd;
}

QString MainWindow::ddr_process_dumps()
{
    QString cmd = "py -3 " + rdetPath + "\\extensions\\support_scripts\\DDR_process_dumps\\ddr_process_dumps_warpper.py ";
    qDebug()<<"Inside QString MainWindow::ddr_process_dumps()";
    cmd += outputPath;
    cmd += " --target " + targetName;
    qDebug()<<"cmd = "<<cmd;
    qDebug()<<"Exiting QString MainWindow::ddr_process_dumps()";
    return cmd;
}
