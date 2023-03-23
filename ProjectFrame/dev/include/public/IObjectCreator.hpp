#pragma once

#include <QMap>
#include <QtGlobal>

#include "IMainCtrl.hpp"


class QWidget;
class IObjectCreator
{
public:
    IObjectCreator(IMainCtrl *pMainCtrl)
    {
        m_pMainCtrl = pMainCtrl;
    }

    virtual ~IObjectCreator(){}

public:
    //!初始化对象
    virtual void Init() = 0;

    //!获取对象数量
    virtual int GetObjectCount()
    {
        return m_pObjMap.count();
    }

    //!获取对象指针
    virtual void* GetObjectPtr(const QString &objName)
    {
        return m_pObjMap.value(objName, NULL);
    }

    //!周期调度数据
    virtual void Refresh() = 0;

    /*
     * 图层？
    void showDlg(const QString &dlgName,  void *parent)
    {
        if(this == nullptr || parent == nullptr)
            return ;

        QWidget* pSubWidget = (QWidget*)this->GetObjectPtr(dlgName);

        if(pSubWidget == nullptr)
            return ;

        if(!m_DlgMap.contains(dlgName))
        {
            QWidget* pWid=  new FrameWidget(pSubWidget ,(QWidget*)parent);
            m_DlgMap.insert(dlgName, pWid);
        }
        m_DlgMap.value(dlgName)->show();
    }
    */

protected:
    IMainCtrl * m_pMainCtrl;
    QMap <QString, void*> m_pObjMap;    //对象Map //在子类中将命令添加到m_pObjMap中
    QMap <QString, QWidget*> m_DlgMap;  // key = 界面名称 value 界面指针

};





