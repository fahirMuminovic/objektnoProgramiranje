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
    void konektujSignale();
    // koristi se za provjeru broja procesa unutar stanja
    bool provjeriErrore(Stanje *izStanja, Stanje *doStanja);

private slots:
    // reaguje na klik pushButtona imena kreirajProces
    void on_kreirajProces_clicked();
    // reaguje na klik pushButtona imena kreirajProces
    void on_unistiProces_clicked();
    // pomjera proces iz jednog stanja u drugo
    void pomjeriProces();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

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
};

#endif // DIALOG_H
