#include "ihm.h"
#include "ui_ihm.h"

IHM::IHM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHM)
{
    ui->setupUi(this);
    this->logs = new Logs(this);
    setWindowTitle("Fil Vibrant v1.1");
    //setWindowIcon();
    ui->stackedWidget->setCurrentIndex(0);
    sens = false;


    ui->lineEdit_folder->setText(QDir::homePath() + "/Desktop");

    // Initialisation des graphes
    graph = new Graphes;

    xDelta0Chart = new QChart;
    xDelta0Chart->setBackgroundVisible(false);

    yDelta0Chart = new QChart;
    yDelta0Chart->setBackgroundVisible(false);

    xDelta0Graph = new QChartView(xDelta0Chart);
    xDelta0Graph->setRenderHint(QPainter::Antialiasing);
    xDelta0Graph->setStyleSheet("background-color: rgb(35, 39, 42);");

    yDelta0Graph = new QChartView(yDelta0Chart);
    yDelta0Graph->setRenderHint(QPainter::Antialiasing);
    yDelta0Graph->setStyleSheet("background-color: rgb(35, 39, 42);");

    ui->Graphe_Xexp_Xcal->addWidget(xDelta0Graph);
    ui->Graphe_Yexp_Ycal->addWidget(yDelta0Graph);

    xCalibrationChart = new QChart;
    xCalibrationChart->setBackgroundVisible(false);

    yCalibrationChart = new QChart;
    yCalibrationChart->setBackgroundVisible(false);

    xCalibrationGraph = new QChartView(xCalibrationChart);
    xCalibrationGraph->setRenderHint(QPainter::Antialiasing);
    xCalibrationGraph->setStyleSheet("background-color: rgb(35, 39, 42);");

    yCalibrationGraph = new QChartView(yCalibrationChart);
    yCalibrationGraph->setRenderHint(QPainter::Antialiasing);
    yCalibrationGraph->setStyleSheet("background-color: rgb(35, 39, 42);");

    ui->Graphe_Xexp_Xcal_2->addWidget(xCalibrationGraph);
    ui->Graphe_Yexp_Ycal_2->addWidget(yCalibrationGraph);

    xViscoChart = new QChart;
    xViscoChart->setBackgroundVisible(false);

    yViscoChart = new QChart;
    yViscoChart->setBackgroundVisible(false);

    xViscoGraph = new QChartView(xViscoChart);
    xViscoGraph->setRenderHint(QPainter::Antialiasing);
    xViscoGraph->setStyleSheet("background-color: rgb(35, 39, 42);");

    yViscoGraph = new QChartView(yViscoChart);
    yViscoGraph->setRenderHint(QPainter::Antialiasing);
    yViscoGraph->setStyleSheet("background-color: rgb(35, 39, 42);");

    ui->Graphe_Xexp_Xcal_3->addWidget(xViscoGraph);
    ui->Graphe_Yexp_Ycal_3->addWidget(yViscoGraph);
    QString nom = essai.connexionDetecteur();
    QString port = essai.nomPort();
    if (nom != "")
        ui->comboBox_port->addItem(nom + port);
}

IHM::~IHM()
{
    delete ui;
    this->logs->~Logs();
}

QString IHM::getFileEmplacement() {
    if (ui->lineEdit_folder->text() != "" && ui->lineEdit_filename->text() != "") {
        return ui->lineEdit_folder->text() + "/" + ui->lineEdit_filename->text() + ".txt";
    } else {
        return QDir::homePath() + "/Desktop/mesures.txt";
    }
}

