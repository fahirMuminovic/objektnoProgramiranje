#include "tranzicija.h"

Tranzicija::Tranzicija(int koordinataX, int koordinataY,int duzina, int rotacija)
{
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->tempX = koordinataX;
    this->tempY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;
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
        return QRectF(260, 315, 285, 30);
    }
    if(rotacija == 180){
        return QRectF(255, 265, 285, 30);
    }
    if(rotacija == 53){
        return QRectF(65, 120, 150, 250);
    }
    if(rotacija == 307){
        return QRectF(630, 120, 140, 160);
    }
    if(rotacija == 135){
        return QRectF(400, 325, 200, 180);
    }
    if(rotacija == 225){
        return QRectF(200, 325, 160, 165);
    }
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}
