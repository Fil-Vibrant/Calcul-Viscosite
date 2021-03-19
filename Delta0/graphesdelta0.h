#ifndef GRAPHESDELTA0_H
#define GRAPHESDELTA0_H

#include <QObject>
#include <QtCharts>
#include <vector>
#include <delta0.h>

using namespace QtCharts;
using namespace std;

class GraphesDelta0 : public QObject
{
    Q_OBJECT

private:/*
    vector<double> Xexp,
                   frequencies,
                   Xcal,
                   Yexp,
                   Ycal;*/

    Delta0 *d0;

    QChart* xChart;
    QScatterSeries* xExpSerie;
    QSplineSeries* xCalSerie;
    QChartView* xGraph;

    QChart* yChart;
    QScatterSeries* yExpSerie;
    QSplineSeries* yCalSerie;
    //QChartView* yGraph;

public:
    explicit GraphesDelta0(QObject *parent = nullptr);

    QChartView* drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> frequencies);
    QChart* drawYGraph();

signals:

};

#endif // GRAPHESDELTA0_H
