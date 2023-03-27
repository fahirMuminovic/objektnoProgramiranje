#include "tranzicija.h"
#include <QGraphicsSceneMouseEvent>
#include <QMap>

Tranzicija::Tranzicija(int koordinataX, int koordinataY, int duzina, int rotacija)
{
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;
}

void Tranzicija::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen linije;
    QBrush boja;
    QPainterPath strelica;
    QPolygon tackeStrelice;

    // odredjuje tacke koje ce se koristiti u addPolygon metodi
    tackeStrelice << QPoint(koordinataX, koordinataY);
    tackeStrelice << QPoint(koordinataX + duzina, koordinataY);
    tackeStrelice << QPoint(koordinataX + duzina, koordinataY - 10);
    tackeStrelice << QPoint(koordinataX + duzina + 15, koordinataY + 5);
    tackeStrelice << QPoint(koordinataX + duzina, koordinataY + 20);
    tackeStrelice << QPoint(koordinataX + duzina, koordinataY + 10);
    tackeStrelice << QPoint(koordinataX, koordinataY + 10);

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
    painter->fillPath(strelica, boja);
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const
{
    // definisi mapu koja kao kljuc sadrzi rotaciju a kao vrijednost koordinate boundingRect-a
    QMap<int, QRectF> boundingRects{
        {0, QRectF(260, 315, 285, 30)},    // ready run
        {180, QRectF(255, 265, 285, 30)},  // run ready
        {53, QRectF(65, 120, 105, 135)},   // start ready
        {307, QRectF(632, 125, 112, 138)}, // run stop
        {135, QRectF(435, 348, 145, 142)}, // run wait
        {225, QRectF(218, 353, 142, 140)}  // wait ready
    };
    return boundingRects[rotacija];
}

void Tranzicija::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    emit onClick();
}
