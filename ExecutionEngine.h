#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <QObject>
#include <QReadWriteLock>
#include <QWaitCondition>

#include "ExecutionEngineCommon.h"

class ExecutionEngine : public QObject
{
    Q_OBJECT
public:
    explicit ExecutionEngine(QObject *parent = nullptr);
    ~ExecutionEngine();

signals:
    void signal_executionStatusChanged(ExecutionStatus status);

public slots:
    void execute();

public:
    ExecutionStatus getExecutionStatus();
    void setExecutionStatus(ExecutionStatus status);

private:
    //执行状态
    ExecutionStatus status_;
    //执行状态读写锁
    QReadWriteLock statusRWL_;

    //暂停
    QWaitCondition pauseWaitCondition_;
};

#endif // EXECUTIONENGINE_H
