#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // kreiranje scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    // podešavanje veličine scene
    scene->setSceneRect(0,0,800,600);
    // poboljšava kvalitet rendera
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
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
    // konektuj signale klika strelice sa slotovima pomjeriProces()
    konektujSignale();
}

Dialog::~Dialog()
{
    delete ui;
}
// funkcija kontruktuje stanja
void Dialog::inicijalizirajElemente() {
    startStanje = new Stanje(10, 20, QString("Start"));
    readyStanje = new Stanje(150, 250, QString("Ready"));
    waitStanje = new Stanje(350, 480, QString("Wait"));
    runStanje = new Stanje(550, 250, QString("Run"));
    stopStanje = new Stanje(690, 20, QString("Stop"));

    readyRunTranzicija = new Tranzicija(260, 325, 270, 0);
    runReadyTranzicija = new Tranzicija(-540, -285, 270, 180);
    startReadyTranzicija = new Tranzicija(140,15, 150, 53);
    waitReadyTranzicija = new Tranzicija(-600, -100, 180, 225);
    runWaitTranzicija = new Tranzicija(-160, -660, 180, 135);
    runStopTranzicija = new Tranzicija(175, 660, 155, 307);
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
// kreira procese u stanju start
void Dialog::on_kreirajProces_clicked(){
    if(startStanje->brojProcesa < 5){
        startStanje->brojProcesa++;
        ui->graphicsView->viewport()->repaint();
    }
}
// uklanja procese iz stanja stop
void Dialog::on_unistiProces_clicked(){
    if(stopStanje->brojProcesa > 0){
        stopStanje->brojProcesa--;
        ui->graphicsView->viewport()->repaint();
    }
}

// omogućava izvrsavanje custom funkcija na zadati signal (onClick)
void Dialog::konektujSignale() {
    connect(  readyRunTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
    connect(  runReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
    connect(startReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
    connect( waitReadyTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
    connect(   runWaitTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
    connect(   runStopTranzicija,SIGNAL(onClick()),this,SLOT(pomjeriProces()));
}

// provjera da li se procesi mogu prebaciti iz odgovarajucih stanja
bool Dialog::imaErrore(Stanje *izStanja, Stanje *doStanja){
    return izStanja->brojProcesa <= 0 || doStanja->brojProcesa >= 5;
}

// pokrece animaciju prelazka procesa za odredjeno stanje
void Dialog::pokreniAnimaciju(Stanje *izStanja, Stanje *doStanja)
{
    QPointF pocetnaPozicija;
    QPointF krajnjaPozicija;
    QPointF korak;
    int interval;

    if(izStanja == readyStanje && doStanja == runStanje)
    {
        pocetnaPozicija.setX(256);
        pocetnaPozicija.setY(300);

        krajnjaPozicija.setX(536);
        krajnjaPozicija.setY(300);

        korak.setX(10);
        korak.setY(0);

        interval = 15;
    }
    else if(izStanja == runStanje && doStanja == readyStanje)
    {
        pocetnaPozicija.setX(536);
        pocetnaPozicija.setY(300);

        krajnjaPozicija.setX(256);
        krajnjaPozicija.setY(300);

        korak.setX(-10);
        korak.setY(0);

        interval = 15;
    }
    else if(izStanja == startStanje && doStanja == readyStanje)
    {
        pocetnaPozicija.setX(50);
        pocetnaPozicija.setY(126);

        krajnjaPozicija.setX(150);
        krajnjaPozicija.setY(276);

        korak.setX(1);
        korak.setY(1.5);

        interval = 3;
    }
    else if(izStanja == runStanje && doStanja == waitStanje)
    {
        pocetnaPozicija.setX(593);
        pocetnaPozicija.setY(360);

        krajnjaPozicija.setX(443);
        krajnjaPozicija.setY(510);

        korak.setX(-1);
        korak.setY(1);

        interval = 3;
    }
    else if(izStanja == waitStanje && doStanja == readyStanje)
    {
        pocetnaPozicija.setX(350);
        pocetnaPozicija.setY(511);

        krajnjaPozicija.setX(190);
        krajnjaPozicija.setY(351);

        korak.setX(-1);
        korak.setY(-1);

        interval = 3;
    }
    else if(izStanja == runStanje && doStanja == stopStanje)
    {
        pocetnaPozicija.setX(620);
        pocetnaPozicija.setY(240);

        krajnjaPozicija.setX(730);
        krajnjaPozicija.setY(86);

        korak.setX(1);
        korak.setY(-1.4);

        interval = 3;
    }

    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
    ellipse->setBrush(Qt::red);

    // postavi poziciju elipse na sceni
    ellipse->setPos(pocetnaPozicija);
    scene->addItem(ellipse);

    // kreiraj QTimer objekt i konektuj njegov timeout signal sa slotom
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() {
        // pomjeri elipsu na sceni za odredjeni korak
        ellipse->setPos(ellipse->pos() + korak);
        if(ellipse->pos() == krajnjaPozicija)
        {
            timer->stop();
            scene->removeItem(ellipse);
            ui->graphicsView->viewport()->repaint();
        }
    });

    // postavi interval timera u milisekundama i pokreni ga
    timer->start(interval);
}

// funkcija koja prebacuje procese iz jednog stanja u drugo na klik strelice
void Dialog::pomjeriProces(){

    // definisi mapu koja sadrzi tranzicije i stanja povezana sa tom tranzicijom
    QMap<QObject*, QPair<Stanje*, Stanje*>> tranzicije {
    {readyRunTranzicija, {readyStanje, runStanje}},
    {runReadyTranzicija, {runStanje, readyStanje}},
    {startReadyTranzicija, {startStanje, readyStanje}},
    {runWaitTranzicija, {runStanje, waitStanje}},
    {waitReadyTranzicija, {waitStanje, readyStanje}},
    {runStopTranzicija, {runStanje, stopStanje}}
    };

    // pronadji povezana stanja sa kliknutom tranzicijom
    QPair<Stanje*, Stanje*> povezanaStanja = tranzicije[sender()];

    // provjeri errore
    if(!imaErrore(povezanaStanja.first, povezanaStanja.second)){
        // update-uj broj procesa u povezanim stanjima
        povezanaStanja.first->brojProcesa--;
        povezanaStanja.second->brojProcesa++;

        // pokreni animaciju za tranziciju
        pokreniAnimaciju(povezanaStanja.first, povezanaStanja.second);
    }
}
