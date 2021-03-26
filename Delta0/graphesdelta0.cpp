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
}

QChart* GraphesDelta0::drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> frequencies)
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

QChart* GraphesDelta0::drawYGraph(vector<double> yExp, vector<double> yCal, vector<double> frequencies)
{
    for (unsigned long long i = 0; i < yExp.size(); ++i)
    {
        yExpSerie->append(frequencies[i], yExp[i]);
        yCalSerie->append(frequencies[i], yCal[i]);
    }

    yChart->addSeries(yCalSerie);
    yChart->addSeries(yExpSerie);
    yChart->createDefaultAxes();

    QPen axisPen;
    axisPen.setWidth(1);

    yExpSerie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    yExpSerie->setPen(axisPen);
    yExpSerie->setColor(QColor::fromRgb(0, 0, 0, 0.));
    yExpSerie->setBorderColor(QColor::fromRgb(117, 138, 224));
    yExpSerie->setMarkerSize(7);

    yCalSerie->setPen(axisPen);
    yCalSerie->setColor(QColor::fromRgb(255, 0, 0, 255));

    return yChart;
}

