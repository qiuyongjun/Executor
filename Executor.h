#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <QObject>
#include <QMutex>

#include <QThread>

#include "ExecutionEngineCommon.h"

class ExecutionEngine;

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = nullptr);

signals:
    void signal_executionStatusChanged(ExecutionStatus status);

public:
    static Executor * getInstance();

public:
    void startExecution();
    void stopExecution();
    void pauseExecution();
    void continueExecution();

private:
    //执行引擎
    ExecutionEngine * executionEngine_;

    //执行线程
    QThread * executionThread_;

private:
    //实例
    static Executor * instance_;
    //实例 互斥锁
    static QMutex instanceMutex_;

private:
    //自动回收内存
    class Recycler
    {
    public:
        ~Recycler()
        {
            if (instance_ != nullptr)
            {
                delete instance_;
                instance_ = nullptr;
            }
        }
    };
    static Recycler recycler_;
};

#endif // SCRIPTEXECUTOR_H
