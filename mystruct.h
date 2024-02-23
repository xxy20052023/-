#pragma once
#include<stdio.h>
#include"easyx.h"
#include"tools.h"
#include<time.h>
#include<mmsystem.h>
#include<math.h>


#define ZOOMMAX 15
#define BULLETMAX 30

struct Mouse													//��¼������
{
	int choice = 0;												//�Ƿ�ѡ������
	int choiceNumber = -1;											//ѡ�ж���
	int state = 0;												//���״̬��1Ϊ���£�0��֮
	ExMessage message;
};
struct Plant
{
	int exist = 0;												//�ж�ֲ���Ƿ����
	int type;
	int state = 0;
	int life;
	int sunCount = 0;
	int sunCNT = 100;
	int delay = 0;
};
struct Sunshine
{
	double x, y = 60;
	int exist = 0;
	int indy,indx;
	int state = 0;
};
struct Zoom
{
	int x=300, y=300;
	int state=0;
	int exist=0;
	int speed;
	int row;
	int life = 100;
	int deadState;
	int eatState;
};
struct PeaBullet
{
	int row;
	int x, y;
	int speed;
	int exist = 0;
	int state = 0;
	
};
struct IcePeaBullet
{
	int row;
	int x, y;
	int speed;
	int exist = 0;
	int state = 0;

};
enum { PEA, SUN_FLOWER,NUT,CHILI,CHERRY, ICEPEA,PLANT_COUNT };					//ȷ��ֲ������
enum {GOING,WIN,FAIL};


extern int sunnumber;
extern IMAGE imgBg;
extern IMAGE imgBar;
extern IMAGE imgCard[PLANT_COUNT];
extern IMAGE* imgPlant[PLANT_COUNT][20];
extern struct Mouse mouse;
extern struct Plant plantMap[5][9];
extern struct Sunshine sun[10];
extern IMAGE imgSun[29];
extern IMAGE imgZooms[22];
extern Zoom ZM[ZOOMMAX];
extern PeaBullet peaBullets[BULLETMAX];
extern IMAGE bullet[4];
extern IMAGE imgZoomDead[20];
extern IMAGE imgZoomEat[21];
extern IMAGE imgZoomStand[11];
extern int gameState,zoomNumber;
extern IMAGE imgWin, imgFail;
extern IMAGE imgChiliBullet;
extern IcePeaBullet icepeaBullets[BULLETMAX];
extern IMAGE icebullet[4];