#ifndef FUNTIONS1_H
#define FUNTIONS1_H

#include <QtCore/qglobal.h>
#include <iostream>

#if defined(FUNTIONS1_LIBRARY)
#  define FUNTIONS1_EXPORT Q_DECL_EXPORT
#else
#  define FUNTIONS1_EXPORT Q_DECL_IMPORT
#endif


using namespace std;

class FUNTIONS1_EXPORT Funtions1
{
public:
    Funtions1();

    /*设置文件名*/
    void SetFileName(string fileName);

    /*获取文件*/
    string GetNCFile();
};

#endif // FUNTIONS1_H