void IHM::showNotification(QString type, QString message) {
    QMessageBox msgBox;
    if (type == "information") {
        msgBox.setWindowTitle("Information");
        msgBox.setIcon(QMessageBox::Information);
    } else if (type == "avertissement") {
        msgBox.setWindowTitle("Avertissement");
        msgBox.setIcon(QMessageBox::Warning);
    } else {
        msgBox.setWindowTitle("Erreur");
        msgBox.setIcon(QMessageBox::Critical);
    }

    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void IHM::updateText() {
    QString text;

    QString tension, freq_r, freq_start, freq_end, pas_f;
    tension = ui->lineEdit_voltage->text();
    freq_r = ui->lineEdit_frequence_r->text();
    freq_start = ui->lineEdit_freq_depart->text();
    freq_end = ui->lineEdit_freq->text();
    pas_f = ui->lineEdit_pas_de_f->text();

    if (tension == "")
        tension = "0";
    if(freq_r == "")
        freq_r = "0.00";
    if(freq_start == "")
        freq_start = "0.00";
    if(freq_end == "")
        freq_end = "0.00";
    if(pas_f == "")
        pas_f = "0.00";

    text = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Tension : </span><span style=\" font-size:10pt; color:#ffffff;\">"+ tension +" V</span></p></body></html>";
    ui->label_info_tension->setText(text);
    ui->label_info_tension_2->setText(text);
    text = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Fréquence de Référence : </span><span style=\" font-size:10pt; color:#ffffff;\">"+ freq_r +" Hz</span></p></body></html>";
    ui->label_info_freq_r->setText(text);
    ui->label_info_freq_r_2->setText(text);
    text = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Fréquence de départ : </span><span style=\" font-size:10pt; color:#ffffff;\">"+ freq_start +" Hz</span></p></body></html>";
    ui->label_info_freq_start->setText(text);
    ui->label_info_freq_start_2->setText(text);
    text = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Pas de Fréquence : </span><span style=\" font-size:10pt; color:#ffffff;\">"+ pas_f +"</span></p></body></html>";
    ui->label_info_pas_f->setText(text);
    ui->label_info_pas_f_2->setText(text);
    text = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Fréquence d'arrivée : </span><span style=\" font-size:10pt; color:#ffffff;\">"+ freq_end +" Hz</span></p></body></html>";
    ui->label_info_freq_end->setText(text);
    ui->label_info_freq_end_2->setText(text);
}

// Menu
void IHM::on_btn_etalonage_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void IHM::on_btn_balayage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void IHM::on_btn_grapheXY_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void IHM::on_btngrapheXetY_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void IHM::on_btn_delta0_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void IHM::on_btn_calibration_clicked()
{
   ui->stackedWidget->setCurrentIndex(5);
}

void IHM::on_btn_visco_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

// Check Edit
void IHM::on_lineEdit_frequence_r_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QValidator *validator = new QDoubleValidator(-1000000000, 1000000000, 3, ui->lineEdit_frequence_r);
    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_frequence_r->backspace();
        showNotification("information", "Vous pouvez entrée un nombre compris entre -1000000000 et 1000000000.");
    }
}

void IHM::on_lineEdit_voltage_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QValidator *validator = new QDoubleValidator(0, 50, 6, ui->lineEdit_voltage);
    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_voltage->backspace();
        showNotification("information", "Vous pouvez entrer un nombre compris entre 0 et 50.");
    }
}

void IHM::on_lineEdit_freq_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QValidator *validator = new QDoubleValidator(-1000000000, 1000000000, 3, ui->lineEdit_freq);
    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_freq->backspace();
        showNotification("information", "Vous pouvez entrer un nombre compris entre -1000000000 et 1000000000.");
    }
    updateText();
}

void IHM::on_lineEdit_filename_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QRegularExpression re("^[a-zA-Z0-9_-]*$");
    QValidator *validator = new QRegularExpressionValidator(re, ui->lineEdit_filename);

    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_filename->backspace();
        showNotification("information", "Vous ne pouvez entrer que les caractère suivants :\n- a-z\n- A-Z\n- 0-9\n- _ et -");
    } else if (text.toUpper() == "COM" || text.toUpper() == "PRN" || text.toUpper() == "AUX" || text.toUpper() == "NUL" || text.toUpper() == "COM1" || text.toUpper() == "COM2" || text.toUpper() == "COM3" || text.toUpper() == "COM4" || text.toUpper() == "COM5" || text.toUpper() == "COM6" || text.toUpper() == "COM7" || text.toUpper() == "COM8" || text.toUpper() == "COM9" || text.toUpper() == "LPT1" || text.toUpper() == "LPT2" || text.toUpper() == "LPT3" || text.toUpper() == "LPT4" || text.toUpper() == "LPT5" || text.toUpper() == "LPT6" || text.toUpper() == "LPT7" || text.toUpper() == "LPT8" || text.toUpper() == "LPT9") {
        ui->lineEdit_filename->setText("");
        showNotification("avertissement", "Vous ne pouvez pas utiliser ce nom de fichier.");
    }
}

void IHM::on_lineEdit_freq_depart_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QValidator *validator = new QDoubleValidator(-1000000000, 1000000000, 3, ui->lineEdit_freq_depart);
    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_freq_depart->backspace();
        showNotification("information", "Vous pouvez entrer un nombre compris entre -1000000000 et 1000000000.");
    }
    updateText();
}

