#ifndef N1VARIATIONTREND_H
#define N1VARIATIONTREND_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "savecount.h"
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
namespace Ui {
class N1VariationTrend;
}
//用来显示的函数
class N1VariationTrend : public QWidget
{
    Q_OBJECT

public:
    explicit N1VariationTrend(QWidget *parent = 0);
    ~N1VariationTrend();
    void setData(const vCountData &myVCount);
    void setNumberY(int y);

private:
    Ui::N1VariationTrend *ui;
    void draw(QPainter *painter);
    int sample;
    int numberY;
    QPushButton *sampleBtn;
    QLabel *sampleLabel;
    QTextEdit *sampleText;
    QHBoxLayout *sampleHLayout;
    void createWin();

    vCountData vData;

private slots:
    void onSampleBtn();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // N1VARIATIONTREND_H
