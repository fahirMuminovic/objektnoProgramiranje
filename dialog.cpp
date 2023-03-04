#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    brojProcesa = 9;
    trenutnoOdabraniAlgoritam = QString("FCFS");

    nacrtajScenu();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::nacrtajScenu(){
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    scene->setSceneRect(0,0,750,450);

    QPen koordinatneOsePen;
    koordinatneOsePen.setColor(Qt::blue);
    koordinatneOsePen.setWidth(3);

    // y-osa
    scene->addLine(20,0,20,460,koordinatneOsePen);
    scene->addLine(10,20,20,0,koordinatneOsePen); // strelica lijeva
    scene->addLine(20,0,30,20,koordinatneOsePen); // strelica desna

    // x-osa
    scene->addLine(0,440,780,440,koordinatneOsePen);
    scene->addLine(760,430,780,440,koordinatneOsePen);  //strelica gornja
    scene->addLine(760,450,780,440,koordinatneOsePen);  //strelica donja

    // text na osama
    QGraphicsTextItem *textProcesi = scene->addText(QString("Procesi"),QFont("Times New Roman", 14));
    textProcesi->setPos(35,-1);
    textProcesi->setDefaultTextColor(Qt::blue);
    QGraphicsTextItem *textBrojCiklusa = scene->addText(QString("Broj Ciklusa"),QFont("Times New Roman", 14));
    textBrojCiklusa->setPos(650,438);
    textBrojCiklusa->setDefaultTextColor(Qt::blue);
}

