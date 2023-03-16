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
    QPainterPath strelica = shape();

    // definise pen koji ce se koristiti za iscrtavanje strelice
    linije.setWidth(2);
    linije.setColor(Qt::black);
    painter->setPen(linije);

    // odredjuje boju strelica
    boja.setColor(Qt::green);
    boja.setStyle(Qt::SolidPattern);

painter->drawRect(boundingRect());
    // Set the position of the Tranzicija item based on the top-left corner of the QGraphicsScene
    QPointF position(0, 0);
    setPos(position);

    // Set the rotation of the Tranzicija item around itself
//    this->setRotation(rotation);

    // Rotate the polygon around its center point by the rotation value
    QPointF center = strelica.boundingRect().center(); // get the center point of the polygon
    QTransform transform;
    transform.translate(center.x(), center.y()); // translate to the center point
    transform.rotate(rotacija); // rotate
    transform.translate(-center.x(), -center.y()); // translate back
    strelica = transform.map(strelica); // apply the transformation to the polygon

    // Paint the polygon on the QGraphicsScene
    painter->drawPath(strelica);

    painter->fillPath(strelica,boja);
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
