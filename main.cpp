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
   float w_;
   float h_;
   HDC image;
   bool visible;
   int v;

    void draw()
    {
        if (visible)
        {
            Win32::TransparentBlt(txDC(), x, y, w_, h_, image, 0, 0, w, h, TX_WHITE);
        }
    }
};

struct Button
{
    int x;
    int y;
    int w;
    int h;
    const char* text;
    bool visible;

    void draw()
    {
        txSetColor (TX_WHITE, 3);
        txSetFillColor (TX_YELLOW);
        Win32::RoundRect (txDC(), x, y, x+w, y+h, 30, 30);
        txSelectFont("Times New Roman", 30);
        txSetColor (TX_RED);
        txDrawText(x, y, x+w, y+h, text);
    }

    bool click()
    {
        return(txMouseX()>x && txMouseX()<x+w &&
                txMouseY()>y && txMouseY()<y+h &&
                txMouseButtons() == 1 && visible);
    }
};

int main()
{
txCreateWindow (800, 600);
txTextCursor (false);

string PAGE = "menu";

Button btn0 = {100, 100, 200, 40, "�����", true};
Button btn1 = {100, 150, 200, 40, "������� ����", true};
Button btn2 = {100, 200, 200, 40, "�����", true};
Button btn3 = {0, 0, 200, 40, "�����", true};

HDC menu_image = txLoadImage("Pictures/menu_image.bmp");
HDC fon = txLoadImage("Pictures/Sea.bmp");

Submarine sub = {300, txLoadImage("Pictures/sub.bmp")};
Ship ship1 = {-150, 230, 300, 93, 100, 31, txLoadImage("Pictures/ship.bmp"), true};
Torpeda torpeda = {sub.x+100, 560, 25, 100, 25, 100, txLoadImage("Pictures/torpeda.bmp"), false, 0};


    while(!btn2.click())
    {

        txBegin();
        txClear();

        if(PAGE == "menu")
        {
            txBitBlt(txDC(), 0, 60, 800, 480, menu_image);

            btn0.draw();
            btn1.draw();
            btn2.draw();

            btn2.visible = true;

            if(btn0.click())
            {
                PAGE = "game";
            }

            if(btn1.click())
            {
                PAGE = "rules";
            }

            txSetFillColor (TX_BLACK);
        }

        if(PAGE == "rules")
        {
            btn3.draw();
            if(btn3.click())
            {
                PAGE = "menu";
            }
            btn2.visible = false;

            txSelectFont("Times New Roman", 50);
            txSetColor (TX_RED);
            txDrawText(0, 0, 800, 200, "������� ����");
            txSelectFont("Times New Roman", 19);
            txDrawText(0, 200, 800, 600,    "����� ������� ������� ������ ����� ������� �� ���������,\n"
                                            "������ ����������� ����, ������� ���������� ����� ����� ��������� �������� ��� ������ �������,\n"
                                            "�� �������� ���������� ������ ���������� ��������� �����, ������� � 1 � ������ ���������� �����,\n"
                                            "����������� �������� ���� � ���������� ��� �������� ���������; ������������ �������� ������� 1�3 ���.,\n"
                                            "����������� ������ ������ �������,\n"
                                            "��� ������ ��������� ������� � ����:\n"
                                            "\n"
                                            "�������������� �������� � �������� �������� ������; ������������ �������� �������� 1�3 ���.,\n"
                                            "����������� ��������� ��������,\n"
                                            "�� �������� ���������� ����� ���������� ��������� �����, ������� � 1, � ������ ����������,\n"
                                            "���� (������ �������) ������ ����������� ��������, ����� ���� ��������� �������� ���������� �����,\n"
                                            "����� ������� ��������� ���������� � ������� ������������ ����������� �������������.\n"
                                            "������������ ���������� �������, ���������� �� ���� ����� ���� ���������� 10 ��.");

            txSetFillColor (TX_YELLOW);
        }

        if(PAGE == "game")
        {
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
                torpeda.w_ = 25;
                torpeda.h_ = 100;
            }
            if(torpeda.v != 0)
            {
                torpeda.y = torpeda.y - torpeda.v;
                torpeda.w_ -= 0.1;
                torpeda.h_ -= 1;
            }

            if(torpeda.y < 250)
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

            btn3.draw();
            if(btn3.click())
            {
                PAGE = "menu";
            }
            btn2.visible = false;

            txSetFillColor (TX_BLACK);
        }


        txEnd();
        txSleep(10);

    }

txDeleteDC(fon);

txDisableAutoPause();
return 0;
}

