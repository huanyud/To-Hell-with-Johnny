/*��Ϸ��ʼ*/

#include <graphics.h>
#include <conio.h>


DrawMainMenu()
{
  int graphdriver = VGA;
  int graphmode = VGAHI;

  /*ͼ�γ�ʼ��*/
  initgraph(&graphdriver,&graphmode,"f:\\tc"); 
  cleardevice();
  setbkcolor(BLACK);

  /*������Ϸ����*/
  setcolor(BROWN);      
  settextstyle(4,HORIZ_DIR,8);
  outtextxy(55,19,"Hundred Layers");


  /*��Ϸ������˵��*/
  setcolor(WHITE);      
  settextstyle(2,HORIZ_DIR,6);
  outtextxy(490,455,"No.3080030167");
  hanzi("������",480,430);
  hanzi("�����",550,430);


  /*������Ϸѡ��*/
  setfillstyle(1,BLUE); 
  setcolor(YELLOW);
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
  settextjustify(1,1);
  outtextxy(300,155,"New  Game (N)");
  outtextxy(300,155+(374-155)/3,"Load Game (L)");
  outtextxy(300,155+(374-155)*2/3,"Help (H)");
  outtextxy(300,374,"Exit (Esc or Q)");
}

MenuChoice()
{
  while(1)
  {
    key = 0;
    key = bioskey(0);
    switch(key)
    {
      case ENTER: case LOWERN: case UPPERN: StartGame(0);break;
      case LOWERL: case UPPERL: StartGame(1);break;
      case UPPERH: case LOWERH: case F1: Help(); break;
      case ESC: case UPPERQ: case LOWERQ: Byebye();break;
      default: break;
    }  
  } 
}