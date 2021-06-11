#ifndef ESSAI_H
#define ESSAI_H

#include "delta0.h"
#include "calibration.h"
#include "viscosite.h"
#include <QDebug>
#include <vector>
//#include<CapteurTemperature.h>

using namespace std;

class Essai
{
    Delta0 d0;
    Calibration cal;
    Viscosite visco;
    //CapteurTemperature temp;


public:
    Essai();

    double calculerDelta0(double r, double d, QString pathToData, QString pathToSciFile);
    double calculerRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile);
    double calculerViscosite(double ro, double ros3, double rayon, double delta0, QString pathToData, QString pathToSciFile);
    vector<double> Xexp, Yexp, Xcal, Ycal, frequencies;
    //float temperature();
};

#endif // ESSAI_H
