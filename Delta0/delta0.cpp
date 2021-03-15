#include "delta0.h"

Delta0::Delta0(QObject *parent) : QObject(parent)
{
    delta0 = 0;
    rayonFil = 0;
    viscosite = 0;

    if ( StartScilab(NULL, NULL, 0) == FALSE ) // Appel de Scilab
    {
        //qDebug() << "Impossible d'appeler StartScilab";
    }
    else
        SendScilabJob((char*)"exec('C:/Users/SN/Desktop/ProjetScilab/delta0.sci');");
}

void Delta0::calculDelta0()
{
    int* piD0 = NULL;
    int* piROS = NULL;
    int* piD0I = NULL;

    SciErr D0 = getVarAddressFromName(pvApiCtx, "D0", &piD0);
    SciErr ROS = getVarAddressFromName(pvApiCtx, "ros", &piROS);
    SciErr D0I = getVarAddressFromName(pvApiCtx, "D0i", &piD0I);

    if (D0.iErr || ROS.iErr || D0I.iErr)
    {
        //qDebug() << "Impossible de recuperer une des variables";
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

vector<double> Delta0::getDVexpValues()
{
    int* piDVexp = NULL;

    SciErr DVexp = getVarAddressFromName(pvApiCtx, "dVexp", &piDVexp);

    if (DVexp.iErr)
    {
        //qDebug() << "Impossible de recuperer une des variables";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        DVexp = getMatrixOfDouble(pvApiCtx, piDVexp, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piDVexp, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            dVexp.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
    return dVexp;
}

vector<double> Delta0::getFrequencies()
{
    int* piFreq = NULL;

    SciErr Freq = getVarAddressFromName(pvApiCtx, "f", &piFreq);

    if (Freq.iErr)
    {
        //qDebug() << "Impossible de recuperer une des variables";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        Freq = getMatrixOfDouble(pvApiCtx, piFreq, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piFreq, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            frequencies.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
    return frequencies;
}

vector<double> Delta0::getDVcalValues()
{
    int* piDVcal = NULL;

    SciErr DVcal = getVarAddressFromName(pvApiCtx, "dVcal", &piDVcal);

    if (DVcal.iErr)
    {
        //qDebug() << "Impossible de recuperer une des variables";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        DVcal = getMatrixOfDouble(pvApiCtx, piDVcal, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piDVcal, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            dVcal.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
    return dVcal;
}

double Delta0::getRos()
{
    return ros;
}

double Delta0::getD0i()
{
    return D0i;
}

double Delta0::getD0()
{
    return delta0;
}

