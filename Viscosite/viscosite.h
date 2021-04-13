#ifndef VISCOSITE_H
#define VISCOSITE_H

#include <stack-c.h>
#include <call_scilab.h>
#include <api_scilab.h>
#include <Scierror.h>
#include <vector>
#include <QDebug>

using namespace std;

class Viscosite
{
    double viscosite;

    vector<double> Xexp,
                   frequencies,
                   Xcal,
                   Yexp,
                   Ycal;

    void getXexpValues(),
         getFrequencies(),
         getXcalValues(),
         getYexpValues(),
         getYcalValues();

public:
    Viscosite();

    double getViscosite();

    vector<double> getXexp(),
                   getXcal(),
                   getFreq(),
                   getYexp(),
                   getYcal();

    void calculViscosite(double ro, double ros3, double rayon, double delta0, QString pathToData, QString pathToSciFile);
};

#endif // VISCOSITE_H
