#include "gdop.h"
#include <cmath>
#define PI 3.14159265
#include "eigen3/Eigen/Eigen"
using namespace Eigen;
GDOP::GDOP()
{

}

GDOP::~GDOP()
{

}

float GDOP::calculatorGDOP(const QDate &d, const QTime &t, AerData &aerData, const std::vector<std::string> satellite)
{
    float gdop=0.0;
    uint lineK=satellite.size();
    float tempAzimuth1;
    float tempAzimuth2;
    float tempElevation1;
    float tempElevation2;
    int thresholdTime=10*60;
    QTime zeroTime(23,59,59);
    int differSecondt1=0;
    int differSecond=0;
    float *matrixK=new float[4*lineK];
    for(uint i=0;i<lineK;i++)
    {
        AerData::iterator pos;
        for(pos=aerData.begin();pos!=aerData.end();++pos)
        {
            if(satellite[i]==pos->first)
            {
                std::vector<AerStruct> tempVAer=pos->second;
                struct AerStruct tempStruct1;
                struct AerStruct tempStruct2;
                for(uint j=0;j<tempVAer.size()-1;j++)
                {
                    tempStruct1=tempVAer[j];
                    tempStruct2=tempVAer[j+1];
//                    QTime differ21=tempStruct2.time-tempStruct1.time;
                    if(tempStruct1.date!=tempStruct2.date )
                    {
                        differSecond=24*3600-(tempStruct1.time.hour()*3600+tempStruct1.time.minute()*60+tempStruct1.time.second())+tempStruct2.time.hour()*3600+tempStruct2.time.minute()*60+tempStruct2.time.second();
//                        QTime differ21();
                        if(t>=tempStruct1.time || t<=tempStruct2.time && differSecond<thresholdTime)
                        {
                            if(t>=tempStruct1.time && t<=zeroTime)
                                differSecondt1=t.hour()*3600+t.minute()*60+t.second()-(tempStruct1.time.hour()*3600+tempStruct1.time.minute()*60+tempStruct1.time.second());
                            else
                            {
                                differSecondt1=t.hour()*3600+t.minute()*60+t.second()+24*3600-(tempStruct1.time.hour()*3600+tempStruct1.time.minute()*60+tempStruct1.time.second());
                            }
//                            secondt1=differt1.hour()*3600+differt1.minute()*60+differt1.second();
//                            second21=differ21.hour()*3600+differ21.minute()*60+differ21.second();
                            tempAzimuth1=tempStruct1.azimuth;
                            tempAzimuth2=tempStruct2.azimuth;
                            tempElevation1=tempStruct1.elevation;
                            tempElevation2=tempStruct2.elevation;
                            tempAzimuth1=(float)(tempAzimuth1+tempAzimuth2)*(differSecondt1/differSecond);
                            tempElevation1=(float)(tempElevation1+tempElevation2)*(differSecondt1/differSecond);
                            matrixK[i*4]=(float)cos(tempElevation1*PI/180)*cos(tempAzimuth1*PI/180);
                            matrixK[i*4+1]=(float)cos(tempElevation1*PI/180)*sin(tempAzimuth1*PI/180);
                            matrixK[i*4+2]=(float)sin(tempElevation1*PI/180);
                            matrixK[i*4+3]=1.0;
                        }
                    }else if (d==tempStruct1.date && d==tempStruct2.date) {
                        differSecond=tempStruct2.time.hour()*3600+tempStruct2.time.minute()*60+tempStruct2.time.second()-tempStruct1.time.hour()*3600+tempStruct1.time.minute()*60+tempStruct1.time.second();
                        if(t>=tempStruct1.time && t<=tempStruct2.time && differSecond<thresholdTime)
                        {
                            differSecondt1=t.hour()*3600+t.minute()*60+t.second()-(tempStruct1.time.hour()*3600+tempStruct1.time.minute()*60+tempStruct1.time.second());
//                            secondt1=differt1.hour()*3600+differt1.minute()*60+differt1.second();
//                            second21=differ21.hour()*3600+differ21.minute()*60+differ21.second();
                            tempAzimuth1=tempStruct1.azimuth;
                            tempAzimuth2=tempStruct2.azimuth;
                            tempElevation1=tempStruct1.elevation;
                            tempElevation2=tempStruct2.elevation;
                            tempAzimuth1=(float)(tempAzimuth1+tempAzimuth2)*(differSecondt1/differSecond);
                            tempElevation1=(float)(tempElevation1+tempElevation2)*(differSecondt1/differSecond);
                            matrixK[i*4]=(float)cos(tempElevation1*PI/180)*cos(tempAzimuth1*PI/180);
                            matrixK[i*4+1]=(float)cos(tempElevation1*PI/180)*sin(tempAzimuth1*PI/180);
                            matrixK[i*4+2]=(float)sin(tempElevation1*PI/180);
                            matrixK[i*4+3]=1.0;
                        }
                    }
                }
            }
        }
    }
    MatrixXd eigenMatrix(lineK,4);
    eigenMatrix=MatrixXd::Zero(lineK,4);
    for(uint i=0;i<lineK;i++)
    {
        for(uint j=0;j<4;j++)
        {
            eigenMatrix(i,j)=matrixK[i*lineK+j];
        }
    }
    MatrixXd eigentransMatrix(4,lineK);
    eigentransMatrix=MatrixXd::Zero(4,lineK);
    eigentransMatrix=eigenMatrix.transpose();
    Matrix4d ATA= Matrix4d::Zero(4, 4);
    ATA=eigentransMatrix*eigenMatrix;
    Matrix4d inverseATA= Matrix4d::Zero(4, 4);
    inverseATA=ATA.inverse();
    gdop=sqrt(ATA(0,0)+ATA(1,1)+ATA(2,2)+ATA(3,3));
//    gdop=matrixGDOP(lineK,4,matrixK);
    delete []matrixK;
    return gdop;
}

