#include "ProjectFrame.h"

#include <QApplication>
#include <QDebug>

#include "funtions1.h"
#include "ProcessingNCData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProjectFrame w;
    w.show();


    QString fileName = QString::fromLocal8Bit("C:/Users/Administrator/Desktop/雷达数据格式/数据/湛江06CDN/tmp/KLG341717020220820092037010.PPI");


    /*读文件*/
    //ProcessingNCData prodata;
    //bool ret = prodata.GetNCFile(string(fileName.toLocal8Bit().data()),"E:/Demo/ProcessingNCData/outNCPath",0);
    //bool ret = prodata.GetNCFile(string("C:/Users/Administrator/Desktop/雷达数据格式/数据/湛江06CDN/tmp/KLG341717020220820092037010.PPI"),"E:/Demo/ProcessingNCData/outNCPath",0);
    bool ret = ProcessingNCData::GetNCFile("E:/Demo/ProcessingNCData/intputFile/ZhanJiang06CDN/KLG341717020220820092037010.PPI","E:/Demo/ProcessingNCData/outNCPath",1);
    if(ret == true){
        qDebug() << "输出NC文件结束";
    } else {
        qDebug() << "输出NC文件失败";
    }

    //Funtions1 fun;
    //fun.SetFileName("nc123.10P");
    //fun.GetNCFile();

    return a.exec();
}
