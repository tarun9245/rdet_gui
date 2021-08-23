#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "rdetlogshandler.h"
#include "libsubscripts.h"
#include "metahandler.h"
#include "extensionssubscripts.h"
#include "xmlfilehandler.h"

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
    void readingMeta();
    void runSubScripts();
    void updatingMetaInfoToLogsFile();
private slots:
    void on_pushButtonSettings_clicked();

    void on_pushButtonSubmit_clicked();

    void on_checkBox_ramparser_stateChanged(int arg1);

    void on_lineEditMetaPath_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    settings *setting;
    RdetLogsHandler logHandler;
    xmlFileHandler *xml;
    libSubScripts *lib;
    extensionsSubScripts *ext;
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
