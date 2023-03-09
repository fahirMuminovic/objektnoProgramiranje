#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    visinaScene = 390.00;
    duzinaScene = 650.00;

    initializeBrojProcesa();
    postaviUIElementeUNizove();
    podesiUIElemente();
    nacrtajScenu();
}
// postavlja broj procesa na vrijednost iz comboBoxa "broj_procesa" koje je korisnik odabrao
void Dialog::initializeBrojProcesa(){
    brojProcesa = ui->broj_procesa_comboBox->currentText().toInt();
}

// crta početnu scenu kada se pokrene program
void Dialog::nacrtajScenu(){
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);

    scene->setSceneRect(0,0,750,450);

    QPen koordinatneOsePen;
    koordinatneOsePen.setColor(Qt::blue);
    koordinatneOsePen.setWidth(2);

    // y-osa
    scene->addLine(20,0,20,460,koordinatneOsePen);
    scene->addLine(10,20,20,0,koordinatneOsePen); // strelica lijeva
    scene->addLine(20,0,30,20,koordinatneOsePen); // strelica desna

    // x-osa
    scene->addLine(0,440,780,440,koordinatneOsePen);
    scene->addLine(760,430,780,440,koordinatneOsePen);  //strelica gornja
    scene->addLine(760,450,780,440,koordinatneOsePen);  //strelica donja

    // text na y-osi
    QGraphicsTextItem *textProcesi = scene->addText(QString("Procesi"),QFont("Times New Roman", 14));
    textProcesi->setPos(35,-1);
    textProcesi->setDefaultTextColor(Qt::blue);

    // text na x-osi
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
void Dialog::postaviUIElementeUNizove(){
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

// inicijalizira niz koji sadrži objekte proces
void Dialog::napraviNizObjekataProces()
{
    for(int i = 0; i < brojProcesa; i++) {
        procesi[i].trajanje = trajanjeCiklusa[i]->value();
        procesi[i].trenutakDolaska = dolazakUCiklusu[i]->value();
        procesi[i].redniBroj = i;
    }
}

// sortira niz procesi po redoslijedu dolaska od elementa koji je dosao prvi do elementa koji je dosao posljednji
void Dialog::sortirajProcesePoTrenutkuDolaska(){
    for(int i = 0; i < brojProcesa; i++){
        for(int j = i + 1; j < brojProcesa; j++){
            if(procesi[j].trenutakDolaska < procesi[i].trenutakDolaska){
                Proces temp = procesi[i];
                procesi[i] = procesi[j];
                procesi[j] = temp;
            }
        }
    }
}

// funkcija koja dodaje text za odgovarajuću proces pored y ose u zavisnosti od korisnicki odredjenog broja procesa
void Dialog::nacrtajProcesText(){
    float posX = 0;
    float posY = 0;
    for(int i = 0; i < brojProcesa; i++){
        // broj 27 u formuli je izračunat na osnovu porebnog odstojanja od y-ose zbog strelica na y-osi
        posY = ((((visinaScene/brojProcesa)/2))*(i*2+1))+27;

        QGraphicsTextItem *procesText = scene->addText(procesiLabel[i]->text(),QFont("Times New Roman", 10));
        procesText->setPos(posX,posY);
        procesText->setDefaultTextColor(Qt::blue);
    }
}

void Dialog::nacrtajProcese(){
    QPen okvirProcesa;
    okvirProcesa.setWidth(1);
    okvirProcesa.setColor(Qt::blue);

    QPen isprekidanaLinija;
    isprekidanaLinija.setWidth(1);
    isprekidanaLinija.setColor(Qt::blue);
    isprekidanaLinija.setStyle(Qt::DashLine);

    QBrush bojaProcesa(Qt::green);
    sortirajProcesePoTrenutkuDolaska();

    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesi[i].trajanje;
    }

    float koordinataX = 0;
    float koordinataY = 0;
    float duzina = 0;
    float visina = visinaScene/brojProcesa;  // visina kvadrata koji predstavlja proces
    int dosadasnjaDuzina = 0;

    for(int i = 0; i < brojProcesa; i++){
        // 21 je potrebno odstojanje lijevog ruba scene
        koordinataX = 21 + dosadasnjaDuzina;
        // 40 je potrebno odstojanje od gornjeg ruba scene
        koordinataY = 40 + visina * procesi[i].redniBroj;
        duzina = procesi[i].trajanje * (duzinaScene / ukupnaDuzinaProcesa);
        dosadasnjaDuzina += procesi[i].trajanje * (duzinaScene/ukupnaDuzinaProcesa);

        // kvadrat koji predstavlja proces
        QRectF proces(koordinataX,koordinataY,duzina,visina);
        // dodaj proces na scenu
        scene->addRect(proces,okvirProcesa,bojaProcesa);

        // isprekidana linija nakon kvadrata koji predstavlja proces
        if(i == brojProcesa - 1) break; // ne želimo isprekidanu liniju nakon zadnjeg procesa
        scene->addLine(koordinataX + duzina,0,koordinataX + duzina,440,isprekidanaLinija);
    }
}

// akivira se kada korisnik klikne na dugme Nacrtaj Gantov Dijagram
void Dialog::on_nacrtajDijagramBtn_clicked()
{
    // ocisti scenu od prethodnih elemenata
    scene->clear();
    nacrtajScenu();

    // sprema korisnicki odabrani broj procesa u varijablu brojProcesa
    initializeBrojProcesa();
    // inicijaliziraj niz "procesi"
    napraviNizObjekataProces();
    // iscrtaj text za procese pored y ose
    nacrtajProcesText();
    // iscrtaj QRectItem-e za procese na odgovarajucim koordinatama
    nacrtajProcese();
}

// funkcija prikazuje ili sakriva UI elemente prilikom prvog loadovanja programa
void Dialog::podesiUIElemente(){
    for(int i = 0; i < 9; i++){
        prioritetCiklusa[i]->setEnabled(false);
    }
    ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
    ui->sa_pretpraznjenjem_radioButton->setChecked(false);
    ui->sa_pretpraznjenjem_label->setEnabled(false);
}
// u zavisnosti od koriscki odabranog algoritma funckija prikazuje ili sakriva UI elemente
void Dialog::on_algoritam_comboBox_currentTextChanged(const QString &odabraniAlgoritam)
{
    if(odabraniAlgoritam != "Prioritet"){
        for(int i = 0; i < 9; i++){
            prioritetCiklusa[i]->setEnabled(false);
        }
    }else{
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // omogućava klik na radio button
        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);

        for(int i = 0; i < 9; i++){
            prioritetCiklusa[i]->setEnabled(true);
        }
    }

    if (odabraniAlgoritam == "FCFS") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // ignoriše klik na radio button

        ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(false);
    }
    else if (odabraniAlgoritam == "SJF") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // omogućava klik na radio button

        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
    }
    else if (odabraniAlgoritam == "RR") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // ignoriše klik na radio button

        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(true);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
