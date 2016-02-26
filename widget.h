#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "n1variationtrend.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setN1AccessPath(const QString &path);
    void setN2AccessPath(const QString &path);
    void setN1DataCountPath(const QString &path);
    void setN2DataCountPath(const QString &path);

private:
    Ui::Widget *ui;
    QPushButton *n1AccessBtn;
    QPushButton *n2AccessBtn;
    QPushButton *calculateCountBtn;
    QPushButton *n1AerBtn;
    QPushButton *n2AerBtn;
    QPushButton *calculateGDOPBtn;
    QPushButton *n1ShowBtn;
    QPushButton *n2ShowBtn;
    QPushButton *n1n2ShowBtn;
    QPushButton *maxN1N2Showbtn;
    QPushButton *n1ShowGDOPBtn;
    QPushButton *n2ShowGDOPBtn;
    QString n1AccessPath;
    QString n2AccessPath;
    QString n1DataCountPath;
    QString n2DataCountPath;

    N1VariationTrend *n1Widget;
    N1VariationTrend *n2Widget;
    N1VariationTrend *n1n2Widget;
    N1VariationTrend *maxN1N2Widget;

    void creatInterface();

private slots:
    void onN1AccessBtn();
    void onN2AccessBtn();
    void oncalculateCountBtn();
    void onN1AerBtn();
    void onN2AerBtn();
    void oncalculateGDOPBtn();

    void onN1ShowBtn();
    void onN2ShowBtn();
    void onN1N2ShowBtn();
    void onMaxN1N2Btn();
};

#endif // WIDGET_H
