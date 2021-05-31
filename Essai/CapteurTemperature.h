#ifndef CAPTEURTEMPERATURE_H
#define CAPTEURTEMPERATURE_H
#include <NIDAQmx.h>


class CapteurTemperature
{
public:
    CapteurTemperature();

    void recupTension();
    float CalculTemp(float tens);
    float Gettension();
    float GetTemp();


private:
    TaskHandle taskhandle = 0;
    float tension;
    float temp;



};

#endif // CAPTEURTEMPERATURE_H
