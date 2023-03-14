#include "dialog.h"
#include "ui_dialog.h"
#include "proces.h"
#include <QDebug>
#include <algorithm>
#include <vector>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    inicijalizirajBrojProcesa();
    postaviUIElementeUNizove();
    podesiUIElemente();
    nacrtajScenu();
}

// pomocna funkcija postavlja broj procesa na vrijednost iz comboBoxa "broj_procesa" koje je korisnik odabrao
void Dialog::inicijalizirajBrojProcesa(){
    brojProcesa = ui->broj_procesa_comboBox->currentText().toInt();
}

// pomocna UI funkcija prikazuje ili sakriva UI elemente prilikom prvog loadovanja programa
void Dialog::podesiUIElemente(){
    for(int i = 0; i < 9; i++){
        prioritetProcesa[i]->setEnabled(false);
    }
    ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
    ui->sa_pretpraznjenjem_radioButton->setChecked(false);
    ui->sa_pretpraznjenjem_label->setEnabled(false);
}

// pomocna funkcija postavalja UI elemente u odgovarajuce nizove zbog lakse obrade u kodu
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

    prioritetProcesa[0] = ui->prioritet_1;
    prioritetProcesa[1] = ui->prioritet_2;
    prioritetProcesa[2] = ui->prioritet_3;
    prioritetProcesa[3] = ui->prioritet_4;
    prioritetProcesa[4] = ui->prioritet_5;
    prioritetProcesa[5] = ui->prioritet_6;
    prioritetProcesa[6] = ui->prioritet_7;
    prioritetProcesa[7] = ui->prioritet_8;
    prioritetProcesa[8] = ui->prioritet_9;

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

// UI funkcija koja crta pocetnu scenu kada se pokrene program
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

// glavna funkcija koja upravlja tokom programa
// akivira se kada korisnik klikne na dugme Nacrtaj Gantov Dijagram
void Dialog::on_nacrtajDijagramBtn_clicked()
{
    // ocisti scenu od prethodnih elemenata
    scene->clear();
    nacrtajScenu();

    // sprema korisnicki odabrani broj procesa u varijablu brojProcesa
    inicijalizirajBrojProcesa();
    // inicijaliziraj niz "procesi"
    napraviNizObjekataProces();
    // iscrtaj text za procese pored y ose
    nacrtajProcesText();
    // iscrtaj QRectItem-e za procese na odgovarajucim koordinatama
    nacrtajProces();
}

// pomocna funkcija koja inicijalizira niz koji sadrži objekte proces
void Dialog::napraviNizObjekataProces()
{
    if(ui->algoritam_comboBox->currentText() == "Prioritet"){
        for(int i = 0; i < brojProcesa; i++) {
            procesi[i].trajanje = trajanjeCiklusa[i]->value();
            procesi[i].trenutakDolaska = dolazakUCiklusu[i]->value();
            procesi[i].redniBroj = i;
            procesi[i].preostaloVrijemeIzvrsavanja = trajanjeCiklusa[i]->value();
            procesi[i].prioritet = prioritetProcesa[i]->value();  // dodatni property koji imaju procesi u prioritet algoritmu
        }
    }else{
        for(int i = 0; i < brojProcesa; i++) {
            procesi[i].trajanje = trajanjeCiklusa[i]->value();
            procesi[i].trenutakDolaska = dolazakUCiklusu[i]->value();
            procesi[i].redniBroj = i;
            procesi[i].preostaloVrijemeIzvrsavanja = trajanjeCiklusa[i]->value();
        }
    }
}

// UI funkcija koja dodaje text za odgovarajuću proces pored y ose u zavisnosti od korisnicki odredjenog broja procesa
void Dialog::nacrtajProcesText(){
    float posX = 0;
    float posY = 0;
    for(int i = 0; i < brojProcesa; i++){
        // broj 27 u formuli je izračunat na osnovu porebnog odstojanja od y-ose zbog strelica na y-osi
        posY = ((((VISINA_SCENE/brojProcesa)/2))*(i*2+1))+27;

        QGraphicsTextItem *procesText = scene->addText(procesiLabel[i]->text(),QFont("Times New Roman", 10));
        procesText->setPos(posX,posY);
        procesText->setDefaultTextColor(Qt::blue);
    }
}

