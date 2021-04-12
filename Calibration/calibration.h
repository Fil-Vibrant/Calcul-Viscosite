#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "stack-c.h"
#include "call_scilab.h"
#include "api_scilab.h"
#include "Scierror.h"
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

public:
    Calibration();

    double getRayonFil();

    vector<double> getXexp(),
                   getXcal(),
                   getFreq(),
                   getYexp(),
                   getYcal();

    void getXexpValues(),
         getFrequencies(),
         getXcalValues(),
         getYexpValues(),
         getYcalValues();

    void calculRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile);
};

#endif // CALIBRATION_H
