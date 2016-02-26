#include "widget.h"
#include <QApplication>
#include "n1variationtrend.h"

//测试用
#include "gdop.h"
#include "readaer.h"
#include "readaccess.h"
#include "eigen3/Eigen/Eigen"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QString accessPath="../Scenario2/00N1-ACCESS.txt";
    QString aerPath="../Scenario2/00N1-AER.txt";
    ReadAccess readAccess;
    QDate date(2015,12,25);
    QTime time(16,55,30);
    float minDuratuion=0.0;
    readAccess.setPath(accessPath);
    readAccess.setTime(date,time);
    readAccess.setMinDuration(minDuratuion);
    int count=readAccess.getSeeSatelliteCount();
    std::vector<std::string> satellite=readAccess.getSatellite();

    ReadAer aer;
    aer.setPath(aerPath);
    AerData aerData;
    aer.readAerFile(aerData);

    GDOP n1Gdop;
    float gdop=n1Gdop.calculatorGDOP(date,time,aerData,satellite);

    return a.exec();
}