// funkcija koja crta korisnicki odabrani algoritam tj. poziva fukncije koje crtaju odgovarajuce algoritme
void Dialog::nacrtajProces(){
    int odabraniProces = ui->algoritam_comboBox->currentIndex();

    switch (odabraniProces) {
    case 0:
        nacrtajFCFS();
        break;
    case 1:
        if(ui->sa_pretpraznjenjem_radioButton->isChecked()){
            pripremiSJFsaPretpaznjenjem();
        }else pripremiSJF();

        nacrtajAlgoritam();
        break;
    case 2:
        pripremiRR();
        nacrtajAlgoritam();
        break;
    case 3:
        pripremiPrioritet();
        nacrtajAlgoritam();
    default:
        break;
    }
}

// funkcija koja crta FCFS algoritam
void Dialog::nacrtajFCFS(){
    QPen okvirProcesa;
    okvirProcesa.setWidth(1);
    okvirProcesa.setColor(Qt::blue);

    QPen isprekidanaLinija;
    isprekidanaLinija.setWidth(1);
    isprekidanaLinija.setColor(Qt::blue);
    isprekidanaLinija.setStyle(Qt::DashLine);

    QBrush bojaProcesa(Qt::green);

    // kopiraj niz proces koristeci std::copy funkciju za deep copy
    Proces procesiKopija[brojProcesa];
    std::copy(procesi, procesi+brojProcesa, procesiKopija);

    sortirajProcesePoTrenutkuDolaska(procesiKopija);

    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesiKopija[i].trajanje;
    }

    float koordinataX = 0;
    float koordinataY = 0;
    float duzina = 0;
    float visina = VISINA_SCENE/brojProcesa;  // visina kvadrata koji predstavlja proces
    int dosadasnjaDuzina = 0;

    for(int i = 0; i < brojProcesa; i++){
        // 21 je potrebno odstojanje lijevog ruba scene
        koordinataX = 21 + dosadasnjaDuzina;
        // 40 je potrebno odstojanje od gornjeg ruba scene
        koordinataY = 40 + visina * procesiKopija[i].redniBroj;
        duzina = procesiKopija[i].trajanje * (DUZINA_SCENE / ukupnaDuzinaProcesa);
        dosadasnjaDuzina += procesiKopija[i].trajanje * (DUZINA_SCENE/ukupnaDuzinaProcesa);

        // kvadrat koji predstavlja proces
        QRectF proces(koordinataX,koordinataY,duzina,visina);
        // dodaj proces na scenu
        scene->addRect(proces,okvirProcesa,bojaProcesa);

        // isprekidana linija nakon kvadrata koji predstavlja proces
        if(i == brojProcesa - 1) break; // ne želimo isprekidanu liniju nakon zadnjeg procesa
        scene->addLine(koordinataX + duzina,0,koordinataX + duzina,440,isprekidanaLinija);
    }
}

