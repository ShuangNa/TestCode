#include "MainCtrl.h"
#include <QFile>
#include <QApplication>
#include <QLibrary>
#include <QDebug>


//定义创建组件的函数指针
typedef IComponent* (* ICreateComponent)(IMainCtrl* pMainCtrl);

MainCtrl::MainCtrl()
{
}

MainCtrl::~MainCtrl()
{
}


//!初始化
void MainCtrl::Init()
{
    /*注册所有组件*/
    RegisterAllComponents();
}

//!获取组件指针
IComponent* MainCtrl::GetComponent(const QString & componentId)
{
    if (m_componentsHash.contains(componentId))
    {
        return m_componentsHash.value(componentId);
    }

    return NULL;
}


//!获取组件中某接口指针 componentId：组件名称 speciallName：空间接口名称
void* MainCtrl::GetComponentSpatialInterfacePtr(const QString & componentId, const QString &spatialInterfaceName)
{
    IComponent* pComponentPtr = GetComponent(componentId);

    if(pComponentPtr)
    {
        return  pComponentPtr->GetInterfacePtr(spatialInterfaceName.toStdString().data());
    }

    return NULL;
}




//!执行命令
bool MainCtrl::ExecuteCommand(const QString &szCommandID, void* pInParam, void** pOutParam)
{
    mutex().lockForRead();

    QHash<QString, IComponent*>::const_iterator i = CommandAndComponentHash().find(QString(szCommandID));
    if (i != CommandAndComponentHash().end())
    {
        IComponent* pComponent = i.value();
        ICommand* pCommand = (ICommand*)pComponent->GetInterfacePtr(I_INTERFACE_COMMAND);
        if (pCommand != NULL)
        {
            mutex().unlock();
            int iRet = pCommand->ExecuteCommand(szCommandID, pInParam, pOutParam);

            return iRet;
        }
    }
    mutex().unlock();

    return false;
}


//!发送消息
void MainCtrl::SendMessage(const QString &szMessage, int iValue, void* pValue)
{
    //根据szMessage ID所引到对应组件OnMesssage
    mutex().lockForRead();
    QList<IMessage*> messages = MessageMultiHash() .values(QString(szMessage));
    mutex().unlock();

    for(int i=0; i<messages.size(); ++i)
    {
        IMessage* pMessage = (IMessage*)messages.at(i);
        if(0 != pMessage)
        {
            pMessage->OnMesssage(szMessage, iValue, pValue);
        }
    }
}


//!获取接口指针
void* MainCtrl::GetInterfacePtr(const QString & szInterfaceID)
{
    mutex().lockForRead();
    QHash<QString, void*>::const_iterator i =SpecialInterfaceHash().find(QString(szInterfaceID));
    if(i != SpecialInterfaceHash().end())
    {
        mutex().unlock();
        return i.value();
    }
    mutex().unlock();

    return NULL;
}


//!绘制
void MainCtrl::OnDraw(quint64 ihdc)
{
    for (auto i=0; i<m_listDrawer.count(); i++)
    {
        IMainDrawer* pDrawer = m_listDrawer[i];
        pDrawer->OnDraw(ihdc);
    }
}




//!设置定时器
int MainCtrl::SetTimer(int iElapse,const QString& szComponentID)
{
    QHash<QString, IComponent*>::const_iterator i = m_componentsHash.find(QString(szComponentID));
    if(i != m_componentsHash.end())
    {
        int id = startTimer(iElapse);
        m_hashTimer2Component.insert(id, i.value());
        return id;
    }
    return -1;
}


//!删除定时器
bool MainCtrl::KillTimer(int iTimerID)
{
    killTimer(iTimerID);
    return true;
}

void MainCtrl::timerEvent(QTimerEvent *event)
{
    int id = event->timerId();
    QHash<int, IComponent*>::const_iterator i = m_hashTimer2Component.find(id);
    if(i != m_hashTimer2Component.end())
    {
        IComponent* p = i.value();
        void* ptr = p->GetInterfacePtr(I_INTERFACE_MAIN_TIMER);

        IMainTimer* pTimer = (IMainTimer*)(ptr);
        if(pTimer != 0)
        {
            pTimer->OnTimer(id);
        }
    }
}


//!退出
void MainCtrl::Quit()
{
     qApp->quit();
}


//!获取窗口句柄
quint64 MainCtrl::GetWindowHandle()
{
     return (quint64)(this);
}



