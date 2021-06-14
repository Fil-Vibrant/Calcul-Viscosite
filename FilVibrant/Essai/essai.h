#ifndef ESSAI_H
#define ESSAI_H

#include "delta0.h"
#include "calibration.h"
#include "viscosite.h"
#include <QDebug>
#include <vector>
//#include<CapteurTemperature.h>
#include "detecteur.h"

using namespace std;

class Essai
{
    Delta0 d0;
    Calibration cal;
    Viscosite visco;
    //CapteurTemperature temp;
    Detecteur sr850;


public:
    Essai();

    double calculerDelta0(double r, double d, QString pathToData, QString pathToSciFile);
    double calculerRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile);
    double calculerViscosite(double ro, double ros3, double rayon, double delta0, QString pathToData, QString pathToSciFile);
    void creerFichierTxt(QString path);
    QString connexionDetecteur();
    QString nomPort();
    void setParametres(double freqDepart, double freqArrivee, double pasDeFreq, double freqRef, int echantillons);
    void modifierTension(double tens);
    void apply1();
    void apply2();
    void configTrace();
    void start();
    void etalonnage();
    void balayage();
    void enregistrerValeurs();
    vector<double> Xexp, Yexp, Xcal, Ycal, frequencies;
    //float temperature();
};

#endif // ESSAI_H
