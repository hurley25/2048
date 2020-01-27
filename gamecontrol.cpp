#include "gamecontrol.h"

#include <QPainter>
#include <QKeyEvent>

#include "gameconfig.h"

GameControl::GameControl(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(config.WINDOW_WIDTH, config.WINDOW_HEIGHT);
    this->setFocusPolicy(Qt::StrongFocus);
}

void GameControl::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            model_.moveUp();
            this->update();
            break;
        case Qt::Key_Down:
            model_.moveDown();
            this->update();
            break;
        case Qt::Key_Left:
            model_.moveLeft();
            this->update();
            break;
        case Qt::Key_Right:
            model_.moveRight();
            this->update();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
    }
}

void GameControl::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setFont(QFont("Verdana", 25, QFont::Bold));
    painter.setBrush(QBrush(QColor(config.BACKGROUND_COLOR)));
    painter.drawRect(this->rect());

    QVector<QVector<int>> &gameData = model_.getGameData();
    for (int i = 0; i < gameData.size(); i++) {
        for (int j = 0; j < gameData[i].size(); ++j) {
            int x = config.GRID_PADDING + i * (config.GRID_SIZE + config.GRID_PADDING);
            int y = config.GRID_PADDING + j * (config.GRID_SIZE + config.GRID_PADDING);
            int number = gameData[i][j];
            painter.fillRect(x, y, config.GRID_SIZE, config.GRID_SIZE, QBrush(QColor(config.bgColorMap[number])));
            if (number != 0) {
                painter.setPen(QColor(config.numberColorMap[number]));
                QString text = QString::number(number);
                int tx = x + config.NUMBER_PADDING_X - (text.length() - 1) * config.NUMBER_WIDTH;
                int ty = y + config.NUMBER_PADDING_Y;
                painter.drawText(tx, ty, text);
            }
        }
    }
}
