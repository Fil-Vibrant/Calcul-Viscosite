#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <delta0.h>
#include <QDebug>
#include <graphesdelta0.h>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QChart* xChart;/*
    QScatterSeries* xExpSerie;
    QSplineSeries* xCalSerie;*/
    QChartView* xGraph;

    QChart* yChart;/*
    QScatterSeries* yExpSerie;
    QSplineSeries* yCalSerie;*/
    QChartView* yGraph;
};
#endif // MAINWINDOW_H
