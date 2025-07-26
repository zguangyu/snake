#ifndef SNAKERECT_H
#define SNAKERECT_H

#include <QGraphicsRectItem>

class SnakeRect : public QGraphicsRectItem
{
public:
    SnakeRect(QPoint pos, int tile_size);
    QPoint get_pos();
    void move(QPoint pos);

private:
    QPoint pos;
    int tile_size;
};

#endif // SNAKERECT_H
