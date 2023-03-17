#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>
#include <QString>
#include <QBrush>
#include "proces.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    int pocetakCiklusa();
    bool imaKraceVrijemeIzvrsavanja(std::vector<Proces>& redCekanja,const Proces& trenutniProces);
    bool imaVeciPrioritet(std::vector<Proces>& redCekanja,const Proces& trenutniProces);
private slots:
    void on_broj_procesa_comboBox_currentIndexChanged(const QString &broj);
    void on_nacrtajDijagramBtn_clicked();
    void on_algoritam_comboBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;

    int brojProcesa;
    float const VISINA_SCENE = 390;
    float const DUZINA_SCENE = 730;
    QSpinBox *dolazakUCiklusu[9];
    QSpinBox *trajanjeCiklusa[9];
    QSpinBox *prioritetProcesa[9];
    QLabel *procesiLabel[9];
    Proces procesi[9];
    std::vector<Proces> redoslijedIzvrsavanja;
    int ukupnoTrajanjeProcesa();

    void nacrtajScenu();
    void podesiUIElemente();
    void inicijalizirajBrojProcesa();
    void postaviUIElementeUNizove();
    void napraviNizObjekataProces();
    void nacrtajProcesText();
    void nacrtajProceseZaOdabraniAlgoritam();

    void pripremiFCFS();
    void pripremiSJF();
    void pripremiSJFsaPretpaznjenjem();
    void pripremiRR();
    void pripremiPrioritet();
    void pripremiPrioritetSaPretpraznjenjem();
    void nacrtajAlgoritam();

    void sortirajProcesePoTrenutkuDolaska(Proces *niz);
    void sortirajProcesePoTrenutkuDolaska(std::vector<Proces> &vector);
    void sortirajProcesePoTrajanju(Proces *niz);
    void sortirajProcesePoTrajanju(std::vector<Proces> &vector);
    void sortirajProcesePoPrioritetu(std::vector<Proces> &vector);

    void sortirajProcesePoRednomBroju(std::vector<Proces> &vector);
    void dodatnoSortirajPoRednomBroju(std::string tipSortiranja, std::vector<Proces> &redCekanja);
};

#endif // DIALOG_H
