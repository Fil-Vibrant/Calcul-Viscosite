#include "delta0.h"

Delta0::Delta0(QObject *parent) : QObject(parent)
{
    delta0 = 0;
    rayonFil = 0;
    //viscosite = 0;

}

void Delta0::calculDelta0(double r, double d, QString pathToData, QString pathToSciFile)
{
    Call_ScilabOpen(NULL, FALSE, NULL, 0);
    qDebug() << "Scilab started";
    // ros and d0i inputs
    // Declare ros and D0i variables (matrix in Scilab)
    double ros[] = {r},
           d0i[] = {d};

    int row = 1, col = 1; // number of rows & cols of each matrix

    // Scilab variables names
    char rosVarName[] = "ros";
    char d0iVarName[] = "D0i";

    // Write into Scilab's memory
    SciErr ROS = createNamedMatrixOfDouble(pvApiCtx, rosVarName, row, col, ros);
    SciErr D0I = createNamedMatrixOfDouble(pvApiCtx, d0iVarName, row, col, d0i);

    // command to read data file
    QString beginReadCommand = "Data = read('";
    QString endReadCommand = "',-1,3);";
    QString dataPath = pathToData;
    QString rCommand = beginReadCommand + dataPath + endReadCommand;
    QByteArray readCommand = rCommand.toLocal8Bit();

    // sending the command to Scilab
    SendScilabJob(readCommand.data());

    // Reading data from file
    SendScilabJob((char*)"f = Data(:,1)");
    SendScilabJob((char*)"Xexp = Data(:,2)");
    SendScilabJob((char*)"Yexp = Data(:,3)");

    // command to execute Scilab's file
    QString beginExecCommand = "exec('";
    QString endExecCommand = "');";
    QString sciFilePath = pathToSciFile;
    QString eCommand = beginExecCommand + sciFilePath + endExecCommand;
    QByteArray execCommand = eCommand.toLocal8Bit();

    // sending the command to Scilab
    SendScilabJob(execCommand.data());

    int* piD0 = NULL;

    // Read into Scilab's memory
    SciErr D0 = getVarAddressFromName(pvApiCtx, "D0", &piD0);

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

        getXexpValues();
        getFrequencies();
        getXcalValues();
        getYexpValues();
        getYcalValues();

    }
}

void Delta0::getXexpValues()
{
    qDebug() << "xexp";
    int* piXexp = NULL;

    SciErr xexp = getVarAddressFromName(pvApiCtx, "Xexp", &piXexp);

    if (xexp.iErr)
    {
        qDebug() << "Impossible de recuperer Xexp";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        getMatrixOfDouble(pvApiCtx, piXexp, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piXexp, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        qDebug() << "getting values ...";
        for (int i = 0; i < ligne; ++i)
        {
            Xexp.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
        qDebug() << "values added";
    }
}

void Delta0::getFrequencies()
{
    int* piFreq = NULL;

    SciErr Freq = getVarAddressFromName(pvApiCtx, "f", &piFreq);

    if (Freq.iErr)
    {
        qDebug() << "Impossible de recuperer une des variables";
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
}

void Delta0::getXcalValues()
{
    int* piXcal = NULL;

    SciErr xcal = getVarAddressFromName(pvApiCtx, "Xcal", &piXcal);

    if (xcal.iErr)
    {
        qDebug() << "Impossible de recuperer Xcal";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        xcal = getMatrixOfDouble(pvApiCtx, piXcal, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piXcal, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            Xcal.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
}

void Delta0::getYexpValues()
{
    int* piYexp = NULL;

    SciErr yexp = getVarAddressFromName(pvApiCtx, "Yexp", &piYexp);

    if (yexp.iErr)
    {
        qDebug() << "Impossible de recuperer Yexp";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        yexp = getMatrixOfDouble(pvApiCtx, piYexp, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piYexp, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            Yexp.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
}

void Delta0::getYcalValues()
{
    int* piYcal = NULL;

    SciErr ycal = getVarAddressFromName(pvApiCtx, "Ycal", &piYcal);

    if (ycal.iErr)
    {
        qDebug() << "Impossible de recuperer Ycal";
    }
    else
    {
        int ligne, colonne;
        double *matrixOfDouble = NULL;
        ycal = getMatrixOfDouble(pvApiCtx, piYcal, &ligne, &colonne, &matrixOfDouble);
        getVarDimension(pvApiCtx, piYcal, &ligne, &colonne); // récupère la taille de la matrice (nb lignes et colonnes)
        //qDebug() << ligne << colonne;
        for (int i = 0; i < ligne; ++i)
        {
            Ycal.push_back(matrixOfDouble[i]); // ajout des valeurs dans un tableau dynamique
        }
    }
}

double Delta0::getD0()
{
    return delta0;
}

vector<double> Delta0::getXexp()
{
    return Xexp;
}

vector<double> Delta0::getXcal()
{
    return Xcal;
}

vector<double> Delta0::getFreq()
{
    return frequencies;
}


vector<double> Delta0::getYexp()
{
    return Yexp;
}

vector<double> Delta0::getYcal()
{
    return Ycal;
}
