#include "ExecutionEngine.h"

#include <QTime>
#include <QThread>

#include <QDebug>

ExecutionEngine::ExecutionEngine(QObject *parent) : QObject(parent)
{
    status_ = ExecutionStatus::Stopped;
    qRegisterMetaType<ExecutionStatus>("ExecutionStatus");
}

ExecutionEngine::~ExecutionEngine()
{

}

void ExecutionEngine::execute()
{
    //开始执行
    setExecutionStatus(ExecutionStatus::Running);

    for(int i=0;i<=99999999;i++)
    {

        ExecutionStatus status = getExecutionStatus();
        qDebug()<<__FUNCTION__<<QThread::currentThreadId()<<QTime::currentTime().toString("hh:mm:ss.zzz")<<"---";
        switch (status)
        {
        case ExecutionStatus::ReadyPause:
        {
            setExecutionStatus(ExecutionStatus::Paused);

            //暂停
            QMutex pauseMutex;
            pauseMutex.lock();
            pauseWaitCondition_.wait(&pauseMutex);
            pauseMutex.unlock();

            ExecutionStatus newStatus = getExecutionStatus();
            switch (newStatus)
            {
            case ExecutionStatus::ReadyRun:
            {
                setExecutionStatus(ExecutionStatus::Running);
                break;
            }case ExecutionStatus::ReadyStop:
            {
                setExecutionStatus(ExecutionStatus::Stopped);
                return;
            }
            default:
            {
                break;
            }
            }

            break;
        }
        case ExecutionStatus::ReadyStop:
        {
            setExecutionStatus(ExecutionStatus::Stopped);
            return;
        }
        default:
        {
            break;
        }
        }


        QThread::msleep(100);
        qDebug()<<__FUNCTION__<<QThread::currentThreadId()<<QTime::currentTime().toString("hh:mm:ss.zzz");
    }

    //执行结束
    setExecutionStatus(ExecutionStatus::Stopped);
}

ExecutionStatus ExecutionEngine::getExecutionStatus()
{
    QReadLocker locker(&statusRWL_);
    return status_;
}

void ExecutionEngine::setExecutionStatus(ExecutionStatus status)
{
    QWriteLocker locker(&statusRWL_);
    status_ = status;
    emit signal_executionStatusChanged(status_);

    qDebug()<<__FUNCTION__<<QThread::currentThreadId()<<QTime::currentTime().toString("hh:mm:ss.zzz")<<status;

    switch (status)
    {
    case ExecutionStatus::ReadyRun:
    case ExecutionStatus::ReadyStop:
    {
        pauseWaitCondition_.wakeAll();
        break;
    }
    default:
    {
        break;
    }
    }

}
