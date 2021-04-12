#ifndef GRAPHESDELTA0_H
#define GRAPHESDELTA0_H

#include <QObject>
#include <QtCharts>
#include <vector>
#include <delta0.h>
#include <mainwindow.h>

using namespace QtCharts;
using namespace std;

class GraphesDelta0 : public QObject
{
    Q_OBJECT

private:
    Delta0 *d0;

    QChart* xChart;
    QScatterSeries* xExpSerie;
    QSplineSeries* xCalSerie;
    QChartView* xGraph;

    QValueAxis *xf, *yf, *x, *y;

    QChart* yChart;
    QScatterSeries* yExpSerie;
    QSplineSeries* yCalSerie;
    QChartView* yGraph;

public:
    explicit GraphesDelta0(QObject *parent = nullptr);

    QChart* drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> frequencies);
    QChart* drawYGraph(vector<double> yExp, vector<double> yCal, vector<double> frequencies);

signals:

};

#endif // GRAPHESDELTA0_H
