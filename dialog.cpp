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
    // konektujSignale();
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

    readyRunTranzicija = new Tranzicija(-100, 20, 210, 0);
    runReadyTranzicija = new Tranzicija(-110, 30, 210, 180);
    startReadyTranzicija = new Tranzicija(-350, 100, 150, 45);
    waitReadyTranzicija = new Tranzicija(-80, -140, 140, 225);
    runWaitTranzicija = new Tranzicija(-50, -135, 140, 135);
    runStopTranzicija = new Tranzicija(195, 110, 150, 315);
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

//void Dialog::konektujSignale() {
//    connect(readyRunTranzicija, SIGNAL(onClick()),this,SLOT(readyRunClicked()));
//    connect(runReadyTranzicija, SIGNAL(onClick()),this,SLOT(runReadyClicked()));
//    connect(startReadyTranzicija, SIGNAL(onClick()),this,SLOT(startReadyClicked()));
//    connect(waitReadyTransition, SIGNAL(onClick()),this,SLOT(waitReadyClicked()));
//    connect(runWaitTransition, SIGNAL(onClick()),this,SLOT(runWaitClicked()));
//    connect(runStopTransition, SIGNAL(onClick()),this,SLOT(runStopClicked()));

//    connect(readyRunTranzicija->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesReadyRun()));
//    connect(runReadyTranzicija->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesRunReady()));
//    connect(startReadyTranzicija->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesStartReady()));
//    connect(waitReadyTransition->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesWaitReady()));
//    connect(runWaitTransition->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesRunWait()));
//    connect(runStopTransition->timer, SIGNAL(timeout()),this,SLOT(pomjeriProcesRunStop()));
//}

//bool Dialog::provjeriErrore(Tranzicija *tranzicija, Stanje *izStanja, Stanje *doStanja){
//    return tranzicija->timer->isActive() || izStanja->brojProcesa == 0 || doStanja->brojProcesa == 5;
//}

//void Dialog::startReadyClicked(){
//    startReadyTranzicija->tempY -= 280;
//    startReadyTranzicija->tempX += 50;
//    startReadyTranzicija->timer->start(50);
//}

//void Dialog::readyRunClicked(){
//    if(!provjeriErrore(readyRunTranzicija, readyStanje, runStanje)){
//            readyRunTranzicija->timer->start(50);
//       }
//}


//void Dialog::pomjeriProcesStartReady(){
//    if(startReadyTranzicija->tempY > -100){
//        scene->addEllipse(startReadyTranzicija->tempX-10, startReadyTranzicija->tempY+10,10,10,QPen(Qt::blue),QBrush(Qt::blue));
//        startReadyTranzicija->tempX = startReadyTranzicija->koordinataX;
//        startReadyTranzicija->tempY = startReadyTranzicija->koordinataY;

//        startStanje->brojProcesa--;
//        readyStanje->brojProcesa++;

//        ui->graphicsView->viewport()->repaint();

//        startReadyTranzicija->timer->stop();
//        return;
//    }else{
//        scene->addEllipse(startReadyTranzicija->tempX-10,startReadyTranzicija->tempY+10,10,10,QPen(Qt::blue),QBrush(Qt::blue));
//        scene->addEllipse(startReadyTranzicija->tempX,startReadyTranzicija->tempY+20,10,10,QPen(Qt::red),QBrush(Qt::red));

//        startReadyTranzicija->tempX+=10;
//        startReadyTranzicija->tempY+=10;

//        ui->graphicsView->viewport()->repaint();
//        return;
//    }
//}

//void Dialog::pomjeriProcesReadyRun(){
//    if(readyRunTranzicija->tempX-readyRunTranzicija->koordinataX > 160) {
//       scene->addEllipse(readyRunTranzicija->tempX-10,readyRunTranzicija->tempY+20,10,10,QPen(Qt::blue),QBrush(Qt::blue));
//       readyRunTranzicija->tempX = readyRunTranzicija->koordinataX;
//       readyRunTranzicija->tempY = readyRunTranzicija->koordinataY;

//       readyStanje->brojProcesa--;
//       runStanje->brojProcesa++;

//       ui->graphicsView->viewport()->repaint();
//       readyRunTranzicija->timer->stop();
//       return;
//   }
//   scene->addEllipse(readyRunTranzicija->tempX-10,readyRunTranzicija->tempY+20,10,10,QPen(Qt::blue),QBrush(Qt::blue));
//   scene->addEllipse(readyRunTranzicija->tempX,readyRunTranzicija->tempY+20,10,10,QPen(Qt::red),QBrush(Qt::red));
//   readyRunTranzicija->tempX+=10;
//   ui->graphicsView->viewport()->repaint();
//}
