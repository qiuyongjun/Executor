#include "Executor.h"

#include "ExecutionEngine.h"

#include <QDebug>

//初始化静态成员
Executor* Executor::instance_ = nullptr;
QMutex Executor::instanceMutex_;

Executor::Executor(QObject *parent) : QObject(parent)
{
    executionEngine_ = new ExecutionEngine();

    connect(executionEngine_,&ExecutionEngine::signal_executionStatusChanged,this,&Executor::signal_executionStatusChanged);

    executionThread_ = new QThread(this);
    executionEngine_->moveToThread(executionThread_);
    connect(executionThread_,&QThread::destroyed,executionEngine_,&ExecutionEngine::deleteLater);
    executionThread_->start();
}

Executor *Executor::getInstance()
{
    if (instance_ == nullptr)
    {
        instanceMutex_.lock();
        if (instance_ == nullptr)
        {
            instance_ = new Executor;
        }
        instanceMutex_.unlock();
    }

    return instance_;
}

void Executor::startExecution()
{
    switch (executionEngine_->getExecutionStatus())
    {
    case ExecutionStatus::Stopped:
    {
        executionEngine_->setExecutionStatus(ExecutionStatus::ReadyRun);

        //开始执行
        QMetaObject::invokeMethod(executionEngine_,"execute");
        break;
    }
    default:
        break;
    }
}

void Executor::stopExecution()
{    
    switch (executionEngine_->getExecutionStatus())
    {
    case ExecutionStatus::Running:
    case ExecutionStatus::Paused:
    {
        executionEngine_->setExecutionStatus(ExecutionStatus::ReadyStop);
        break;
    }
    default:
        break;
    }
}

void Executor::pauseExecution()
{  
    switch (executionEngine_->getExecutionStatus())
    {
    case ExecutionStatus::Running:
    {
        executionEngine_->setExecutionStatus(ExecutionStatus::ReadyPause);
        break;
    }
    default:
        break;
    }
}

void Executor::continueExecution()
{
    switch (executionEngine_->getExecutionStatus())
    {
    case ExecutionStatus::Paused:
    {
        executionEngine_->setExecutionStatus(ExecutionStatus::ReadyRun);
        break;
    }
    default:
        break;
    }
}
