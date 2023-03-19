#include "dialog.h"
#include "ui_dialog.h"
#include "proces.h"
#include <QDebug>
#include <algorithm>
#include <vector>
#include <string>

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog)
{
    ui->setupUi(this);

    inicijalizirajBrojProcesa();
    postaviUIElementeUNizove();
    podesiUIElemente();
    nacrtajScenu();
}

// pomocna funkcija postavlja broj procesa na vrijednost iz comboBoxa "broj_procesa" koje je korisnik odabrao
void Dialog::inicijalizirajBrojProcesa()
{
    brojProcesa = ui->broj_procesa_comboBox->currentText().toInt();
}

// pomocna UI funkcija prikazuje ili sakriva UI elemente prilikom prvog loadovanja programa
void Dialog::podesiUIElemente()
{
    for (int i = 0; i < 9; i++)
    {
        prioritetProcesa[i]->setEnabled(false);
    }
    ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
    ui->sa_pretpraznjenjem_radioButton->setChecked(false);
    ui->sa_pretpraznjenjem_label->setEnabled(false);
}

// pomocna funkcija postavalja UI elemente u odgovarajuce nizove zbog lakse obrade u kodu
void Dialog::postaviUIElementeUNizove()
{
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
void Dialog::nacrtajScenu()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    scene->setSceneRect(0, 0, 750, 450);

    QPen koordinatneOsePen;
    koordinatneOsePen.setColor(Qt::blue);
    koordinatneOsePen.setWidth(2);

    // y-osa
    scene->addLine(20, 0, 20, 460, koordinatneOsePen);
    scene->addLine(10, 20, 20, 0, koordinatneOsePen); // strelica lijeva
    scene->addLine(20, 0, 30, 20, koordinatneOsePen); // strelica desna

    // x-osa
    scene->addLine(0, 440, 780, 440, koordinatneOsePen);
    scene->addLine(760, 430, 780, 440, koordinatneOsePen); // strelica gornja
    scene->addLine(760, 450, 780, 440, koordinatneOsePen); // strelica donja

    // text na y-osi
    QGraphicsTextItem *textProcesi = scene->addText(QString("Procesi"), QFont("Times New Roman", 14));
    textProcesi->setPos(35, -1);
    textProcesi->setDefaultTextColor(Qt::blue);

    // text na x-osi
    QGraphicsTextItem *textBrojCiklusa = scene->addText(QString("Broj Ciklusa"), QFont("Times New Roman", 14));
    textBrojCiklusa->setPos(650, 438);
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
    nacrtajProceseZaOdabraniAlgoritam();
}

// pomocna funkcija koja inicijalizira niz koji sadrži objekte proces
void Dialog::napraviNizObjekataProces()
{
    for (int i = 0; i < brojProcesa; i++)
    {
        procesi[i].trajanje = trajanjeCiklusa[i]->value();
        procesi[i].trenutakDolaska = dolazakUCiklusu[i]->value();
        procesi[i].redniBroj = i;
        procesi[i].preostaloVrijemeIzvrsavanja = trajanjeCiklusa[i]->value();

        if (ui->algoritam_comboBox->currentText() == "Prioritet")
        {
            procesi[i].prioritet = prioritetProcesa[i]->value();
        }
    }
}

// UI funkcija koja dodaje text za odgovarajuću proces pored y ose u zavisnosti od korisnicki odredjenog broja procesa
void Dialog::nacrtajProcesText()
{
    float posX = 0;
    float posY = 0;
    for (int i = 0; i < brojProcesa; i++)
    {
        // broj 27 u formuli je izračunat na osnovu porebnog odstojanja od y-ose zbog strelica na y-osi
        posY = ((((VISINA_SCENE / brojProcesa) / 2)) * (i * 2 + 1)) + 27;

        QGraphicsTextItem *procesText = scene->addText(procesiLabel[i]->text(), QFont("Times New Roman", 10));
        procesText->setPos(posX, posY);
        procesText->setDefaultTextColor(Qt::blue);
    }
}

