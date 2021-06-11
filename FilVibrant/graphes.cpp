#include "graphes.h"

Graphes::Graphes(QObject *parent) : QObject(parent)
{
    xexpserie = new QScatterSeries;
    xcalserie = new QSplineSeries;
    //yExpSerie = new QScatterSeries;
    //yCalSerie = new QSplineSeries;

    xf = new QValueAxis;
    yf = new QValueAxis;
    x = new QValueAxis;
    y = new QValueAxis;

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
    //xexpserie->setBorderColor(QColor::fromRgb(117, 138, 224));
    xexpserie->setBorderColor(QColor::fromRgb(54, 145, 244));
    xexpserie->setMarkerSize(5);

    pen.setWidth(1);
    xcalserie->setPen(pen);
    xcalserie->setColor(QColor::fromRgb(224, 0, 0));


}

QChart* Graphes::drawXGraph(vector<double> xExp, vector<double> xCal, vector<double> freq)
{
    xChart = new QChart;
    xChart->legend()->hide();
    xChart->setBackgroundVisible(false);

    yChart = new QChart;
    yChart->legend()->hide();
    yChart->setBackgroundVisible(false);

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
    x->setRange(min-0.00002, max+0.00002);
    xChart->setAxisX(xf);
    xChart->setAxisY(x);
    xexpserie->attachAxis(x);
    xexpserie->attachAxis(xf);
    xcalserie->attachAxis(x);
    xcalserie->attachAxis(xf);

    return xChart;
}
