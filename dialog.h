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
    bool nijeUSjfProcesi(std::vector<Proces> procesi, int redniBroj);
    bool postojiKraceVrijemeIzvrsavanja(std::vector<Proces> redCekanja, Proces trenutniProces);
    bool postojiProcesSaVecimPrioritetom(std::vector<Proces> redCekanja, Proces trenutniProces);
private slots:
    void on_broj_procesa_comboBox_currentIndexChanged(const QString &broj);
    void on_nacrtajDijagramBtn_clicked();
    void on_algoritam_comboBox_currentTextChanged(const QString &arg1);

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

    void nacrtajScenu();
    void podesiUIElemente();
    void inicijalizirajBrojProcesa();
    void postaviUIElementeUNizove();
    void napraviNizObjekataProces();
    void nacrtajProcesText();
    void nacrtajProces();

    void pripremiFCFS();
    void nacrtajAlgoritam();
    void pripremiSJF();
    void pripremiSJFsaPretpaznjenjem();
    void pripremiRR();
    void pripremiPrioritet();
    void pripremiPrioritetSaPretpraznjenjem();

    void sortirajProcesePoTrenutkuDolaska(Proces *niz);
    void sortirajProcesePoTrajanju(Proces *niz);

    std::vector<Proces> sortirajProcesePoTrajanjuVector(std::vector<Proces> vector);
    std::vector<Proces> sortirajProcesePoPrioritetu(std::vector<Proces> vector);
    std::vector<Proces> sortirajProcesePoRednomBroju(std::vector<Proces> vector);
    std::vector<Proces> dodatnoSortiraj(std::vector<Proces> redCekanja);
};

#endif // DIALOG_H
