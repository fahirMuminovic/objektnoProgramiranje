#include "tranzicija.h"
#include <QGraphicsSceneMouseEvent>

Tranzicija::Tranzicija(int koordinataX, int koordinataY,int duzina, int rotacija)
{
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;

    setFlag(ItemIsMovable);
}

void Tranzicija::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    QPen linije;
    QBrush boja;
    QPainterPath strelica;
    QPolygon tackeStrelice;

    // odredjuje tacke koje ce se koristiti u addPolygon metodi
    tackeStrelice << QPoint(koordinataX,koordinataY);
    tackeStrelice << QPoint(koordinataX+duzina,koordinataY);
    tackeStrelice << QPoint(koordinataX+duzina,koordinataY-10);
    tackeStrelice << QPoint(koordinataX+duzina+15,koordinataY+5);
    tackeStrelice << QPoint(koordinataX+duzina,koordinataY+20);
    tackeStrelice << QPoint(koordinataX+duzina,koordinataY+10);
    tackeStrelice << QPoint(koordinataX,koordinataY+10);

    // definise pen koji ce se koristiti za iscrtavanje strelice
    linije.setWidth(2);
    linije.setColor(Qt::black);
    painter->setPen(linije);

    // odredjuje boju strelica
    boja.setColor(Qt::green);
    boja.setStyle(Qt::SolidPattern);

    // pravi strelicu na osnovu zadanih tacki
    strelica.addPolygon(tackeStrelice);
    // rotacija strelice
    painter->rotate(rotacija);
    // crta strelicu
    painter->drawPolygon(tackeStrelice);
    // boji strelicu
    painter->fillPath(strelica,boja);
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const{
    if(rotacija == 0){
        //ready run
        return QRectF(260, 315, 285, 30);
    }
    else if(rotacija == 180){
        // run ready
        return QRectF(255, 265, 285, 30);
    }
    else if(rotacija == 53){
        // start ready
        return QRectF(65, 120, 105, 135);
    }
    else if(rotacija == 307){
        // run stop
        return QRectF(632, 125, 112, 138);
    }
    else if(rotacija == 135){
        // run wait
        return QRectF(435, 348, 145, 142);
    }
    else {
        // wait ready
        return QRectF(218, 353, 142, 140);
    }
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();

    // get the position of the mouse click
    QPointF pos = event->scenePos();

    // log the position
    qDebug() << "Mouse clicked at position:" << pos;
}
