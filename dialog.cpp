#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QMap>
#include <QPair>

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // kreiranje scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    // podešavanje veličine scene
    scene->setSceneRect(0, 0, 800, 600);
    // poboljšava kvalitet rendera
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    // ukloni horizontalni scroll bar
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ukloni vertikalni scroll bar
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
void Dialog::inicijalizirajElemente()
{
    startStanje = new Stanje(10, 20, QString("Start"));
    readyStanje = new Stanje(150, 250, QString("Ready"));
    waitStanje = new Stanje(350, 480, QString("Wait"));
    runStanje = new Stanje(550, 250, QString("Run"));
    stopStanje = new Stanje(690, 20, QString("Stop"));

    readyRunTranzicija = new Tranzicija(260, 325, 270, 0);
    runReadyTranzicija = new Tranzicija(-540, -285, 270, 180);
    startReadyTranzicija = new Tranzicija(140, 15, 150, 53);
    waitReadyTranzicija = new Tranzicija(-600, -100, 180, 225);
    runWaitTranzicija = new Tranzicija(-160, -660, 180, 135);
    runStopTranzicija = new Tranzicija(175, 660, 155, 307);
}

// funkcija crta elemente na QGraphicsView
void Dialog::iscrtajElemente()
{
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
void Dialog::on_kreirajProces_clicked()
{
    if (startStanje->brojProcesa < 5)
    {
        startStanje->brojProcesa++;
        ui->graphicsView->viewport()->repaint();
    }
}
// uklanja procese iz stanja stop
void Dialog::on_unistiProces_clicked()
{
    if (stopStanje->brojProcesa > 0)
    {
        stopStanje->brojProcesa--;
        ui->graphicsView->viewport()->repaint();
    }
}

// omogućava izvrsavanje custom funkcija na zadati signal (onClick)
void Dialog::konektujSignale()
{
    connect(readyRunTranzicija,   SIGNAL(onClick()), this, SLOT(pomjeriProces()));
    connect(runReadyTranzicija,   SIGNAL(onClick()), this, SLOT(pomjeriProces()));
    connect(startReadyTranzicija, SIGNAL(onClick()), this, SLOT(pomjeriProces()));
    connect(waitReadyTranzicija,  SIGNAL(onClick()), this, SLOT(pomjeriProces()));
    connect(runWaitTranzicija,    SIGNAL(onClick()), this, SLOT(pomjeriProces()));
    connect(runStopTranzicija,    SIGNAL(onClick()), this, SLOT(pomjeriProces()));
}

// provjera da li se procesi mogu prebaciti iz odgovarajucih stanja
bool Dialog::imaErrore(Stanje *izStanja, Stanje *doStanja)
{
    return izStanja->brojProcesa <= 0 || doStanja->brojProcesa >= 5;
}

// pokrece animaciju prelaska procesa iz jednog stanja u drugo
void Dialog::pokreniAnimaciju(Stanje *izStanja, Stanje *doStanja)
{
    // definisi parametre animacije kao strukturu
    struct ParametriAnimacija
    {
        QPointF pocetnaPozicija;
        QPointF krajnjaPozicija;
        QPointF korak;
        int interval;
    };

    // definisi mapu koja sadrzi stanja i parametre animacije za ta stanja
    QMap<QPair<Stanje *, Stanje *>, ParametriAnimacija> animationMap{
        {{readyStanje, runStanje},   {{256, 300}, {536, 300}, {10, 0},   15}},
        {{runStanje, readyStanje},   {{536, 300}, {256, 300}, {-10, 0},  15}},
        {{startStanje, readyStanje}, {{50, 126},  {150, 276}, {1, 1.5},  3}},
        {{runStanje, waitStanje},    {{593, 360}, {443, 510}, {-1, 1},   3}},
        {{waitStanje, readyStanje},  {{350, 511}, {190, 351}, {-1, -1},  3}},
        {{runStanje, stopStanje},    {{620, 240}, {730, 86},  {1, -1.4}, 3}}};

    // pronadji parametre animacije za stanja koja su proslijedjena kao parametri u funkciju
    ParametriAnimacija parametriAnimacije = animationMap.value(qMakePair(izStanja, doStanja));

    // napravi ellipsu koja predstavlja proces u tranziciji i dodaj je na scenu
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
    ellipse->setBrush(Qt::red);
    ellipse->setPos(parametriAnimacije.pocetnaPozicija);
    scene->addItem(ellipse);

    // napravi QTimer objekat i konektuj njegov timeout signal sa lambda funkcijom koja predstavlja animaciju
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]()
                     {
        // postavi posiciju elipse
        ellipse->setPos(ellipse->pos() + parametriAnimacije.korak);

        // ukoliko elipsa dodje do svoje krajnje pozicije zaustavi animaciju
        if(ellipse->pos() == parametriAnimacije.krajnjaPozicija)
        {
            timer->stop();
            scene->removeItem(ellipse);
            ui->graphicsView->viewport()->repaint();
        } });

    // postavi interval timera i pokreni ga
    timer->start(parametriAnimacije.interval);
}

// funkcija koja prebacuje procese iz jednog stanja u drugo na klik strelice
void Dialog::pomjeriProces()
{

    // definisi mapu koja sadrzi tranzicije i stanja povezana sa tom tranzicijom
    QMap<QObject *, QPair<Stanje *, Stanje *>> tranzicije{
        {readyRunTranzicija, {readyStanje, runStanje}},
        {runReadyTranzicija, {runStanje, readyStanje}},
        {startReadyTranzicija, {startStanje, readyStanje}},
        {runWaitTranzicija, {runStanje, waitStanje}},
        {waitReadyTranzicija, {waitStanje, readyStanje}},
        {runStopTranzicija, {runStanje, stopStanje}}};

    // pronadji povezana stanja sa kliknutom tranzicijom
    QPair<Stanje *, Stanje *> povezanaStanja = tranzicije[sender()];

    // provjeri errore
    if (!imaErrore(povezanaStanja.first, povezanaStanja.second))
    {
        // update-uj broj procesa u povezanim stanjima
        povezanaStanja.first->brojProcesa--;
        povezanaStanja.second->brojProcesa++;

        // pokreni animaciju za tranziciju
        pokreniAnimaciju(povezanaStanja.first, povezanaStanja.second);
    }
}
