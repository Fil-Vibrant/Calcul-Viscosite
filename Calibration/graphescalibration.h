#ifndef GRAPHESCALIBRATION_H
#define GRAPHESCALIBRATION_H

#include <QObject>
#include <QtCharts>
#include <vector>

using namespace QtCharts;
using namespace std;

class GraphesCalibration : public QObject
{
    Q_OBJECT

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
    explicit GraphesCalibration(QObject *parent = nullptr);

    QChart* drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> frequencies);
    QChart* drawYGraph(vector<double> yExp, vector<double> yCal, vector<double> frequencies);
signals:

};

#endif // GRAPHESCALIBRATION_H
