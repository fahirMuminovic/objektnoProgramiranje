#ifndef TRANZICIJA_H
#define TRANZICIJA_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QPolygon>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QPainter>
#include <QtGui>
#include <QTimer>
#include <QDebug>

class Tranzicija : public QObject, public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT
public:
    // konstruktor klase
    Tranzicija(int koordinataX, int koordinataY,int duzina, int rotacija);
    // metoda overloada QPainter
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget  * widget);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void onClick();

public:
    int duzina;
    int koordinataX;
    int koordinataY;
    int tempX;
    int tempY;
    int rotacija;
};

#endif // TRANZICIJA_H
