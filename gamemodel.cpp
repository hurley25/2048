#include "gamemodel.h"

#include <QRandomGenerator>
#include <QMessageBox>

#include "gameconfig.h"

GameModel::GameModel() {
    gameData_.resize(config.GRID_LEN);
    for (int i = 0; i < config.GRID_LEN; ++i) {
        gameData_[i].resize(config.GRID_LEN);
    }
    reset();
}

void GameModel::reset() {
    for (int i = 0; i < config.GRID_LEN; ++i) {
        for (int j = 0; j < config.GRID_LEN; ++j) {
            gameData_[i][j] = 0;
        }
    }
    addNewNumber(2);
    addNewNumber(2);
}

int GameModel::getRandom(int bounded) {
    return QRandomGenerator::global()->bounded(bounded);
}

QVector<QVector<int>> GameModel::transpose(QVector<QVector<int>> &data) {
    auto newData = data;
    for (int i = 0; i < config.GRID_LEN; ++i) {
        for (int j = 0; j < config.GRID_LEN; ++j) {
            newData[i][j] = data[j][i];
        }
    }
    return newData;
}

void GameModel::mergeAndMoveToLeft(QVector<int> &vect) {
    for (int i = 0; i < config.GRID_LEN - 1; ++i) {
        if (vect[i] != 0 && vect[i] == vect[i+1]) {
            vect[i] *= 2;
            vect[i+1] = 0;
        }
        for (int i = 0; i < config.GRID_LEN - 1; ++i) {
            if (vect[i] == 0 && vect[i+1] != 0) {
                std::swap(vect[i], vect[i+1]);
            }
        }
    }
}

GameModel::State GameModel::checkGameState() {
    for (int i = 0; i < config.GRID_LEN; ++i) {
        for (int j = 0; j < config.GRID_LEN; ++j) {
            if (gameData_[i][j] == 2048) {
                return State::WIN;
            }
        }
    }
    for (int i = 0; i < config.GRID_LEN; ++i) {
        for (int j = 0; j < config.GRID_LEN; ++j) {
            if (gameData_[i][j] == 0) {
                return State::NORMAL;
            } else if (j < config.GRID_LEN - 1 && gameData_[i][j] == gameData_[i][j+1]) {
                return State::NORMAL;
            } else if (i < config.GRID_LEN -1 && gameData_[i][j] == gameData_[i+1][j]) {
                return State::NORMAL;
            }
        }
    }
    return State::GAMEOVER;
}

void GameModel::checkWinOrGameOver() {
    State state = checkGameState();
    if (state == State::WIN) {
        QMessageBox::information(nullptr, "Congratulations", "You Win!");
        reset();
    } else if (state == State::GAMEOVER) {
        QMessageBox::warning(nullptr, "Unfortunately", "Gameover!");
        reset();
    }
}

void GameModel::addNewNumber(int number) {
    if (checkGameState() == State::GAMEOVER) {
        return;
    }
    QVector<QPair<int, int>> emptyPonits;
    for (int i = 0; i < config.GRID_LEN; ++i) {
        for (int j = 0; j < config.GRID_LEN; ++j) {
            if (gameData_[i][j] == 0) {
                emptyPonits.append(qMakePair(i, j));
            }
        }
    }
    if (emptyPonits.empty()) {
        return;
    }
    int index = getRandom(emptyPonits.size());
    int x = emptyPonits[index].first;
    int y = emptyPonits[index].second;
    if (number) {
        gameData_[x][y] = number;
    } else {
        if (getRandom(11) > 8) {
            gameData_[x][y] = 4;
        } else {
            gameData_[x][y] = 2;
        }
    }
}

/*
 *          x
 *  0 ------->
 *    |
 *    |
 *    |
 *  y v
 *
 */

void GameModel::moveLeft() {
    auto tmpData = gameData_;
    auto data = transpose(gameData_);
    for (int i = 0; i < config.GRID_LEN; ++i) {
        mergeAndMoveToLeft(data[i]);
    }
    gameData_ = transpose(data);
    if (tmpData != gameData_) {
        addNewNumber();
    }
    checkWinOrGameOver();
}

void GameModel::moveRight() {
    auto tmpData = gameData_;
    auto data = transpose(gameData_);
    for (int i = 0; i < config.GRID_LEN; ++i) {
        auto line = data[i];
        std::reverse(line.begin(), line.end());
        mergeAndMoveToLeft(line);
        std::reverse(line.begin(), line.end());
        data[i] = line;
    }
    gameData_ = transpose(data);
    if (tmpData != gameData_) {
        addNewNumber();
    }
    checkWinOrGameOver();
}

void GameModel::moveUp() {
    auto tmpData = gameData_;
    for (int i = 0; i < config.GRID_LEN; ++i) {
        mergeAndMoveToLeft(gameData_[i]);
    }
    if (tmpData != gameData_) {
        addNewNumber();
    }
    checkWinOrGameOver();
}

void GameModel::moveDown() {
    auto tmpData = gameData_;
    for (int i = 0; i < config.GRID_LEN; ++i) {
        auto line = gameData_[i];
        std::reverse(line.begin(), line.end());
        mergeAndMoveToLeft(line);
        std::reverse(line.begin(), line.end());
        gameData_[i] = line;
    }
    if (tmpData != gameData_) {
        addNewNumber();
    }
    checkWinOrGameOver();
}

QVector<QVector<int>> &GameModel::getGameData() {
    return gameData_;
}
