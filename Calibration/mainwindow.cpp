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
        Calibration cal;
        double ro = ui->roFluideCal->value();
        double ros = ui->ros2->value();
        double eta = ui->etaFluideCal->value();
        double d0 = ui->d0->value(); // d0 est récupérée lors du calcul de delta0 !!
        cal.calculRayonFil(ro, ros, eta, d0, dataFileName, scilabFileName);
        ui->rayon->setText(QString::number(cal.getRayonFil()));
        vector<double> frequencies = cal.getFrequencies();

        GraphesCalibration g;
        xChart = g.drawXGraph(cal.getXexp(), cal.getXcal(), frequencies);
        yChart = g.drawYGraph(cal.getYexp(), cal.getYcal(), frequencies);
        xGraph->setChart(xChart);
        yGraph->setChart(yChart);
    }
}