void IHM::on_lineEdit_pas_de_f_textChanged(const QString &arg1)
{
    int pos = arg1.size()-1;
    QString text = arg1;
    QValidator *validator = new QDoubleValidator(0.0, 100.0, 8, ui->lineEdit_pas_de_f);
    if (validator->validate(text,pos) == 0) {
        ui->lineEdit_pas_de_f->backspace();
        showNotification("information", "Vous pouvez entrer un nombre compris entre 0 et 100.");
    }
    updateText();
}

// Fin edit
void IHM::on_lineEdit_frequence_r_editingFinished()
{
    updateText();
    this->logs->write("Fréquence de Référence modifié à " + ui->lineEdit_frequence_r->text(), true);
}

void IHM::on_lineEdit_voltage_editingFinished()
{
    updateText();
    this->logs->write("Voltage modifié à " + ui->lineEdit_voltage->text(), true);
}

void IHM::on_comboBox_port_currentIndexChanged(const QString &arg1)
{
    this->logs->write("Port COM modifié à " + arg1, true);
}

void IHM::on_lineEdit_filename_editingFinished()
{
    this->logs->write("Nom du fichier modifié en " + ui->lineEdit_filename->text(), true);
}

void IHM::on_lineEdit_freq_depart_editingFinished()
{
    this->logs->write("Fréquence de départ modifié à " + ui->lineEdit_filename->text(), true);

}

void IHM::on_lineEdit_freq_editingFinished()
{
    this->logs->write("Fréquence d'arrivé modifié à " + ui->lineEdit_filename->text(), true);
}

void IHM::on_lineEdit_pas_de_f_editingFinished()
{
    this->logs->write("Pas de fréquence modifié à " + ui->lineEdit_pas_de_f->text(), true);
}

// Boutons
void IHM::on_lineEdit_selectfolder_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(0, ("Sélectionnez le dossier de sortie"), QDir::homePath() + "\\Desktop", QFileDialog::ShowDirsOnly);
    if (folder != "") {
        ui->lineEdit_folder->setText(folder);
        this->logs->write("Répertoire de sauvegarde définie à : " + folder, true);
    }
}

void IHM::on_btn_etalonage_2_clicked()
{
    if (ui->lineEdit_frequence_r->text() == "" || ui->lineEdit_voltage->text() == "") {
        showNotification("avertissement", "Vous devez completer tous les champs.");
    } else {
        this->logs->write("Début étalonage", true);
        essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
        essai.etalonnage();
    }
}

void IHM::on_pushButton_balay_clicked()
{
    if (ui->lineEdit_folder->text() == "" || ui->lineEdit_filename->text() == "" || ui->lineEdit_freq_depart->text() == "" || ui->lineEdit_freq->text() == ""  || ui->lineEdit_pas_de_f->text() == "") {
        showNotification("avertissement", "Vous devez completer tous les champs.");
    } else {
        this->logs->write("Début balayage", true);
        QString path = getFileEmplacement();
        essai.creerFichierTxt(path);
        essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
        essai.balayage();
        essai.enregistrerValeurs();
    }
}

void IHM::on_pushButton_delta0_clicked()
{
    graph = new Graphes;
    if (ui->lineEdit_ros->text() == "" || ui->lineEdit_d0i->text() == "") {
        showNotification("avertissement", "Vous devez completer tous les champs.");
    } else {
        QString dataFileName = QFileDialog::getOpenFileName(this, tr("Data file"), "", tr("Text Files (*.txt)"));
        QString scilabFileName = QFileDialog::getOpenFileName(this, tr("Scilab file"), "", tr("Scilab Files (*.sci *.sce)"));
        if (dataFileName.length() > 0 && scilabFileName.length() > 0)
        {
            this->logs->write("Début du calcule de Delta0", true);
            QString delta0 = QString::number(essai.calculerDelta0(ui->lineEdit_ros->text().toDouble(), ui->lineEdit_d0i->text().toDouble(), dataFileName, scilabFileName));
            ui->lineEdit_delta0->setText(delta0);
            ui->lineEdit_d0->setText(delta0);
            ui->lineEdit_d0_2->setText(delta0);

            xDelta0Graph->setChart(graph->drawXD0Graph(essai.Xexp, essai.Xcal, essai.frequencies));
            yDelta0Graph->setChart(graph->drawYD0Graph(essai.Yexp, essai.Ycal, essai.frequencies));
            ui->Graphe_Xexp_Xcal->addWidget(xDelta0Graph, 0, 0);
            ui->Graphe_Yexp_Ycal->addWidget(yDelta0Graph, 0, 0);
        }
    }
}

