#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
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
    void runCommand(QString cmd);
    QString rdetCmd();
    QString ramparserCmd();
    QString memoryCorruptionCmd();
    QString tzParserCmd();

private slots:
    void on_pushButtonSettings_clicked();

    void on_pushButtonSubmit_clicked();

    void on_checkBox_ramparser_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    settings *setting;
    QString rdetPath;
    QString metaPath;
    QString dumpsPath;
    QString appsPath;
    QString options;
};

#endif // MAINWINDOW_H
