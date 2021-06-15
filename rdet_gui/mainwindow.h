#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "rdetlogshandler.h"

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
    QString rdetCmd();
    QString ramparserCmd(QString hardware);
    QString memoryCorruptionCmd();
    QString tzParserCmd();
    QString module_symbolCmd();
    QString platform_infoCmd();
    QString dcc_wrapperCmd();
    QString task_statsCmd();
    QString excessive_loggingCmd();
    QString ramparser_svmCmd();
    QString ddrCookiesCmd();
    QString rdet_html_genCmd();
    QString read_power_collapse_cnt();
    QString tme_parser();
    QString tme_debugging();
    QString scandump_parser();
    QString instr_fetcher();
    QString bus_error_decoder();
    QString smmu_fault_decoder();
    QString parse_panic_regs();
    QString edit_t32_shortcut();
    QString watchdog_parser();
    QString ion_buf_analyzer();
    QString wa_log();
    QString lockup_parser();
    QString rtb_schedstat();
    QString memory_corruption();
    QString iommu_pagetable();
    QString vidc_parse();
    QString smmu_test_bus_decoding();
    QString memory_summarize();
    QString tz_parser();
    QString aop_parser();
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
};

#endif // MAINWINDOW_H