//!注册plugin 文件夹下面插件
void MainCtrl::RegisterAllComponents()
{
    QString pluginExtensionName;
#if defined(Q_OS_WIN)
    pluginExtensionName=".dll";
#elif defined(Q_OS_LINUX)
    pluginExtensionName=".so";
#endif

    QFile file(qApp->applicationDirPath()+"/../config/ComponentList.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QString pluginName = file.readLine().trimmed();
        if(pluginName.contains("#") || pluginName.isEmpty())  //注释插件使用#
            continue;

        QString pluginPath = qApp->applicationDirPath()+"/"+pluginName+pluginExtensionName;

        qDebug() << QStringLiteral("开始加载 *** [%1]*****************").arg(pluginPath);

        QLibrary lib(pluginPath);
        if(!lib.load())
        {
            QString libError =lib.errorString();
            qDebug() << QStringLiteral("%1 - 加载注册失败, [%2]!").arg(pluginPath).arg(libError);
            continue;
        }


        /******************************************************************
        //组件创建函数 重要 重要 重要 ！ ！ ！
        IComponent* CreateComponent(IMainCtrl* pMainCtrl)
        {
            IComponent* p = new JComponent(pMainCtrl);
            return p;
        }

        typedef IComponent* (*CreateComponent)(IMainCtrl* pMainCtrl);
        ******************************************************************/
        //获取动态库中函数CreateComponent的函数指针
        ICreateComponent pFunc = (ICreateComponent)lib.resolve("CreateComponent");
        if(pFunc == nullptr)
        {
            continue;
        }

        //执行函数指针，将IMainCtrl传给构造函数，获取组件指针
        //多态，调用子类构造函数
        IComponent *pComponent =pFunc((IMainCtrl*)this);

        qDebug() << QStringLiteral("%1 - 加载注册成功!").arg(pComponent->GetID());

        //记录组件
        m_componentsHash.insert(pComponent->GetID(), pComponent);

        /*多态，调用子类Init*/
        pComponent->Init();

        /*注册Command*/
        RegisterCommand(pComponent);

        /*注册消息*/
        RegisterMessage(pComponent);

        /*注册组件中空间接口指针*/
        RegisterSpatialInterfacePtr(pComponent);

        /*注册绘制*/
        RegisterDrawer(pComponent);


    }
}



//!注册所有组件中的所有Command，根据组件索引，
//!从m_componentObjMap组件对象Map中获取对应ICommand，因为ICommand在IComponent中初始化
void MainCtrl::RegisterCommand(IComponent* pComponent)
{
    ICommand* p = (ICommand*)pComponent->GetInterfacePtr(I_INTERFACE_COMMAND);
    if(p != 0)
    {
        int count = p->GetCommandCount();
        for(int i=0; i<count; ++i)
        {
            m_commandAndComponentHash.insert(QString(p->GetCommandID(i)), pComponent);
        }
    }
}


//!注册消息
//!注册所有组件中的所有IMessage，根据组件索引，
//!从m_messageMultiHash消息对象Hash中获取对应ICommand，因为ICommand在IComponent中初始化
void MainCtrl::RegisterMessage(IComponent* pComponent)
{
    IMessage* p = (IMessage*)pComponent->GetInterfacePtr(I_INTERFACE_MESSAGE);
    if (p != NULL)
    {
        int count = p->GetMessageCount();
        for(int i=0; i<count; ++i)
        {
            m_messageMultiHash.insert(QString(p->GetMessageID(i)), p);
        }
    }
}

//!注册组件中空间接口指针
void MainCtrl::RegisterSpatialInterfacePtr(IComponent* pComponent)
{
    int count = pComponent->GetInterfaceCount();
    QString strInterfaceName;
    for(int i=0; i<count; i++)
    {
        strInterfaceName = pComponent->GetInterfaceID(i);
        if (strInterfaceName.isEmpty())
        {
            continue;
        }

        m_specialInterfaceHash.insert(strInterfaceName, pComponent->GetInterfacePtr(strInterfaceName.toLocal8Bit().data()));
    }
}


//!注册绘制
void MainCtrl::RegisterDrawer(IComponent* pComponent)
{
    IMainDrawer* pDrawer = (IMainDrawer*)pComponent->GetInterfacePtr(I_INTERFACE_MAIN_DRAWER);

    if(pDrawer)
    {
        m_listDrawer.append(pDrawer);
    }
}

//!获取组件Hash
QHash<QString, IComponent*>& MainCtrl::CommandAndComponentHash()
{
    return m_commandAndComponentHash;
}

//!获取消息Hash
QMultiHash<QString, IMessage*> & MainCtrl::MessageMultiHash()
{
    return m_messageMultiHash;
}

//!获取接口Hash
QHash<QString, void*>  &MainCtrl::SpecialInterfaceHash()
{
     return m_specialInterfaceHash;
}

//!
QReadWriteLock &MainCtrl::mutex()
{
    return m_mutex;
}
