#include "Detecteur.h"

Detecteur::Detecteur(QObject *parent) : QObject(parent)
{
}
int Detecteur::seConnecter()
{
    int etatConnection=0;
    QList<QSerialPortInfo> listePorts;
    listePorts = QSerialPortInfo::availablePorts();

    for (int i=0; i < listePorts.size();++i)
    {
        QString nomPort=listePorts[i].portName();

        port->setPortName(nomPort);
        port->setBaudRate(QSerialPort::Baud9600);
        port->setParity(QSerialPort::NoParity);
        port->setDataBits(QSerialPort::Data8);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);
        // ouverture du port
        port->open(QIODevice::ReadWrite);
        // vérification du paramétrage et de l'ouverture du port
        qDebug() << nomPort <<"<debug> etat ouverture port :" << port->isOpen();
        if (port->isOpen())
        {
            port->write("*IDN?\r");
            //reponse du detecteur sera: "Stanford_Research_Systems,SR850,s/n00001,ver001"
            QByteArray r;

            while (port->waitForReadyRead(1000))
            {
                r = port->readAll();
                if (r != "\r")
                {
                    tramR+=r;
                }
                else
                    break;
            }
            if (tramR.contains("SR850"))
            {
                nomDetecteur=tramR;
                tramR = "";
                etatConnection=1;
                break;
            }
        }
        qDebug() << tramR;
    }
    return etatConnection;
}
QString Detecteur::getPortName()
{
    return port->portName();
}
QString Detecteur::getNomDetecteur()
{
    return nomDetecteur;
}
void Detecteur::setFileName(QString fTxt)
{
    file = new QFile(fTxt);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
}
void Detecteur::setNombreEchantillon(int nbEchantillon)
{
    nombreEchantillon=nbEchantillon;
}
void Detecteur::setFrequenceReference(double freqReference)
{
    frequenceReference=freqReference;
}
void Detecteur::setFrequenceDepart(double freqDepart)
{
    frequenceDepart=freqDepart;
}
void Detecteur::setPasFrequence(double pasFreq)
{
    pasFrequence=pasFreq;
}
void Detecteur::setFrequenceFin(double freqFin)
{
    frequenceFin=freqFin;
}
QVector<QString> Detecteur::getvecteurX()
{
    return vecteurX;
}
QVector<QString> Detecteur::getvecteurF()
{
    return vecteurF;
}
QVector<QString> Detecteur::getvecteurY()
{
    return vecteurY;
}
QVector<QString> Detecteur::getvecteurR()
{
    return vecteurR;
}
void Detecteur::recupererMesuresSNAP()
{
    QByteArray r;
    while (r!="\r")
    {
        r = port->readAll();
        tramR+=r;
    }
    qDebug() << tramR;
    int s=tramR.size();
    tramR.truncate(s-2);
    vecteurData.push_back(tramR);
    tramR="";
}
void Detecteur::enregistrerDansFichierTxt()
{
    double nb=((frequenceFin-frequenceDepart)/pasFrequence)*5;
    int nbe;
    nbe=(int)nb;
    for(int l=0;l!=nbe;l=l+5)
    {
        QString d=vecteurData[l];
        QString d2=vecteurData[l+1];
        QString d3=vecteurData[l+2];
        QString d4=vecteurData[l+3];
        QString d5=vecteurData[l+4];
        file->write(d.toUtf8()+" "+d2.toUtf8()+" "+d3.toUtf8()+" "+d4.toUtf8()+" "+d5.toUtf8()+"\n");
    }
}
void Detecteur::recupererMesuresSPTS()
{
    QByteArray r;
    while (r!="\r")
    {
        r = port->readAll();
        tramR+=r;
        qDebug() << tramR;
    }
    int s=tramR.size();
    tramR.truncate(s-2);
    QString donnee;
    donnee=(QString)tramR;
    if (vecteurX.size()<=nombreEchantillon)
        vecteurX.push_back(donnee);
    else
        if(vecteurF.size()<=nombreEchantillon)
            vecteurF.push_back(donnee);
        else
            vecteurY.push_back(donnee);
}
void Detecteur::initialisationSR850()
{
    //Initialisation de l’afficheur monochrome
    port->write("SMOD 1; ADSP 1; DTYP1, 3;DTRC 1, 1;DSCL 1,1.000000;DOFF 1,0.000000;DHZS 1,11\r");
    //Initialisation de la tension
    port->write("SLVL 0.060000\r");    
}
void Detecteur::modificationVoltage(double v)
{
    QByteArray volt = QByteArray::number(v, 'f', 6);
    port->write("SLVL " + volt+"\r");
}
void Detecteur::applySettings1()
{
    port->write("SRC 1;IGND 1;ICPL 0;ILIN 2;OFSL 1;SYNC 1\r");
    port->write("AGAN;ARSV;OFLT 8\r");
    QByteArray fr = QByteArray::number(frequenceReference, 'f', 6);
    QByteArray fd = QByteArray::number(frequenceDepart, 'f', 6);
    QByteArray ff = QByteArray::number(frequenceFin, 'f', 6);
    QByteArray nbE = QByteArray::number(nombreEchantillon);

    port->write("FMOD 1;PHAS 0.000000;FREQ "+fr+";HARM 1;SWPT 0;SLLM "+fd+";SULM "+ff+";RSLP 0;SEND 0;SRAT 4;SLEN "+nbE+"\r");

}
void Detecteur::applySettings2()
{
    port->write("SRC 1;IGND 1;ICPL 0;ILIN 2;OFSL 1;SYNC 1\r");
    port->write("AGAN;ARSV;OFLT 8\r");
    QByteArray fr = QByteArray::number(frequenceReference, 'f', 6);
    QByteArray fd = QByteArray::number(frequenceDepart, 'f', 6);
    QByteArray ff = QByteArray::number(frequenceFin, 'f', 6);
    QByteArray nbE = QByteArray::number(nombreEchantillon);

    port->write("FMOD 1;PHAS 0.000000;FREQ "+fr+";HARM 1;SWPT 0;SLLM "+fd+";SULM "+ff+";RSLP 0;SEND 0;SRAT 4;SLEN "+nbE+"\r");
}
void Detecteur::configTrace1et2()
{
    port->write("TRCD 1, 1, 0, 0, 1\r");
    port->write("TRCD 2, 12, 0, 0, 1\r");
    port->write("TRCD 3, 2, 0, 0, 1\r");

}
void Detecteur::start()
{
    QObject::disconnect(port,SIGNAL(readyRead()),this,SLOT(recupererMesuresSNAP()));
    //port->write("");
    port->write("STRT\r");
    double attente=(frequenceFin-frequenceDepart)/pasFrequence;
    QByteArray att = QByteArray::number(attente, 'f', 0);
    int time;
    time=(int)attente;
    qDebug()<<time;
    QTimer t;
    t.start(time*1000);
    int i=0;
    QByteArray r;
    while (i!=1)
    {
        port->write("SPTS? 1\r");
        while (port->waitForReadyRead(10000))
        {
            r = port->readAll();
            if (r != "\r")
            {
                tramR+=r;
            }
            else
                break;
        }
        if (tramR.contains(att))
        {
            tramR = "";
            i=1;
        }
        else
            tramR = "";
    }
    QObject::connect(port,SIGNAL(readyRead()),this,SLOT(recupererMesuresSPTS()));
    QByteArray nbE = QByteArray::number(nombreEchantillon);
    port->write("TRCA? 1,0,"+nbE+"\r");
    port->write("TRCA? 2,0,"+nbE+"\r");
    port->write("TRCA? 3,0,"+nbE+"\r");
}
void Detecteur::recalcul()
{
    int i, freq;
    double f=(frequenceFin-frequenceDepart)/pasFrequence;
    freq=(int)f;
    for (i=0; freq<=i; ++i)
    {
        int d=f*i+frequenceReference;
        QString donnee;
        donnee=(QString)d;
        vecteurR.push_back(donnee);
    }
}
void Detecteur:: etalonnage()
{
    QByteArray fr = QByteArray::number(frequenceReference, 'f', 6);

    port->write("FMOD 0;PHAS 0.000000;FREQ "+fr+";HARM 1;SWPT 0;SLLM 1000.000000;SULM 1000.000000;RSLP 0;ISRC 1;IGND 1;ICPL 0;ILIN 2;OFSL 1;SYNC 0\r");
    port->write("AGAN;ARSV;OFLT 8");
    port->write("FMOD 0;PHAS 0.000000;FREQ "+fr+";HARM 1;SWPT 0;SLLM 1000.000000;SULM 1000.000000;RSLP 0;ISRC 1;IGND 1;ICPL 0;ILIN 2;OFSL 1;SYNC 0\r");
}
void Detecteur::lancerBalayage()
{
    QObject::disconnect(port,SIGNAL(readyRead()),this,SLOT(recupererMesuresSPTS()));

    QObject::connect(port,SIGNAL(readyRead()),this,SLOT(recupererMesuresSNAP()));

    QByteArray fd = QByteArray::number(frequenceDepart, 'f', 6);
    QByteArray ff = QByteArray::number(frequenceFin, 'f', 6);
    double variationFrequence=frequenceDepart;
    QByteArray vf = QByteArray::number(variationFrequence, 'f', 6);
    while(variationFrequence<frequenceFin)
    {
        //FREQ va varier de Freq Départ à Freq Fin avec un increment de Pas de fréquence
        port->write("FMOD 0;PHAS 0.000000;FREQ "+vf+";HARM 1;SWPT 0;SLLM "+fd+";SULM "+ff+";RSLP 0\r");
        port->write("SNAP? 1,2,3,4,9\r");
        variationFrequence+=pasFrequence;
        vf = QByteArray::number(variationFrequence, 'f', 6);         
    }
}

