#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <delta0.h>
#include <QDebug>

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

    vector<double> dVexp,
                   frequencies,
                   dVcal;

    QChart *chart;
    QScatterSeries *xExpSerie;
    QSplineSeries *xCalSerie;
    QChartView *chartView;
};
#endif // MAINWINDOW_H