//实际计算构造完矩阵的GDOP
float GDOP::matrixGDOP(int m, int n, float *matrix)
{
    //求转置
    float *matriXT=new float[n*m];
    for(uint j=0;j<n;j++)
    {
        for(uint i=0;i<m;i++)
        {
            matriXT[j*m+i]=matrix[i*n+j];
        }
    }
    //求AT*A
    float *ATA=new float[n*n];
    for(uint i=0;i<n;i++)
    {
        for(uint j=0;j<n;j++)
        {
            ATA[i*n+j]=0;
            for(int k=0;k<m;k++)
                ATA[i*n+j]+=matriXT[i*m+k]*matrix[k*n+j];
        }
    }

    float ATAdet=mydet(n,ATA);                          //ATA的行列式
    float *adjoint=new float[n*n];                //为ATA的伴随矩阵分配空间
    adjoint=adjointMatrix(n,ATA);                //计算ATA的伴随矩阵

    //求ATA的逆矩阵
    float *inverseMatrix=new float[n*n];      //为ATA的逆矩阵分配内存
    for(uint i=0;i<n;i++)
    {
        for(uint j=0;j<n;j++)
        {
            inverseMatrix[i*n+j]=(float)adjoint[i*n+j]/ATAdet;
        }
    }

    //计算GDOP，即根号下逆矩阵的迹，也是根号下（伴随矩阵的迹除以矩阵的行列式）
    float gdop=0.0;
    for(uint i=0;i<n;i++)
        for(uint j=0;j<n;j++)
        {
            if(i==j)
                gdop+=adjoint[i*n+j];
        }
    gdop=sqrtf(gdop/ATAdet);
    delete []matriXT;
    delete []ATA;
    delete []inverseMatrix;
    delete []adjoint;
    return gdop;
}

//迭代计算矩阵的行列式的值
float GDOP::mydet(uint n, float *matrix)
{
    float tempDet=0.0;
    if(n==1)
    {
        tempDet=matrix[0];
        return tempDet;
    }
    int n1=n-1;
    int row=0;
    int col=0;
    int x=0;
    int y=0;
    float *tempMatrix=new float[n1*n1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(row=0, x=0;x<n;x++)
            {
                if(x!=i)
                {
                    for(col=0,y=0;y<n;y++)
                        if(y!=j)
                        {
                            tempMatrix[row*n1+col]=matrix[i*n+j];
                            col++;
                        }
                    row++;
                }
            }
            tempDet+=((-1)^(i+j+2))*mydet(n1,tempMatrix)*matrix[i*n+j];
        }
    }
    delete []tempMatrix;
    return tempDet/n;
}

//求伴随矩阵
float *GDOP::adjointMatrix(int n, float *matrix)
{
    int n1=n-1;
    int row=0;
    int col=0;
    int x=0;
    int y=0;
    float *tempMatrix=new float[n1*n1];
    float *adjoint=new float[n*n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(row=0, x=0;x<n;x++)
            {
                if(x!=i)
                {
                    for(col=0,y=0;y<n;y++)
                        if(y!=j)
                        {
                            tempMatrix[row*n1+col]=matrix[i*n+j];
                            col++;
                        }
                    row++;
                }
            }
            adjoint[j*n+i]=((-1)^(i+j+2))*mydet(n1,tempMatrix);
        }
    }
    delete []tempMatrix;
    return adjoint;
}

