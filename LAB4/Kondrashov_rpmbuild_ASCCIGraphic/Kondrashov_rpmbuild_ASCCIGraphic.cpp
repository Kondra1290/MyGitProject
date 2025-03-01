#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ncurses.h>

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
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // Цвет стен
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Цвет игрока
    init_pair(3, COLOR_BLUE, COLOR_BLACK);    // Цвет пола
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Темные стены (дальний вид)
}

// Функция отрисовки мини-карты
void DrawMiniMap() {
    for (int y = 0; y < nMapHeight; y++) {
        for (int x = 0; x < nMapWidth; x++) {
            attron(COLOR_PAIR(1));
            mvprintw(y + 1, x + 1, "%c", map[y * nMapWidth + x]);
            attroff(COLOR_PAIR(1));
        }
    }
    attron(COLOR_PAIR(2));
    mvprintw(fPlayerY + 1, fPlayerX + 1, "P"); // Отображение игрока
    attroff(COLOR_PAIR(2));

    // Отображение координат и угла поворота
    mvprintw(nMapHeight + 2, 1, "X=%d, Y=%d, Angle=%.1f deg", fPlayerX, fPlayerY, fPlayerA * 180 / PI);
}

// Функция отрисовки 3D-сцены
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

            if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
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
                attron(COLOR_PAIR(3)); // Пол
                screen[y * nScreenWidth + x] = ' ';
                attroff(COLOR_PAIR(3));
            } else if (y > nCeiling && y <= nFloor) {
                attron(fDistanceToWall < fDepth / 2.0 ? COLOR_PAIR(1) : COLOR_PAIR(4));
                screen[y * nScreenWidth + x] = (fDistanceToWall < fDepth / 3.0) ? '█' :
                                               (fDistanceToWall < fDepth / 2.0) ? '▓' :
                                               (fDistanceToWall < fDepth) ? '▒' : '░';
                attroff(fDistanceToWall < fDepth / 2.0 ? COLOR_PAIR(1) : COLOR_PAIR(4));
            } else {
                attron(COLOR_PAIR(3)); // Потолок
                screen[y * nScreenWidth + x] = '.';
                attroff(COLOR_PAIR(3));
            }
        }
    }
}

// Функция отрисовки экрана
void DrawScreen(wchar_t* screen) {
    clear();

    DrawMiniMap(); // Отрисовка мини-карты
    Draw3D(screen); // Отрисовка 3D-сцены
// Вывод 3D-изображения справа от мини-карты
    for (int y = 0; y < nScreenHeight; y++) {
        for (int x = 0; x < nScreenWidth; x++) {
            mvaddch(y, x + nMapWidth + 4, screen[y * nScreenWidth + x]);
        }
    }
    refresh();
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    InitColors(); // Инициализация цветов

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

    while (true) {
        int ch = getch();
        if (ch == 'q') break; // Выход

        if (ch == 'a') fPlayerA -= TURN_ANGLE; // Поворот на -45°
        if (ch == 'd') fPlayerA += TURN_ANGLE; // Поворот на +45°

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
