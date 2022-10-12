#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <Executor.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(Executor::getInstance(),&Executor::signal_executionStatusChanged,this,&MainWindow::slot_executionStatusChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    if(!ui->pushButton_start->text().compare(QStringLiteral("开始")))
    {
        Executor::getInstance()->startExecution();
    }else if (!ui->pushButton_start->text().compare(QStringLiteral("暂停")))
    {
        Executor::getInstance()->pauseExecution();
    }else if (!ui->pushButton_start->text().compare(QStringLiteral("继续")))
    {
        Executor::getInstance()->continueExecution();
    }

}

void MainWindow::on_pushButton_stop_clicked()
{
    Executor::getInstance()->stopExecution();
}

void MainWindow::slot_executionStatusChanged(ExecutionStatus status)
{
    switch(status)
    {
    case ExecutionStatus::Running:
    {
        ui->pushButton_start->setText(QStringLiteral("暂停"));
        ui->pushButton_stop->setEnabled(true);
        break;
    }
    case ExecutionStatus::Paused:
    {
        ui->pushButton_start->setText(QStringLiteral("继续"));
        ui->pushButton_stop->setEnabled(true);
        break;
    }
    case ExecutionStatus::Stopped:
    {
        ui->pushButton_start->setText(QStringLiteral("开始"));
        ui->pushButton_stop->setEnabled(false);
        break;
    }
    default:
    {
        break;
    }
    }
}
