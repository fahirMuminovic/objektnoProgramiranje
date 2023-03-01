#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QPainter>
#include <stanje.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    // funkcija pravi elemente "stanje"
    void inicijalizirajStanja();
    // funkcija "crta" elemente na QGraphicsView
    void inicijalizirajElemente();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    Stanje *startStanje;
    Stanje *readyStanje;
    Stanje *waitStanje;
    Stanje *runStanje;
    Stanje *stopStanje;
};

#endif // DIALOG_H
