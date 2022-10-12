#ifndef EXECUTIONENGINECOMMON_H
#define EXECUTIONENGINECOMMON_H

//执行状态
enum ExecutionStatus
{
    Running,//正在运行
    Paused,//已经暂停
    Stopped,//已经停止
    ReadyRun,//将要开始
    ReadyPause,//将要暂停
    ReadyStop,//将要停止
};

#endif // EXECUTIONENGINECOMMON_H
