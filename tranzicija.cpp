#include "tranzicija.h"
#include <QGraphicsSceneMouseEvent>


Tranzicija::Tranzicija(int koordinataX, int koordinataY,int duzina, int rotacija)
{
    this->koordinataX = koordinataX;
    this->koordinataY = koordinataY;
    this->tempX = koordinataX;
    this->tempY = koordinataY;
    this->rotacija = rotacija;
    this->duzina = duzina;
    setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);

    setFlag(QGraphicsItem::ItemIsMovable);
}

void Tranzicija::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    QPen linije;
    QBrush boja;
    QPainterPath path = shape();
    QPolygonF strelica(shape());


}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const
{

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

    QPointF scenePos = event->scenePos();
    qDebug() << "Mouse click at:" << scenePos.x() << "," << scenePos.y();
}
