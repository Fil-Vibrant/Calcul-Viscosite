#include "CapteurTemperature.h"
#include <stdio.h>
#include <QDebug>


CapteurTemperature::CapteurTemperature()
{

}

void CapteurTemperature::recupTension()
{


        //int32       error=0;
        TaskHandle  taskHandle=0;
        int32       read;
        float64    data[1000];
        const float minVolt = 0;
        const float maxVolt = 10;
        //char        errBuff[2048]={'\0'};


        /*********************************************/
        // DAQmx Configure Code
        /*********************************************/
         DAQmxCreateTask("",&taskHandle);
         DAQmxCreateAIVoltageChan(taskHandle,"Dev1/ai0","",DAQmx_Val_RSE,minVolt,maxVolt,DAQmx_Val_Volts,NULL);



        /*********************************************/
        // DAQmx Start Code
        /*********************************************/
        DAQmxStartTask(taskHandle);

        /*********************************************/
        // DAQmx Read Code
        /*********************************************/
        DAQmxReadAnalogF64(taskHandle,1000,10.0,DAQmx_Val_GroupByChannel,data,1000,&read,NULL);

            qDebug() <<"la tension est" <<data[0];

        tension=data[0];

}
float CapteurTemperature::Gettension()
{
    return tension;
}
float CapteurTemperature::CalculTemp(float tens)
{
    const float minVolt = 0;
    const float maxVolt = 10;
    const float minTemp = 20;
    const float maxTemp = 60;
    float b=minTemp;
    float a=(maxTemp-minTemp)/(maxVolt-minVolt);
    temp=tens*a+b;
    return temp;

}
float CapteurTemperature::GetTemp()
{
    return temp;
}
















