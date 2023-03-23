#pragma once
#include <QVector>
#include <QtGlobal>

#include "IMainCtrl.hpp"


class IMessage
{
public:
    IMessage(IMainCtrl *pMainCtrl)
    {
        m_pMainCtrl = pMainCtrl;

        //Init();
    }

    virtual ~IMessage(){}

    //!初始化
    virtual void Init() = 0;

    //!消息响应
    virtual void OnMesssage(const QString &msgName, int iValue, void* pValue) = 0;

    //!获取消息个数
    virtual int GetMessageCount()
    {
        return m_messageVector.count();
    }

    //!获取消息ID
    virtual const QString GetMessageID(int iIndex)
    {
        return m_messageVector.count()<iIndex ? "" : m_messageVector.at(iIndex);
    }

protected:
    IMainCtrl *m_pMainCtrl;
    QVector<QString> m_messageVector;   //在子类中将命令添加到m_messageVector中
};

