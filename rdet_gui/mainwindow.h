#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButtonSettings_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
