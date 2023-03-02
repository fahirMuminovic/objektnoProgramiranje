#include "tranzicija.h"
#include <QDebug>

Tranzicija::Tranzicija(int koordinataX, int koordinataY,int duzina, int rotacija)
{
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->tempX = koordinataX;
    this->tempY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;
    timer = new QTimer(this->parent());
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
    linije.setJoinStyle(Qt::MiterJoin);
    painter->setPen(linije);

    // boja strelice
    boja.setColor(Qt::green);
    boja.setStyle(Qt::SolidPattern);

    strelica.addPolygon(tackeStrelice);

    painter->rotate(rotacija);

    painter->drawPolygon(tackeStrelice);

    painter->fillPath(strelica,boja);
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const{
    if(rotacija == 0) {
       //QRectF::QRectF(qreal x, qreal y, qreal width, qreal height)
       //Constructs a rectangle with (x, y) as its top-left corner and the given width and height.
       return QRectF(-100,10,225,30);
    }
    if(rotacija == 180) {
       return QRectF(-115,-50,230,30);
    }
    if(rotacija == 315) {
       return QRectF(200,-180,135,135);
    }
    if(rotacija == 135) {
       return QRectF(10,40,200,200);
    }
    if(rotacija == 225) {
       return QRectF(-160,20,135,135);
    }
    else {
       return QRectF(-330,-200,135,165);
    }
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}



