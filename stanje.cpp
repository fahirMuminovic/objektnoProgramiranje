#include "stanje.h"

Stanje::Stanje(int x, int y, QString naslovStanja)
{
    koordinataX = x;
    koordinataY = y;
    naslov = naslovStanja;
    brojProcesa = 0;
}

void Stanje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // koordinate za iscrtavanje ruba elementa koje uzimamo iz boundingRect() funkcije
    QRectF rubElipse = boundingRect();
    // boje koje se koriste za element
    QBrush zutaBoja(Qt::yellow);
    QBrush sivaBoja(Qt::gray);
    QBrush crvenaBoja(Qt::red);

    // linija ruba elementa Stanje
    QPen rubElementaStanja(Qt::black, 2);
    // qt default pen
    QPen defaultPen;
    // font za naslov Stanja
    QFont font("Times New Roman", 15, QFont::Bold);

    // iscrtavanje glavnog dijela elementa
    painter->setPen(rubElementaStanja);
    painter->setBrush(zutaBoja);
    painter->drawEllipse(rubElipse);

    // iscrtavanje naslova elementa
    painter->setFont(font);
    painter->drawText(koordinataX + 28, koordinataY + 40, naslov);

    // iscrtavanje reda čekanja elementa
    painter->setPen(defaultPen);
    painter->setBrush(sivaBoja);
    for (int i = 0; i < 5; i++)
    {
        painter->drawRect(QRect(koordinataX + 12 + (i * 15), koordinataY + 50, 15, 15));
    }

    // iscrtavanje procesa unutar reda čekanja za element
    painter->setBrush(crvenaBoja);
    for (int i = 0; i < brojProcesa; i++)
    {
        painter->drawEllipse(QRect(koordinataX + 15 * (i + 1), koordinataY + 52, 10, 10));
    }
}

// funkcija koja definira granice elementa
QRectF Stanje::boundingRect() const
{
    return QRectF(koordinataX, koordinataY, 100, 100);
}
