
#include"mystruct.h"
#include"sun.h"
#include"all.h"



;




int main()
{
	
	initgraph(900, 600);
	gameInit();
	mciSendString("play res/audio/plantsgarden.mp3 repeat",0,0,0);
	startMenu();
	viewScene();
	mciSendString("close res/audio/plantsgarden.mp3",0,0,0);

	mciSendString("play res/bg.MP3 repeat", 0, 0, 0);
	LARGE_INTEGER startcount, endcount, F;
	long long timetake;
	QueryPerformanceFrequency(&F);
	timeBeginPeriod(1);
	BeginBatchDraw();
	while (1)
	{
		QueryPerformanceCounter(&startcount);

		//����ִ����Ϸ����
		cleardevice();
		
		userClick();
		updateinf();
		gameEnd();
		updateWin();
		
		
		


		FlushBatchDraw();
		QueryPerformanceCounter(&endcount);
		timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		while (timetake < 50)																	//�̶�֡��
		{
			peekmessage(&mouse.message);
			Sleep(1);
			QueryPerformanceCounter(&endcount);
			timetake = 1000 * (endcount.QuadPart - startcount.QuadPart) / F.QuadPart;
		}


		if (gameState)
		{
			mciSendString("close res/bg.MP3", 0, 0, 0);
			Sleep(5000);
			exit(0);
		}
	}

	EndBatchDraw();
	timeEndPeriod(1);
}
