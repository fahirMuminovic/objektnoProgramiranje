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
    setFlag(ItemIsMovable);
}

void Tranzicija::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    QPen linije;
    QBrush boja;
    QPainterPath strelica;
    QPolygon tackeStrelice;
    QRectF bounds = boundingRect();

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
    painter->drawPolygon(bounds);
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const{
//    if(rotacija == 0) {
//       // readyRunTranzicija
//       return QRectF(-100,0,225,40);
//    }
//    if(rotacija == 45) {
//       //startReadyTranzicija
//       return QRectF(-350,85,165,40);
//    }
//    if(rotacija == 135) {
//       //runWaitTranzicija
//       return QRectF(-80,-165,155,40);
//    }
//    if(rotacija == 180) {
//       //runReadyTranzicija
//       return QRectF(-110,10,225,40);
//    }
//    if(rotacija == 225) {
//       //waitReadyTranzicija
//       return QRectF(-80,-155,155,40);
//    }
//    if(rotacija == 315) {
//       //runStopTranzicija
//       return QRectF(185,95,165,40);
//    }

        return QRectF(koordinataX,koordinataY,100,100);

//    if(rotacija == 0) {
//        return QRectF(-120,0,230,30);
//    }
//    if(rotacija == 180) {
//        return QRectF(-120,-60,230,30);
//    }
//    if(rotacija == 315) {
//        return QRectF(200,-160,135,135);
//    }
//    if(rotacija == 135) {
//        return QRectF(10,40,200,200);
//    }
//    if(rotacija == 225) {
//        return QRectF(-160,20,135,135);
//    }
//    else {
//        return QRectF(-330,-200,135,165);
//    }
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}



