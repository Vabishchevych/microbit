#include <MicroBit.h>
#include <iostream>
#include <vector>
MicroBit uBit;
using namespace std;

MicroBitImage screen(5, 5);
int HeadSnakeX = 2, HeadSnakeY = 2;
char DirectionMove = 'U'; // U - UP; L - LEFT; R - RIGHT; D - DOWN;
int AppleX = -1, AppleY = -1;
int PartSnakeBackX, PartSnakeBackY;

vector<pair<pair<int, int>, pair<int, int>>> PartsSnake; // перший паір це його координати, а другий то його батько.

void GameInit();
void GameRender();
void SnakeMove();
void Food();
bool IsWin();
bool IsGameOver();

int main() {

    GameInit();

    while (!IsWin() && !IsGameOver()) {
        Food();
        SnakeMove();
        GameRender();
    }

    if (IsWin()) uBit.io.P1.setDigitalValue(1);
    else if (IsGameOver()) uBit.io.P0.setDigitalValue(1);

    while (1) uBit.sleep(100);
    release_fiber();
    return 0;
}

void GameInit() {
    uBit.init();
    srand(uBit.io.P2.getAnalogValue());
    screen.clear();
    PartsSnake.push_back({{2, 3}, {HeadSnakeX, HeadSnakeY}});
    Food();
    GameRender();
}

void SnakeMove() {
    char AB = 'O'; // якщо О - ненатиснуто жодну кнопку, А та В натиснуто одну з кнопок.
    for (int m=0; m<13; ++m) {
        if (uBit.buttonA.isPressed() && AB == 'O') {
            AB = 'A';
        }
        if (uBit.buttonB.isPressed() && AB == 'O') {
            AB = 'B';
        }
        uBit.sleep(50); // It`s 650 mili.
    }
    PartSnakeBackX = PartsSnake.back().first.first;
    PartSnakeBackY = PartsSnake.back().first.second;
    switch (DirectionMove) {
        case 'U':
            if (AB == 'A') DirectionMove = 'L';
            else if (AB == 'B') DirectionMove = 'R';
            if (HeadSnakeY > 0) HeadSnakeY--;
            else HeadSnakeY = 4;
            break;
        case 'L':
            if (AB == 'A') DirectionMove = 'D';
            else if (AB == 'B') DirectionMove = 'U';
            if (HeadSnakeX > 0) HeadSnakeX--;
            else HeadSnakeX = 4;
            break;
        case 'R':
            if (AB == 'A') DirectionMove = 'U';
            else if (AB == 'B') DirectionMove = 'D';
            if (HeadSnakeX < 4) HeadSnakeX++;
            else HeadSnakeX = 0;
            break;
        case 'D':
            if (AB == 'A') DirectionMove = 'R';
            else if (AB == 'B') DirectionMove = 'L';
            if (HeadSnakeY < 4) HeadSnakeY++;
            else HeadSnakeY = 0;
            break;
        }

    for (int i=0; i<PartsSnake.size(); i++) {
        PartsSnake[i].first.first = PartsSnake[i].second.first;
        PartsSnake[i].first.second = PartsSnake[i].second.second;

        if (i != 0) {
            PartsSnake[i].second.first = PartsSnake[i-1].first.first;
            PartsSnake[i].second.second = PartsSnake[i-1].first.second;
        } else {
            PartsSnake[i].second.first = HeadSnakeX;
            PartsSnake[i].second.second = HeadSnakeY;
        }
    }
}

void Food() {
    int y = rand()%10;//uBit.random(5);
    int x = rand()%10;//uBit.random(5);
    while (AppleY == -1 && AppleX == -1) {
        if (y < 5 && x < 5 && screen.getPixelValue(x, y) == 0) {
            AppleY = y;
            AppleX = x;
        } else {
            y = rand()%10;
            x = rand()%10;
        }
    }

    if (HeadSnakeY == AppleY && HeadSnakeX == AppleX) {
        AppleY = -1; AppleX = -1;
        PartsSnake.push_back({{PartSnakeBackX, PartSnakeBackY}, PartsSnake.back().second});
    }
}

void GameRender() {
    screen.clear();
    if (AppleX != -1 && AppleY != -1) {
        screen.setPixelValue(AppleX, AppleY, 1);
    }
    screen.setPixelValue(HeadSnakeX, HeadSnakeY, 9);
    for (int i = 0; i < PartsSnake.size(); i++) {
        screen.setPixelValue(PartsSnake[i].first.first, PartsSnake[i].first.second, 3);
    }
    uBit.display.print(screen);
}

bool IsWin() {
    if (PartsSnake.size() == 24) return true;
    return false;
}

bool IsGameOver() {
    for (int i=0; i<PartsSnake.size(); i++) {
        if (HeadSnakeX == PartsSnake[i].first.first && HeadSnakeY == PartsSnake[i].first.second) return true;
    }
    return false;
}

/*
    uBit.display.print(screen);

    int x = 0;
    for (int i=0; i<9; ++i) {
        if (i < 6) screen.setPixelValue(x, 0, i);
        else screen.setPixelValue(x, 1, i);
        ++x;
        if (x == 6) x = 0;
    }
    screen.setPixelValue(2, 1, 6);
*/

/*while (AppleY == -1) {
        bool isy = true;
        if (y < 5) {
            if (HeadSnakeY != y) {
                for (int i=0; i<PartsSnake.size(); i++) {
                    if (y == PartsSnake[i].first.second) {
                        isy = false;
                    }
                }
            } else isy = false;
        } else isy = false;

        if (isy) AppleY = y;
        else y = rand()%10;//uBit.random(5);
    }

    while (AppleX == -1) {
        bool isx = true;
        if (x < 5) {
            if (HeadSnakeX != x) {
                for (int i=0; i<PartsSnake.size(); i++) {
                    if (x == PartsSnake[i].first.first) {
                        isx = false;
                    }
                }
            } else isx = false;
        } else isx = false;

        if (isx) AppleX = x;
        else x = rand()%10;//uBit.random(5);
    }*/