// funkcija koja priprema niz procesa za SJF algoritam
void Dialog::pripremiSJF(){
    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesi[i].trajanje;
    }

    sortirajProcesePoTrenutkuDolaska(procesi);  // sortiraj prvobitni niz po trenutku dolaska procesa

    Proces procesiKopija[brojProcesa];  // niz koji se koristi za dodatno sortiranje po duzini trajanja procesa
    // kopiraj niz proces koristeci std::copy funkciju za deep copy
    std::copy(procesi, procesi+brojProcesa, procesiKopija);

    sortirajProcesePoTrajanju(procesiKopija);   // sortiraj kopirani niz po duzini trajanja procesa

    std::vector<Proces> redCekanja;
    redCekanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    for(int ciklus = pocetakCiklusa(); ciklus < ukupnaDuzinaProcesa; ciklus++){
        for(int i = 0; i < brojProcesa; i++){
            // ukoliko proces dolazi u ovom ciklusu dodaj ga u red cekanja
            if(procesiKopija[i].trenutakDolaska == ciklus){
                redCekanja.push_back(procesiKopija[i]);
            }
            // ukoliko je ovo prvi proces koji dolazi onda ga odma dodajemo u red izvrsavanja
            if(!redCekanja.empty() && redoslijedIzvrsavanja.empty()){
                redoslijedIzvrsavanja.push_back(redCekanja.front());
                redCekanja.clear();
            }
        }

        if(!redCekanja.empty()){
            redCekanja = sortirajProcesePoTrajanjuVector(redCekanja);
        }

        // ukoliko red cekanja ima procese i proces koji se trenutno izvsava ima 0 preostalog vremena tj. gotov je sa izvrsavanjem
        if((!redCekanja.empty()) && redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0){
            // ukoliko proces nije vec u redu cekanja
            if(nijeUSjfProcesi(redoslijedIzvrsavanja, redCekanja.front().redniBroj)){
                // dodaj prvi proces u redu cekanja u red izvrsavanja
                redoslijedIzvrsavanja.push_back(redCekanja.front());
            };
            // obrisi proces koji je ubacen u vektor iz reda cekanja
            redCekanja.erase(redCekanja.begin());
        }

        // na kraju ciklusa umanji vrijeme izvrsavanja procesa koji se trenutno izvrsava
        if(redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0){
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
        }
    }
}

// funkcija koja priprema niz procesa za SJF algoritam sa pretpraznjenjem
void Dialog::pripremiSJFsaPretpaznjenjem(){
    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesi[i].trajanje;
    }

    sortirajProcesePoTrenutkuDolaska(procesi);  // sortiraj prvobitni niz po trenutku dolaska procesa

    Proces procesiKopija[brojProcesa];  // niz koji se koristi za dodatno sortiranje po duzini trajanja procesa
    // kopiraj niz proces koristeci std::copy funkciju za deep copy
    std::copy(procesi, procesi+brojProcesa, procesiKopija);

    sortirajProcesePoTrajanju(procesiKopija);   // sortiraj kopirani niz po duzini trajanja procesa

    std::vector<Proces> redCekanja;
    redCekanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    for(int ciklus = pocetakCiklusa(); ciklus < ukupnaDuzinaProcesa; ciklus++){
        for(int i = 0; i < brojProcesa; i++){
            // ukoliko proces dolazi u ovom ciklusu dodaj ga u red cekanja
            if(procesiKopija[i].trenutakDolaska == ciklus){
                redCekanja.push_back(procesiKopija[i]); // dodaj proces u red cekanja
            }
        }
        // sortiraj red cekanja
        if(!redCekanja.empty()){
            redCekanja = sortirajProcesePoTrajanjuVector(redCekanja);
        }

        // ukoliko postoje procesi u redu cekanja
        if(!redCekanja.empty()){
            // ukoliko je ovo prvi proces koji dolazi dodaj ga u red izvrsavanja bez obzira na vrijeme izvrsavanja i trajanje
            if(redoslijedIzvrsavanja.empty()){
                redoslijedIzvrsavanja.push_back(redCekanja.front());
                redCekanja.clear(); // isprazni red cekanja
            }else{
                // ukoliko je trenutni proces zavrsio sa izvrsavanjem
                if(redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0){
                    sortirajProcesePoTrajanjuVector(redCekanja);    // sortiraj redCekanja tako da prvi proces ima najkrace vrijeme izrsavanja

                    redoslijedIzvrsavanja.push_back(redCekanja.front());   // pomjeri proces iz reda cekanja u sfjProcese
                    redCekanja.erase(redCekanja.begin());   // obrisi dodani proces iz reda cekanja
                }
                // ukoliko jedan od procesa u redu cekanja ima krace vrijeme izvrsavanja od trenutnog procesa
                else if(postojiKraceVrijemeIzvrsavanja(redCekanja, redoslijedIzvrsavanja.back())){
                    // ukoliko proces nije vec u redu cekanja
                    if(nijeUSjfProcesi(redoslijedIzvrsavanja, redCekanja.front().redniBroj)){
                        //  ukoliko proces koji se trenutno izvrsava nije gotov sa izvrsavanjem
                        if(redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0){
                            redCekanja.push_back(redoslijedIzvrsavanja.back());    // dodaj proces u red cekanja
                        }
                        // dodaj prvi proces u redu cekanja u red izvrsavanja
                        redoslijedIzvrsavanja.push_back(redCekanja.front());
                        // obrisi proces ubaceni proces iz reda cekanja
                        redCekanja.erase(redCekanja.begin());
                    }
                }
            }
        }
        // smanji preostalo vrijeme izvrsavanja za trenutni proces
        if(redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0){
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
        }
        redoslijedIzvrsavanja.back().burst += 1; // dodaj burst time
    }
}

