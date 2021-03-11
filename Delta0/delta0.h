#ifndef DELTA0_H
#define DELTA0_H

#include <QObject>
#include "stack-c.h"
#include "call_scilab.h"
#include "api_scilab.h"
#include "Scierror.h"
#include <vector>

using namespace std;

class Delta0 : public QObject
{
    Q_OBJECT

    double delta0,
           rayonFil,
           viscosite,
           ros,
           D0i;
     vector<double> dVexp,
                    frequencies;

public:
    explicit Delta0(QObject *parent = nullptr);

    double getRos(),
           getD0i(),
           getD0();

    vector<double> getDVexpValues(),
                   getFrequencies();

    void calculDelta0(),
         showDVexp();

signals:

};

#endif // DELTA0_H
