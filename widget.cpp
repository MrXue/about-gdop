#include "widget.h"
#include "savecount.h"
#include "readaccess.h"

#include "ui_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QProgressDialog>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    creatInterface();
    adjustSize();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setN1AccessPath(const QString &path)
{
    n1AccessPath=path;
}

void Widget::setN2AccessPath(const QString &path)
{
    n2AccessPath=path;
}

void Widget::setN1DataCountPath(const QString &path)
{
    n1DataCountPath=path;
}

void Widget::setN2DataCountPath(const QString &path)
{
    n2DataCountPath=path;
}

void Widget::creatInterface()
{
    n1AccessBtn=new QPushButton(tr("Open N1 Access"),this);
    n1AccessBtn->setMinimumSize(100,30);
    connect(n1AccessBtn,SIGNAL(clicked()),this,SLOT(onN1AccessBtn()));

    n2AccessBtn=new QPushButton(tr("Open N2 Access"),this);
    n2AccessBtn->setMinimumSize(100,30);
    connect(n2AccessBtn,SIGNAL(clicked()),this,SLOT(onN2AccessBtn()));

    calculateCountBtn=new QPushButton(tr("Calculate Count"),this);
    calculateCountBtn->setMinimumSize(100,30);
    connect(calculateCountBtn,SIGNAL(clicked()),this,SLOT(oncalculateCountBtn()));

    n1AerBtn=new QPushButton(tr("Open N1 AER"),this);
    n1AerBtn->setMinimumSize(100,30);
    connect(n1AerBtn,SIGNAL(clicked()),this,SLOT(onN1AerBtn()));

    n2AerBtn=new QPushButton(tr("Open N2 AER"),this);
    n2AerBtn->setMinimumSize(100,30);
    connect(n2AerBtn,SIGNAL(clicked()),this,SLOT(onN2AerBtn()));

    calculateGDOPBtn=new QPushButton(tr("Calculate GDOP"),this);
    calculateGDOPBtn->setMinimumSize(100,30);
    connect(calculateGDOPBtn,SIGNAL(clicked()),this,SLOT(oncalculateGDOPBtn()));

    n1ShowBtn=new QPushButton(tr("Show N1"),this);
    n1ShowBtn->setMinimumSize(100,30);
    connect(n1ShowBtn,SIGNAL(clicked()),this,SLOT(onN1ShowBtn()));

    n2ShowBtn=new QPushButton(tr("Show N2"),this);
    n2ShowBtn->setMinimumSize(100,30);
    connect(n2ShowBtn,SIGNAL(clicked()),this,SLOT(onN2ShowBtn()));

    n1n2ShowBtn=new QPushButton(tr("Show N1+N2"),this);
    n1n2ShowBtn->setMinimumSize(100,30);
    connect(n1n2ShowBtn,SIGNAL(clicked()),this,SLOT(onN1N2ShowBtn()));

    maxN1N2Showbtn=new QPushButton(tr("Show Max(N1,N2)"),this);
    maxN1N2Showbtn->setMinimumSize(100,30);
    connect(maxN1N2Showbtn,SIGNAL(clicked()),this,SLOT(onMaxN1N2Btn()));

    n1ShowGDOPBtn=new QPushButton(tr("Show N1 GDOP"));
    n1ShowGDOPBtn->setMinimumSize(100,30);

    n2ShowGDOPBtn=new QPushButton(tr("Show N2 GDOP"));
    n2ShowGDOPBtn->setMinimumSize(100,30);

    QHBoxLayout *n1HLayout=new QHBoxLayout;
    n1HLayout->addWidget(n1AccessBtn);
    n1HLayout->addStretch();
    n1HLayout->addWidget(n1AerBtn);

    QHBoxLayout *n2HLayout=new QHBoxLayout;
    n2HLayout->addWidget(n2AccessBtn);
    n2HLayout->addStretch();
    n2HLayout->addWidget(n2AerBtn);

    QHBoxLayout *calculateHLayout=new QHBoxLayout;
    calculateHLayout->addWidget(calculateCountBtn);
    calculateHLayout->addStretch();
    calculateHLayout->addWidget(calculateGDOPBtn);

    QHBoxLayout *showSingleNLay=new QHBoxLayout;
    showSingleNLay->addWidget(n1ShowBtn);
    showSingleNLay->addStretch();
    showSingleNLay->addWidget(n2ShowBtn);

    QHBoxLayout *showN1n2Layout=new QHBoxLayout;
    showN1n2Layout->addWidget(n1n2ShowBtn);
    showN1n2Layout->addStretch();
    showN1n2Layout->addWidget(maxN1N2Showbtn);

    QHBoxLayout *showGDOPHLayout=new QHBoxLayout;
    showGDOPHLayout->addWidget(n1ShowGDOPBtn);
    showGDOPHLayout->addStretch();
    showGDOPHLayout->addWidget(n2ShowGDOPBtn);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(n1HLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(n2HLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(calculateHLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(showSingleNLay);
    mainLayout->addStretch();
    mainLayout->addLayout(showN1n2Layout);
    mainLayout->addStretch();
    mainLayout->addLayout(showGDOPHLayout);

    setLayout(mainLayout);
}

void Widget::onN1AccessBtn()
{
    n1AccessPath=QFileDialog::getOpenFileName(this,tr("Open N1 Access File"),"D:/",tr("Access (*.txt)"));
}

void Widget::onN2AccessBtn()
{
    n2AccessPath=QFileDialog::getOpenFileName(this,tr("Open N2 Access File"),n1AccessPath,tr("Access (*.txt)"));
}

void Widget::oncalculateCountBtn()
{
      //计算每隔10秒所看的卫星数
    QFileInfo info;
    info=QFileInfo(n1AccessPath);
    n1DataCountPath=info.absolutePath()+"/"+"00N1-60DataCount.txt";
    SaveCount n1SaveCount;
    n1SaveCount.setDataPath(n1DataCountPath);
    n1SaveCount.setAccessPath(n1AccessPath);
    n1SaveCount.setMinDuration(60.0);
    n1SaveCount.setInterval(10);
    n1SaveCount.caculate();
    QMessageBox::information(this,tr("Information"),QStringLiteral("N1所看到卫星数计算完毕"),QMessageBox::Ok);

    QFileInfo infon2;
    infon2=QFileInfo(n2AccessPath);
    n2DataCountPath=infon2.absolutePath()+"/"+"00N2-60DataCount.txt";
    SaveCount n2SaveCount;
    n2SaveCount.setDataPath(n2DataCountPath);
    n2SaveCount.setAccessPath(n2AccessPath);
    n2SaveCount.setMinDuration(60.0);
    n2SaveCount.setInterval(10);
    n2SaveCount.caculate();
    QMessageBox::information(this,tr("Information"),QStringLiteral("N2所看到卫星数计算完毕"),QMessageBox::Ok);

//    QProgressDialog process(this);
//    process.setLabelText(QStringLiteral("正在计算N1所看到的卫星数..."));
//    process.setRange(0,8640);
//    process.setModal(true);
//    process.setCancelButtonText(QStringLiteral("取消"));
//    if(!n1AccessPath.isEmpty()&&!n1DataCountPath.isEmpty())
//    {
//        process.show();
//        QFile n1DataFile(n1DataCountPath);
//        if(!n1DataFile.open(QIODevice::WriteOnly|QIODevice::Text))
//            return;
//        QTextStream n1out(&n1DataFile);
//        n1out<<"DateTime              "<<"                 "<<"See The Satellite Counts"<<"\n";
//        QDate startDate(2015,12,25);
//        QTime startTime(04,00,00);
//        QDate stopDate(2015,12,25);
//        QTime stopTime(23,59,59);
//        int iProcess=0;
//        ReadAccess accessN1;
//        accessN1.setPath(n1AccessPath);
//        float dur=0.0;
//        accessN1.setMinDuration(dur);

//        for(;startTime<=stopTime&&startDate==stopDate;startTime=startTime.addSecs(10))
//        {
//            if(startTime<=QTime(0,0,59))
//            {
//                startDate=startDate.addDays(1);
//                break;
//            }
//            accessN1.setTime(startDate,startTime);

//            int count=accessN1.getSeeSatelliteCount();
//            QString datetime=startDate.toString("dd MM yyyy")+"   "+startTime.toString("hh:mm:ss.zzz");
//            n1out<<datetime<<"               "<<count<<"\n";
//            iProcess++;
//            process.setValue(iProcess);
//            if(process.wasCanceled())
//                return;
//        }
//        startTime=QTime(0,0,10);
//        startDate=QDate(2015,12,26);
//        stopTime=QTime(3,59,59);
//        stopDate=QDate(2015,12,26);
//        for(;startTime<stopTime&&startDate==stopDate;startTime=startTime.addSecs(10))
//        {
//            if(startTime>QTime(4,0,0))
//                break;

//            accessN1.setTime(startDate,startTime);
//            int count=accessN1.getSeeSatelliteCount();
//            QString datetime=startDate.toString("dd MM yyyy")+"   "+startTime.toString("hh:mm:ss.zzz");
//            n1out<<datetime<<"               "<<count<<"\n";
//            process.setValue(iProcess);
//            if(process.wasCanceled())
//                return;
//        }
//        n1DataFile.close();
//        process.close();
//        QMessageBox::information(this,tr("Information"),QStringLiteral("N1所看到卫星数计算完毕"),QMessageBox::Ok);
//     }

//    QFileInfo infoN2;
//    infoN2=QFileInfo(n2AccessPath);
//    n2DataCountPath=infoN2.absolutePath()+"/"+"00N2-DataCount.txt";
//    QProgressDialog processN2(this);
//    processN2.setLabelText(QStringLiteral("正在计算N2所看到的卫星数..."));
//    processN2.setRange(0,8640);
//    processN2.setModal(true);
//    processN2.setCancelButtonText(QStringLiteral("取消"));
//    if(!n2AccessPath.isEmpty()&&!n2DataCountPath.isEmpty())
//    {
//        processN2.show();
//        int iProcess=0;
//            QFile n2DataFile(n2DataCountPath);
//            if(!n2DataFile.open(QIODevice::WriteOnly|QIODevice::Text))
//                return;
//            QTextStream n2out(&n2DataFile);
//            n2out<<"DateTime              "<<"                 "<<"See The Satellite Numbers"<<"\n";
//            QDate n2StartDate(2015,12,25);
//            QTime n2StartTime(04,00,00);
//            QDate n2StopDate(2015,12,25);
//            QTime n2StopTime(23,59,59);
//            ReadAccess accessN2;
//            accessN2.setPath(n2AccessPath);
//            float dur=0.0;
//            accessN2.setMinDuration(dur);
//            for(;n2StartTime<=n2StopTime&&n2StartDate==n2StopDate;n2StartTime=n2StartTime.addSecs(10))
//            {
//                if(n2StartTime<=QTime(0,0,59))
//                    n2StartDate=n2StartDate.addDays(1);
//                accessN2.setTime(n2StartDate,n2StartTime);
//                int count=accessN2.getSeeSatelliteCount();
//                QString datetime=n2StartDate.toString("dd MM yyyy")+"   "+n2StartTime.toString("hh:mm:ss.zzz");
//                n2out<<datetime<<"               "<<count<<"\n";
//                iProcess++;
//                processN2.setValue(iProcess);
//                if(processN2.wasCanceled())
//                    return;
//            }
//            n2StartTime=QTime(0,0,10);
//            n2StartDate=QDate(2015,12,26);
//            n2StopTime=QTime(3,59,59);
//            n2StopDate=QDate(2015,12,26);

//            for(;n2StartTime<n2StopTime&&n2StartDate==n2StopDate;n2StartTime=n2StartTime.addSecs(10))
//            {
//                if(n2StartTime>QTime(4,0,0))
//                    break;
//                accessN2.setTime(n2StartDate,n2StartTime);
//                accessN2.setMinDuration(dur);
//                int count=accessN2.getSeeSatelliteCount();
//                QString datetime=n2StartDate.toString("dd MM yyyy")+"   "+n2StartTime.toString("hh:mm:ss.zzz");
//                n2out<<datetime<<"               "<<count<<"\n";
//                iProcess++;
//                processN2.setValue(iProcess);
//                if(processN2.wasCanceled())
//                    return;
//            }
//            n2DataFile.close();
//            processN2.close();
//            QMessageBox::information(this,tr("Information"),QStringLiteral("N2所看到卫星数计算完毕"),QMessageBox::Ok);
//    }
}

void Widget::onN1AerBtn()
{

}

void Widget::onN2AerBtn()
{

}

void Widget::oncalculateGDOPBtn()
{

}

void Widget::onN1ShowBtn()
{
    if(n1DataCountPath.isEmpty())
    {
        QString fileName=QFileDialog::getOpenFileName(this,tr("Open N1 Data Count"),"D:/",tr("Data (*.txt)"));
        if (fileName.isEmpty())
            return;
        n1DataCountPath=fileName;
    }
    SaveCount *n1SaveCount=new SaveCount;
    n1SaveCount->setDataPath(n1DataCountPath);
    vCountData myCountData;
    n1SaveCount->readCount(myCountData);
    n1Widget=new N1VariationTrend;
    n1Widget->setData(myCountData);
//    n1Widget->setWindowTitle(tr("天线N1看到卫星的个数随时间变化的规律"));
    n1Widget->setWindowTitle(QStringLiteral("天线N1看到卫星的个数随时间变化的规律"));
    n1Widget->show();
}

void Widget::onN2ShowBtn()
{
    if(n2DataCountPath.isEmpty())
    {
        QString fileName=QFileDialog::getOpenFileName(this,tr("Open N2 Data Count"),"D:/",tr("Data (*.txt)"));
        if (fileName.isEmpty())
            return;
        n2DataCountPath=fileName;
    }
    SaveCount *n2SaveCount=new SaveCount;
    n2SaveCount->setDataPath(n2DataCountPath);
    vCountData myCountData;
    n2SaveCount->readCount(myCountData);
    n2Widget=new N1VariationTrend;
    n2Widget->setData(myCountData);
    n2Widget->setWindowTitle(QStringLiteral("天线N2看到卫星的个数随时间变化的规律"));
    n2Widget->show();
}

void Widget::onN1N2ShowBtn()
{
    if(n1DataCountPath.isEmpty()||n2DataCountPath.isEmpty())
    {
        n1DataCountPath=QFileDialog::getOpenFileName(this,tr("Open N1 Data Count"),"D:/",tr("Data (*.txt)"));
        if(n1DataCountPath.isEmpty())
            return;
        n2DataCountPath=QFileDialog::getOpenFileName(this,tr("Open N2 Data Count"),n1DataCountPath,tr("Data (*.txt)"));
        if(n2DataCountPath.isEmpty())
            return;
    }

    SaveCount *n1SaveCount=new SaveCount;
    n1SaveCount->setDataPath(n1DataCountPath);
    vCountData n1CountData;
    n1SaveCount->readCount(n1CountData);

    SaveCount *n2SaveCount=new SaveCount;
    n2SaveCount->setDataPath(n2DataCountPath);
    vCountData n2CountData;
    n2SaveCount->readCount(n2CountData);

    vCountData n1n2CountData;
    for(uint i=0;i<n1CountData.size();++i)
    {
       struct  CountData n1=n1CountData[i];
       struct  CountData n2=n2CountData[i];
       n1.count+=n2.count;
       n1n2CountData.push_back(n1);
    }
    n1n2Widget=new N1VariationTrend;
    n1n2Widget->setData(n1n2CountData);
    n1n2Widget->setNumberY(24);
    n1n2Widget->setWindowTitle(QStringLiteral("天线N1和N2所看到卫星个数的和随时间变化的规律"));
    n1n2Widget->show();
}

void Widget::onMaxN1N2Btn()
{
    if(n1DataCountPath.isEmpty()||n2DataCountPath.isEmpty())
    {
        n1DataCountPath=QFileDialog::getOpenFileName(this,tr("Open N1 Data Count"),"D:/",tr("Data (*.txt)"));
        if(n1DataCountPath.isEmpty())
            return;
        n2DataCountPath=QFileDialog::getOpenFileName(this,tr("Open N2 Data Count"),n1DataCountPath,tr("Data (*.txt)"));
        if(n2DataCountPath.isEmpty())
            return;
    }

    SaveCount *n1SaveCount=new SaveCount;
    n1SaveCount->setDataPath(n1DataCountPath);
    vCountData n1CountData;
    n1SaveCount->readCount(n1CountData);

    SaveCount *n2SaveCount=new SaveCount;
    n2SaveCount->setDataPath(n2DataCountPath);
    vCountData n2CountData;
    n2SaveCount->readCount(n2CountData);

    vCountData n1n2CountData;
    for(uint i=0;i<n1CountData.size();++i)
    {
       struct  CountData n1=n1CountData[i];
       struct  CountData n2=n2CountData[i];
       n1.count=n1.count>n2.count ? n1.count:n2.count;
       n1n2CountData.push_back(n1);
    }
    maxN1N2Widget=new N1VariationTrend;
    maxN1N2Widget->setData(n1n2CountData);
    maxN1N2Widget->setWindowTitle(QStringLiteral("天线N1和N2看到卫星个数的最大值随时间变化的规律"));
    maxN1N2Widget->show();
}
