#ifndef GRAPHES_H
#define GRAPHES_H

#include <QObject>
#include <QtCharts>
#include <vector>

using namespace std;
using namespace QtCharts;

class Graphes : public QObject
{
    Q_OBJECT
    QScatterSeries *xexpserie, *yexpserie;
    QSplineSeries *xcalserie, *ycalserie;

    QChart* xChart;
    QChart* yChart;

    QValueAxis *xf, *yf, *x, *y;
public:
    explicit Graphes(QObject *parent = nullptr);
    QChart* drawXD0Graph(vector<double> xExp, vector<double> xCal, vector<double> freq);
    QChart* drawYD0Graph(vector<double> yExp, vector<double> yCal, vector<double> freq);
    QChart* drawXCalGraph(vector<double> yExp, vector<double> yCal, vector<double> freq);
    QChart* drawYCalGraph(vector<double> yExp, vector<double> yCal, vector<double> freq);

signals:

};

#endif // GRAPHES_H
