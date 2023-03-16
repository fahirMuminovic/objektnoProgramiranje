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

    painter->drawPath(shape());
    painter->drawRect(boundingRect());
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const
{
//    if(rotacija == 0){
//        //ready run
//        return QRectF(260, 315, 285, 30);
//    }
//    else if(rotacija == 180){
//        // run ready
//        return QRectF(255, 265, 285, 30);
//    }
//    else if(rotacija == 53){
//        // start ready
//        return QRectF(65, 120, 105, 135);
//    }
//    else if(rotacija == 307){
//        // run stop
//        return QRectF(632, 125, 112, 138);
//    }
//    else if(rotacija == 135){
//        // run wait
//        return QRectF(435, 348, 145, 142);
//    }
//    else {
//        // wait ready
//        return QRectF(218, 353, 142, 140);
//    }
    return shape().boundingRect();
}


QPainterPath Tranzicija::shape() const
{
    QPainterPath path;
    QPolygonF strelica;

    strelica << QPointF(koordinataX,koordinataY);
    strelica << QPointF(koordinataX+duzina,koordinataY);
    strelica << QPointF(koordinataX+duzina,koordinataY-10);
    strelica << QPointF(koordinataX+duzina+15,koordinataY+5);
    strelica << QPointF(koordinataX+duzina,koordinataY+20);
    strelica << QPointF(koordinataX+duzina,koordinataY+10);
    strelica << QPointF(koordinataX,koordinataY+10);

    path.addPolygon(strelica);
    return path;
}

// override mousePressEvent funkcije tako da emituje signal onClick()
void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}
