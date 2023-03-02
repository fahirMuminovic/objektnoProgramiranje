#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QPainter>
#include "stanje.h"
#include "tranzicija.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    // funkcija pravi elemente "stanje"
    void inicijalizirajElemente();
    // funkcija "crta" elemente na QGraphicsView
    void iscrtajElemente();
    // spoji signale
    //void konektujSignale();
    //bool provjeriErrore(Tranzicija *tranzicija,Stanje *izStanja, Stanje *doStanja);

private slots:
    void on_kreirajProces_clicked();
    void on_unistiProces_clicked();
//    void startReadyClicked();
//    void runReadyClicked();
//    void runStopClicked();
//    void readyRunClicked();
//    void waitReadyClicked();
//    void runWaitClicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;

    Stanje *startStanje;
    Stanje *readyStanje;
    Stanje *waitStanje;
    Stanje *runStanje;
    Stanje *stopStanje;

    Tranzicija *startReadyTranzicija;
    Tranzicija *readyRunTranzicija;
    Tranzicija *runReadyTranzicija;
    Tranzicija *waitReadyTranzicija;
    Tranzicija *runWaitTranzicija;
    Tranzicija *runStopTranzicija;

//public slots:
//    void pomjeriProcesStartReady();
//    void pomjeriProcesReadyRun();
//    void pomjeriProcesRunReady();
//    void pomjeriProcesWaitReady();
//    void pomjeriProcesRunWait();
//    void pomjeriProcesRunStop();
};

#endif // DIALOG_H
