#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    xChart = new QChart;
    xExpSerie = new QScatterSeries;
    xCalSerie = new QSplineSeries;
    xChart->legend()->hide();
    xChart->setBackgroundVisible(false);

    xGraph = new QChartView(xChart);
    xGraph->setRenderHint(QPainter::Antialiasing);
    xGraph->setStyleSheet("background-color: rgb(35, 39, 42)");
    ui->gridLayout->addWidget(xGraph, 0, 0);
    ui->gridLayout->setAlignment(Qt::AlignCenter);

    yChart = new QChart;
    yExpSerie = new QScatterSeries;
    yCalSerie = new QSplineSeries;
    yChart->legend()->hide();
    yChart->setBackgroundVisible(false);

    yGraph = new QChartView(yChart);
    yGraph->setRenderHint(QPainter::Antialiasing);
    yGraph->setStyleSheet("background-color: rgb(35, 39, 42)");
    ui->gridLayout->addWidget(yGraph, 1, 0);
    ui->gridLayout->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Delta0 d0;

    // Récupération des données pour graphe X (Xexp Xcal et f)
    Xexp = d0.getXexpValues();
    frequencies = d0.getFrequencies();
    Xcal = d0.getXcalValues();
    for (unsigned long long i = 0; i < Xexp.size(); ++i)
    {
        xExpSerie->append(frequencies[i], Xexp[i]);
        xCalSerie->append(frequencies[i], Xcal[i]);
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

    // Récupération des données pour graphe Y (Yexp Ycal et f)
    Yexp = d0.getYexpValues();
    frequencies = d0.getFrequencies();
    Ycal = d0.getYcalValues();
    for (unsigned long long i = 0; i < Yexp.size(); ++i)
    {
        yExpSerie->append(frequencies[i], Yexp[i]);
        yCalSerie->append(frequencies[i], Ycal[i]);
    }
    yChart->addSeries(yCalSerie);
    yChart->addSeries(yExpSerie);
    yChart->createDefaultAxes();
    axisPen.setWidth(1);
    yExpSerie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    yExpSerie->setPen(axisPen);
    yExpSerie->setColor(QColor::fromRgb(0, 0, 0, 0.));
    yExpSerie->setBorderColor(QColor::fromRgb(117, 138, 224));
    yExpSerie->setMarkerSize(7);
    yCalSerie->setPen(axisPen);
    yCalSerie->setColor(QColor::fromRgb(255, 0, 0, 255));

    // Calcul delta0
    d0.calculDelta0();
    ui->label->setText(QString::number(d0.getD0()));
}