// funkcija koja crta korisnicki odabrani algoritam tj. poziva fukncije koje crtaju odgovarajuce algoritme
void Dialog::nacrtajProceseZaOdabraniAlgoritam()
{
    int odabraniAlgoritam = ui->algoritam_comboBox->currentIndex();

    switch (odabraniAlgoritam)
    {
    case 0: // FCFS algoritam
        pripremiFCFS();
        nacrtajAlgoritam();
        break;

    case 1: // SJF algoritam
        if (ui->sa_pretpraznjenjem_radioButton->isChecked())
        {
            pripremiSJFsaPretpaznjenjem();
        }
        else
        {
            pripremiSJF();
        }

        nacrtajAlgoritam();
        break;

    case 2: // Round Robin algoritam
        pripremiRR();
        nacrtajAlgoritam();
        break;

    case 3: // Prioritet algoritam
        if (ui->sa_pretpraznjenjem_radioButton->isChecked())
        {
            pripremiPrioritetSaPretpraznjenjem();
        }
        else
        {
            pripremiPrioritet();
        }

        nacrtajAlgoritam();
        break;
    default:
        break;
    }
}

// funkcija koja priprema redoslijed procesa za crtanje FCFS algoritma
void Dialog::pripremiFCFS()
{
    // procese sortiramo po njihovom trenutku dolaska
    sortirajProcesePoTrenutkuDolaska(procesi);

    std::vector<Proces> redCekanja;
    // ukoliko korisnik pokrece isti algoritam vise puta
    redCekanja.clear();
    redoslijedIzvrsavanja.clear();

    for (int ciklus = pocetakCiklusa(); ciklus < ukupnoTrajanjeProcesa(); ciklus++)
    {
        // ubaci procese koji dolaze u ovom ciklusu u red cekanja
        for (int i = 0; i < brojProcesa; i++)
        {
            if (procesi[i].trenutakDolaska == ciklus)
            {
                redCekanja.insert(redCekanja.begin(), procesi[i]);
            }
        }

        if (!redCekanja.empty())
        {
            // procese sortiramo po njihovom trenutku dolaska
            sortirajProcesePoTrenutkuDolaska(redCekanja);
            // ukoliko dva procesa dolaze u istom ciklusu uzima se onaj koji ima manji redni broj
            dodatnoSortirajPoRednomBroju("Trenutak Dolaska",redCekanja);

            // dodaj prvi proces iz reda cekanja u redoslijed izrsavanja
            redoslijedIzvrsavanja.push_back(redCekanja.front());
            redCekanja.erase(redCekanja.begin());
        }
    }
}

// funkcija koja priprema redoslijed procesa za crtanje SJF algoritma
void Dialog::pripremiSJF()
{
    sortirajProcesePoTrenutkuDolaska(procesi); // sortiraj procese po trenutku dolaska

    Proces sortiraniProcesi[brojProcesa];
    // kopiraj niz proces koristeci std::copy funkciju za deep copy
    std::copy(procesi, procesi + brojProcesa, sortiraniProcesi);

    sortirajProcesePoTrajanju(sortiraniProcesi); // sortiraj procese po duzini trajanja

    std::vector<Proces> redCekanja;
    // u slucaju da korisnik pokrece isti algoritam drugi put
    redCekanja.clear();
    redoslijedIzvrsavanja.clear();

    for (int ciklus = pocetakCiklusa(); ciklus <= ukupnoTrajanjeProcesa(); ciklus++)
    {
        // ubaci procese koji dolaze u ovom ciklusu u red cekanja
        for (const auto proces : sortiraniProcesi)
        {
            if (proces.trenutakDolaska == ciklus)
            {
                redCekanja.push_back(proces);
            }
        }

        // sortiraj red čekanja po dužini trajanja procesa
        if (redCekanja.size() > 1)
        {
            sortirajProcesePoTrajanju(redCekanja);
            dodatnoSortirajPoRednomBroju("Preostalo Vrijeme", redCekanja);
        }

        // ako je red izvršavanja prazan, dodaj prvi proces iz reda čekanja
        if (redoslijedIzvrsavanja.empty())
        {
            redoslijedIzvrsavanja.push_back(redCekanja.front());
            redCekanja.erase(redCekanja.begin()); // obrisi proces iz reda cekanja
        }

        // ukoliko je proces izvrsen u potpunosti
        if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0 && !redCekanja.empty())
        {
            // dodaj prvi proces iz reda cekanja u red izvrsavanja
            redoslijedIzvrsavanja.push_back(redCekanja.front());

            // obrisi proces koji je ubacen u red izvrsavanja iz reda cekanja
            redCekanja.erase(redCekanja.begin());
        }

        // na kraju ciklusa umanji vrijeme izvrsavanja procesa koji se trenutno izvrsava
        if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
        {
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
        }
    }
}

