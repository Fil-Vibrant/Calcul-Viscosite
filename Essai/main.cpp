#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "essai.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Essai e;

    cout << "****************************************** ESSAI ******************************************" << endl;
    cout << "1: Tester Delta0" << endl;
    cout << "2: Tester Calibration" << endl;
    cout << "3: Tester Viscosite" << endl << endl;
    cout << "Saisir num test:" << endl << endl;
    int choix;
    cin >> choix;
    switch (choix) {
    case 1:
        cout << "delta0 = " << e.calculerDelta0(19304, 1e-9, "C:/Users/SN/Desktop/ProjetScilab/dataair2.txt", "C:/Users/SN/Desktop/ProjetScilab/delta0.sci");

        break;
    case 2:
        cout << "rayon = " << e.calculerRayonFil(998.21, 19304, 0.0010016, 0.000142162, "C:/Users/SN/Desktop/ProjetScilab/dataEauAmetek.txt", "C:/Users/SN/Desktop/ProjetScilab/calibration.sci");
        break;
    case 3:
        cout << "viscosite = " << e.calculerViscosite(857.7, 19304, 4.95506e-5, 0.000142172, "C:/Users/SN/Desktop/ProjetScilab/dataToluene1Ametek.txt", "C:/Users/SN/Desktop/ProjetScilab/viscosite.sci");
        break;
    default:
        break;
    }

    return a.exec();
}
