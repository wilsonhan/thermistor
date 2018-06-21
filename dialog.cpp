/**************************************************************************
 Author weiming
 date: June 18,2018




  ***************************************************************************/

#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <QMessageBox>


double MASCTemperature[60] ={-50,-40,-30,-20,-15,-10,-5,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,140,150};
double MASCResistance[60] ={ 667828,335671,176683,96974,72895,55298,42314,32650,31030,29500,28054,26688,25396,24173,23016,21921,20885,19904,18974,18092,17257,16465,15714,15001,14325,13623,13053,12494,11943,11420,10923,10450,10000,9572,9165,8777,8408,8056,6530,5325,4367,3601,2985,2487,2082,1751,1480,1256,1070,916.1,787,678.6,587.3,510.1,444.5,388.6,340.8,300,234.1,184.8};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);




}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setResistanceValue(double ResisVal){

    ResistanceValue = ResisVal;
}

double Dialog::LineInterpolation(double ResistanceValue)
{
    QStringList model,ResistanceAndTemperatureTableArray;
    float ResistanceTable[200];
    qint16 TemperatureTable[200];
    bool ok;

    QFile file("C:/Users/e1205074/Documents/test/A-10K3A1.csv");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
    }

    QTextStream ResistanceAndTemperatureTable(&file);

    while(!ResistanceAndTemperatureTable.atEnd()){

        QString line = ResistanceAndTemperatureTable.readLine();
        QStringList fields = line.split(",");
        ResistanceAndTemperatureTableArray.append(fields);

    }
    file.close();


    for (int i=0; i<=((ResistanceAndTemperatureTableArray.size())/2-1);i++ ){

        TemperatureTable[i] = ResistanceAndTemperatureTableArray.at(i*2).toInt(&ok,10);

        ResistanceTable[i] = ResistanceAndTemperatureTableArray.at(i*2+1).toFloat(&ok);

    }



    if  ((ResistanceValue > MASCResistance[0])||(ResistanceValue < MASCResistance[59])){
            return 0;
    }



    for (int i = 0;i<=60 ;i++){



            if (ResistanceValue > MASCResistance[i]){
              double  resultTemperature = MASCTemperature[i] +(ResistanceValue-MASCResistance[i])* ((MASCTemperature[i-1]-MASCTemperature[i])/(MASCResistance[i-1]-MASCResistance[i]));
              std::cout <<resultTemperature;
              return resultTemperature;
            } 
        }

}

void Dialog::on_pushButton_clicked()
{
     double   ResistanceValue;
     double   FahrenheitTemperature;
     //LineInterpolation lineinterpolation;

     
    if (ui->ResistanceName->text().isEmpty())
        {
         ResistanceValue = 0.1;
        }
    else
        {
           ResistanceValue = (ui->ResistanceName->text()).toFloat();

           std::cout << "Hello world";

           std::cout<<LineInterpolation(ResistanceValue);

            QString strValue = QString::number(LineInterpolation(ResistanceValue), 'f', 2);

             FahrenheitTemperature = LineInterpolation(ResistanceValue)*(9/5) + 32;

            QString strValueF = QString::number(FahrenheitTemperature, 'f', 3);

            ui->TemperatureName->setText(strValue);
            ui->FTemperatureName->setText(strValueF);

        }


}




//void Dialog::on_SensorType_activated(int index)
//{

//}
