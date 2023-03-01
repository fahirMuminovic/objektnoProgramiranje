#ifndef STANJE_H
#define STANJE_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QFont>
#include <QString>

class Stanje : public QGraphicsEllipseItem
{
public:
    // konstruktor klase
    Stanje(int x, int y, QString naslovStanja);
    // metoda paint overloada QPainter
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    // vraća koordinate elementa na QGraphicsView
    QRectF pozicijaElementa() const;
    // broj procesa koji su inicijalizirani unutar stanja
    int brojProcesa;

private:
    int koordinataX;
    int koordinataY;
    QString naslov;
};


#endif // STANJE_H

