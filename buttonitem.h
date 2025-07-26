#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>

class ButtonItem : public QGraphicsObject
{
    Q_OBJECT
public:
    ButtonItem(const QRectF &rect, QGraphicsItem *parent = nullptr)
        : QGraphicsObject(parent), m_rect(rect)
    {
        setAcceptedMouseButtons(Qt::LeftButton);
        setFlag(QGraphicsItem::ItemIsFocusable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setZValue(100);   // 确保在最上层
    }

    QRectF boundingRect() const override { return m_rect; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        painter->setBrush(QColor(255,100,100));
        painter->setPen(QPen(Qt::white, 2));
        painter->drawRect(m_rect);

        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 12));
        painter->drawText(boundingRect(), Qt::AlignCenter, "Restart");
    }

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override
    {
        qDebug() << "clicked";
        emit clicked();
    }

private:
    QRectF m_rect;
};

#endif // BUTTONITEM_H
