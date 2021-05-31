#include "essai.h"

Essai::Essai()
{

}


double Essai::calculerDelta0(double r, double d, QString pathToData, QString pathToSciFile)
{
    d0.calculDelta0(r, d, pathToData, pathToSciFile);
    Xexp = d0.getXexp();
    Xcal = d0.getXcal();
    Yexp = d0.getYexp();
    Ycal = d0.getYcal();
    frequencies = d0.getFrequencies();
    return d0.getD0();
}

double Essai::calculerRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile)
{
    cal.calculRayonFil(ro, ros2, eta, delta0, pathToData, pathToSciFile);
    Xexp = cal.getXexp();
    Xcal = cal.getXcal();
    Yexp = cal.getYexp();
    Ycal = cal.getYcal();
    frequencies = cal.getFrequencies();
    return cal.getRayonFil();
}

double Essai::calculerViscosite(double ro, double ros3, double rayon, double delta0, QString pathToData, QString pathToSciFile)
{
    visco.calculViscosite(ro, ros3, rayon, delta0, pathToData, pathToSciFile);
    Xexp = visco.getXexp();
    Xcal = visco.getXcal();
    Yexp = visco.getYexp();
    Ycal = visco.getYcal();
    frequencies = visco.getFrequencies();
    return visco.getViscosite();
}
