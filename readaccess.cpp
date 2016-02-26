#include "readaccess.h"
#include <QDate>
#include <QTime>
#include <QFile>
#include <QTextStream>

ReadAccess::ReadAccess():minDuration(0.0)
{

}

ReadAccess::ReadAccess(const QString &filePath):minDuration(0.0)
{
    path=filePath;
    readFile();
}

ReadAccess::~ReadAccess()
{

}

void ReadAccess::setPath(const QString &filePath)
{
    path=filePath;
    readFile();
}

int ReadAccess::getSeeSatelliteCount()
{
    int count=0;
    if(saveData.empty())
        return 0;
    MyData::iterator pos;
    std::vector<std::string> tempVector;
    satellite.swap(tempVector);
    for(pos=saveData.begin();pos!=saveData.end();++pos)
    {
        bool judget=false;
        std::vector<StaStoDur> tempStaStoDur;
        tempStaStoDur=pos->second;
        for(uint j=0;j<tempStaStoDur.size();j++)
        {
            StaStoDur temp=tempStaStoDur[j];
            float tempDur=temp.duration;
            QDate tempStartDate=temp.startDate;
            QTime tempStartTime=temp.startTime;
            QDate tempStopDate=temp.stopDate;
            QTime tempStopTime=temp.stopTime;
            if(tempStartDate.day()==tempStopDate.day())
            {
                if(date.day()==tempStartDate.day() && time>=tempStartTime && time<tempStopTime && tempDur>=minDuration)
                {
                    judget=true;
                    break;
                }
            }else if (tempStartDate.day()<tempStopDate.day()) {
                if(time>=tempStartTime||time<tempStopTime && tempDur>=minDuration)
                {
                    judget=true;
                    break;
                }
            }
          }
        if(judget)
        {
             count++;
             std::string tempSatellite=pos->first;
             satellite.push_back(tempSatellite);
        }
    }
    return count;
}

void ReadAccess::setTime(const QDate &mDate,const  QTime &mTime)
{
//    int y=mDate.year();
//    int m=mDate.month();
//    int d=mDate.day();
//    if(!date.setDate(y,m,d))
//        return;
//    int h=mTime.hour();
//    int mi=mTime.minute();
//    int s=mTime.second();
//    int ms=mTime.msec();
//    if(!time.setHMS(h,mi,s,ms))
//        return;
    date=mDate;
    time=mTime;
}

void ReadAccess::setTime(const QDateTime &mDatetime)
{
    dateTime=mDatetime;
}

void ReadAccess::setMinDuration(const float &second)
{
    minDuration=second;
}

std::vector<std::string> ReadAccess::getSatellite()
{
    return satellite;
}

void ReadAccess::getDateTime(QDate &d, QTime &t)
{
    d=date;
    t=time;
}

void ReadAccess::readFile()
{
    if(path.isEmpty())
        return;
    QFile accessFile(path);
    if(accessFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&accessFile);
        QString temp;
        QString nToGPS;
        temp=in.readLine(1000);
        temp=in.readLine(100);
        temp=in.readLine(1000);
        temp=in.readLine(10);
        temp=in.readLine(10);
        while (!in.atEnd()) {
            nToGPS=in.readLine(255);
            temp=in.readLine(255);
            temp=in.readLine(255);
            temp=in.readLine(255);
            QString accessID;
            int year1=2015;
            int day1=0;
            QString month1;
            int startMonth=0;
            QString time1;
            int year2=2015;
            int day2=0;
            int stopMonth=0;
            QString month2;
            QString time2;
            float duration=0.0;
            std::vector<StaStoDur> vStartStoDur;
            while (1) {
                in>>accessID;
                if(accessID=="Global")
                    break;
                in>>day1>>month1>>year1>>time1>>day2>>month2>>year2>>time2>>duration;
                if(month1=="Dec")
                    startMonth=12;
                if(month2=="Dec")
                    stopMonth=12;
                QDate startDate(year1,startMonth,day1);
                QTime startTime=QTime::fromString(time1,"hh:mm:ss.zzz");
                QDate stopDate(year2,stopMonth,day2);
                QTime stopTime=QTime::fromString(time2,"hh:mm:ss.zzz");
//                QDateTime startDateTime=QDateTime(startDate,startTime);
//                QDateTime stopDateTime=QDateTime(stopDate,stopTime);
                struct StaStoDur startstopDur;
                startstopDur.accessID=accessID.toInt();
                startstopDur.duration=duration;
                startstopDur.startDate=startDate;
                startstopDur.startTime=startTime;
                startstopDur.stopDate=stopDate;
                startstopDur.stopTime=stopTime;
                vStartStoDur.push_back(startstopDur);
            }
            std::string strN2GPS=nToGPS.toStdString();
            saveData.insert(std::make_pair(strN2GPS,vStartStoDur));
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
            temp=in.readLine(100);
        }
    }
    accessFile.close();
}

void ReadAccess::caculatorCount()
{

}