// funkcija koja crta algoritme sa pretpraznjenjem
void Dialog::nacrtajAlgoritam(){
    QPen okvirProcesa;
    okvirProcesa.setWidth(1);
    okvirProcesa.setColor(Qt::blue);

    QPen isprekidanaLinija;
    isprekidanaLinija.setWidth(1);
    isprekidanaLinija.setColor(Qt::blue);
    isprekidanaLinija.setStyle(Qt::DashLine);

    QBrush bojaProcesa(Qt::green);


    float koordinataX = 0;
    float koordinataY = 0;
    float duzina = 0;
    float visina = VISINA_SCENE/brojProcesa; // visina kvadrata koji predstavlja proces
    float dosadasnjaDuzina = 0;

    // vrijednost ove varijable je zbir trajanja svih procesa
    float ukupnaDuzinaProcesa = 0;
    if(ui->sa_pretpraznjenjem_radioButton->isChecked()){ // sa pretpraznjenjem
        for(auto proces : redoslijedIzvrsavanja){
            ukupnaDuzinaProcesa += proces.burst;
        }
    }else if(!ui->sa_pretpraznjenjem_radioButton->isChecked()){  // bez pretpraznjenja
        for(auto proces : redoslijedIzvrsavanja){
            ukupnaDuzinaProcesa += proces.trajanje;
        }
    }

    for(auto proces : redoslijedIzvrsavanja){
        // 21 je potrebno odstojanje lijevog ruba scene
        koordinataX = 21 + dosadasnjaDuzina;
        // 40 je potrebno odstojanje od gornjeg ruba scene
        koordinataY = 40 + visina * proces.redniBroj;

        // kada je odabran SJF sa pretpraznjenjem
        if(ui->sa_pretpraznjenjem_radioButton->isChecked()){
            duzina = proces.burst * (DUZINA_SCENE / ukupnaDuzinaProcesa);;
        }else if(!ui->sa_pretpraznjenjem_radioButton->isChecked()){
            // kada je odabran SJF bez pretpraznjenja
            duzina = proces.trajanje * (DUZINA_SCENE / ukupnaDuzinaProcesa);
        }

        dosadasnjaDuzina += duzina;

        // kvadrat koji predstavlja proces
        QRectF procesEl(koordinataX,koordinataY,duzina,visina);
        // dodaj proces na scenu
        scene->addRect(procesEl,okvirProcesa,bojaProcesa);

        // isprekidana linija nakon kvadrata koji predstavlja proces
        if(dosadasnjaDuzina >= DUZINA_SCENE) break; // ne zelimo isprekidanu liniju nakon zadnjeg procesa
        scene->addLine(koordinataX + duzina,0,koordinataX + duzina,440,isprekidanaLinija);
    }
}

