#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "calculs.h"
#include <vector>
//#include <QtCharts>

//using namespace QtCharts;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void delta0ExpGraph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    Calculs calculs;
/*
    QChart *chart;
    QLineSeries *serie;
*/
    vector<double> dvexp,
                   frequencies;
};
#endif // WIDGET_H
