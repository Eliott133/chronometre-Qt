#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chrono.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SaveCSV();
    void lap(QString, QString);
    void start();
    void stop();

private:
    Ui::MainWindow *ui;
    Chrono *chrono;  // Replace QLCDNumber with Chrono
};
#endif // MAINWINDOW_H
