#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <QDebug>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QDoubleValidator>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QtCharts>
#include <vector>
#include <Essai/essai.h>
#include <graphes.h>
#include <logs.h>

using namespace QtCharts;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class IHM; }
QT_END_NAMESPACE

class IHM : public QMainWindow
{
    Q_OBJECT
private:
     double voltage;
     double frequence_r;
     bool sens;
     Essai essai;
     Graphes *graph;

     // Déclaration des graphes
     QChart *xDelta0Chart, *xCalibrationChart, *xViscoChart;
     QChart *yDelta0Chart, *yCalibrationChart, *yViscoChart;
     QChartView *xDelta0Graph, *xCalibrationGraph, *xViscoGraph;
     QChartView *yDelta0Graph, *yCalibrationGraph, *yViscoGraph;
public:
    IHM(QWidget *parent = nullptr);
    ~IHM();

    QString getFileEmplacement();
    void showNotification(QString type, QString message);
    void updateText();

private slots:
    // Menu
    void on_btn_etalonage_clicked();
    void on_btn_balayage_clicked();
    void on_btn_grapheXY_clicked();
    void on_btngrapheXetY_clicked();
    void on_btn_delta0_clicked();
    void on_btn_calibration_clicked();
    void on_btn_visco_clicked();

    // Check Edit
    void on_lineEdit_frequence_r_textChanged(const QString &arg1);
    void on_lineEdit_voltage_textChanged(const QString &arg1);
    void on_lineEdit_freq_textChanged(const QString &arg1);
    void on_lineEdit_filename_textChanged(const QString &arg1);
    void on_lineEdit_freq_depart_textChanged(const QString &arg1);
    void on_lineEdit_pas_de_f_textChanged(const QString &arg1);

    // Fin edit
    void on_lineEdit_frequence_r_editingFinished();
    void on_lineEdit_voltage_editingFinished();
    void on_comboBox_port_currentIndexChanged(const QString &arg1);
    void on_lineEdit_filename_editingFinished();
    void on_lineEdit_freq_depart_editingFinished();
    void on_lineEdit_freq_editingFinished();
    void on_lineEdit_pas_de_f_editingFinished();

    // Boutons
    void on_lineEdit_selectfolder_clicked();
    void on_btn_etalonage_2_clicked();
    void on_pushButton_balay_clicked();
    void on_pushButton_delta0_clicked();
    void on_pushButton_calibration_clicked();
    void on_pushButton_Visco_clicked();
    void on_pushButton_clicked();
    void on_pushButton_apply_set_1_clicked();
    void on_pushButton_apply_set_2_clicked();
    void on_pushButton_config_trace_clicked();
    void on_pushButton_edit_tention_clicked();

    void on_pushButton_config_clicked();

    void on_pushButton_edit_tension_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::IHM *ui;
    Logs *logs;
};
#endif // IHM_H
