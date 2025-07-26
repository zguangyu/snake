#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include "gameoveroverlay.h"
#include "buttonitem.h"

QGraphicsItemGroup *GameOverOverlay::g_group = nullptr;

void GameOverOverlay::show(MainWidget *parent, const QString &msg)
{
    if (g_group) hide();

    auto scene = parent->scene();

    g_group = new QGraphicsItemGroup;
    g_group->setHandlesChildEvents(false);

    auto *bg = new QGraphicsRectItem(0, 0, 400, 200);
    bg->setBrush(QColor(0,0,0,180));
    bg->setPen(Qt::NoPen);
    bg->setPos(scene->width()/2 - 200, scene->height()/2 - 100);
    g_group->addToGroup(bg);

    auto *text = new QGraphicsTextItem(msg);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("Arial", 28, QFont::Bold));
    text->setPos(bg->pos() + QPointF(200 - text->boundingRect().width()/2, 60));
    g_group->addToGroup(text);

    auto *btn = new ButtonItem(QRectF(0,0,120,40));
    btn->setPos(bg->pos() + QPointF(140,120));

    g_group->addToGroup(btn);

    QObject::connect(btn, &ButtonItem::clicked, [parent]{
        GameOverOverlay::hide();
        parent->reset();
    });

    scene->addItem(g_group);
}

void GameOverOverlay::hide()
{
    if (!g_group) return;
    delete g_group;
    g_group = nullptr;
}
