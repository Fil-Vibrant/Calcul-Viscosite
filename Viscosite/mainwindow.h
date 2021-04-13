#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <viscosite.h>
#include <QDebug>
#include <graphesviscosite.h>
#include <QFileDialog>

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

    QChart* xChart;
    QChartView* xGraph;

    QChart* yChart;
    QChartView* yGraph;
};
#endif // MAINWINDOW_H
