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
   bool visible;

    void draw()
    {
        if (visible)
        {
            Win32::TransparentBlt(txDC(), x, y, w_scr, h_scr, image, 0, 0, w, h, TX_WHITE);
        }
    }
};

struct Torpeda
{
   int x;
   int y;
   int w;
   int h;
   HDC image;
   bool visible;
   int v;

    void draw()
    {
        if (visible)
        {
            Win32::TransparentBlt(txDC(), x, y, 25, 100, image, 0, 0, w, h, TX_WHITE);
        }
    }
};

int main()
{
txCreateWindow (800, 600);
txTextCursor (false);

HDC fon = txLoadImage("Pictures/Sea.bmp");

Submarine sub = {300, txLoadImage("Pictures/sub.bmp")};
Ship ship1 = {-150, 230, 300, 93, 100, 31, txLoadImage("Pictures/ship.bmp"), true};
Torpeda torpeda = {sub.x+100, 560, 25, 100, txLoadImage("Pictures/torpeda.bmp"), false, 0};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {

        txBegin();
        txClear();

        txSetFillColor (TX_BLACK);

        txBitBlt(txDC(), 0, 0, 800, 600, fon);
        ship1.draw();
        torpeda.draw();
        sub.draw();

        if(GetAsyncKeyState(VK_RIGHT))
        {
            sub.x += 5;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            sub.x -= 5;
        }

        ship1.x += 2;

        if(GetAsyncKeyState(VK_SPACE))
        {
            torpeda.x = sub.x+100;
            torpeda.visible = true;
            torpeda.v = 5;
        }

        torpeda.y = torpeda.y - torpeda.v;

        if(torpeda.y < -200)
        {
            torpeda.visible = false;
            torpeda.v = 0;
            torpeda.y = 560;
        }


        if( torpeda.x>ship1.x && torpeda.x+25<ship1.x+ship1.w_scr &&
            torpeda.y<ship1.y+ship1.h_scr)
        {
            torpeda.visible = false;
            ship1.visible = false;
            torpeda.v = 0;
            torpeda.y = 560;
        }





        txEnd();
        txSleep(10);

    }

txDeleteDC(fon);

txDisableAutoPause();
return 0;
}

