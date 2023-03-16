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
    QPainterPath strelica;
    QPolygon tackeStrelice;

    // definise pen koji ce se koristiti za iscrtavanje strelice
    linije.setWidth(2);
    linije.setColor(Qt::black);
    painter->setPen(linije);

    // odredjuje boju strelica
    boja.setColor(Qt::green);
    boja.setStyle(Qt::SolidPattern);

    // Calculate the center point of the item
    QPointF centerPoint = boundingRect().center();

    painter->drawRect(boundingRect());

    // Save the current painter state
    painter->save();

    // Translate the painter to the desired position on the scene
    painter->translate(0, 0);

    // Set the rotation origin point to the center of the item
    setTransformOriginPoint(centerPoint);

    // Rotate the item
    QTransform transform;
    transform.rotate(rotacija);
    setTransform(transform);

    // Paint the item's shape relative to the top-left corner of the scene
    painter->drawPath(shape());
    painter->fillPath(shape(),boja);

    // Restore the painter state
    painter->restore();
}

// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const
{
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

    QPointF scenePos = event->scenePos();
    qDebug() << "Mouse click at:" << scenePos.x() << "," << scenePos.y();
}
