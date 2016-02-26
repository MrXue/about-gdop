#ifndef READAER_H
#define READAER_H


#include <vector>
#include <map>
#include <string>
#include <QString>

#include <QDate>
#include <QTime>

//用来存储每一行的数据
struct AerStruct
{
    QDate date;
    QTime time;
    float azimuth;
    float elevation;
    double range;
};
//用来存储每一颗卫星的数据，string卫星名
typedef std::map<std::string,std::vector<AerStruct>> AerData;

class ReadAer
{
public:
    ReadAer();
    ~ReadAer();
    void setPath(const QString &path);             //设置读取Aer的路径
    void readAerFile(AerData &aerData);         //读取数据并用AerData存储数据

private:
    QString filePath;
};

#endif // READAER_H
