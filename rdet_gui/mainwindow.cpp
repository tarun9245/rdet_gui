#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include "settings.h"
#include <QMessageBox>

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
    QString str = ui->lineEditDumpPath->text();
    qDebug()<<"Str = "<<str;

    qDebug()<<"Exiting QString MainWindow::getDumpsPath()";
    return str;
}

QString MainWindow::getMetaPath()
{
    qDebug()<<"Inside QString MainWindow::getMetaPath()";
    QString str = ui->lineEditMetaPath->text();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getMetaPath()";
    return str;
}

QString MainWindow::getAppsPath()
{
    qDebug()<<"Inside QString MainWindow::getAppsPath()";
    QString str = ui->lineEditAppsPath->text();
    qDebug()<<"Str = "<<str;
    qDebug()<<"Exiting QString MainWindow::getAppsPath()";
    return str;
}

void MainWindow::runCommand(QString cmd)
{
    qDebug()<<"Inside void MainWindow::runCommand(QString cmd)";
    qDebug()<<"cmd to run = "<<cmd;
    system(cmd.toUtf8().data());
    system("pause>nil");
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

void MainWindow::on_pushButtonSubmit_clicked()
{
    qDebug()<<"Inside void MainWindow::on_pushButtonSubmit_clicked()";
    rdetPath = setting->getRdetPath();
    metaPath = ui->lineEditMetaPath->text();
    dumpsPath = ui->lineEditDumpPath->text();
    appsPath = ui->lineEditAppsPath->text();
    if(metaPath == "" || dumpsPath == "") {
        QMessageBox::warning(this,tr("Error"), tr("Dump or Meta location cannot be Empty!"));
        return;
    }
    QString cmd = rdetCmd();
    runCommand(cmd);
    qDebug()<<"Exiting void MainWindow::on_pushButtonSubmit_clicked()";
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
    ui->checkBox_sym_path->setEnabled(arg1);
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
