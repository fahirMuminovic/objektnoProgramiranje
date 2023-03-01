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
    // konstruktuj stanja
    inicijalizirajStanja();
    // iscrtaj elemente na QGraphicsView
    inicijalizirajElemente();
}

Dialog::~Dialog()
{
    delete ui;
}
// funkcija kontruktuje stanja
void Dialog::inicijalizirajStanja() {
    startStanje = new Stanje(-390, -280, QString("Start"));
    readyStanje = new Stanje(-220, -65, QString("Ready"));
    waitStanje = new Stanje(-50, 150, QString("Wait"));
    runStanje = new Stanje(120, -65, QString("Run"));
    stopStanje = new Stanje(290, -280, QString("Stop"));
}

// funkcija crta elemente na QGraphicsView
void Dialog::inicijalizirajElemente(){
    scene->addItem(startStanje);
    scene->addItem(readyStanje);
    scene->addItem(waitStanje);
    scene->addItem(runStanje);
    scene->addItem(stopStanje);
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
