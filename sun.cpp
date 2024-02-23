#include"sun.h"


void createSun()
{
	static int count = 100;
	static int num = 100;
	count++;
	if (count > num)
	{
		num = rand() % 150 + 150;
		count = 0;
		for (int i = 0; i < 10; i++)
		{
			if (sun[i].exist == 0)
			{
				sun[i].x = rand() % 640 + 260;
				sun[i].y = 0;
				sun[i].indy = (rand() % 4) * 90 + 200;
				sun[i].exist = 1;
				break;
			}
		}
	}
}
void updateSun()
{
	for (int i = 0; i < 10; i++)
	{
		if (sun[i].exist == 1)
		{
			if (sun[i].y < sun[i].indy)
				sun[i].y += 2;
			sun[i].state++;
			if (sun[i].state == 28)
				sun[i].state = 0;
		}
		else if (sun[i].exist == 2)
		{
			double th = sun[i].y / (sun[i].x - 262);
			th = atan(th);
			double vx = 20 * cos(th);
			double vy = 20 * sin(th);
			sun[i].x -= vx;
			sun[i].y -= vy;
			if (sun[i].x - 260 < 5 && sun[i].y < 5)
				sun[i].exist = 0;
			sun[i].state++;
			if (sun[i].state == 28)
				sun[i].state = 0;
		}
	}
}
void drawSun()
{
	for (int i = 0; i < 10; i++)
	{
		if (sun[i].exist)
			putimagePNG(sun[i].x, sun[i].y, &imgSun[sun[i].state]);
	}
}
void clickSun()
{
	for (int i = 0; i < 10; i++)
	{
		if (sun[i].exist == 1 && mouse.message.x > sun[i].x && mouse.message.x<sun[i].x + 79 && mouse.message.y>sun[i].y && mouse.message.y < sun[i].y + 79)
		{
			sunnumber += 25;
			sun[i].exist = 2;
			mciSendString("play res/sunshine.mp3", 0, 0, 0);
		}
	}
}
void setText()
{
	LOGFONT f;													//ÅäÖÃ×ÖÌå
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
}
void drawText()
{
	char score[8];
	sprintf_s(score, "%d", sunnumber);
	outtextxy(267, 67, score);
}
void plantSun()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (plantMap[i][j].exist == 1 && plantMap[i][j].type == 1)
			{
				plantMap[i][j].sunCount++;
				if (plantMap[i][j].sunCount > plantMap[i][j].sunCNT)
				{
					plantMap[i][j].sunCount = 0;
					plantMap[i][j].sunCNT = rand() % 100 + 100;
					for (int i = 0; i < 10; i++)
					{
						if (sun[i].exist == 0)
						{
							sun[i].indx = rand() % 60 + j * 81 + 280;
							sun[i].indy = rand() % 50 + 90 + i * 102;
							sun[i].y = 90 + i * 102;
							sun[i].x = 280 + j * 81;
							sun[i].exist = 1;
							break;
						}
					}

				}
			}
		}
	}
}
int sunCost()
{
	switch (mouse.choiceNumber)
	{
	case 0:
		return 100;
	case 1:
		return 50;
	case 2:
		return 50;
	case 3:
		return 125;
	case 4:
		return 150;
	case 5:
		return 175;
	}
}