#include "calibration.h"

Calibration::Calibration()
{
    rayonFil = 0;
}

void Calibration::calculRayonFil(double ro, double ros2, double eta, double delta0, QString pathToData, QString pathToSciFile)
{
    Call_ScilabOpen(NULL, FALSE, NULL, 0);
    qDebug() << "Scilab started";

    double roFluideCal[] = {ro},
           ros[] = {ros2},
           etaFluideCal[] = {eta},
           d0[] = {delta0};

    int row = 1, col = 1;

    char roVarName[] = "ro",
         rosVarName[] = "ros",
         etaVarName[] = "eta",
         d0VarName[] = "D0";

    SciErr RO = createNamedMatrixOfDouble(pvApiCtx, roVarName, row, col, roFluideCal);
    SciErr ROS = createNamedMatrixOfDouble(pvApiCtx, rosVarName, row, col, ros);
    SciErr ETA = createNamedMatrixOfDouble(pvApiCtx, etaVarName, row, col, etaFluideCal);
    SciErr D0 = createNamedMatrixOfDouble(pvApiCtx, d0VarName, row, col, d0);

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

    int* piRayon = NULL;

    SciErr RAYON = getVarAddressFromName(pvApiCtx, "Rayon", &piRayon);

    if (RO.iErr || ROS.iErr || ETA.iErr || D0.iErr || RAYON.iErr)
    {
        qDebug() << "Impossible de recuperer une ou plusieurs variables";
    }
    else
    {
        int ligne, colonne;
        double* matrixOfDouble = NULL;
        RAYON = getMatrixOfDouble(pvApiCtx, piRayon, &ligne, &colonne, &matrixOfDouble);
        rayonFil = *matrixOfDouble;

        getXexpValues();
        getFrequencies();
        getXcalValues();
        getYexpValues();
        getYcalValues();
    }
}

void Calibration::getXexpValues()
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

void Calibration::getFrequencies()
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

void Calibration::getXcalValues()
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

void Calibration::getYexpValues()
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

void Calibration::getYcalValues()
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

double Calibration::getRayonFil()
{
    return rayonFil;
}

vector<double> Calibration::getXexp()
{
    return Xexp;
}

vector<double> Calibration::getXcal()
{
    return Xcal;
}

vector<double> Calibration::getFreq()
{
    return frequencies;
}


vector<double> Calibration::getYexp()
{
    return Yexp;
}

vector<double> Calibration::getYcal()
{
    return Ycal;
}
