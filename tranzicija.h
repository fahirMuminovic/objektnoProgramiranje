#ifndef TRANSITION_H
#define TRANSITION_H

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

class Transition : public QObject, public QgraphicsItem{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT

public:
    // konstruktor klase
    Transition(int koordinataX, int koordinataY, int duzina, int rotacija);
    // metoda paint overloada QPainter
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    // vraća koordinate elementa na QGraphicsView
    QRectF pozicijaElementa() const;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void: onClick();

public:
    int duzina;
    int koordinataX;
    int koordinataY;
    int tempX;
    int tempY;
    int rotacija;
    QTimer *timer;
};

#endif // TRANZICIJA