void Dialog::pripremiRR(){
    int const TIME_QUANTUM = 2;

    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesi[i].trajanje;
    }

    sortirajProcesePoTrenutkuDolaska(procesi);  // sortiraj prvobitni niz po trenutku dolaska procesa

    std::vector<Proces> redCekanja;
    std::vector<Proces> trenutniRedIzvrsavanja; // sluzi za pohranu procesa koji se trenutno izvrsava
    redCekanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    int preostaloVrijemeIzvrsavanjaSvihProcesa = 0;
    int ciklus = pocetakCiklusa();

    do {
        preostaloVrijemeIzvrsavanjaSvihProcesa = 0; // sluzi za provjeru da li su svi procesi zavrsili sa izvrsavanjem u slucaju da jesu prekida se do while petlja

        for(int i = 0; i < brojProcesa; i++){
            // ukoliko proces dolazi u ovom ciklusu
            if(procesi[i].trenutakDolaska == ciklus){
                redCekanja.insert(redCekanja.begin(),procesi[i]);  // dodaj proces u red cekanja
            }
        }

        // ukoliko je ovo prvi proces koji dolazi u red izvrsavanja
        if(redoslijedIzvrsavanja.empty()){
            trenutniRedIzvrsavanja.push_back(redCekanja.front()); // dodaj proces u trenutni red izvrsavanja
            redCekanja.clear(); // obrisi red cekanja

        // ukoliko red cekanja nije prazan i imamo procese koji su izvrseni
        }else if(!redCekanja.empty() && !redoslijedIzvrsavanja.empty()){
            trenutniRedIzvrsavanja.insert(trenutniRedIzvrsavanja.begin(),redCekanja.front()); // u trenutni red izvrsavanja ubaci prvi proces iz reda cekanja
            redCekanja.erase(redCekanja.begin());
        }

        // for petlja koja simulira izvrsavanje procesa za duzinu trajanja TIME_QUANTUMA
        for(int i = 0; i < TIME_QUANTUM; i++){

            // slucaj kada je proces u potpunosti izvrsen prije isteka TIME_QUANTUMA
            if(trenutniRedIzvrsavanja.front().preostaloVrijemeIzvrsavanja <= 0){
                // kada proces zavrsi prije time quantuma tada se uzima sljedeci proces

                i = 0;  // resetuj for petlju koja simulira izvrsavanje procesa za duzinu trajanja TIME_QUANTUMA

                redoslijedIzvrsavanja.push_back(trenutniRedIzvrsavanja.front());   // dodaj upravo izvrseni proces u redoslijedIzvrsavanja
                trenutniRedIzvrsavanja.clear(); // obrisi sve procese iz trenutnog reda izvrsavanja

                trenutniRedIzvrsavanja.insert(trenutniRedIzvrsavanja.begin(),redCekanja.front()); // dodaj prvi proces iz reda cekanja u trenutni red izvrsavanja
                redCekanja.erase(redCekanja.begin()); // izbrisi proces koji se trenutno izvrsava iz reda cekanja

                // izvrsi trenutni proces jednom
                trenutniRedIzvrsavanja.front().preostaloVrijemeIzvrsavanja -= 1;
                trenutniRedIzvrsavanja.front().burst = i+1; // upisi burst time

                // ukoliko je proces koji se trenutno izvrsava posljedji te je u potpunosti izvrsen
                if(trenutniRedIzvrsavanja.front().preostaloVrijemeIzvrsavanja == 0 && redCekanja.empty()) {
                    break;  //  prekini petlju odnosno simulaciju izvrsavanja procesa
                }
            }else{
               // izvrsi trenutni proces za vrijeme trajanja TIME_QUANTUMA tj. simuliraj izvrsavanje procesa
               trenutniRedIzvrsavanja.front().preostaloVrijemeIzvrsavanja -= 1; // umanji preostalo vrijeme izvrsavanja procesa
               trenutniRedIzvrsavanja.front().burst = i+1;  // upisi burst time
            }
        }
        if(trenutniRedIzvrsavanja.front().preostaloVrijemeIzvrsavanja > 0){
            redCekanja.push_back(trenutniRedIzvrsavanja.front()); // ukoliko proces nije u potpunosti zavrsio sa izvrsavanjem dodaj ga na kraj reda cekanja
        }

        redoslijedIzvrsavanja.push_back(trenutniRedIzvrsavanja.front()); // dodaj trenutni proces u redoslijed izvrsavanja
        trenutniRedIzvrsavanja.clear(); // ocisti trenutni red izvrsavanja

        // provjeri koliko je vremena preostalo da se procesi zavrse
        for(auto it : redCekanja){
            preostaloVrijemeIzvrsavanjaSvihProcesa += it.preostaloVrijemeIzvrsavanja;
        }

        // inkrementiraj ciklus
        ciklus++;

    } while(preostaloVrijemeIzvrsavanjaSvihProcesa > 0);
}

