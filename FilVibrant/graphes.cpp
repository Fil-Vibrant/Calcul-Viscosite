#include "graphes.h"

Graphes::Graphes(QObject *parent) : QObject(parent)
{



}

QChart* Graphes::drawXD0Graph(vector<double> xExp, vector<double> xCal, vector<double> freq)
{
    xChart = new QChart;
    xChart->legend()->hide();
    xChart->setBackgroundVisible(false);
    xexpserie = new QScatterSeries;
    xcalserie = new QSplineSeries;


    xf = new QValueAxis;
    x = new QValueAxis;

    QPen minorPen(QColor::fromRgb(76, 85, 92), 1, Qt::SolidLine);
    x->setMinorGridLinePen(minorPen);
    x->setMinorTickCount(10);
    xf->setMinorTickCount(10);
    xf->setMinorGridLinePen(minorPen);
    xf->setLabelsColor(QColor::fromRgb(255, 255, 255));
    x->setLabelsColor(QColor::fromRgb(255, 255, 255));
    xf->setTickCount(20);
    x->setTickCount(5);

    QPen pen;
    pen.setWidth(1);
    xexpserie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    xexpserie->setPen(pen);
    xexpserie->setColor(QColor::fromRgb(0, 0, 0, .0));
    xexpserie->setBorderColor(QColor::fromRgb(117, 138, 224));
    xexpserie->setMarkerSize(5);

    pen.setWidth(1);
    xcalserie->setPen(pen);
    xcalserie->setColor(QColor::fromRgb(255, 0, 0));

    double min = xExp[0];
    double max = xExp[0];
    for (unsigned long long i = 0; i < xExp.size(); ++i) {
        xexpserie->append(freq[i], xExp[i]);
        xcalserie->append(freq[i], xCal[i]);
        if (xExp[i] < min)
            min = xExp[i];
        else {
            if (xExp[i] > max)
                max = xExp[i];
        }
    }
    xChart->addSeries(xcalserie);
    xChart->addSeries(xexpserie);

    xf->setRange(freq[0]-0.05, freq[freq.size()-1]+0.05);
    x->setRange(min-0.001*min, max+0.001*max);
    xChart->setAxisX(xf);
    xChart->setAxisY(x);
    xexpserie->attachAxis(x);
    xexpserie->attachAxis(xf);
    xcalserie->attachAxis(x);
    xcalserie->attachAxis(xf);

    return xChart;
}

QChart* Graphes::drawYD0Graph(vector<double> yExp, vector<double> yCal, vector<double> freq)
{
    yChart = new QChart;
    yChart->legend()->hide();
    yChart->setBackgroundVisible(false);
    yexpserie = new QScatterSeries;
    ycalserie = new QSplineSeries;
    yf = new QValueAxis;
    y = new QValueAxis;

    QPen minorPen(QColor::fromRgb(76, 85, 92), 1, Qt::SolidLine);
    y->setMinorGridLinePen(minorPen);
    y->setMinorTickCount(10);
    yf->setMinorTickCount(10);
    yf->setMinorGridLinePen(minorPen);
    yf->setLabelsColor(QColor::fromRgb(255, 255, 255));
    y->setLabelsColor(QColor::fromRgb(255, 255, 255));
    yf->setTickCount(20);
    y->setTickCount(5);

    QPen pen;
    pen.setWidth(1);
    yexpserie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    yexpserie->setPen(pen);
    yexpserie->setColor(QColor::fromRgb(0, 0, 0, .0));
    yexpserie->setBorderColor(QColor::fromRgb(117, 138, 224));
    yexpserie->setMarkerSize(5);

    pen.setWidth(1);
    ycalserie->setPen(pen);
    ycalserie->setColor(QColor::fromRgb(255, 0, 0));

    double min = yExp[0];
    double max = yExp[0];
    qDebug() << yExp.size();
    for (unsigned long long i = 0; i < yExp.size(); ++i) {
        yexpserie->append(freq[i], yExp[i]);
        ycalserie->append(freq[i], yCal[i]);
        if (yExp[i] < min)
            min = yExp[i];
        else {
            if (yExp[i] > max)
                max = yExp[i];
        }
    }
    yChart->addSeries(ycalserie);
    yChart->addSeries(yexpserie);

    yf->setRange(freq[0]-0.05, freq[freq.size()-1]+0.05);
    y->setRange(min+0.1*min, max+0.1*max);
    yChart->setAxisX(yf);
    yChart->setAxisY(y);
    yexpserie->attachAxis(y);
    yexpserie->attachAxis(yf);
    ycalserie->attachAxis(y);
    ycalserie->attachAxis(yf);
    return yChart;
}
