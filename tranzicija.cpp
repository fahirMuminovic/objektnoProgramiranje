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

void Tranzicija::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath strelica(shape());

    // Save painter state
    painter->save();

    // Translate painter to the top-left corner of the scene
    painter->translate(0, 0);

    // Translate painter to the center of the Tranzicija item
    QPointF center = strelica.boundingRect().center();
    painter->translate(center);

    // Rotate painter by the rotation of the Tranzicija item
    painter->rotate(rotacija);

    // Translate painter back to the top-left corner of the Tranzicija item
    painter->translate(- center);

    // Set the color and pen for drawing the Tranzicija item
    QPen pen(Qt::black);
    painter->setPen(pen);
    QBrush brush(Qt::white);
    painter->setBrush(brush);

    // Draw the Tranzicija item as a polygon
    painter->drawPath(shape());

    // Restore painter state
    painter->restore();
}


// funkcija koja definira granice elementa
QRectF Tranzicija::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(koordinataX - penWidth/2, koordinataY - penWidth/2, duzina + penWidth, duzina + penWidth);
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
