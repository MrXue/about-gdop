#include "n1variationtrend.h"
#include "ui_n1variationtrend.h"
#include <QPalette>
N1VariationTrend::N1VariationTrend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::N1VariationTrend),sample(10),numberY(12)
{
    ui->setupUi(this);
//    QPalette palette;
//    palette.setColor(QPalette::Background,QColor(0,0,0));
//    this->setPalette(palette);
    createWin();
}

N1VariationTrend::~N1VariationTrend()
{
    delete ui;
}

void N1VariationTrend::setData(const vCountData &myVCount)
{
    vData=myVCount;
}

void N1VariationTrend::setNumberY(int y)
{
    if(y<=0)
    {
        numberY=12;
        return;
    }
    numberY=y;
}

void N1VariationTrend::draw(QPainter *painter)
{
    QFontMetrics metrics=painter->fontMetrics();
    int textHeight=metrics.ascent()+metrics.descent();
    int leftWidth=metrics.width(tr("100"))+5;
    int rightWidth=metrics.width(tr("1000"));
    int width=this->width()-leftWidth-rightWidth;
    int height=this->height()-5*textHeight;

    float deltaX=(float)width/12.0f;
    float deltaY=(float)height/numberY;

//    painter->drawRect(5,5,this->width()-15,this->height()-15);
    painter->translate(leftWidth,textHeight+height);
    painter->drawLine(0,0,width,0); //X
    painter->drawText(width,0,tr("Time"));
    int iCount=0;
    for(int i=4;i<=24;i+=2)
    {
        QString time=QString("%1").arg(i);
        painter->drawLine(deltaX*iCount,0,deltaX*iCount,4);
        painter->drawText(deltaX*iCount,4+textHeight,time);
        iCount++;
    }
    painter->drawLine(deltaX*11,0,deltaX*11,4);
    painter->drawLine(deltaX*12,0,deltaX*12,4);
    painter->drawText(deltaX*11,4+textHeight,tr("2"));
    painter->drawText(deltaX*12,4+textHeight,tr("4"));

    painter->drawLine(0,0,0,-height);//Y
    painter->drawText(-metrics.width(tr("N")),-(height+textHeight/4),tr("N"));
    for(int i=0;i<=numberY;++i)
    {
        QString value=QString("%1").arg(i);
        int stringWidth=metrics.width(value);
        painter->drawLine(-4,-i*deltaY,0,-i*deltaY);
        painter->drawText(-stringWidth-4,-(deltaY*i+textHeight/2-metrics.ascent()),value);
    }
    if(vData.empty())
        return;
    QPainterPath path;
    float deltaDataX=(float)width/8640;
    int tempSample=(int)sample/10;
    for(uint i=0;i<vData.size()/tempSample-1;++i)
    {
        struct CountData temp1CountData=vData[i*tempSample];
//        struct CountData temp2CountData=myCountData[i+sample];
//        struct CountData temp3CountData=myCountData[i+2*sample];
        path.lineTo(i*tempSample*deltaDataX,-temp1CountData.count*deltaY);
//        path.cubicTo(i*deltaDataX,-temp1CountData.count*deltaY,(i+sample)*deltaDataX,-temp2CountData.count*deltaY,(i+2*sample)*deltaDataX,-temp3CountData.count*deltaY);
//        painter->drawLine(i*deltaDataX,-temp1CountData.count*deltaY,(i+1)*deltaDataX,-temp2CountData.count*deltaY);
    }
    painter->drawPath(path);
}

void N1VariationTrend::createWin()
{
    sampleBtn=new QPushButton(tr("OK"));
    connect(sampleBtn,SIGNAL(clicked()),this,SLOT(onSampleBtn()));
    sampleBtn->setMinimumSize(80,25);
    sampleBtn->setMaximumSize(80,25);

//    sampleBtn->move(this->width(),this->height());
//    sampleBtn->setGeometry(this->width()-50,this->height()-30,45,25);

    sampleLabel=new QLabel(QStringLiteral("采样间隔:"));
//    sampleLabel->setMaximumSize(sampleBtn->width(),sampleBtn->height());
    sampleLabel->setMinimumSize(80,25);
    sampleLabel->setMaximumSize(80,25);
//    sampleLabel->setStyleSheet("QLabel{background:rgb(255,255,255);color:black}");
    sampleText=new QTextEdit;
    sampleText->setMinimumSize(60,25);
    sampleText->setMaximumSize(60,25);

    sampleHLayout=new QHBoxLayout;
    sampleHLayout->addStretch();
    sampleHLayout->addWidget(sampleLabel);
    sampleHLayout->addWidget(sampleText);
    sampleHLayout->addWidget(sampleBtn);
    setLayout(sampleHLayout);
    int move=sampleBtn->width()+sampleLabel->width()+sampleText->width();
    sampleHLayout->setGeometry(QRect(this->width()-move-5,this->height()-50,move,25));
}

void N1VariationTrend::onSampleBtn()
{
    sample=sampleText->toPlainText().toInt();
    if(sample==0||sample<0)
    {
        sample=10;
        return;
    }
    this->repaint();
}

void N1VariationTrend::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setCapStyle(Qt::RoundCap);
    pen.setStyle(Qt::SolidLine);
//    pen.setColor(QColor(0,0,255));
    painter.setPen(pen);
    draw(&painter);
}

void N1VariationTrend::resizeEvent(QResizeEvent *)
{
    int move=sampleBtn->width()+sampleLabel->width()+sampleText->width();
    sampleHLayout->setGeometry(QRect(this->width()-move-5,this->height()-40,move,25));
}
