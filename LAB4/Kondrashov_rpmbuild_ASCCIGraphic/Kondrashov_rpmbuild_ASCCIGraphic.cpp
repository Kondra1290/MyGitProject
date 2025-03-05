#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <locale.h>
#include <ncursesw/ncurses.h> // Используем wide ncurses

using namespace std;

const float PI = 3.14159f;
const float TURN_ANGLE = PI / 4; // 45 градусов
int nScreenWidth = 120;
int nScreenHeight = 40;
int nMapWidth = 16;
int nMapHeight = 16;

int fPlayerX = 1; // Начальная позиция игрока (целые числа)
int fPlayerY = 1;
float fPlayerA = 0.0f;
float fFOV = PI / 4.0f; // Поле зрения
float fDepth = 16.0f;   // Дальность видимости

wstring map =
    L"################"
    L"#..............#"
    L"#.......########"
    L"#..............#"
    L"#......##......#"
    L"#......##......#"
    L"#..............#"
    L"###............#"
    L"##.............#"
    L"#......####..###"
    L"#......#.......#"
    L"#......#.......#"
    L"#..............#"
    L"#......#########"
    L"#..............#"
    L"################";

// Функция инициализации цветов
void InitColors() {
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK); // Стены
        init_pair(2, COLOR_GREEN, COLOR_BLACK); // Игрок
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Пустые пространства (мини-карта)
    }
}

// Функция отрисовки мини-карты (корректное позиционирование)
void DrawMiniMap() {
    for (int y = 0; y < nMapHeight; y++) {
        for (int x = 0; x < nMapWidth; x++) {
            if (map[y * nMapWidth + x] == '#') {
                attron(COLOR_PAIR(1));
                mvprintw(y, x, "#");
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(3));
                mvprintw(y, x, "·"); // Точки вместо пустых пространств
                attroff(COLOR_PAIR(3));
            }
        }
    }
    attron(COLOR_PAIR(2));
    mvprintw(fPlayerY, fPlayerX, "P"); // Отображение игрока
    attroff(COLOR_PAIR(2));
}

// Функция отрисовки 3D-сцены (Используем wide-символы)
void Draw3D(wchar_t* screen) {
    for (int x = 0; x < nScreenWidth; x++) {
        float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / nScreenWidth) * fFOV;
        float fStepSize = 0.1f;
        float fDistanceToWall = 0.0f;
        bool bHitWall = false;

        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);

        while (!bHitWall && fDistanceToWall < fDepth) {
            fDistanceToWall += fStepSize;
            int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
            int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

            if (nTestX < 0 || nTestX >= nMapWidth ||  nTestY < 0 || nTestY >= nMapHeight) {
                bHitWall = true;
                fDistanceToWall = fDepth;
            } else {
                if (map[nTestY * nMapWidth + nTestX] == '#') {
                    bHitWall = true;
                }
            }
        }

        int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / fDistanceToWall;
        int nFloor = nScreenHeight - nCeiling;

        for (int y = 0; y < nScreenHeight; y++) {
            if (y <= nCeiling) {
                screen[y * nScreenWidth + x] = L' ';
            } else if (y > nCeiling && y <= nFloor) {
                screen[y * nScreenWidth + x] = (fDistanceToWall < fDepth / 3.0) ? L'█' :
                                               (fDistanceToWall < fDepth / 2.0) ? L'▓' :
                                               (fDistanceToWall < fDepth) ? L'▒' : L'░';
            } else {
                screen[y * nScreenWidth + x] = L' '; // Черный пол
            }
        }
    }
}

// Функция отрисовки экрана
void DrawScreen(wchar_t* screen) {
    clear();
    DrawMiniMap();
    Draw3D(screen);

    for (int y = 0; y < nScreenHeight; y++) {
        for (int x = 0; x < nScreenWidth; x++) {
            mvaddwstr(y, x + nMapWidth + 4, &screen[y * nScreenWidth + x]);
        }
    }
    refresh();
}

int main() {
    setlocale(LC_ALL, "");  // Поддержка Unicode
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    InitColors();
wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

    while (true) {
        int ch = getch();
        if (ch == 'q') break;

        if (ch == 'a') fPlayerA -= TURN_ANGLE;
        if (ch == 'd') fPlayerA += TURN_ANGLE;

        if (fPlayerA < 0) fPlayerA += 2 * PI;
        if (fPlayerA >= 2 * PI) fPlayerA -= 2 * PI;

        int fNewX = fPlayerX;
        int fNewY = fPlayerY;

        if (ch == 'w') {
            fNewX += round(sinf(fPlayerA));
            fNewY += round(cosf(fPlayerA));
        }

        if (ch == 's') {
            fNewX -= round(sinf(fPlayerA));
            fNewY -= round(cosf(fPlayerA));
        }

        if (fNewX >= 0 && fNewX < nMapWidth && fNewY >= 0 && fNewY < nMapHeight) {
            if (map[fNewY * nMapWidth + fNewX] != '#') {
                fPlayerX = fNewX;
                fPlayerY = fNewY;
            }
        }

        DrawScreen(screen);
    }

    endwin();
    delete[] screen;
    return 0;
}
