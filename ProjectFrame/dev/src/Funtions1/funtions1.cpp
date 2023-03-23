#include "funtions1.h"

Funtions1::Funtions1()
{

}

/*设置文件名*/
void Funtions1::SetFileName(string)
{
    cout << "seting file name is successful" << endl;
}

/*获取文件*/
string Funtions1::GetNCFile()
{
     cout << "get nc file name is successful" << endl;
     string nc = "testfile.nc";
     return nc;
}
