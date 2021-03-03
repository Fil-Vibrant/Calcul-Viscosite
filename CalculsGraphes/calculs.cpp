#include "calculs.h"

Calculs::Calculs()
{
    delta0 = 0;
    rayonFil = 0;
    viscosite = 0;

    if ( StartScilab(NULL, NULL, 0) == FALSE ) // Appel de Scilab
    {
        qDebug() << "Impossible d'appeler StartScilab";
    }
}

Calculs::~Calculs()
{
    if ( TerminateScilab(NULL) == FALSE ) {
        qDebug() << "Impossible d'appeler TerminateScilab\n";
    }
}

void Calculs::calculDelta0()
{
    SendScilabJob((char*)"exec('C:/Users/SN/Desktop/ProjetScilab/delta0.sci');");

    int* piD0 = NULL;
    int* piROS = NULL;
    int* piD0I = NULL;

    SciErr D0 = getVarAddressFromName(pvApiCtx, "D0", &piD0);
    SciErr ROS = getVarAddressFromName(pvApiCtx, "ros", &piROS);
    SciErr D0I = getVarAddressFromName(pvApiCtx, "D0i", &piD0I);

    if (D0.iErr || ROS.iErr || D0I.iErr)
    {
        qDebug() << "Impossible de recuperer une des variables";
    }
    else
    {
        //*pi renvoie le TYPE de la variable. Ici: sci_matrix: matrices de double
        int ligne, colonne; // va contenir le nb de lignes et de colonnes de la matrice
        double *matrixOfDouble = NULL;
        D0 = getMatrixOfDouble(pvApiCtx, piD0, &ligne, &colonne, &matrixOfDouble);
        delta0 = *matrixOfDouble; // récupération de D0
        ROS = getMatrixOfDouble(pvApiCtx, piROS, &ligne, &colonne, &matrixOfDouble);
        ros = *matrixOfDouble; // récupération de ros
        D0I = getMatrixOfDouble(pvApiCtx, piD0I, &ligne, &colonne, &matrixOfDouble);
        D0i = *matrixOfDouble; // récupréation de d0i
    }
}

vector<double> Calculs::getDVexpValues()
{
    int* piDVexp = NULL;

    SciErr DVexp = getVarAddressFromName(pvApiCtx, "dVexp", &piDVexp);

    if (DVexp.iErr)
    {
        qDebug() << "Impossible de recuperer la variable";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        DVexp = getMatrixOfDouble(pvApiCtx, piDVexp, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piDVexp, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            dVexp.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
}

vector<double> Calculs::getFrequencies()
{
    int* piFreq;

    SciErr Freq = getVarAddressFromName(pvApiCtx, "f", &piFreq);

    if (Freq.iErr)
    {
        qDebug() << "Impossible de recuperer la variable";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        Freq = getMatrixOfDouble(pvApiCtx, piFreq, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piFreq, &ligne, &colonne);
        qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
            freq.push_back(matrixOfDouble[i]);
    }

    return freq;
}

double Calculs::getRos()
{
    return ros;
}

double Calculs::getD0i()
{
    return D0i;
}

double Calculs::getD0()
{
    return delta0;
}
