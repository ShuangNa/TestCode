#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <QtCore/qglobal.h>

#if defined(MAINCTRL_LIBRARY)
#  define MAINCTRL_EXPORT Q_DECL_EXPORT
#else
#  define MAINCTRL_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QTimerEvent>
#include <QReadWriteLock>
#include <QHash>
#include <QMultiHash>

#include "IMainCtrl.hpp"
#include "ICommand.hpp"
#include "IMessage.hpp"
#include "IObjectCreator.hpp"
#include "IComponent.hpp"
#include "IMainTimer.hpp"
#include "IMainDrawer.hpp"
#include "GloblPlulic.h"

class MAINCTRL_EXPORT MainCtrl : public QObject, public IMainCtrl
{
public:
    MainCtrl();
    ~MainCtrl();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///    IMainCtrl
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //!初始化
    void Init();

    //!获取组件指针
    IComponent* GetComponent(const QString & szComponentId);

    //!获取组件中空间接口指针 componentId：组件名称 speciallName：空间接口名称
    void* GetComponentSpatialInterfacePtr(const QString & szComponentId, const QString &speciallName);

    //!执行命令
    bool ExecuteCommand(const QString &szCommandID, void* pInParam, void** pOutParam);

    //!发送消息
    void SendMessage(const QString &szMessage, int iValue, void* pValue);

    //!获取接口指针
    void* GetInterfacePtr(const QString & szInterfaceID);

    //!退出
    void Quit();

    //!获取窗口句柄
    quint64 GetWindowHandle() =0;

    //!绘制
    void OnDraw(quint64 ihdc);

    //!设置定时器
    int SetTimer(int iElapse,const QString& szComponentID);

    //!删除定时器
    bool KillTimer(int iTimerID);

    void timerEvent(QTimerEvent *event);



private:
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //!注册plugin 文件夹下面插件
    void RegisterAllComponents();

    //!注册Command
    void RegisterCommand(IComponent* pComponent);

    //!注册组件中空间接口指针
    void RegisterSpatialInterfacePtr(IComponent* pComponent);

    //!注册消息
    void RegisterMessage(IComponent* pComponent);

    //!注册绘制
    void RegisterDrawer(IComponent* pComponent);

    //!获取组件Hash
    QHash<QString, IComponent*>& CommandAndComponentHash();

    //!获取消息Hash
    QMultiHash<QString, IMessage*> & MessageMultiHash();

    //!获取接口Hash
    QHash<QString, void*>  &SpecialInterfaceHash();

    //!
    QReadWriteLock &mutex() ;


private:
    QReadWriteLock m_mutex;

    QHash<QString, IComponent*> m_componentsHash;           //记录组件 <组件名称, 组件>
    QHash<QString, IComponent*> m_commandAndComponentHash;  //组件命令与组件映射
    QMultiHash<QString, IMessage*> m_messageMultiHash;      //消息映射
    QHash<int, IComponent*> m_hashTimer2Component;          //定时器与组件映射
    QHash<QString, void*> m_specialInterfaceHash;           //组件专有接口


    QList<IMainDrawer*> m_listDrawer;                       //绘制画家
};

#endif // MAINCTRL_H
