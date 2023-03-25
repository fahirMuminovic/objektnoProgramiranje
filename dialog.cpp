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

// funkcija koja prebacuje procese iz jednog stanja u drugo na klik strelice
void Dialog::pomjeriProces(){
    if(sender()==readyRunTranzicija){
        if(!imaErrore(readyStanje,runStanje)){
            readyStanje->brojProcesa--;

            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(256, 300);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(10, 0));
        //                qDebug()<<ellipse->pos();
        //                qDebug()<<timer->remainingTime();
                if(ellipse->pos() == QPointF(536,300))
                {
                    runStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(30);
        }
    }
    if(sender()==runReadyTranzicija){
        if(!imaErrore(runStanje,readyStanje)){
            runStanje->brojProcesa--;

            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(536, 300);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(-10, 0));
                if(ellipse->pos() == QPointF(256,300))
                {
                    readyStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(30);
        }
    }
    if(sender()==startReadyTranzicija){
        if(!imaErrore(startStanje,readyStanje)){
            startStanje->brojProcesa--;

            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(53, 126);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(10, 13));
//                qDebug()<<ellipse->pos();
                if(ellipse->pos() == QPointF(153,256))
                {
                    readyStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(40);
        }
    }
    if(sender()==runWaitTranzicija){
        if(!imaErrore(runStanje,waitStanje)){
            runStanje->brojProcesa--;

            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(593, 360);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(-10, 10));
//                qDebug()<<ellipse->pos();
                if(ellipse->pos() == QPointF(443,510))
                {
                    waitStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(35);
        }
    }
    if(sender()==waitReadyTranzicija){
        if(!imaErrore(waitStanje,readyStanje)){
            waitStanje->brojProcesa--;

            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(350, 511);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(-10, -10));
//                qDebug()<<ellipse->pos();
                if(ellipse->pos() == QPointF(190,351))
                {
                    readyStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(35);
        }
    }
    if(sender()==runStopTranzicija){
        if(!imaErrore(runStanje,stopStanje)){
            runStanje->brojProcesa--;


            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 10, 10));
            ellipse->setBrush(Qt::red);
//            qDebug()<<ellipse->pos();
            // Set the position of the ellipse item on the scene
            ellipse->setPos(621, 250);
            scene->addItem(ellipse);

            // Create a QTimer object and connect its timeout signal to a slot
            QTimer* timer = new QTimer();
            QObject::connect(timer, &QTimer::timeout, [=]() {
                // Move the ellipse item's position by a certain amount
                ellipse->setPos(ellipse->pos() + QPointF(10, -14));
//                qDebug()<<ellipse->pos();
                if(ellipse->pos() == QPointF(721,110))
                {
                    stopStanje->brojProcesa++;
                    timer->stop();
                    scene->removeItem(ellipse);
                    ui->graphicsView->viewport()->repaint();
                }
            });

            // Set the interval of the timer in milliseconds and start it
            timer->start(40);
        }
    }
}

void Dialog::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // get the position of the mouse click
    QPointF pos = event->scenePos();

    // log the position
    qDebug() << "Mouse clicked at position:" << pos;
}

