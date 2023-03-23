#pragma once
#include <QVector>
#include <QtGlobal>

#include "IMainCtrl.hpp"


class IMainDrawer
{
public:

   ~IMainDrawer() = default;

    //!绘制事件
    virtual bool OnDraw(quint64 iHdc) = 0;

private:

};