// funkcija koja priprema redoslijed procesa za crtanje SJF algoritama sa pretpraznjenjem
void Dialog::pripremiSJFsaPretpaznjenjem()
{
    sortirajProcesePoTrenutkuDolaska(procesi); // sortiraj prvobitni niz po trenutku dolaska procesa

    Proces procesiKopija[brojProcesa]; // niz koji se koristi za dodatno sortiranje po duzini trajanja procesa
    // kopiraj niz proces koristeci std::copy funkciju za deep copy
    std::copy(procesi, procesi + brojProcesa, procesiKopija);

    sortirajProcesePoTrajanju(procesiKopija); // sortiraj kopirani niz po duzini trajanja procesa

    std::vector<Proces> redCekanja;
    redCekanja.clear();            // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    for (int ciklus = pocetakCiklusa(); ciklus < ukupnoTrajanjeProcesa(); ciklus++)
    {
        // ubaci procese koji dolaze u ovom ciklusu u red cekanja
        for (const auto proces : procesiKopija)
        {
            if (proces.trenutakDolaska == ciklus)
            {
                redCekanja.push_back(proces);
            }
        }

        // ukoliko je vise procesa u redu cekanja sortiraj red cekanja po trajanju procesa
        if (redCekanja.size() > 1)
        {
            sortirajProcesePoTrajanju(redCekanja);
            dodatnoSortirajPoRednomBroju("Preostalo Vrijeme",redCekanja);
        }

        // ukoliko je ovo prvi i jedini proces koji dolazi onda ga odma dodajemo u red izvrsavanja
        if (redoslijedIzvrsavanja.empty())
        {
            redoslijedIzvrsavanja.push_back(redCekanja.front());
            redCekanja.erase(redCekanja.begin()); // obrisi proces iz reda cekanja
        }

        // ukoliko postoje procesi u redu cekanja i postoje procesi u redoslijeduIzrsavanja
        else if (!redCekanja.empty())
        {
            // ukoliko je trenutni proces zavrsio sa izvrsavanjem
            if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0)
            {
                redoslijedIzvrsavanja.push_back(redCekanja.front()); // pomjeri proces iz reda cekanja u red izvrsavanja
                redCekanja.erase(redCekanja.begin());                // obrisi dodani proces iz reda cekanja
            }
            // ukoliko jedan od procesa u redu cekanja ima krace vrijeme izvrsavanja od trenutnog procesa
            else if (imaKraceVrijemeIzvrsavanja(redCekanja, redoslijedIzvrsavanja.back()))
            {
                //  ukoliko proces koji se trenutno izvrsava nije gotov sa izvrsavanjem
                if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
                {
                    redCekanja.push_back(redoslijedIzvrsavanja.back()); // dodaj proces u red cekanja
                    redCekanja.back().burst = 0;                        // resetuj burst time za proces koji je upravo dodan u red cekanja
                }

                // dodaj prvi proces u redu cekanja u red izvrsavanja
                redoslijedIzvrsavanja.push_back(redCekanja.front());
                // obrisi proces ubaceni proces iz reda cekanja
                redCekanja.erase(redCekanja.begin());
            }
        }

        // smanji preostalo vrijeme izvrsavanja za trenutni proces
        if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
        {
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
            redoslijedIzvrsavanja.back().burst += 1; // dodaj burst time
        }
    }
}

