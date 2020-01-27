#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>

#include "gamemodel.h"

class GameControl : public QWidget {
    Q_OBJECT
public:
    explicit GameControl(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

signals:

private:
    GameModel model_;
};

#endif // GAMEVIEW_H
