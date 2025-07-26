#include "snakerect.h"
#include <QPen>

SnakeRect::SnakeRect(QPoint pos, int tile_size)
{
    setBrush(Qt::green);
    setPen(QPen(Qt::darkGray, 2));
    setRect(0, 0, tile_size, tile_size);
    setPos(pos.x()*tile_size, pos.y()*tile_size);

    this->pos = pos;
    this->tile_size = tile_size;
}


QPoint SnakeRect::get_pos()
{
    return pos;
}

void SnakeRect::move(QPoint pos)
{
    setPos(pos.x()*tile_size, pos.y()*tile_size);
    this->pos = pos;
}
