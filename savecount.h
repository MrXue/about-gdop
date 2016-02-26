#ifndef COUNTPATH
#define COUNTPATH
#include <QString>
#include <QFile>
#include <vector>
struct CountData
{
    int timeSecond;
    int count;
};

typedef std::vector<CountData> vCountData;
//用来计算和存储任意时刻看见卫星的个数
class SaveCount
{
public:
    SaveCount();
    SaveCount(QString &savePath);
    ~SaveCount();
    QString &getDataPath();
    void setDataPath(const QString &savePath);      //设置文件路径
    void setInterval(const int second);                       //设置计算时间的间隔
    void setAccessPath(const QString &NPath);       //设置Access文件的路径
//    const vCountData& readCount();
    void readCount(vCountData &myCountData);     //读取任意时刻看见卫星的个数
    void caculate();                                        //实际计算和输出到文件的函数
    void setMinDuration(const float &second);
private:
    QString accessPath;
    QString dataPath;
    float minDur;
    int interval;


};
#endif // COUNTPATH

