#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    brojProcesa = 9;
    visinaScene = 390;
    duzinaScene = 650;
    trenutnoOdabraniAlgoritam = QString("FCFS");

    postaviUiElementeUNizove();
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

// funkcija mijenja UI u odnosu na korisnički odabrani broj procesa
void Dialog::on_broj_procesa_comboBox_currentIndexChanged(const QString &odabraniBrojProcesa)
{
    brojProcesa = odabraniBrojProcesa.toInt();

    for(int i = 0; i < 9; i++){
        if(i < brojProcesa){
            dolazakUCiklusu[i]->setVisible(true);
            trajanjeCiklusa[i]->setVisible(true);
            prioritetCiklusa[i]->setVisible(true);
            procesiLabel[i]->setVisible(true);
        }else{
            dolazakUCiklusu[i]->setVisible(false);
            trajanjeCiklusa[i]->setVisible(false);
            prioritetCiklusa[i]->setVisible(false);
            procesiLabel[i]->setVisible(false);
        }
    }
}

// funkcija postavalja ui elemente u odgovarajuce nizove zbog lakse obrade u kodu
void Dialog::postaviUiElementeUNizove(){
    dolazakUCiklusu[0] = ui->dolazak_u_ciklusu_1;
    dolazakUCiklusu[1] = ui->dolazak_u_ciklusu_2;
    dolazakUCiklusu[2] = ui->dolazak_u_ciklusu_3;
    dolazakUCiklusu[3] = ui->dolazak_u_ciklusu_4;
    dolazakUCiklusu[4] = ui->dolazak_u_ciklusu_5;
    dolazakUCiklusu[5] = ui->dolazak_u_ciklusu_6;
    dolazakUCiklusu[6] = ui->dolazak_u_ciklusu_7;
    dolazakUCiklusu[7] = ui->dolazak_u_ciklusu_8;
    dolazakUCiklusu[8] = ui->dolazak_u_ciklusu_9;

    trajanjeCiklusa[0] = ui->broj_ciklusa_trajanja_1;
    trajanjeCiklusa[1] = ui->broj_ciklusa_trajanja_2;
    trajanjeCiklusa[2] = ui->broj_ciklusa_trajanja_3;
    trajanjeCiklusa[3] = ui->broj_ciklusa_trajanja_4;
    trajanjeCiklusa[4] = ui->broj_ciklusa_trajanja_5;
    trajanjeCiklusa[5] = ui->broj_ciklusa_trajanja_6;
    trajanjeCiklusa[6] = ui->broj_ciklusa_trajanja_7;
    trajanjeCiklusa[7] = ui->broj_ciklusa_trajanja_8;
    trajanjeCiklusa[8] = ui->broj_ciklusa_trajanja_9;

    prioritetCiklusa[0] = ui->prioritet_1;
    prioritetCiklusa[1] = ui->prioritet_2;
    prioritetCiklusa[2] = ui->prioritet_3;
    prioritetCiklusa[3] = ui->prioritet_4;
    prioritetCiklusa[4] = ui->prioritet_5;
    prioritetCiklusa[5] = ui->prioritet_6;
    prioritetCiklusa[6] = ui->prioritet_7;
    prioritetCiklusa[7] = ui->prioritet_8;
    prioritetCiklusa[8] = ui->prioritet_9;

    procesiLabel[0] = ui->P1;
    procesiLabel[1] = ui->P2;
    procesiLabel[2] = ui->P3;
    procesiLabel[3] = ui->P4;
    procesiLabel[4] = ui->P5;
    procesiLabel[5] = ui->P6;
    procesiLabel[6] = ui->P7;
    procesiLabel[7] = ui->P8;
    procesiLabel[8] = ui->P9;
}

// funkcija koja dodaje text za odgovarajuću proces pored y ose u zavisnosti od korisnicki odredjenog broja procesa
void Dialog::nacrtajProcesText(){
    for(int i = 0; i < brojProcesa; i++){
        QGraphicsTextItem *procesText = scene->addText(procesiLabel[i]->text(),QFont("Times New Roman", 10));
        procesText->setPos(1,40+(visinaScene/brojProcesa)*i);
        procesText->setDefaultTextColor(Qt::blue);
    }
}

// akivira se kada korisnik klikne na dugme Nacrtaj Gantov Dijagram
void Dialog::on_nacrtajDijagramBtn_clicked()
{
    // ocisti scenu od prethodnih elemenata
    scene->clear();
    nacrtajScenu();
    // iscrtaj text za procese pored y ose
    nacrtajProcesText();
    // iscrtaj qrectiteme za procese na odgovarajucim koordinatama
    // iscrtaj isprekidane linije na kraju svakog qrect itema paralelno sa y osom
}