void IHM::on_pushButton_calibration_clicked()
{
    graph = new Graphes;
    if (ui->lineEdit_etat_fluide->text() == "" || ui->lineEdit_d0->text() == "" || ui->lineEdit_ro_fluide->text() == "" || ui->lineEdit_ros2->text() == "") {
        showNotification("avertissement", "Vous devez completer tous les champs.");
    } else {
        QString dataFileName = QFileDialog::getOpenFileName(this, tr("Data file"), "", tr("Text Files (*.txt)"));
        QString scilabFileName = QFileDialog::getOpenFileName(this, tr("Scilab file"), "", tr("Scilab Files (*.sci *.sce)"));
        if (dataFileName.length() > 0 && scilabFileName.length() > 0)
        {
            this->logs->write("Début de la calibration", true);
            QString rayon = QString::number(essai.calculerRayonFil(ui->lineEdit_ro_fluide->text().toDouble(), ui->lineEdit_ros2->text().toDouble(), ui->lineEdit_etat_fluide->text().toDouble(), ui->lineEdit_d0->text().toDouble(), dataFileName, scilabFileName));
            ui->lineEdit_rayon->setText(rayon);
            ui->lineEdit_rayon_3->setText(rayon);

            xCalibrationGraph->setChart(graph->drawXD0Graph(essai.Xexp, essai.Xcal, essai.frequencies));
            yCalibrationGraph->setChart(graph->drawYD0Graph(essai.Yexp, essai.Ycal, essai.frequencies));
            ui->Graphe_Xexp_Xcal_2->addWidget(xCalibrationGraph, 0, 0);
            ui->Graphe_Yexp_Ycal_2->addWidget(yCalibrationGraph, 0, 0);
        }
    }
}

void IHM::on_pushButton_Visco_clicked()
{
    graph = new Graphes;
    if (ui->lineEdit_ros3->text() == "" || ui->lineEdit_rayon_3->text() == "" || ui->lineEdit_d0_2->text() == "" || ui->lineEdit_ro_fluide_2->text() == "") {
        showNotification("avertissement", "Vous devez completer tous les champs.");
    } else {
        QString dataFileName = QFileDialog::getOpenFileName(this, tr("Data file"), "", tr("Text Files (*.txt)"));
        QString scilabFileName = QFileDialog::getOpenFileName(this, tr("Scilab file"), "", tr("Scilab Files (*.sci *.sce)"));
        if (dataFileName.length() > 0 && scilabFileName.length() > 0)
        {
            this->logs->write("Début de la visco", true);
            QString eta = QString::number(essai.calculerViscosite(ui->lineEdit_ro_fluide_2->text().toDouble(), ui->lineEdit_ros3->text().toDouble(), ui->lineEdit_rayon_3->text().toDouble(), ui->lineEdit_d0_2->text().toDouble(), dataFileName, scilabFileName));
            ui->lineEdit_eta2->setText(eta);
            xViscoGraph->setChart(graph->drawXD0Graph(essai.Xexp, essai.Xcal, essai.frequencies));
            yViscoGraph->setChart(graph->drawYD0Graph(essai.Yexp, essai.Ycal, essai.frequencies));
            ui->Graphe_Xexp_Xcal_3->addWidget(xViscoGraph, 0, 0);
            ui->Graphe_Yexp_Ycal_3->addWidget(yViscoGraph, 0, 0);
        }
    }

}

void IHM::on_pushButton_clicked()
{
    essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
    essai.start();
}

void IHM::on_pushButton_apply_set_1_clicked()
{
    essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
    essai.apply1();
}

void IHM::on_pushButton_apply_set_2_clicked()
{
    essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
    essai.apply2();
}

void IHM::on_pushButton_config_trace_clicked()
{
    essai.configTrace();
}

void IHM::on_pushButton_edit_tention_clicked()
{

}

void IHM::on_pushButton_config_clicked()
{

    QString configFileName = QFileDialog::getOpenFileName(this, tr("Config file"), "", tr("*.xml"));

}

void IHM::on_pushButton_edit_tension_clicked()
{
    double voltage = ui->lineEdit_voltage->text().toDouble();
    essai.modifierTension(voltage);

}

void IHM::on_pushButton_start_clicked()
{
    essai.setParametres(ui->lineEdit_freq_depart->text().toDouble(), ui->lineEdit_freq->text().toDouble(), ui->lineEdit_pas_de_f->text().toDouble(), ui->lineEdit_frequence_r->text().toDouble(), ui->lineEdit_echantillons->text().toInt());
    essai.start();
}
