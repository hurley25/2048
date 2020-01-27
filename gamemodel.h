#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QVector>

class GameModel {
public:
    enum State {
        NORMAL,
        WIN,
        GAMEOVER
    };
public:
    GameModel();

    QVector<QVector<int>> &getGameData();

    void reset();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

private:
    int getRandom(int bounded);
    void addNewNumber(int number = 0);
    void mergeAndMoveToLeft(QVector<int> &vect);
    State checkGameState();
    void checkWinOrGameOver();
    QVector<QVector<int>> transpose(QVector<QVector<int>> &data);

private:
    QVector<QVector<int>> gameData_;
};

#endif // GAMEMODEL_H
