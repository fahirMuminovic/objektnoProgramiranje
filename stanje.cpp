#include "stanje.h"

Stanje::Stanje(int x, int y, QString naslovStanja){
    koordinataX = x;
    koordinataY = y;
    naslov = naslovStanja;
    brojProcesa = 0;
    setFlag(ItemIsMovable);
}

void Stanje::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    // koordinate elementa na QGraphicsView-u
    QRectF koordinateElementa = pozicijaElementa();
    // boje koje se koriste za element
    QBrush zutaBoja(Qt::yellow);
    QBrush sivaBoja(Qt::gray);
    QBrush crvenaBoja(Qt::red);

    // rubElementa se koristi za iscrtavanje linije ruba elementa
    QPen rubElementa;
    rubElementa.setWidth(3);
    rubElementa.setBrush(Qt::black);
    // qt default pen
    QPen pen;
    // font za naslov elementa
    QFont font("Times New Roman", 15);
    font.setBold(true);

    // iscrtavanje glavnog dijela elementa
    painter->setPen(rubElementa);
    painter->setBrush(zutaBoja);
    painter->drawEllipse(koordinateElementa);

    //iscrtavanje naslova elementa
    painter->setFont(font);
    painter->drawText(koordinataX + 28, koordinataY + 40, naslov);

    // iscrtavanje reda čekanja elementa
    painter->setPen(pen);
    painter->setBrush(sivaBoja);

    painter->drawRect(QRect(koordinataX + 12+0, koordinataY + 50, 15, 15));
    painter->drawRect(QRect(koordinataX + 12+15,koordinataY + 50, 15, 15));
    painter->drawRect(QRect(koordinataX + 12+30,koordinataY + 50, 15, 15));
    painter->drawRect(QRect(koordinataX + 12+45,koordinataY + 50, 15, 15));
    painter->drawRect(QRect(koordinataX + 12+60,koordinataY + 50, 15, 15));

    // iscrtavanje procesa unutar reda čekanja za element
    painter->setBrush(crvenaBoja);
    for (int i = 0; i < brojProcesa; i ++){
        painter->drawEllipse(QRect(koordinataX + 15 * (i+1), koordinataY + 52, 10, 10));
    }
}

// funkcija koja vraca koordinate elementa "stanje"
QRectF Stanje::pozicijaElementa() const{
    return QRectF(koordinataX, koordinataY, 100, 100);
}
