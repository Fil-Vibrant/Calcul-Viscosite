#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
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
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Delta0 d0;
    d0.calculDelta0();
    ui->label->setText(QString::number(d0.getD0()));
    vector<double> xexp = d0.getXexpValues();
    vector<double> xcal = d0.getXcalValues();
    vector<double> f = d0.getFrequencies();
    GraphesDelta0 graph;/*
    // Récupération des données pour graphe X (Xexp Xcal et f)
    QChartView* x = graph.drawXGraph(xexp, xcal, f);

    x->setGeometry(ui->graphLayout->geometry());
    ui->graphLayout->addWidget(x, 0, 0, Qt::AlignCenter);*/
    //ui->gridLayout->setAlignment(Qt::AlignCenter);
/*
    // Récupération des données pour graphe Y (Yexp Ycal et f)
    QChartView *y = graph.drawXGraph();

    ui->gridLayout->addWidget(y, 1, 0);
    ui->gridLayout->setAlignment(Qt::AlignCenter);
*/
    // Calcul delta0
}
