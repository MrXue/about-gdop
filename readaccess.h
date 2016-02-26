#ifndef READN_H
#define READN_H

#include <map>
#include <string>
#include <vector>
#include <QDateTime>
class QDate;
class QTime;
struct StaStoDur{
    int accessID;
    QDate startDate;
    QTime startTime;
    QDate stopDate;
    QTime stopTime;
//    QDateTime startDTime=new QDateTime();
//    QDateTime stopDTime=new QDateTime();
    float duration;
};

typedef std::map<std::string,std::vector<StaStoDur>> MyData;
class ReadAccess
{
public:
    ReadAccess();
    ReadAccess(const QString &filePath);
    ~ReadAccess();
    void setPath(const QString &filePath);   //设置access文件路径
    int getSeeSatelliteCount();                       //获得任意时间天线所看到的卫星个数


    void setTime(const QDate &mTate,const QTime &mTime); //设置时间
    void setTime(const QDateTime &mDatetime);            //设置时间
    void setMinDuration(const float &second);                 //设置看见卫星最小时长，默认为1分钟
    std::vector<std::string> getSatellite();                           //获取任意时刻看到的卫星的编号
    void getDateTime(QDate &d,QTime &t);          //获取这一刻的时间

private:
    void readFile();                //读取文件到saveData中
    void caculatorCount();    // 计算天线所看到的卫星个数

    QString path;                              //access文件路径
    float minDuration;                      //看见卫星最小时长
//    StaStoDur time;
    MyData saveData;                      //存储数据
    std::vector<std::string> satellite;
    QDate date;
    QTime time;
    QDateTime dateTime;
};

#endif // READN_H
