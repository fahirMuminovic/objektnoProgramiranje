#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // kreiranje scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    // podešavanje veličine scene
    scene->setSceneRect(-400,-300,800,600);
    // ukloni horizontalni scroll bar
    ui->graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    // ukloni vertikalni scroll bar
    ui->graphicsView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    // oboji pozadinu scene u plavu boju
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::blue));
    // konstruktuj elemente
    inicijalizirajElemente();
    // iscrtaj elemente na QGraphicsView
    iscrtajElemente();
    // konektuj signale
    konektujSignale();
}

Dialog::~Dialog()
{
    delete ui;
}
// funkcija kontruktuje stanja
void Dialog::inicijalizirajElemente() {
    startStanje = new Stanje(-390, -280, QString("Start"));
    readyStanje = new Stanje(-220, -65, QString("Ready"));
    waitStanje = new Stanje(-50, 150, QString("Wait"));
    runStanje = new Stanje(120, -65, QString("Run"));
    stopStanje = new Stanje(290, -280, QString("Stop"));

    readyRunTranzicija = new Tranzicija(-100, 15, 210, 0);
    runReadyTranzicija = new Tranzicija(-110, 25, 210, 180);
    startReadyTranzicija = new Tranzicija(-350, 100, 150, 45);
    waitReadyTranzicija = new Tranzicija(-80, -140, 140, 225);
    runWaitTranzicija = new Tranzicija(-80, -150, 150, 135);
    runStopTranzicija = new Tranzicija(185, 110, 150, 315);
}

// funkcija crta elemente na QGraphicsView
void Dialog::iscrtajElemente(){
    scene->addItem(startStanje);
    scene->addItem(readyStanje);
    scene->addItem(waitStanje);
    scene->addItem(runStanje);
    scene->addItem(stopStanje);

    scene->addItem(readyRunTranzicija);
    scene->addItem(runReadyTranzicija);
    scene->addItem(startReadyTranzicija);
    scene->addItem(waitReadyTranzicija);
    scene->addItem(runWaitTranzicija);
    scene->addItem(runStopTranzicija);
}

void Dialog::on_kreirajProces_clicked(){
    if(startStanje->brojProcesa < 5){
        startStanje->brojProcesa++;
        ui->graphicsView->viewport()->repaint();
    }
}

void Dialog::on_unistiProces_clicked(){
    if(stopStanje->brojProcesa > 0){
        stopStanje->brojProcesa--;
        ui->graphicsView->viewport()->repaint();
    }
}

// omogućava izvrsavanje custom funkcija na zadati signal (onClick)
void Dialog::konektujSignale() {
     connect(startReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
     connect(  readyRunTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
     connect(   runStopTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
     connect(  runReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
     connect(   runWaitTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
     connect( waitReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));

}

// provjera da li se procesi mogu prebaciti iz odgovarajucih stanja
bool Dialog::provjeriErrore(Stanje *izStanja, Stanje *doStanja){
    return izStanja->brojProcesa == 0 || doStanja->brojProcesa == 5;
}

// funkcija koja prebacuje procese iz jednog stanja u drugo na klik strelice
void Dialog::pomjeriProces(){
    if(sender()==startReadyTranzicija){
        if(!provjeriErrore(startStanje,readyStanje)){
            startStanje->brojProcesa--;
            readyStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
    if(sender()==readyRunTranzicija){
        if(!provjeriErrore(readyStanje,runStanje)){
            readyStanje->brojProcesa--;
            runStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
    if(sender()==runStopTranzicija){
        if(!provjeriErrore(runStanje,stopStanje)){
            runStanje->brojProcesa--;
            stopStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
    if(sender()==runReadyTranzicija){
        if(!provjeriErrore(runStanje,readyStanje)){
            runStanje->brojProcesa--;
            readyStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
    if(sender()==runWaitTranzicija){
        if(!provjeriErrore(runStanje,waitStanje)){
            runStanje->brojProcesa--;
            waitStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
    if(sender()==waitReadyTranzicija){
        if(!provjeriErrore(waitStanje,readyStanje)){
            waitStanje->brojProcesa--;
            readyStanje->brojProcesa++;

            ui->graphicsView->viewport()->repaint();
        }
    }
}
