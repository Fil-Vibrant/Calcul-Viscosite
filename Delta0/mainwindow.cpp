#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart;
    serie = new QScatterSeries;
    chart->legend()->hide();
    chart->setBackgroundVisible(false);
    ui->frame->setStyleSheet("background-color: rgb(35, 39, 42");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->frame);

    chartView->resize(ui->frame->size());
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
    for (unsigned long long i = 0; i < dVexp.size(); ++i)
    {
        serie->append(frequencies[i], dVexp[i]);
        qDebug() << i << frequencies[i] << dVexp[i];
    }
    chart->addSeries(serie);
    chart->createDefaultAxes();
    serie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    serie->setColor(QColor::fromRgb(0, 0, 0, 0.));
    serie->setBorderColor(QColor::fromRgb(94, 130, 255));
    serie->setMarkerSize(3);


    d0.calculDelta0();
    ui->label->setText(QString::number(d0.getD0()));
}
