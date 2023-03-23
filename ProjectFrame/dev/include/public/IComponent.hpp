#pragma once

#include <QtGlobal>
#include "ICommand.hpp"
#include "IMessage.hpp"
#include "IObjectCreator.hpp"

class IComponent
{

public:
    virtual ~IComponent(){}

    //!获取ID
    virtual QString GetID() = 0;

    //!初始化
    virtual void Init() = 0;

    //!释放资源
    virtual void Release() = 0;

    //!获取组件个数
    virtual int GetInterfaceCount()
    {
        return m_componentObjMap.count();
    }

    //!获取组件ID
    virtual QString GetInterfaceID(int iIndex)
    {
        return m_componentObjMap.keys().at(iIndex);
    }

    //!获取组件指针
    virtual void* GetInterfacePtr(const QString& szInterfaceID)
    {
        if(m_componentObjMap.contains(szInterfaceID))
        {
            m_componentObjMap.value(szInterfaceID);
        }
        else
        {
            return nullptr;
        }
        return nullptr;
    }

    //!获取ICommand指针
    virtual ICommand* GetCommand() = 0;

    //!获取IMessage指针
    virtual IMessage* GetMessage() = 0;

    //!获取IObjectCreator指针
    virtual IObjectCreator * GetObjectCreator() = 0;

protected:
    QMap<QString, void*> m_componentObjMap;

};

