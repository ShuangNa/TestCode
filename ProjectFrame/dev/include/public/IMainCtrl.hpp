#pragma once

#include <QtGlobal>
#include <QString>

struct MenuCommandStruct
{
    MenuCommandStruct()
    {
        commandName.clear();
        strCommandType.clear();
        commandID.clear();
        param1.clear();
        param2.clear();
        mainwindow = nullptr;
    }

    QString commandName;
    QString strCommandType;
    QString commandID;
    QString param1;
    QString param2;
    void * mainwindow;
};


class IComponent;
class IMainCtrl
{
public:
    virtual ~ IMainCtrl()  {}

    //!初始化
    virtual void Init() = 0;

    //!获取组件指针
    virtual IComponent* GetComponent(const QString & szComponentId) = 0;

    //!获取组件指针
    virtual void* GetComponentSpeciallPtr(const QString & szComponentId, const QString &speciallName) = 0;

    //!指定命令
    virtual bool ExecuteCommand(const QString &szCommandID, void* pInParam, void** pOutParam) = 0;

    //!发送消息
    virtual void SendMessage(const QString &szMessage, int iValue, void* pValue) = 0;

    //!获取接口指针
    virtual void* GetInterfacePtr(const QString & szInterfaceID) = 0;

    //!退出
    virtual void Quit() = 0;

    //!获取窗口句柄
    virtual quint64 GetWindowHandle() =0;

    //!绘制
    virtual void OnDraw(quint64 ihdc) = 0;

    //!设置定时器
    virtual int SetTimer(int iElapse,const QString& szComponentID) = 0;

    //!删除定时器
    virtual bool KillTimer(int iTimerID) = 0;



};

