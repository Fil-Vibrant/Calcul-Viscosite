#include "graphesdelta0.h"

GraphesDelta0::GraphesDelta0(QObject *parent) : QObject(parent)
{
    xChart = new QChart;
    xExpSerie = new QScatterSeries;
    xCalSerie = new QSplineSeries;
    xChart->legend()->hide();
    xChart->setBackgroundVisible(false);

    xGraph = new QChartView(xChart);
    xGraph->setRenderHint(QPainter::Antialiasing);
    xGraph->setStyleSheet("background-color: rgb(35, 39, 42)");

    yChart = new QChart;
    yExpSerie = new QScatterSeries;
    yCalSerie = new QSplineSeries;
    yChart->legend()->hide();
    yChart->setBackgroundVisible(false);

    yGraph = new QChartView(yChart);
    yGraph->setRenderHint(QPainter::Antialiasing);
    yGraph->setStyleSheet("background-color: rgb(35, 39, 42)");
}


QChart* GraphesDelta0::drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> f)
{
    for (unsigned long long i = 0; i < xExp.size(); ++i)
    {
        xExpSerie->append(frequencies[i], xExp[i]);
        xCalSerie->append(frequencies[i], xCal[i]);
    }

    xChart->addSeries(xCalSerie);
    xChart->addSeries(xExpSerie);
    xChart->createDefaultAxes();
    QPen axisPen;
    axisPen.setWidth(1);
    xExpSerie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    xExpSerie->setPen(axisPen);
    xExpSerie->setColor(QColor::fromRgb(0, 0, 0, 0.));
    xExpSerie->setBorderColor(QColor::fromRgb(117, 138, 224));
    xExpSerie->setMarkerSize(7);
    xCalSerie->setPen(axisPen);
    xCalSerie->setColor(QColor::fromRgb(255, 0, 0, 255));

    return xChart;
}
