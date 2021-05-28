#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "call_scilab.h"
#include "api_scilab.h"
#include <vector>
#include <QDebug>

using namespace std;

class Calibration
{
    double rayonFil;

    vector<double> Xexp,
                   frequencies,
                   Xcal,
                   Yexp,
                   Ycal;

    void setXexpValues(),
         setFrequencies(),
         setXcalValues(),
         setYexpValues(),
         setYcalValues();

public:
    Calibration();

    double getRayonFil();

    vector<double> getXexp(),
                   getXcal(),
                   getFrequencies(),
                   getYexp(),
                   getYcal();

    void calculRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile);
};

#endif // CALIBRATION_H
