#ifndef DELTA0_H
#define DELTA0_H

#include "call_scilab.h"
#include "api_scilab.h"
#include <vector>
#include <QDebug>

using namespace std;

class Delta0
{

    double delta0;

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
    explicit Delta0();

    double getD0();

    vector<double> getXexp(),
                   getXcal(),
                   getFrequencies(),
                   getYexp(),
                   getYcal();

    void calculDelta0(double r, double d, QString pathToData, QString pathToSciFile);


};

#endif // DELTA0_H
