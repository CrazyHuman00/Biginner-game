//ボールをお互いに弾いて対決するゲーム。人数２人用。ぼっちプレイも可。
//左右画面端が互いのゴールとなっており、左側（青パドル）はW（=上）S（=下）、
//右側（赤パドル）はO（=上）K（=下）で動かしボールがゴールされないように弾いていく。
//2個ボールがあるのでなかなか難しく、初期スピードは配列と乱数でランダムに決められる。
//たまにパドルの当たり判定がおかしくなることがある。

#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include <time.h>

#define WINDOWSIZEX (1000)
#define WINDOWSIZEY (600)
#define BALLRADIUS (20)
#define PADDLESIZEX (5)
#define PADDLESIZEY (80)

int main(void)
{
  HgOpen(WINDOWSIZEX, WINDOWSIZEY);

  int i, j, k, l, m;

  srand(time(NULL));
  for (k = 0; k < 1; k++)
  {
    i = rand() % 9;
    j = rand() % 9;
    l = rand() % 9;
  }

  int t = 5;
  double circlespeedarray[10] = {1, 1.5, 2, 2.5, 3, -1, -1.5, -2, -2.5, -3}; //スピード配列
  int firstcxv = circlespeedarray[i];                                       //ボール１の速さx
  int firstcyv = circlespeedarray[j];                                       //ボール１の速さy
  int secondcxv = circlespeedarray[l];                                      //ボール２の速さ
  int secondcyv = circlespeedarray[i];                                      //ボール２の速さ
  int firstcirclex = 400;                                                   //ボール１のx座標
  int firstcircley = WINDOWSIZEY / 2;                                       //ボール１のy座標
  int secondcirclex = 600;                                                  //ボール２のx座標
  int secondcircley = WINDOWSIZEY / 2;                                      //ボール２のy座標

  int firstpaddlex = 0;    //左青パドルのx
  int firstpaddley = 250;  //左青パドルのy
  int secondpaddlex = 995; //右赤パドルのx
  int secondpaddley = 250; //右赤パドルのy
  int thirdpaddlex = 498;  //中央パドルのx
  int thirdpaddley = 1;    //中央パドルのy
  int paddlefirstv = 0;    //左青パドルの速さ
  int paddlesecondv = 0;   //右赤パドルの速さ
  int paddlethirdv = 3;    //中央パドルの速さ

  int imgone = HgImageLoad("image.jpeg");
  int imgtwo = HgImageLoad("sky.jpeg");

  HgImagePut(200, 400, imgone, 0.8, 0);
  HgSetColor(HG_WHITE);
  HgSetFont(HG_CI, 60);
  HgText(300, 400, "BATTLEGAME");
  HgSetFont(HG_C, 60);
  HgText(135, 270, "キーボードタップでスタート");
  HgSetColor(HG_YELLOW);
  HgText(50, 500, "W↑");
  HgText(50, 50, "S↓");
  HgText(900, 500, "↑O");
  HgText(900, 50, "↓K");

  doubleLayer layers;
  layers = HgWAddDoubleLayer(0);
  HgSetEventMask(HG_KEY_EVENT_MASK);
  hgevent *e;

  HgGetChar();
  HgClear();

  HgImagePut(500, 250, imgtwo, 0.5, 0);
  HgSetAlarmTimer(t);

  for (;;)
  {

    int lid = HgLSwitch(&layers);
    HgLClear(lid);

    HgWSetFillColor(lid, HG_BLUE);
    HgWBoxFill(lid, firstpaddlex, firstpaddley, PADDLESIZEX, PADDLESIZEY, 0);
    HgWSetFillColor(lid, HG_RED);
    HgWBoxFill(lid, secondpaddlex, secondpaddley, PADDLESIZEX, PADDLESIZEY, 0);
    HgWSetFillColor(lid, HG_PURPLE);
    HgWBoxFill(lid, thirdpaddlex, thirdpaddley, PADDLESIZEX, 100, 0);

    HgWSetFillColor(lid, HG_YELLOW);
    HgWCircleFill(lid, firstcirclex, firstcircley, BALLRADIUS, 0);
    HgWSetFillColor(lid, HG_GREEN);
    HgWCircleFill(lid, secondcirclex, secondcircley, BALLRADIUS, 0);

    e = HgEventNonBlocking();

    if (e != NULL)
    {
      if (e->type == HG_KEY_DOWN)
      {
        if (e->ch == 'w')
        {
          paddlefirstv = 6;
        }
      }
      else if (e->type == HG_KEY_UP)
      {
        if (e->ch == 'w')
        {
          paddlefirstv = 0;
        }
      }

      if (e->type == HG_KEY_DOWN)
      {
        if (e->ch == 's')
        {
          paddlefirstv = -6;
        }
      }
      else if (e->type == HG_KEY_UP)
      {
        if (e->ch == 's')
        {
          paddlefirstv = 0;
        }
      }

      if (e->type == HG_KEY_DOWN)
      {
        if (e->ch == 'o')
        {
          paddlesecondv = 6;
        }
      }
      else if (e->type == HG_KEY_UP)
      {
        if (e->ch == 'o')
        {
          paddlesecondv = 0;
        }
      }

      if (e->type == HG_KEY_DOWN)
      {
        if (e->ch == 'k')
        {
          paddlesecondv = -6;
        }
      }
      else if (e->type == HG_KEY_UP)
      {
        if (e->ch == 'k')
        {
          paddlesecondv = 0;
        }
      }
    }

    if (firstcircley + BALLRADIUS >= WINDOWSIZEY || firstcircley <= BALLRADIUS)
    {
      firstcyv = -firstcyv;
    }

    if (secondcircley + BALLRADIUS >= WINDOWSIZEY || secondcircley <= BALLRADIUS)
    {
      secondcyv = -secondcyv;
    }

    if (firstcirclex - BALLRADIUS <= firstpaddlex + PADDLESIZEX + 2 && firstpaddley <= firstcircley + BALLRADIUS + 2 && firstpaddley + PADDLESIZEY >= firstcircley - BALLRADIUS - 2)
    {
      firstcxv = -firstcxv;
    }

    if (firstcirclex + BALLRADIUS + 2 >= secondpaddlex && secondpaddley <= firstcircley + BALLRADIUS + 2 && secondpaddley + PADDLESIZEY >= firstcircley - BALLRADIUS - 2)
    {
      firstcxv = -firstcxv;
    }

    if (secondcirclex - BALLRADIUS <= firstpaddlex + PADDLESIZEX + 2 && firstpaddley <= secondcircley + BALLRADIUS + 2 && firstpaddley + PADDLESIZEY >= secondcircley - BALLRADIUS - 2)
    {
      secondcxv = -secondcxv;
    }

    if (secondcirclex + BALLRADIUS + 2 >= secondpaddlex && secondpaddley <= secondcircley + BALLRADIUS + 2 && secondpaddley + PADDLESIZEY >= secondcircley - BALLRADIUS - 2)
    {
      secondcxv = -secondcxv;
    }

    if (thirdpaddley + PADDLESIZEY >= WINDOWSIZEY || thirdpaddley <= 0)
    {
      paddlethirdv = -paddlethirdv;
    }

    if (firstcirclex + BALLRADIUS + 2 >= thirdpaddlex && firstcirclex - BALLRADIUS - 2 <= thirdpaddlex + PADDLESIZEX)
    {
      if (thirdpaddley <= firstcircley + BALLRADIUS + 1 && thirdpaddley + PADDLESIZEY >= firstcircley - BALLRADIUS - 1)
      {
        firstcxv = -firstcxv;
      }
    }

    if (secondcirclex + BALLRADIUS + 2>= thirdpaddlex && secondcirclex - BALLRADIUS - 2 <= thirdpaddlex + PADDLESIZEX)
    {
      if (thirdpaddley <= secondcircley + BALLRADIUS + 1 && thirdpaddley + PADDLESIZEY >= secondcircley - BALLRADIUS - 1)
      {
        secondcxv = -secondcxv;
      }
    }

    if (firstcirclex >= thirdpaddlex && firstcirclex <= thirdpaddlex + PADDLESIZEX)
    {
      if(firstcircley + BALLRADIUS + 1 >= thirdpaddley && thirdpaddley + 100 >= firstcircley - BALLRADIUS - 1)
      {
        paddlethirdv = -paddlethirdv;
      }
    }

    if (secondcirclex >= thirdpaddlex && secondcirclex <= thirdpaddlex + PADDLESIZEX )
    {
      if( secondcircley + BALLRADIUS + 1 >= thirdpaddley && thirdpaddley + 100 >= secondcircley - BALLRADIUS - 1)
      {
        paddlethirdv = -paddlethirdv;
      }
    }

    if (firstcirclex - BALLRADIUS < 0 || secondcirclex - BALLRADIUS < 0)
    {
      firstcxv = 0;
      firstcyv = 0;
      secondcxv = 0;
      secondcyv = 0;

      paddlefirstv = 0;
      paddlesecondv = 0;
      paddlethirdv = 0;

      HgWSetFont(lid, HG_C, 80);
      HgWSetColor(lid, HG_RED);
      HgWText(lid, 350, 270, "REDWIN");
    }

    if (firstcirclex + BALLRADIUS > WINDOWSIZEX || secondcirclex + BALLRADIUS > WINDOWSIZEX)
    {
      firstcxv = 0;
      firstcyv = 0;
      secondcxv = 0;
      secondcyv = 0;

      paddlefirstv = 0;
      paddlesecondv = 0;
      paddlethirdv = 0;

      HgWSetFont(lid, HG_C, 80);
      HgWSetColor(lid, HG_BLUE);
      HgWText(lid, 330, 270, "BLUEWIN");
    }

    firstcirclex += firstcxv;
    firstcircley += firstcyv;

    secondcirclex += secondcxv;
    secondcircley += secondcyv;

    firstpaddley += paddlefirstv;
    secondpaddley += paddlesecondv;
    thirdpaddley += paddlethirdv;

    HgSleep(0.01);
  }

  HgClose();
  return 0;
}