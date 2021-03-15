#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart;
    xExpSerie = new QScatterSeries;
    xCalSerie = new QSplineSeries;
    chart->legend()->hide();
    chart->setBackgroundVisible(false);
    //ui->frame->setStyleSheet("background-color: rgb(35, 39, 42)");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: rgb(35, 39, 42)");
    ui->gridLayout->addWidget(chartView, 0, 0);
    ui->gridLayout->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Delta0 d0;
    dVexp = d0.getDVexpValues();
    frequencies = d0.getFrequencies();
    dVcal = d0.getDVcalValues();
    for (unsigned long long i = 0; i < dVexp.size(); ++i)
    {
        xExpSerie->append(frequencies[i], dVexp[i]);
        xCalSerie->append(frequencies[i], dVcal[i]);
    }
    chart->addSeries(xCalSerie);
    chart->addSeries(xExpSerie);
    chart->createDefaultAxes();
    QPen axisPen;
    axisPen.setWidth(1);
    xExpSerie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    xExpSerie->setPen(axisPen);
    xExpSerie->setColor(QColor::fromRgb(0, 0, 0, 0.));
    xExpSerie->setBorderColor(QColor::fromRgb(117, 138, 224));
    xExpSerie->setMarkerSize(7);
    xCalSerie->setPen(axisPen);
    xCalSerie->setColor(QColor::fromRgb(255, 0, 0, 255));


    d0.calculDelta0();
    ui->label->setText(QString::number(d0.getD0()));
}
