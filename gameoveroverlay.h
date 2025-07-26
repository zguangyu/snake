#ifndef GAMEOVEROVERLAY_H
#define GAMEOVEROVERLAY_H

#include <QObject>
#include <QGraphicsScene>
#include "mainwidget.h"

class GameOverOverlay : public QObject
{
    Q_OBJECT
public:
    static void show(MainWidget *parent, const QString &msg);
    static void hide();
private:
    static QGraphicsItemGroup *g_group;
};

#endif // GAMEOVEROVERLAY_H
