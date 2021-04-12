#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    xChart = new QChart;

    xChart->legend()->hide();
    xChart->setBackgroundVisible(false);

    yChart = new QChart;

    yChart->legend()->hide();
    yChart->setBackgroundVisible(false);

    xGraph = new QChartView(xChart);
    xGraph->setRenderHint(QPainter::Antialiasing);
    xGraph->setStyleSheet("background-color: rgb(35, 39, 42)");
    yGraph = new QChartView(yChart);
    yGraph->setRenderHint(QPainter::Antialiasing);
    yGraph->setStyleSheet("background-color: rgb(35, 39, 42)");

    ui->xGraphLayout->addWidget(xGraph);
    ui->yGraphLayout->addWidget(yGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Delta0 d0;
    double ros = ui->ros->value();
    double d0i = ui->d0i->value();
    d0.calculDelta0(ros, d0i, "C:/Users/SN/Desktop/ProjetScilab/dataAirAmetek.txt", "C:/Users/SN/Desktop/ProjetScilab/delta0.sci");
    ui->label->setText(QString::number(d0.getD0()));

    vector<double> frequencies = d0.getFreq();

    GraphesDelta0 g;
    xChart = g.drawXGraph(d0.getXexp(), d0.getXcal(), frequencies);
    yChart = g.drawYGraph(d0.getYexp(), d0.getYcal(), frequencies);
    xGraph->setChart(xChart);
    yGraph->setChart(yChart);
}