// funkcija koja priprema redoslijed procesa za crtanje Round Robin algoritma
void Dialog::pripremiRR()
{
    int const TIME_QUANTUM = 2;

    sortirajProcesePoTrenutkuDolaska(procesi); // sortiraj prvobitni niz po trenutku dolaska procesa

    std::vector<Proces> redCekanja;
    std::vector<Proces> trenutniRedIzvrsavanja; // sluzi za pohranu procesa koji se trenutno izvrsava
    redCekanja.clear();                         // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear();              // u slucaju da korisnik pokrece isti algoritam drugi put



    int preostaloVrijemeIzvrsavanjaSvihProcesa = 0;
    int ciklus = pocetakCiklusa();

    do
    {
        preostaloVrijemeIzvrsavanjaSvihProcesa = 0; // sluzi za provjeru da li su svi procesi zavrsili sa izvrsavanjem u slucaju da jesu prekida se do while petlja

        qDebug()<<"ciklus "<<ciklus;
        for (int i = 0; i < brojProcesa; i++)
        {
            // ukoliko proces dolazi u ovom ciklusu
            if (procesi[i].trenutakDolaska == ciklus)
            {
                //                redCekanja.insert(redCekanja.begin(), procesi[i]);
                redCekanja.push_back(procesi[i]); // dodaj proces u red cekanja
            }
        }

        // ukoliko u trenutnom redu izvrsavanja nema procesa
        if (trenutniRedIzvrsavanja.empty())
        {
            // dodaj prvi proces iz reda cekanja u trenutni red izvrsavanja
            trenutniRedIzvrsavanja.push_back(redCekanja.front()); // dodaj proces u trenutni red izvrsavanja
            redCekanja.erase(redCekanja.begin()); // obrisi proces iz reda cekanja


        }
        qDebug()<<"----------trenutniRedIzvrsavanja-------------";
        for(auto it : trenutniRedIzvrsavanja)
        {

            qDebug()<<"Proces P"<<it.redniBroj+1;
            qDebug()<<"proces.burst"<<it.burst;
            qDebug()<<"proces.preostaloVrijemeIzvrsavanja"<<it.preostaloVrijemeIzvrsavanja;
            qDebug()<<"proces.prioritet"<<it.prioritet;
            qDebug()<<"proces.trajanje"<<it.trajanje;
            qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;

        }
        qDebug()<<"\n----------trenutniRedIzvrsavanja--------";

        // provjeri koliko je vremena preostalo da se procesi zavrse
        for (auto it : redCekanja)
        {
            preostaloVrijemeIzvrsavanjaSvihProcesa += it.preostaloVrijemeIzvrsavanja;
        }
        for (auto it : trenutniRedIzvrsavanja)
        {
            preostaloVrijemeIzvrsavanjaSvihProcesa += it.preostaloVrijemeIzvrsavanja;
        }


        // na kraju ciklusa umanji vrijeme izvrsavanja procesa koji se trenutno izvrsava
        if (trenutniRedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0)
        {
            redoslijedIzvrsavanja.push_back(trenutniRedIzvrsavanja.back());
            trenutniRedIzvrsavanja.clear(); // ocisti trenutni red izvrsavanja
        }
        else if (trenutniRedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0 && trenutniRedIzvrsavanja.back().burst == TIME_QUANTUM)
        {
            redoslijedIzvrsavanja.push_back(trenutniRedIzvrsavanja.back()); // dodaj proces u redoslijed izvrsavanja

            trenutniRedIzvrsavanja.back().burst = 0;
            redCekanja.push_back(trenutniRedIzvrsavanja.back()); // dodaj proces ponovo u red cekanja

            trenutniRedIzvrsavanja.clear(); // ocisti trenutni red izvrsavanja
        }
        else if (trenutniRedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0 && trenutniRedIzvrsavanja.back().burst != TIME_QUANTUM)
        {
            trenutniRedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
            trenutniRedIzvrsavanja.back().burst += 1;
        }
        qDebug()<<"========red=cekanja======\n";
        for(auto it : redCekanja)
        {

            qDebug()<<"Proces P"<<it.redniBroj+1;
            qDebug()<<"proces.burst"<<it.burst;
            qDebug()<<"proces.preostaloVrijemeIzvrsavanja"<<it.preostaloVrijemeIzvrsavanja;
            qDebug()<<"proces.prioritet"<<it.prioritet;
            qDebug()<<"proces.trajanje"<<it.trajanje;
            qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;


        }
        qDebug()<<"\n========red=cekanja======";
        qDebug()<<"\n";
        qDebug()<<"========redoslijedIzvrsavanja======\n";
        for(auto it : redoslijedIzvrsavanja)
        {

            qDebug()<<"Proces P"<<it.redniBroj+1;
            qDebug()<<"proces.burst"<<it.burst;
            qDebug()<<"proces.preostaloVrijemeIzvrsavanja"<<it.preostaloVrijemeIzvrsavanja;
            qDebug()<<"proces.prioritet"<<it.prioritet;
            qDebug()<<"proces.trajanje"<<it.trajanje;
            qDebug()<<"proces.trenutakDolaska"<<it.trenutakDolaska;


        }
        qDebug()<<"\n========redoslijedIzvrsavanja======";


        // inkrementiraj ciklus
        ciklus++;

    } while (preostaloVrijemeIzvrsavanjaSvihProcesa > 0);
    qDebug()<<"\n\n";
}

