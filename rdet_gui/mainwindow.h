#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "rdetlogshandler.h"
#include "libsubscripts.h"
#include "metahandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getDumpsPath();
    QString getMetaPath();
    QString getAppsPath();
    QString getHardwareName(QString targetName);
    void runCommand(QString cmd);
    QString ramparserCmd();
    QString rdetCmd();
/// Extension functions ///
    QString run_qtf();
    QString dcc_wrapper();
    QString delete_qtf_json();
    QString register_dump_parser();
    QString cpuss_dump_parser();
    QString system_parameters_wrapper();
    QString dcc_gladiator_parser_v2();
    QString ddr_debugging();
    QString ddr_process_dumps();
    QString sensein_noc();
    QString shlog_parser();
    QString noc_decode_dcc();
    QString cxttable_decode();
    QString qtf_parser();
    QString qtf_signature();
    QString logcat_parser();
    QString task_state_parser();
    QString tlb_dump_parser();
    void readingMeta();
    void runSubScripts();
    void updatingMetaInfoToLogsFile();
private slots:
    void on_pushButtonSettings_clicked();

    void on_pushButtonSubmit_clicked();

    void on_checkBox_ramparser_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    settings *setting;
    RdetLogsHandler logHandler;
    libSubScripts *lib;
    metaHandler *meta;
    QString rdetPath;
    QString metaPath;
    QString dumpsPath, outputPath;
    QString appsPath, tzPath;
    QString options, targetName,hardware;
    QString qseeFileName;
    QString qseeFilePath;
    QString monFileName;
    QString monFilePath;
    QString hypFileName;
    QString hypFilePath;
    QString aopFileName;
    QString aopFilePath;
    QString rpmFileName;
    QString rpmFilePath;
    QString aopDir;
};

#endif // MAINWINDOW_H
