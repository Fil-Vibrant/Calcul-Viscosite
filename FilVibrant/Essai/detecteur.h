#ifndef DETECTEUR_H
#define DETECTEUR_H
#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QSerialPortInfo>
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QVector>

class Detecteur : public QObject
{
    Q_OBJECT


public:
    explicit Detecteur(QObject *parent = nullptr);

    int seConnecter();
    QString getPortName();
    QString getNomDetecteur();


    void setFileName(QString fTxt);
    void setNombreEchantillon(int nbEchantillon);
    void setFrequenceReference(double freqReference);
    void setFrequenceDepart(double freqDepart);
    void setPasFrequence(double pasFreq);
    void setFrequenceFin(double freqFin);
    void initialisationSR850();

    void modificationVoltage(double v);
    void applySettings1();
    void applySettings2();
    void configTrace1et2();
    void start();
    void recalcul();
    QVector<QString> getvecteurX();
    QVector<QString> getvecteurF();
    QVector<QString> getvecteurY();
    QVector<QString> getvecteurR();

    void etalonnage();
    void lancerBalayage();
    void enregistrerDansFichierTxt();


public slots:
    void recupererMesuresSNAP();
    void recupererMesuresSPTS();


private:
    QVector<QString> vecteurX,vecteurF,vecteurY,vecteurR,vecteurData;
    int nombreEchantillon;
    double frequenceReference,frequenceDepart,pasFrequence,frequenceFin;
    QSerialPort *port=new QSerialPort();
    QFile *file;
    QByteArray tramR, nomDetecteur;
    int nblecture;



};

#endif // DETECTEUR_H
