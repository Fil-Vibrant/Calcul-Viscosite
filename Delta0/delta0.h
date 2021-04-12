#ifndef DELTA0_H
#define DELTA0_H

#include <QObject>
#include "stack-c.h"
#include "call_scilab.h"
#include "api_scilab.h"
#include "Scierror.h"
#include <vector>
#include <QDebug>

using namespace std;

class Delta0 : public QObject
{
    Q_OBJECT

    double delta0,
           rayonFil;

     vector<double> Xexp,
                    frequencies,
                    Xcal,
                    Yexp,
                    Ycal;

public:
    explicit Delta0(QObject *parent = nullptr);

    double getD0();

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

    void calculDelta0(double r, double d, QString pathToData, QString pathToSciFile);

signals:

};

#endif // DELTA0_H
