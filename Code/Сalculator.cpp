#include "MicroBit.h"
#include "samples/Tests.h"

MicroBit uBit;

int main()
{
    uBit.init();

    int a, b, m = 1, answer, n = 0, o = 0, t = 0;
    uBit.display.print("0");
    while (true)
    {
        if (uBit.buttonA.isPressed())
        {
            if (o == 0 || o == 2) {
                n--;
                if (n > -1 && n < 10) uBit.display.print(n);
                else uBit.display.scroll(n);
            } else if (o == 1) {
                if (m > 1) m--;
                switch (m) {
                    case 1:
                        uBit.display.print("+");
                        break;
                    case 2:
                        uBit.display.print("-");
                        break;
                    case 3:
                        uBit.display.print("/");
                        break;
                    case 4:
                        uBit.display.print("*");
                        break;
                }

            }
        }
        if (uBit.buttonB.isPressed())
        {
            if (o == 0 || o == 2) {
                n++;
                if (n > -1 && n < 10) uBit.display.print(n);
                else uBit.display.scroll(n);
            } else if (o == 1) {
                if (m < 4) m++;
                switch (m) {
                    case 1:
                        uBit.display.print("+");
                        break;
                    case 2:
                        uBit.display.print("-");
                        break;
                    case 3:
                        uBit.display.print("/");
                        break;
                    case 4:
                        uBit.display.print("*");
                        break;
                }
            }
        }
        if (uBit.buttonAB.isPressed() && t >= 3)
        {
            if (o == 0) {
                a = n;
                uBit.display.print("+");
            } else if (o == 1) {
                uBit.display.print("0");
            } else if (o == 2) {
                b = n;
            } else if (o == 3)
            {
                break;
            }
            n = 0;
            o++;
            t = 0;
        }
        uBit.sleep(200);
        t++;
    }
    uBit.display.clear();
    switch (m) {
        case 1:
            answer = a + b;
            break;
        case 2:
            answer = a - b;
            break;
        case 3:
            answer = a / b;
            break;
        case 4:
            answer = a * b;
            break;
    }
    if (answer > -1 && answer < 10) uBit.display.print(answer);
    else uBit.display.scroll(answer);
    release_fiber();
}