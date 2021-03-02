#ifndef CALCULS_H
#define CALCULS_H

#include <QDebug>
#include "stack-c.h"
#include "call_scilab.h"
#include "api_scilab.h"
#include "Scierror.h"
#include <vector>

using namespace std;

class Calculs
{
    double delta0,
           rayonFil,
           viscosite,
           ros,
           D0i;
     vector<double> dVexp;
public:
    Calculs();
    ~Calculs();

    double getRos(),
           getD0i(),
           getD0();

    void calculDelta0(),
         getDVexpValues(),
         showDVexp();
};

#endif // CALCULS_H
