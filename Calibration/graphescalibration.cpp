#include "graphescalibration.h"

GraphesCalibration::GraphesCalibration(QObject *parent) : QObject(parent)
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

    xf = new QValueAxis;
    yf = new QValueAxis;
    x = new QValueAxis;
    y = new QValueAxis;
}

QChart* GraphesCalibration::drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> frequencies)
{

    double min = xExp[0];
    double max = xExp[0];
    for (unsigned long long i = 0; i < xExp.size(); ++i)
    {
        xExpSerie->append(frequencies[i], xExp[i]);
        xCalSerie->append(frequencies[i], xCal[i]);
        if (xExp[i] < min)
            min = xExp[i];
        else
        {
            if (xExp[i] > max)
                max = xExp[i];
        }
    }

    xChart->addSeries(xCalSerie);
    xChart->addSeries(xExpSerie);

    xf->setRange(frequencies[0]-0.05, frequencies[frequencies.size()-1]+0.05);
    x->setRange(min-0.0000002, max+0.0000002);
    x->setTickCount(5);
    xf->setTickCount(20);
    QPen minorPen(QColor::fromRgb(76, 85, 92), 1, Qt::SolidLine);
    x->setMinorGridLinePen(minorPen);
    x->setMinorTickCount(10);
    xf->setMinorTickCount(10);
    xf->setMinorGridLinePen(minorPen);

    xChart->setAxisX(xf);
    xChart->setAxisY(x);

    xExpSerie->attachAxis(x);
    xExpSerie->attachAxis(xf);
    xCalSerie->attachAxis(x);
    xCalSerie->attachAxis(xf);

    //xChart->createDefaultAxes();

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

QChart* GraphesCalibration::drawYGraph(vector<double> yExp, vector<double> yCal, vector<double> frequencies)
{
    double min = yExp[0];
    double max = yExp[0];
    for (unsigned long long i = 0; i < yExp.size(); ++i)
    {
        yExpSerie->append(frequencies[i], yExp[i]);
        yCalSerie->append(frequencies[i], yCal[i]);

        if (yExp[i] < min)
            min = yExp[i];
        else
        {
            if (yExp[i] > max)
                max = yExp[i];
        }
    }

    yChart->addSeries(yCalSerie);
    yChart->addSeries(yExpSerie);
    //yChart->createDefaultAxes();

    yf->setRange(frequencies[0]-0.05, frequencies[frequencies.size()-1]+0.05);
    y->setRange(min-0.0000002, max+0.0000002);
    y->setTickCount(5);
    yf->setTickCount(20);
    QPen minorPen(QColor::fromRgb(76, 85, 92), 1, Qt::SolidLine);
    y->setMinorGridLinePen(minorPen);
    y->setMinorTickCount(10);
    yf->setMinorTickCount(10);
    yf->setMinorGridLinePen(minorPen);

    yChart->setAxisX(yf);
    yChart->setAxisY(y);

    yExpSerie->attachAxis(y);
    yExpSerie->attachAxis(yf);
    yCalSerie->attachAxis(y);
    yCalSerie->attachAxis(yf);

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