// funkcija koja priprema redoslijed procesa za crtanje Prioritet algoritma
void Dialog::pripremiPrioritet()
{
    sortirajProcesePoTrenutkuDolaska(procesi); // sortiraj prvobitni niz po trenutku dolaska procesa

    std::vector<Proces> redCekanja;
    redCekanja.clear();            // u slucaju da korisnik pokrece isti algoritam drugi put
    redoslijedIzvrsavanja.clear(); // u slucaju da korisnik pokrece isti algoritam drugi put

    for (int ciklus = pocetakCiklusa(); ciklus <= ukupnoTrajanjeProcesa(); ciklus++)
    {
        // proces dolazi u ovom ciklusu dodaj ga u red cekanja
        for (int i = 0; i < brojProcesa; i++)
        {
            if (procesi[i].trenutakDolaska == ciklus)
            {
                redCekanja.insert(redCekanja.begin(), procesi[i]);
            }
        }

        // ukoliko imamo vise od jednog elementa u redu cekanja uzimamo element sa vecim prioritetom
        if (!redCekanja.empty())
        {
            sortirajProcesePoPrioritetu(redCekanja);
            // ukoliko dva procesa imaju isti prioritet i vrijeme dolaska
            dodatnoSortirajPoRednomBroju("Prioritet",redCekanja);
        }

        // ukoliko je ovo prvi proces koji dolazi
        if (redoslijedIzvrsavanja.empty())
        {
            redoslijedIzvrsavanja.push_back(redCekanja.front()); // dodaj ga direktno u redoslijed izvrsavanja
            redCekanja.erase(redCekanja.begin());                // obrisi taj proces iz reda cekanja
        }

        // ukoliko red cekanja ima procese i proces koji se trenutno izvrsava je gotov sa izvrsavanjem
        if ((!redCekanja.empty()) && redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0)
        {
            // dodaj prvi proces u redu cekanja u redoslijed izvrsavanja
            redoslijedIzvrsavanja.push_back(redCekanja.front());

            // obrisi proces iz reda cekanja
            redCekanja.erase(redCekanja.begin());
        }

        // na kraju ciklusa umanji vrijeme izvrsavanja procesa koji se trenutno izvrsava
        if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
        {
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
        }
    }
}

