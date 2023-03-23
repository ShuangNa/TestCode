#pragma once
#include <QVector>
#include <QtGlobal>
#include <QHash>

#include "IMainCtrl.hpp"

class IMainTimer
{
public:
    virtual ~IMainTimer() = default;

    virtual void OnTimer(int iTimerID) = 0;

protected:
    QHash<QString, quint32> m_timeID;    //定时器 与 ID映射
};



