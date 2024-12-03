#include "TXLib.h"

struct Submarine
{
     int x;
     HDC image;

     void draw()
     {
         txTransparentBlt(txDC(), x, 560, 200, 37, image, 0, 0, TX_WHITE);
     }
};

struct Ship
{
   int x;
   int y;
   int w;
   int h;
   int w_scr;
   int h_scr;
   HDC image;

    void draw()
    {
        Win32::TransparentBlt(txDC(), x, y, w_scr, h_scr, image, 0, 0, w, h, TX_WHITE);
    }
};



int main()
{
txCreateWindow (800, 600);
txTextCursor (false);

HDC fon = txLoadImage("Pictures/Sea.bmp");

Submarine sub = {300, txLoadImage("Pictures/sub.bmp")};
Ship ship1 = {-150, 230, 300, 93, 100, 31, txLoadImage("Pictures/ship.bmp")};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {

        txBegin();
        txClear();

        txSetFillColor (TX_BLACK);

        txBitBlt(txDC(), 0, 0, 800, 600, fon);
        sub.draw();
        ship1.draw();

        if(GetAsyncKeyState(VK_RIGHT))
        {
            sub.x += 5;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            sub.x -= 5;
        }

        ship1.x += 2;



        txEnd();
        txSleep(10);

    }

txDeleteDC(fon);

txDisableAutoPause();
return 0;
}

