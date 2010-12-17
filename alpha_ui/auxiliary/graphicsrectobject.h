#ifndef GRAPHICSRECTOBJECT_H
#define GRAPHICSRECTOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>

class GraphicsRectObject : public QObject, public QGraphicsRectItem
{
public:
    GraphicsRectObject(const QRectF & rect, QGraphicsItem * parent = 0) : QObject(), QGraphicsRectItem(rect, parent)
    {

    }
};

#endif // GRAPHICSRECTOBJECT_H
