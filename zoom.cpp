#include"zoom.h"

void zoomsInit()
{
	char name[64];
	for (int count = 0; count < 22; count++)
	{
		sprintf_s(name, "res/zm/%d.png", count + 1);
		loadimage(&imgZooms[count], name);
	}
	for (int count = 0; count < 21; count++)
	{
		sprintf(name, "res/zm_eat/%d.png", count + 1);
	}
	for (int count = 0; count < 11; count++)
	{
		sprintf_s(name,"res/zm_stand/%d.png",count+1);
		loadimage(&imgZoomStand[count], name);
	}
}
void zoomsCreate()
{
	static int zmcount = 0;
	static int zmnumber = 400;
	zmcount++;
	if (zmcount == 400)
	{
		mciSendString("play res/audio/awooga.mp3", 0, 0, 0);
	}
	if (zmcount > zmnumber&&zoomNumber<15)
	{
		zmnumber = rand() % 200 + 50;
		zmcount = 0;
		for (int count = 0; count < ZOOMMAX; count++)
		{
			if (ZM[count].exist == 0)
			{
				zoomNumber++;
				ZM[count].exist = 1;
				ZM[count].x = 900;
				ZM[count].row = rand() % 5 ;
				ZM[count].y = ZM[count].row * 100;
				ZM[count].speed = 2;
				ZM[count].deadState = 0;
				ZM[count].life = 200;
				ZM[count].eatState = 0;
				break;
			}
		}
	}
}
void zoomsUpdate()
{
	for (int i = 0; i < ZOOMMAX; i++)
	{
		if (ZM[i].exist)
		{
			if (ZM[i].life > 0 && ZM[i].exist == 1)
			{
				ZM[i].x -= ZM[i].speed;
				ZM[i].state++;
				if (ZM[i].state == 22)
					ZM[i].state = 0;
			}
			else if (ZM[i].exist == 2 && ZM[i].life > 0)
			{
				ZM[i].eatState++;
				if (ZM[i].eatState == 19)
				{
					ZM[i].eatState = 0;
				}
			}
			else
			{
				ZM[i].deadState++;
				if (ZM[i].deadState == 19)
				{
					ZM[i].exist = 0;
				}
			}
		}
	}
}
void zoomsDraw()
{
	for (int i = 0; i < ZOOMMAX; i++)
	{
		if (ZM[i].exist)
		{
			if (ZM[i].life > 0 && ZM[i].exist == 1)
				putimagePNG(ZM[i].x, ZM[i].y, &imgZooms[ZM[i].state]);
			else if (ZM[i].life <=0)
				putimagePNG(ZM[i].x, ZM[i].y, &imgZoomDead[ZM[i].deadState]);
			else
			{
				putimagePNG(ZM[i].x, ZM[i].y, &imgZoomEat[ZM[i].eatState]);
			}
		}

	}
}
void zoomEat()
{
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist)
		{
			for (int i = 0; i < 9; i++)
			{
				if (plantMap[ZM[count].row][i].exist && 200+81*i > ZM[count].x - 30&&200+81*i<ZM[count].x)
				{
					ZM[count].exist = 2;
					if (ZM[count].eatState == 18)
					{
						plantMap[ZM[count].row][i].life -= 20;
						mciSendString("play res/audio/chomp.mp3", 0, 0, 0);
					}
				}
			}
		}
	}
}