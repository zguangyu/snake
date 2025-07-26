#include "mainwidget.h"
#include "gameoveroverlay.h"
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QDirIterator>
#include <QMediaFormat>

#define MAP_WIDTH   41
#define MAP_HEIGHT  31
#define TILE_SIZE   20
#define REFRESH_TIME 200

MainWidget::MainWidget(QWidget *parent)
    : QGraphicsView(parent), map(MAP_WIDTH, std::vector<int>(MAP_HEIGHT, 0))
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, MAP_WIDTH*TILE_SIZE, MAP_HEIGHT*TILE_SIZE);
    setScene(scene);

    rect_list = new QList<SnakeRect*>();

    setWindowTitle("Hello Snake!");

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWidget::refresh);
    connect(scene, &QGraphicsScene::sceneRectChanged, this, &MainWidget::reset);

    eatSound = new QSoundEffect(this);
    eatSound->setSource(QUrl("qrc:/assets/eat.wav"));
    eatSound->setVolume(1);

    init();
}

MainWidget::~MainWidget() {}

void MainWidget::refresh()
{
    SnakeRect *snake_header = rect_list->first();
    SnakeRect *snake_tail = rect_list->last();

    QPoint pos = snake_header->get_pos();
    QPoint next_pos = pos;
    switch (curr_dir) {
    case MOVE_TOP:
        next_pos.setY(next_pos.y() - 1);
        break;
    case MOVE_BOTTOM:
        next_pos.setY(next_pos.y() + 1);
        break;
    case MOVE_LEFT:
        next_pos.setX(next_pos.x() - 1);
        break;
    case MOVE_RIGHT:
        next_pos.setX(next_pos.x() + 1);
        break;
    }
    if (next_pos.x() < 0 || next_pos.x() >= MAP_WIDTH || next_pos.y() < 0 || next_pos.y() >= MAP_HEIGHT) {
        fail();
    }
    else if (next_pos == food->get_pos()) {
        rect_list->push_front(food);
        food = randomRect();
        eatSound->play();
    }
    else if (map[next_pos.x()][next_pos.y()] == 1) {
        fail();
    }
    else {
        moveRect(snake_tail, next_pos);
        rect_list->pop_back();
        rect_list->push_front(snake_tail);
    }
}

SnakeRect* MainWidget::randomRect()
{
    int x, y;
    do {
        x = QRandomGenerator::global()->bounded(MAP_WIDTH);
        y = QRandomGenerator::global()->bounded(MAP_HEIGHT);
    } while (map[x][y] != 0);

    return createRect({x, y});
}

SnakeRect* MainWidget::createRect(QPoint pos)
{
    auto rect = new SnakeRect(pos, TILE_SIZE);
    scene()->addItem(rect);
    map[pos.x()][pos.y()] = 1;
    qDebug() << "create rect " << pos.x() << ' ' << pos.y() << ' ' << map[pos.x()][pos.y()];
    return rect;
}

void MainWidget::fail()
{
    timer->stop();
    GameOverOverlay::show(this, "Game Over!");
}

void MainWidget::reset()
{
    scene()->removeItem(food);
    for (QGraphicsRectItem *item : *rect_list) {
        scene()->removeItem(item);
        delete item;
    }
    rect_list->clear();

    init();
}

void MainWidget::init()
{
    auto rect = createRect({MAP_WIDTH/2, MAP_HEIGHT/2});
    rect_list->append(rect);

    food = randomRect();
    curr_dir = MOVE_TOP;

    timer->start(REFRESH_TIME);
}

void MainWidget::moveRect(SnakeRect *rect, QPoint pos)
{
    QPoint old_pos = rect->get_pos();
    map[old_pos.x()][old_pos.y()] = 0;
    map[pos.x()][pos.y()] = 1;
    rect->move(pos);
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
        qDebug() << "key left, dir " << curr_dir;
        if (curr_dir != MOVE_RIGHT)
            curr_dir = MOVE_LEFT;
        break;
    case Qt::Key_Right:
        qDebug() << "key right, dir " << curr_dir;
        if (curr_dir != MOVE_LEFT)
            curr_dir = MOVE_RIGHT;
        break;
    case Qt::Key_Up:
        qDebug() << "key up, dir " << curr_dir;
        if (curr_dir != MOVE_BOTTOM)
            curr_dir = MOVE_TOP;
        break;
    case Qt::Key_Down:
        qDebug() << "key down, dir " << curr_dir;
        if (curr_dir != MOVE_TOP)
            curr_dir = MOVE_BOTTOM;
        break;
    default: QGraphicsView::keyPressEvent(e);
    }
}

