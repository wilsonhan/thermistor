#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <iostream>


namespace Ui {
class Dialog;
}



class Dialog : public QDialog
{
    Q_OBJECT
    double ResistanceValue;
public:

    explicit Dialog(QWidget *parent = 0);
    void setResistanceValue(double);
    double LineInterpolation(double ResistanceValue);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    //void on_SensorType_currentIndexChanged(const QString &arg1);

    //void on_SensorType_activated(int index);

private:
    Ui::Dialog *ui;
};




#endif // DIALOG_H
