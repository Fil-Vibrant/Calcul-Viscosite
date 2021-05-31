#ifndef VISCOSITE_H
#define VISCOSITE_H

#include <call_scilab.h>
#include <api_scilab.h>
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

    void setXexpValues(),
         setFrequencies(),
         setXcalValues(),
         setYexpValues(),
         setYcalValues();

public:
    Viscosite();

    double getViscosite();

    vector<double> getXexp(),
                   getXcal(),
                   getFrequencies(),
                   getYexp(),
                   getYcal();

    void calculViscosite(double ro, double ros3, double rayon, double delta0, QString pathToData, QString pathToSciFile);
};

#endif // VISCOSITE_H
