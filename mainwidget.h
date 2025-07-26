#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "snakerect.h"
#include <QGraphicsView>

enum MoveDir_t {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_TOP,
    MOVE_BOTTOM
};

class MainWidget : public QGraphicsView
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void reset();

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    SnakeRect* randomRect();
    SnakeRect* createRect(QPoint pos);
    void moveRect(SnakeRect *rect, QPoint pos);
    void refresh();
    void fail();
    void init();

    QTimer *timer;
    QList<SnakeRect*> *rect_list;
    SnakeRect* food;
    std::vector<std::vector<int>> map;
    MoveDir_t curr_dir;
};
#endif // MAINWIDGET_H
