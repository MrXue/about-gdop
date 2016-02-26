#ifndef GDOP_H
#define GDOP_H
#include <QDate>
#include <QTime>
#include "readaer.h"

class GDOP
{
public:
    GDOP();
    ~GDOP();

    //计算GDOP输入为日期d，时间t，aer数据AerData，和卫星编号
    float calculatorGDOP(const QDate &d,const QTime &t, AerData &aerData,const std::vector<std::string> satellite);

private:
    float matrixGDOP(int m,int n,float *matrix);
    float mydet(uint n,float *matrix);           //计算矩阵的行列式的值
    float *adjointMatrix(int n,float *matrix);           //计算伴随矩阵

};

#endif // GDOP_H