void Dialog::pripremiPrioritet(){
    // vrijednost ove varijable je zbir trajanja svih procesa
    int ukupnaDuzinaProcesa = 0;
    for(int i = 0; i < brojProcesa; i++){
        ukupnaDuzinaProcesa += procesi[i].trajanje;
    }

    sortirajProcesePoTrenutkuDolaska(procesi);  // sortiraj prvobitni niz po trenutku dolaska procesa

    qDebug()<<"----------------------------------------";
    for(auto it : procesi){
        qDebug()<<"Proces P"<<it.redniBroj+1;
        qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;
        qDebug()<<"proces.trajanje"<<it.trajanje;
        qDebug()<<"proces.prioritet"<<it.prioritet;
        qDebug()<<"proces.redniBroj"<<it.redniBroj;
    }
    qDebug()<<"----------------------------------------";
    std::vector<Proces> redCekanja;
    redCekanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    for(int ciklus = pocetakCiklusa(); ciklus < ukupnaDuzinaProcesa; ciklus++){
        for(int i = 0; i < brojProcesa; i++){
            if(procesi[i].trenutakDolaska == ciklus){
                //proces dolazi u ovom ciklusu dodaj ga u red cekanja
                redCekanja.insert(redCekanja.begin(), procesi[i]);
            }
        }

        // ukoliko imamo vise od jednog elementa u redu cekanja uzimamo element sa vecim prioritetom
        if(!redCekanja.empty()){
            redCekanja = sortirajProcesePoPrioritetu(redCekanja);
        }

        qDebug()<<"********************************";
        for(auto it : redCekanja){
            qDebug()<<"Proces P"<<it.redniBroj+1;
            qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;
            qDebug()<<"proces.trajanje"<<it.trajanje;
            qDebug()<<"proces.prioritet"<<it.prioritet;
            qDebug()<<"proces.redniBroj"<<it.redniBroj;
        }
        qDebug()<<"********************************";

        // ukoliko je ovo prvi proces koji dolazi
        if(redoslijedIzvrsavanja.empty()){
            redoslijedIzvrsavanja.push_back(redCekanja.front()); // dodaj ga direktno u redoslijed izvrsavanja
            redCekanja.erase(redCekanja.begin());   // obrisi taj proces iz reda cekanja
        }

        // ukoliko red cekanja ima procese i proces koji se trenutno izvsava ima 0 preostalog vremena tj. gotov je sa izvrsavanjem
        if((!redCekanja.empty()) && redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0){
            // dodaj prvi proces u redu cekanja u redoslijed izvrsavanja
            redoslijedIzvrsavanja.push_back(redCekanja.front());

            // obrisi proces iz reda cekanja
            redCekanja.erase(redCekanja.begin());
        }

        // na kraju ciklusa umanji vrijeme izvrsavanja procesa koji se trenutno izvrsava
        if(redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0){
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
        }
    }
        qDebug()<<"********************************";
        for(auto it : redoslijedIzvrsavanja){
            qDebug()<<"Proces P"<<it.redniBroj+1;
            qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;
            qDebug()<<"proces.trajanje"<<it.trajanje;
            qDebug()<<"proces.prioritet"<<it.prioritet;
            qDebug()<<"proces.redniBroj"<<it.redniBroj;
        }
        qDebug()<<"********************************";
}
// pomocna funkcija koja sortira procese po prioritetu gdje manji broj oznacava veci prioritet
std::vector<Proces> Dialog::sortirajProcesePoPrioritetu(std::vector<Proces> vector){
    std::sort(vector.begin(), vector.end(), [](const Proces& prethodnik, const Proces& sljedbenik) {
        return prethodnik.prioritet < sljedbenik.prioritet;
    });
    return vector;
}

// pomocna funkcija koja provjerava da li jedan od procesa u redu cekanja ima krace vrijeme izvrsavanja od trenutnog procesa
bool Dialog::postojiKraceVrijemeIzvrsavanja(std::vector<Proces> redCekanja, Proces trenutniProces){
    for(auto proces : redCekanja){
        if(proces.trajanje < trenutniProces.preostaloVrijemeIzvrsavanja && proces.preostaloVrijemeIzvrsavanja > 0) return true;
    }
    return false;
}

