#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QMap>

class GameConfig {
public:
    GameConfig() {
        BACKGROUND_COLOR = "#92877d";

        bgColorMap[0] = "#9e948a";
        bgColorMap[2] = "#eee4da";
        bgColorMap[4] = "#ede0c8";
        bgColorMap[8] = "#f2b179";
        bgColorMap[16] = "#f59563";
        bgColorMap[32] = "#f67c5f";
        bgColorMap[64] = "#f65e3b";
        bgColorMap[128] = "#edcf72";
        bgColorMap[256] = "#edcc61";
        bgColorMap[512] = "#edc850";
        bgColorMap[1024] = "#edc53f";
        bgColorMap[2048] = "#edc22e";

        numberColorMap[0] = "#776e65";
        numberColorMap[2] = "#776e65";
        numberColorMap[4] = "#776e65";
        numberColorMap[8] = "#f9f6f2";
        numberColorMap[16] = "#f9f6f2";
        numberColorMap[32] = "#f9f6f2";
        numberColorMap[64] = "#f9f6f2";
        numberColorMap[128] = "#f9f6f2";
        numberColorMap[256] = "#f9f6f2";
        numberColorMap[512] = "#f9f6f2";
        numberColorMap[1024] = "#f9f6f2";
        numberColorMap[2048] = "#f9f6f2";
    }

    QString BACKGROUND_COLOR;
    QMap<int, QString> bgColorMap;
    QMap<int, QString> numberColorMap;

    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 400;
    const int GRID_LEN = 4;
    const int GRID_PADDING = 10;
    const int GRID_SIZE = 88;
    const int NUMBER_PADDING_X = 33;
    const int NUMBER_PADDING_Y = 53;
    const double NUMBER_WIDTH = 8.5;
};

extern GameConfig config;

#endif // GAMECONFIG_H
