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

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_broj_procesa_comboBox_currentIndexChanged(const QString &broj);

    void on_nacrtajDijagramBtn_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;

    void postaviUiElementeUNizove();
    void nacrtajProcesText();
    void nacrtajScenu();

    QSpinBox *dolazakUCiklusu[9];
    QSpinBox *trajanjeCiklusa[9];
    QSpinBox *prioritetCiklusa[9];
    QLabel *procesiLabel[9];

    QString trenutnoOdabraniAlgoritam;
    int brojProcesa;
    int visinaScene;
    int duzinaScene;
};

#endif // DIALOG_H