// pomocna funkcija koja provjerava da li je proces vec dodan u vektor
bool Dialog::nijeUSjfProcesi(std::vector<Proces> procesi, int redniBroj){
    for(auto proces : procesi){
        if(proces.redniBroj == redniBroj){
            return false;
        }
    }
    return true;
}


// pomocna funkcija vraca vrijednost koja predstavlja kada ciklusi pocinju
int Dialog::pocetakCiklusa(){
    int pocetakCiklusa = procesi[0].trenutakDolaska;
    for(int i = 0; i < brojProcesa; i++){
        if(procesi[i].trenutakDolaska < pocetakCiklusa){
            pocetakCiklusa = procesi[i].trenutakDolaska;
        }
    }
    return pocetakCiklusa;
}

// pomocna funkcija sortira niz po redoslijedu dolaska od elementa koji je dosao prvi do elementa koji je dosao posljednji
void Dialog::sortirajProcesePoTrenutkuDolaska(Proces *niz){
    for(int i = 0; i < brojProcesa; i++){
        for(int j = i + 1; j < brojProcesa; j++){
            if(niz[j].trenutakDolaska < niz[i].trenutakDolaska){
                Proces temp = niz[i];
                niz[i] = niz[j];
                niz[j] = temp;
            }
        }
    }
}

// pomocna funkcija sortira niz po trajanju od najkraceg do najduzeg
void Dialog::sortirajProcesePoTrajanju(Proces *niz){
    for(int i = 0; i < brojProcesa; i++){
        for(int j = i + 1; j < brojProcesa; j++){
            if(niz[j].trajanje < niz[i].trajanje){
                Proces temp = niz[i];
                niz[i] = niz[j];
                niz[j] = temp;
            }
        }
    }
}

// pomocna funkcija koja sortira elemente vektora po trajanju od najkraceg do najduzeg
std::vector<Proces> Dialog::sortirajProcesePoTrajanjuVector(std::vector<Proces> vector){
    std::sort(vector.begin(), vector.end(), [](const Proces& prethodnik, const Proces& sljedbenik) {
        return prethodnik.trajanje < sljedbenik.trajanje;
    });
    return vector;
}

// UI funkcija koja u zavisnosti od koriscki odabranog broja procesa prikazuje ili sakriva UI elemente
void Dialog::on_broj_procesa_comboBox_currentIndexChanged(const QString &odabraniBrojProcesa)
{
    brojProcesa = odabraniBrojProcesa.toInt();

    for(int i = 0; i < 9; i++){
        if(i < brojProcesa){
            dolazakUCiklusu[i]->setVisible(true);
            trajanjeCiklusa[i]->setVisible(true);
            prioritetProcesa[i]->setVisible(true);
            procesiLabel[i]->setVisible(true);
        }else{
            dolazakUCiklusu[i]->setVisible(false);
            trajanjeCiklusa[i]->setVisible(false);
            prioritetProcesa[i]->setVisible(false);
            procesiLabel[i]->setVisible(false);
        }
    }
}

// UI funkcija koja u zavisnosti od koriscki odabranog algoritma prikazuje ili sakriva UI elemente
void Dialog::on_algoritam_comboBox_currentTextChanged(const QString &odabraniAlgoritam)
{
    if(odabraniAlgoritam != "Prioritet"){
        for(int i = 0; i < 9; i++){
            prioritetProcesa[i]->setEnabled(false);
            ui->prioritet_label->setEnabled(false);
        }
    }else{
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // omogućava klik na radio button
        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);

        for(int i = 0; i < 9; i++){
            prioritetProcesa[i]->setEnabled(true);
        }
        ui->prioritet_label->setEnabled(true);
    }

    if (odabraniAlgoritam == "FCFS") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // ignoriše klik na radio button

        ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(false);
    }
    else if (odabraniAlgoritam == "SJF") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);

        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
    }
    else if (odabraniAlgoritam == "RR") {
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(true);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