void Dialog::pripremiPrioritetSaPretpraznjenjem()
{
    sortirajProcesePoTrenutkuDolaska(procesi); // sortiraj prvobitni niz po trenutku dolaska procesa

    std::vector<Proces> redCekanja;
    std::vector<Proces> trenutniRedIzvrsavanja;

    // u slucaju da korisnik pokrece isti algoritam drugi put
    redCekanja.clear();
    trenutniRedIzvrsavanja.clear();
    redoslijedIzvrsavanja.clear();

    for (int ciklus = pocetakCiklusa(); ciklus <= ukupnoTrajanjeProcesa(); ciklus++)
    {
        for (int i = 0; i < brojProcesa; i++)
        {
            // ukoliko proces dolazi u ovom ciklusu dodaj ga u red cekanja
            if (procesi[i].trenutakDolaska == ciklus)
            {
                redCekanja.push_back(procesi[i]); // dodaj proces u red cekanja
            }
        }

        // ukoliko je vise procesa u redu cekanja sortiraj red cekanja po trajanju procesa
        if (redCekanja.capacity() > 1)
        {
            sortirajProcesePoPrioritetu(redCekanja);
            // ukoliko dva procesa imaju isti prioritet i vrijeme dolaska
        }

        // ukoliko je ovo prvi i jedini proces koji dolazi onda ga odma dodajemo u red izvrsavanja
        if (redoslijedIzvrsavanja.empty())
        {
            redoslijedIzvrsavanja.push_back(redCekanja.front());
            redCekanja.erase(redCekanja.begin()); // obrisi proces iz reda cekanja
        }

        // ukoliko postoje procesi u redu cekanja i postoje procesi u redoslijeduIzrsavanja
        else if (!redCekanja.empty() && !redoslijedIzvrsavanja.empty())
        {
            // ukoliko je trenutni proces zavrsio sa izvrsavanjem
            if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja <= 0)
            {
                redoslijedIzvrsavanja.push_back(redCekanja.front()); // pomjeri proces iz reda cekanja u red izvrsavanja
                redCekanja.erase(redCekanja.begin());                // obrisi dodani proces iz reda cekanja
            }

            // ukoliko jedan od procesa u redu cekanja ima krace vrijeme izvrsavanja od trenutnog procesa
            else if (imaVeciPrioritet(redCekanja, redoslijedIzvrsavanja.back()))
            {
                //  ukoliko proces koji se trenutno izvrsava nije gotov sa izvrsavanjem
                if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
                {
                    redCekanja.push_back(redoslijedIzvrsavanja.back()); // dodaj proces u red cekanja
                    redCekanja.back().burst = 0;                        // resetuj burst time za proces koji je upravo dodan u red cekanja
                }

                // dodaj prvi proces u redu cekanja u red izvrsavanja
                redoslijedIzvrsavanja.push_back(redCekanja.front());
                // obrisi proces ubaceni proces iz reda cekanja
                redCekanja.erase(redCekanja.begin());
            }
        }

        // smanji preostalo vrijeme izvrsavanja za trenutni proces
        if (redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja > 0)
        {
            redoslijedIzvrsavanja.back().preostaloVrijemeIzvrsavanja -= 1;
            redoslijedIzvrsavanja.back().burst += 1; // dodaj burst time
        }
    }
}

