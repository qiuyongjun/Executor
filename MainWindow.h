#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ExecutionEngineCommon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

private slots:
    void slot_executionStatusChanged(ExecutionStatus status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
