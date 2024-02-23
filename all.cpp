#include"all.h"

void gameInit()													//对各个照片进行初始化
{
	char a[64];
	loadimage(&imgBg, "res/map0.jpg");
	loadimage(&imgBar, "res/bar5.png");
	memset(imgPlant, 0, sizeof(imgPlant));
	for (int count = 0; count < PLANT_COUNT; count++)
	{
		sprintf_s(a, sizeof(a), "res/Cards/card_%d.png", count + 1);
		loadimage(&imgCard[count], a);
		for (int i = 0; i < 20; i++)
		{
			sprintf_s(a, "res/zhiwu/%d/%d.png", count, i + 1);
			if (fileexist(a))
			{
				imgPlant[count][i] = new IMAGE;
				loadimage(imgPlant[count][i], a);
			}
			else
				break;
		}
	}
	for (int count = 0; count < 29; count++)
	{
		sprintf_s(a, "res/sunshine/%d.png", count + 1);
		loadimage(&imgSun[count], a);
	}
	setText();
	srand(time(NULL));
	zoomsInit();
	loadimage(&bullet[0], "res/bullets/PeaNormal/PeaNormal_0.png");
	loadimage(&bullet[1], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png");
	loadimage(&bullet[2], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png",bullet[0].getwidth()*1.2,bullet[0].getheight()*1.2);
	loadimage(&bullet[3], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png", bullet[0].getwidth() * 1.4, bullet[0].getheight() * 1.4);
	for (int count = 0; count < 20; count++)
	{
		sprintf_s(a, "res/zm_dead/%d.png", count + 1);
		loadimage(&imgZoomDead[count], a);
	}
	for (int count = 0; count < 20; count++)
	{
		sprintf_s(a, "res/zm_eat/%d.png", count + 1);
		loadimage(&imgZoomEat[count], a);
	}
	loadimage(&imgWin, "res/win.png");
	loadimage(&imgFail, "res/fail2.png");
	loadimage(&imgChiliBullet, "res/bullets/JalapenoAttack.gif");
	loadimage(&icebullet[0], "res/bullets/PeaIce/PeaIce_0.png");
	loadimage(&icebullet[1], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png");
	loadimage(&icebullet[2], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png", bullet[0].getwidth() * 1.2, bullet[0].getheight() * 1.2);
	loadimage(&icebullet[3], "res/bullets/PeaNormalExplode/PeaNormalExplode_0.png", bullet[0].getwidth() * 1.4, bullet[0].getheight() * 1.4);
}
void updateWin()												//绘出各个照片
{
	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);
	for (int count = 0; count < PLANT_COUNT; count++)			//绘出任务栏
	{
		int x = 338 + count * 64;
		putimagePNG(x, 6, &imgCard[count]);
	}
	plantDraw();

	if (mouse.choice == 1 && mouse.choiceNumber != -1)										//画出选择植物
	{
		IMAGE* img = imgPlant[mouse.choiceNumber][0];
		putimagePNG(mouse.message.x - img->getwidth() / 2, mouse.message.y - img->getheight() / 2, img);
	}
	drawSun();
	drawText();
	zoomsDraw();
	peaBulletDraw();
	icepeaBulletDraw();
	chiliBurn();
	cherryBurn();
	if (gameState == WIN)
	{
		putimage(0, 0, &imgWin);
		mciSendString("play res/win.mp3", 0, 0, 0);



	}
	if (gameState == FAIL)
	{
		putimage(0, 0, &imgFail);

		mciSendString("play  res/lose.mp3", 0, 0, 0);


	}
}
void userClick()												//玩家操作
{
	peekmessage(&mouse.message);
	if (mouse.message.message == WM_LBUTTONDOWN)
	{
		mouse.state = 1;
	}
	if (mouse.message.message == WM_LBUTTONUP && mouse.state == 1)										//判断玩家是否点击
	{

		if (mouse.message.y < 96 && mouse.message.x < 338 + 65 * PLANT_COUNT)		//选择植物	
		{
			
			mouse.choiceNumber = (mouse.message.x - 338) / 64;
			if (sunnumber >= sunCost())
			{
				mouse.choice = 1;
				sunnumber -= sunCost();
			}
		}
		else if (mouse.message.y > 67 && mouse.message.y < 591 && mouse.message.x>256)			//种植植物
		{

			int row = (mouse.message.y - 67) / 102;
			int col = (mouse.message.x - 256) / 81;
			if (plantMap[row][col].exist == 0 && mouse.choice == 1)
			{
				mciSendString("play res/audio/plant1.mp3",0,0,0);
				plantMap[row][col].type = mouse.choiceNumber;
				plantMap[row][col].exist = 1;
				plantMap[row][col].life = plantLife(plantMap[row][col].type);
			}
			mouse.choice = 0;
		}

		if (mouse.choice == 0)
		{
			clickSun();
		}
		mouse.state = 0;
	}
}
void startMenu()
{
	IMAGE imgBg, imgMenu1, imgMenu2;
	loadimage(&imgBg, "res/menu.png");
	loadimage(&imgMenu1, "res/menu1.png");
	loadimage(&imgMenu2, "res/menu2.png");

	int is = 0;
	ExMessage msg;
	LARGE_INTEGER startcount, endcount, F;
	long long timetake;
	QueryPerformanceFrequency(&F);
	timeBeginPeriod(1);
	BeginBatchDraw();
	while (1)
	{
		QueryPerformanceCounter(&startcount);

		//具体执行游戏过程
		cleardevice();
		is = 0;
		peekmessage(&msg);
		if (msg.x > 474 && msg.x < 774 && msg.y>75 && msg.y < 215)
			is = 1;
		putimage(0, 0, &imgBg);
		putimagePNG(474, 75, is ? &imgMenu2 : &imgMenu1);
		if (is == 1 && msg.message == WM_LBUTTONDOWN)
			break;



		FlushBatchDraw();
		QueryPerformanceCounter(&endcount);
		timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		while (timetake < 30)
		{
			peekmessage(&msg);
			Sleep(1);
			QueryPerformanceCounter(&endcount);
			timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		}
	}

	EndBatchDraw();
	timeEndPeriod(1);
}
void updateinf()
{
	createSun();
	plantSun();
	updateSun();
	zoomsCreate();
	zoomsUpdate();
	peaBulletGenerate();
	icepeaBulletGenerate();
	peaBulletUpdate();
	icepeaBulletUpdate();
	peaBulletOut();
	icepeaBulletOut();
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist == 2)
			ZM[count].exist = 1;
	}
	peaBulletHit();
	icepeaBulletHit();
	plantUpdate();
	zoomEat();
}
void updateinf2()
{
	
}
void viewScene()
{
	LARGE_INTEGER startcount, endcount, F;
	long long timetake;
	int Sx = -2,is=0,CNT=0,Count=0, zoomPosition[9][2] = { {1050,80},{1030,160},{1130,170},{1030,200},{1015,270},{1065,370},{1105,340},{1205,280},{1190,340} };
	QueryPerformanceFrequency(&F);
	timeBeginPeriod(1);
	BeginBatchDraw();
	while (1)
	{
		QueryPerformanceCounter(&startcount);

		//具体执行游戏过程
		cleardevice();
		if (is == 0&&Sx>-500)
		{
			Sx -= 6;
			for (int count = 0; count < 9; count++)
			{
				zoomPosition[count][0] -= 6;
			}
		}
		if (Sx <=-500)
			is = 1;
		if (is == 1)
			Count++;
		if (is==1&&Count>30)
		{
			Sx += 6;
			for (int count = 0; count < 9; count++)
			{
				zoomPosition[count][0] += 6;
			}
		}
		if (Sx > 0)
			break;
		putimage(Sx, 0, &imgBg);
		CNT++;
		for (int count = 0; count < 9; count++)
		{
			
			putimagePNG(zoomPosition[count][0], zoomPosition[count][1], &imgZoomStand[CNT]);
			
		}
		if (CNT == 10)
			CNT = 0;


		FlushBatchDraw();
		QueryPerformanceCounter(&endcount);
		timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		while (timetake < 30)
		{
			Sleep(1);
			QueryPerformanceCounter(&endcount);
			timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		}
	}

	EndBatchDraw();
	timeEndPeriod(1);
}
void gameEnd()
{
	if (zoomNumber == 15)
	{
		int is = 0;
		for (int count = 0; count < ZOOMMAX; count++)
		{
			if (ZM[count].exist == 1)
			{
				is = 1;
			}
		}
		if (is == 0)
			gameState = WIN;

	}
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist == 1 && ZM[count].x < 56)
			gameState = FAIL;
	}
	
}
