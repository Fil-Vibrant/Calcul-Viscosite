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
    QScatterSeries *xexpserie;
    QSplineSeries *xcalserie;

    QChart* xChart;
    QChart* yChart;

    QValueAxis *xf, *yf, *x, *y;
public:
    explicit Graphes(QObject *parent = nullptr);
    QChart* drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> freq);

signals:

};

#endif // GRAPHES_H
