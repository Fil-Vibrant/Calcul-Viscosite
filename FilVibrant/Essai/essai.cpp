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
/*
float Essai::temperature()
{
    float tension;
    tension= temp.Gettension();
    return temp.CalculTemp(tension);

}*/

void Essai::creerFichierTxt(QString path)
{
    sr850.setFileName(path);
}

QString Essai::connexionDetecteur()
{
    sr850.seConnecter();
    sr850.initialisationSR850();
    return sr850.getNomDetecteur();
}

QString Essai::nomPort()
{
    return sr850.getPortName();
}

void Essai::setParametres(double freqDepart, double freqArrivee, double pasDeFreq, double freqRef, int echantillons) {
    sr850.setFrequenceDepart(freqDepart);
    sr850.setFrequenceFin(freqArrivee);
    sr850.setFrequenceReference(freqRef);
    sr850.setNombreEchantillon(echantillons);
    sr850.setPasFrequence(pasDeFreq);
}

void Essai::modifierTension(double tens)
{
    sr850.modificationVoltage(tens);
}

void Essai::apply1()
{
    sr850.applySettings1();
}

void Essai::apply2()
{
    sr850.applySettings2();
}

void Essai::configTrace()
{
    sr850.configTrace1et2();
}

void Essai::start()
{
    sr850.start();
}

void Essai::etalonnage()
{
    sr850.etalonnage();
}

void Essai::balayage()
{
    sr850.lancerBalayage();
}

void Essai::enregistrerValeurs()
{
    sr850.enregistrerDansFichierTxt();
}







