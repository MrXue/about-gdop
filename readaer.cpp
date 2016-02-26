#include "readaer.h"

#include <QFile>
#include <QTextStream>

ReadAer::ReadAer()
{

}

ReadAer::~ReadAer()
{

}

void ReadAer::setPath(const QString &path)
{
    filePath=path;
}

void ReadAer::readAerFile(AerData &aerData)
{
    if(filePath.isEmpty())
        return;
    QFile aerFile(filePath);
    if(aerFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&aerFile);
        QString temp;
        QString nToGPS;
        QString day;
        QString month;
        int year=2015;
        QString aertime;
        float aerAzimuth=0.0;
        float aerElevation=0.0;
        double aerRange=0.0;
        temp=in.readLine(1000);
        temp=in.readLine(128);
        temp=in.readLine(1000);
        temp=in.readLine(128);
        temp=in.readLine(128);
        while (!in.atEnd()) {
            std::vector<AerStruct> tempVAerStruct;
            struct AerStruct tempStruct;
            QTime tempTime;
            nToGPS=in.readLine(128);
            temp=in.readLine(128);
                while (1) {
                    temp=in.readLine(128);
                    if(temp=="Global Statistics")
                        break;
                    temp=in.readLine(128);
                    while (1) {
                        in>>day;
                        if(day=="Min")
                        {
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            temp=in.readLine(128);
                            break;
                        }
                        in>>month>>year>>aertime>>aerAzimuth>>aerElevation>>aerRange;
                        int tempMonth=0;
                        int tempDay=0;
                        if(month=="Dec")
                            tempMonth=12;
                        if(day=="25")
                            tempDay=25;
                        if(day=="26")
                            tempDay=26;
                        QDate tempDate(year,tempMonth,tempDay);
                        tempTime=QTime::fromString(aertime,"hh:mm:ss.zzz");
                        tempStruct.date=tempDate;
                        tempStruct.time=tempTime;
                        tempStruct.azimuth=aerAzimuth;
                        tempStruct.elevation=aerElevation;
                        tempStruct.range=aerRange;
                        tempVAerStruct.push_back(tempStruct);
                    }
                }
                aerData.insert(std::make_pair(nToGPS.toStdString(),tempVAerStruct));
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
                temp=in.readLine(128);
        }
    }
    aerFile.close();
}
