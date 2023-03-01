#include "tranzicija.h"
#include <QDebug>

Tranzicija::Tranzicija(int koordinataX, int koordinataY, int duzina, int rotacija){
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->tempX = koordinataX;
    this->tempY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;
    timer = new QTimer(this->parent());
}

void Tranzicija::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidged * widget){
    QPen linija;
    QBrush fill;
    QPainterPath putanja;
    QPolygon strelica;

    strelica << QPoint(koordinataX,koordinataY);
    strelica << QPoint(koordinataX + duzina, koordinataY);
    strelica << QPoint(koordinataX + duzina, koordinataY - 10);
    strelica << QPoint(koordinataX + duzina + 15, koordinataY + 5);
    strelica << QPoint(koordinataX + duzina,koordinataY + 20);
    strelica << QPoint(koordinataX + duzina,koordinataY + 10);
    strelica << QPoint(koordinataX,koordinataY + 10);

    linija.setWidth(2);
    linija.setColor(Qt::black);
    linija.setJoinStyle(Qt::MiterJoin);
    painter->setPen(linija);

    fill.setColor(Qt::green);
    fill.setStyle(Qt::solidPattern);
    putanja.addPolygon(strelica);
    painter->rotate(rotacija);
    painter->setPen(linija);
    painter->drawPolygon(strelica);
    painter->fillPath(putanja,fill);
};

QRectF Tranzicija::pozicijaElementa() const{
    if(rotacija == 0){
        return QRectF(-120, 0, 230, 30);
    }
    if(rotacija == 180){
        return QRectF(-120, -60, 230, 30);
    }
    if(rotacija == 315){
        return QRectF(200, -160, 135, 135);
    }
    if(rotacija == 135){
        return QRectF(10, 40, 200, 200);
    }
    if(rotacija == 225){
        return QRectF(-160, 20, 135, 135);
    }
    else{
        return QRectF(-330, -200, 135, 165);
    }
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}