// funkcija koja crta algoritme
void Dialog::nacrtajAlgoritam()
{
    // pen i brush za crtanje procesa
    QPen okvirProcesa(Qt::blue, 1);
    QPen isprekidanaLinija(Qt::blue, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush bojaProcesa(Qt::green);

    // da li se radi o algoritmu sa pretpraznjenjem ili ne
    bool saPretpraznjenjem = ui->sa_pretpraznjenjem_radioButton->isChecked();

    // izracunaj ukupno trajanje procesa
    float ukupnoTrajanjeProcesa = 0;
    for (auto proces : redoslijedIzvrsavanja)
    {
        ukupnoTrajanjeProcesa += saPretpraznjenjem ? proces.burst : proces.trajanje;
    }

    // potrebne varijable za crtanje kvadrata koji predstavlja proces
    float koordinataX = 21; // 21 je potrebno odstojanje lijevog ruba scene
    float koordinataY = 40; // 40 je potrebno odstojanje od gornjeg ruba scene
    float duzina = 0;
    float visina = VISINA_SCENE / brojProcesa; // visina kvadrata koji predstavlja proces

    for (auto proces : redoslijedIzvrsavanja)
    {
        koordinataY += visina * proces.redniBroj;

        // Izračunaj dužinu procesa u pikselima
        duzina = (saPretpraznjenjem ? proces.burst : proces.trajanje) * (DUZINA_SCENE / ukupnoTrajanjeProcesa);

        // kvadrat koji predstavlja proces
        QRectF procesEl(koordinataX, koordinataY, duzina, visina);
        // dodaj proces na scenu
        scene->addRect(procesEl, okvirProcesa, bojaProcesa);

        // dodaj isprekidanu liniju nakon kvadrata koji predstavlja proces, osim za zadnji proces
        if (koordinataX + duzina <= DUZINA_SCENE)
        {
            scene->addLine(koordinataX + duzina, 0, koordinataX + duzina, 440, isprekidanaLinija);
        }

        // pomjeri koordinatu X za sljedeci proces
        koordinataX += duzina;
        // resetuj koordinatu Y
        koordinataY = 40;
    }
}

// pomocna funkcija koja vraća ukupno trajanje procesa
int Dialog::ukupnoTrajanjeProcesa()
{
    int ukupnoTrajanje = 0;
    for (int i = 0; i < brojProcesa; i++)
    {
        ukupnoTrajanje += procesi[i].trajanje;
    }
    return ukupnoTrajanje;
}

// pomocna funkcija koja provjerava da li jedan od procesa u redu cekanja ima krace vrijeme izvrsavanja od trenutnog procesa
bool Dialog::imaKraceVrijemeIzvrsavanja(std::vector<Proces> &redCekanja, const Proces &trenutniProces)
{
    for (auto proces : redCekanja)
    {
        if (proces.preostaloVrijemeIzvrsavanja > 0 && proces.trajanje < trenutniProces.preostaloVrijemeIzvrsavanja)
        {
            return true;
        }
    }
    return false;
}

// pomocna funkcija koja provjerava da li jedan od procesa u redu cekanja ima veci prioritet od trenutnog procesa
bool Dialog::imaVeciPrioritet(std::vector<Proces> &redCekanja, const Proces &trenutniProces)
{
    for (const auto proces : redCekanja)
    {
        if (proces.prioritet < trenutniProces.prioritet && proces.preostaloVrijemeIzvrsavanja > 0)
            return true;
    }
    return false;
}

// pomocna funkcija koja vraca jedinicu vremena kada pocinju ciklusi
int Dialog::pocetakCiklusa()
{
    int pocetakCiklusa = procesi[0].trenutakDolaska;
    for (int i = 0; i < brojProcesa; i++)
    {
        if (procesi[i].trenutakDolaska < pocetakCiklusa)
        {
            pocetakCiklusa = procesi[i].trenutakDolaska;
        }
    }
    return pocetakCiklusa;
}

// pomocna funkcija koja sortira procese po prioritetu gdje manji broj oznacava veci prioritet
void Dialog::sortirajProcesePoPrioritetu(std::vector<Proces> &vector)
{
    std::sort(vector.begin(), vector.end(), [](const Proces &prethodnik, const Proces &sljedbenik)
              { return prethodnik.prioritet < sljedbenik.prioritet; });
}

// pomocna funkcija koja sortira procese po rednom broju od manjeg ka vecem
void Dialog::sortirajProcesePoRednomBroju(std::vector<Proces> &vector)
{
    std::sort(vector.begin(), vector.end(), [](const Proces &prethodnik, const Proces &sljedbenik)
              { return prethodnik.redniBroj < sljedbenik.redniBroj; });
}

// pomocna funkcija koja sortira niz po redoslijedu dolaska od elementa koji je dosao prvi do elementa koji je dosao posljednji
void Dialog::sortirajProcesePoTrenutkuDolaska(Proces *niz)
{
    std::sort(niz, niz + brojProcesa, [](const Proces &prethodnih, const Proces &sljedbenik)
              { return prethodnih.trenutakDolaska < sljedbenik.trenutakDolaska; });
}

// pomocna funkcija koja sortira vector po redoslijedu dolaska od elementa koji je dosao prvi do elementa koji je dosao posljednji
void Dialog::sortirajProcesePoTrenutkuDolaska(std::vector<Proces> &vector)
{
    std::sort(vector.begin(), vector.end(), [](const Proces &prethodnik, const Proces &sljedbenik)
              { return prethodnik.trenutakDolaska < sljedbenik.trenutakDolaska; });
}

// pomocna funkcija koja sortira niz po trajanju od najkraceg do najduzeg
void Dialog::sortirajProcesePoTrajanju(Proces *niz)
{
    std::sort(niz, niz + brojProcesa, [](const Proces &prethodnih, const Proces &sljedbenik)
              { return prethodnih.trajanje < sljedbenik.trajanje; });
}

// pomocna funkcija koja sortira vektor po trajanju od najkraceg do najduzeg
void Dialog::sortirajProcesePoTrajanju(std::vector<Proces> &vector)
{
    std::sort(vector.begin(), vector.end(), [](const Proces &prethodnik, const Proces &sljedbenik)
              { return prethodnik.trajanje < sljedbenik.trajanje; });
}

// pomocna funkcija koja se koristi za dodatno sortiranje ukoliko procesi u redu cekanja imaju isti prioritet, trenutak dolaska ili preostalo vrijeme
void Dialog::dodatnoSortirajPoRednomBroju(std::string tipSortiranja, std::vector<Proces> &redCekanja)
{
    for (unsigned int i = 0; i < redCekanja.size() - 1; i++)
    {
        for (unsigned int j = i + 1; j < redCekanja.size(); j++)
        {
            if (tipSortiranja == "Prioritet" && redCekanja[i].prioritet == redCekanja[j].prioritet && redCekanja[j].redniBroj < redCekanja[i].redniBroj)
            {
                std::swap(redCekanja[i], redCekanja[j]);
            }
            else if (tipSortiranja == "Trenutak Dolaska" && redCekanja[i].trenutakDolaska == redCekanja[j].trenutakDolaska && redCekanja[j].redniBroj < redCekanja[i].redniBroj)
            {
                std::swap(redCekanja[i], redCekanja[j]);
            }
            else if (tipSortiranja == "Preostalo Vrijeme" && redCekanja[i].preostaloVrijemeIzvrsavanja == redCekanja[j].preostaloVrijemeIzvrsavanja && redCekanja[j].redniBroj < redCekanja[i].redniBroj)
            {
                std::swap(redCekanja[i], redCekanja[j]);
            }
        }
    }
}

// UI funkcija koja u zavisnosti od koriscki odabranog broja procesa prikazuje ili sakriva UI elemente
void Dialog::on_broj_procesa_comboBox_currentIndexChanged(const QString &odabraniBrojProcesa)
{
    brojProcesa = odabraniBrojProcesa.toInt();

    for (int i = 0; i < 9; i++)
    {
        const bool visible = i < brojProcesa;
        dolazakUCiklusu[i]->setVisible(visible);
        trajanjeCiklusa[i]->setVisible(visible);
        prioritetProcesa[i]->setVisible(visible);
        procesiLabel[i]->setVisible(visible);
    }
}

// UI funkcija koja u zavisnosti od koriscki odabranog algoritma prikazuje ili sakriva UI elemente
void Dialog::on_algoritam_comboBox_currentIndexChanged(int odabraniAlgoritam)
{
    switch (odabraniAlgoritam)
    {
    case 0:
        // FCFS
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true); // ignoriše klik na radio button
        ui->sa_pretpraznjenjem_radioButton->setEnabled(false);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(false);
        break;

    case 1:
        // SJF
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false); // omogućava klik na radio button
        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
        break;

    case 2:
        // Round Robin
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(true);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
        break;

    case 3:
        // Prioritet
        ui->sa_pretpraznjenjem_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        ui->sa_pretpraznjenjem_radioButton->setEnabled(true);
        ui->sa_pretpraznjenjem_radioButton->setChecked(false);
        ui->sa_pretpraznjenjem_label->setEnabled(true);
        break;

    default:
        break;
    }

    // ako je odabrani algoritam prioritet
    bool prioritetEnabled = (odabraniAlgoritam == 3);
    // prikazi ili sakrij prioritet_label u zavisnosti od prioritetEnabled varijable
    ui->prioritet_label->setEnabled(prioritetEnabled);
    // u zavisnosti od prioritetEnabled varijable prikazi ili sakrij prioritet QSpinBox
    for (int i = 0; i < 9; i++)
    {
        prioritetProcesa[i]->setEnabled(prioritetEnabled);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
