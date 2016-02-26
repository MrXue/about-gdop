#include "savecount.h"
#include <QTextStream>
#include "readaccess.h"
SaveCount::SaveCount():minDur(0.0),interval(10)
{

}

SaveCount::SaveCount(QString &savePath)
{
    dataPath=savePath;
}

SaveCount::~SaveCount()
{

}

QString &SaveCount::getDataPath()
{
    return dataPath;
}

void SaveCount::setDataPath(const QString &savePath)
{
    dataPath=savePath;
}

void SaveCount::setInterval(const int second)
{
     interval=second;
}

void SaveCount::setAccessPath(const QString &NPath)
{
    accessPath=NPath;
}

//const vCountData &SaveCount::readCount()
//{
//    vCountData myCountData;
//    struct CountData stCountData;

//    if(dataPath.isEmpty())
//    {
//        myCountData.clear();
//        return myCountData;
//    }
//    QFile readFile(dataPath);
//    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        myCountData.clear();
//        return myCountData;
//    }
//    QTextStream in(&readFile);
//    QString temp;
//    temp=in.readLine(100);

//    while (!in.atEnd()) {
//        int day;
//        QString month;
//        int year;
//        QString time;
//        int count;
//        in>>day>>month>>year>>time>>count;
//        QTime tempTime=QTime::fromString(time,"hh:mm:ss.zzz");
//        int totalSecond=tempTime.hour()*3600+tempTime.minute()*60+tempTime.second();
//        if(day==26)
//            totalSecond+=20*3600;
//        stCountData.count=count;
//        stCountData.timeSecond=totalSecond;
//        myCountData.push_back(stCountData);
//    }
//    return myCountData;
//}

void SaveCount::readCount(vCountData &myCountData)
{
    struct CountData stCountData;

    if(dataPath.isEmpty())
    {
        return;
    }
    QFile readFile(dataPath);
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in(&readFile);
    QString temp;
    temp=in.readLine(100);

    while (!in.atEnd()) {
        int day;
        QString month;
        int year;
        QString time;
        int count;
        in>>day>>month>>year>>time>>count;
        QTime tempTime=QTime::fromString(time,"hh:mm:ss.zzz");
        int totalSecond=tempTime.hour()*3600+tempTime.minute()*60+tempTime.second()-14400;
        if(day==26)
            totalSecond+=72000;
        stCountData.count=count;
        stCountData.timeSecond=totalSecond;
        myCountData.push_back(stCountData);
    }
}

void SaveCount::caculate()
{
    QFile saveFile(dataPath);
    if(!saveFile.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    QTextStream out(&saveFile);
    out<<"DateTime                "<<"                 "<<"See The Satellite Counts"<<"\n";
    QDate startDate(2015,12,25);
    QTime startTime(04,00,00);
    QDate stopDate(2015,12,25);
    QTime stopTime(23,59,59);
    ReadAccess accessN1;
    accessN1.setPath(accessPath);
    accessN1.setMinDuration(minDur);
    for(;startTime<=stopTime && startDate==stopDate;startTime=startTime.addSecs(interval))
    {
        if(startTime<=QTime(0,0,59))
        {
//            startDate=startDate.addDays(1);
            break;
        }
        accessN1.setTime(startDate,startTime);
        int count=accessN1.getSeeSatelliteCount();
        QString datetime=startDate.toString("dd MM yyyy")+"   "+startTime.toString("hh:mm:ss.zzz");
        out<<datetime<<"               "<<count<<"\n";
    }
    startTime=QTime(0,0,0);
    startDate=QDate(2015,12,26);
    stopTime=QTime(3,59,59);
    stopDate=QDate(2015,12,26);
    for(;startTime<=stopTime && startDate==stopDate;startTime=startTime.addSecs(interval))
    {
        if(startTime>QTime(4,0,0))
            break;
        accessN1.setTime(startDate,startTime);
        int count=accessN1.getSeeSatelliteCount();
        QString datetime=startDate.toString("dd MM yyyy")+"   "+startTime.toString("hh:mm:ss.zzz");
        out<<datetime<<"               "<<count<<"\n";
    }
    saveFile.close();
    //    QMessageBox::information(this,QStringLiteral("Information"),QStringLiteral("天线所看到卫星数计算完毕"),QMessageBox::Ok);
}

void SaveCount::setMinDuration(const float &second)
{

    minDur=second;
}

