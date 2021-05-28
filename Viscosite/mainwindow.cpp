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
    QString dataFileName = QFileDialog::getOpenFileName(this, tr("Data file"), "", tr("Text Files (*.txt)"));
    QString scilabFileName = QFileDialog::getOpenFileName(this, tr("Scilab file"), "", tr("Scilab Files (*.sci *.sce)"));
    if (dataFileName.length() > 0 && scilabFileName.length() > 0)
    {
        Viscosite vis;
        double ro = ui->roFluideVis->value();
        double ros = ui->ros3->value();
        double rayon = ui->rayon_3->value(); // rayon récupéré lors de la calibration !!
        double d0 = ui->d0->value(); // d0 est récupérée lors du calcul de delta0 !!
        vis.calculViscosite(ro, ros, rayon, d0, dataFileName, scilabFileName);
        ui->viscosite->setText(QString::number(vis.getViscosite()));
        vector<double> frequencies = vis.getFrequencies();

        GraphesViscosite g;
        xChart = g.drawXGraph(vis.getXexp(), vis.getXcal(), frequencies);
        yChart = g.drawYGraph(vis.getYexp(), vis.getYcal(), frequencies);
        xGraph->setChart(xChart);
        yGraph->setChart(yChart);
    }
}

