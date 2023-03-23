#pragma once

#include <QVector>
#include <QtGlobal>
#include "IMainCtrl.hpp"

class ICommand
{
public:
    ICommand(IMainCtrl *pMainCtrl)
    {
        m_pMainCtrl = pMainCtrl;

        //Init();
    }

    virtual ~ICommand(){}

    //!命令注册
    virtual void Init() =0;

    //!执行命令
    virtual bool ExecuteCommand(const QString &szCommandID, void* pInParam, void** pOutParam) = 0;

    //!获取命令数量
    virtual int GetCommandCount()
    {
        return m_commandVector.count();
    }

    //!获取命令ID
    virtual const QString GetCommandID(int iIndex)
    {
        return m_commandVector.count()< iIndex ? "" :  m_commandVector.at(iIndex);
    }

protected:
    IMainCtrl * m_pMainCtrl;
    QVector <QString > m_commandVector;     //在子类中将命令添加到m_commandVector中
};
