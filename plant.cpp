#include"plant.h"

void plantDraw()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (plantMap[i][j].exist == 1)
			{
				
					
					if (imgPlant[plantMap[i][j].type][plantMap[i][j].state] == NULL)
						plantMap[i][j].state = 0;
					putimagePNG(256 + j * 81, 67 + i * 102, imgPlant[plantMap[i][j].type][plantMap[i][j].state]);
					if (plantMap[i][j].delay == 0)
					{
						plantMap[i][j].state++;
						plantMap[i][j].delay++;
					}
					
					else
					{
						plantMap[i][j].delay = 0;
					}

				
			}
		}
	}
}
void peaBulletGenerate()
{
	
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist )
		{
			for (int i = 0; i < 9; i++)
			{
				if (plantMap[ZM[count].row][i].exist == 1&&256+i*81<ZM[count].x && plantMap[ZM[count].row][i].type == 0 && plantMap[ZM[count].row][i].state == 2&& plantMap[ZM[count].row][i].delay==0)
				{
					for (int j = 0; j < BULLETMAX; j++)
					{
						if (peaBullets[j].exist == 0)
						{
							peaBullets[j].state = 0;
							peaBullets[j].row = ZM[count].row;
							peaBullets[j].exist = 1;
							peaBullets[j].x = 310 + i * 81;
							peaBullets[j].y = 80 + ZM[count].row * 102;
							peaBullets[j].speed = 5;
							break;
						}
					}
				}
			}
		}
	}
}
void peaBulletUpdate()
{
	for (int count = 0; count < BULLETMAX; count++)
	{
		if (peaBullets[count].exist)
		{
			peaBullets[count].x += peaBullets[count].speed;
			if (peaBullets[count].state != 0)
			{
				peaBullets[count].state++;
				if (peaBullets[count].state == 4)
				{
					peaBullets[count].state = 0;
					peaBullets[count].exist = 0;
				}
			}
		}
	}
}
void peaBulletDraw()
{
	
	for (int count = 0; count < BULLETMAX; count++)
	{
		if (peaBullets[count].exist)
		{
			putimagePNG(peaBullets[count].x, peaBullets[count].y, &bullet[peaBullets[count].state]);
		}
	}
}
void peaBulletOut()
{
	for (int count = 0; count < BULLETMAX; count++)
	{
		if (peaBullets[count].x > 900 && peaBullets[count].exist == 1)
		{
			peaBullets[count].exist = 0;
		}
	}
}
void peaBulletHit()
{
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist )
		{
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (peaBullets[i].x > ZM[count].x + 50 && peaBullets[i].state == 0 && peaBullets[i].row == ZM[count].row && peaBullets[i].x < ZM[count].x + 100)
				{
					peaBullets[i].state = 1;
					ZM[count].life -= 15;
				}
			}
		}
	}
}
void plantUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (plantMap[i][j].exist == 1 && plantMap[i][j].life < 0)
			{
				plantMap[i][j].exist = 0;
			}
		}
	}
}
int plantLife(int type)
{
	switch (type)
	{
		case 0:
			return 100;
		case 1:
			return 60;
		case 2:
			return 200;
		case 3:
			return 100;
		case 4:
			return 100;
		case 5:
			return 100;
	}
}
void chiliBurn()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (plantMap[i][j].exist == 1 && plantMap[i][j].type == 3 && plantMap[i][j].state == 8)
			{
				plantMap[i][j].exist = 0;
				putimagePNG(256, 100*i, &imgChiliBullet);
				for (int count = 0; count < ZOOMMAX; count++)
				{
					if (ZM[count].exist == 1&&ZM[count].row==i)
					{
						ZM[count].life -= 400;
					}
				}
			}
		}
	}
}
void cherryBurn()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (plantMap[i][j].exist == 1 && plantMap[i][j].type == 4 && plantMap[i][j].state == 8)
			{
				plantMap[i][j].exist = 0;
				mciSendString("play res/audio/cherrybomb.mp3", 0, 0, 0);
				for (int count = 0; count < ZOOMMAX; count++)
				{
					if (ZM[count].exist == 1&&(ZM[count].row==i+1||ZM[count].row==i||ZM[count].row==i-1)&&ZM[count].x<j*81+450&&ZM[count].x>j*81+100)
					{
						ZM[count].life -= 400;
						
					}
				}
			}
		}
	}
}

void icepeaBulletGenerate()
{

	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist)
		{
			for (int i = 0; i < 9; i++)
			{
				if (plantMap[ZM[count].row][i].exist == 1 && 256 + i * 81 < ZM[count].x && plantMap[ZM[count].row][i].type == 5 && plantMap[ZM[count].row][i].state == 4 && plantMap[ZM[count].row][i].delay == 0)
				{
					for (int j = 0; j < BULLETMAX; j++)
					{
						if (icepeaBullets[j].exist == 0)
						{
							icepeaBullets[j].state = 0;
							icepeaBullets[j].row = ZM[count].row;
							icepeaBullets[j].exist = 1;
							icepeaBullets[j].x = 310 + i * 81;
							icepeaBullets[j].y = 80 + ZM[count].row * 102;
							icepeaBullets[j].speed = 5;
							break;
						}
					}
				}
			}
		}
	}
}
void icepeaBulletUpdate()
{
	for (int count = 0; count < BULLETMAX; count++)
	{
		if (icepeaBullets[count].exist)
		{
			icepeaBullets[count].x += icepeaBullets[count].speed;
			if (icepeaBullets[count].state != 0)
			{
				icepeaBullets[count].state++;
				if (icepeaBullets[count].state == 4)
				{
					icepeaBullets[count].state = 0;
					icepeaBullets[count].exist = 0;
				}
			}
		}
	}
}
void icepeaBulletDraw()
{

	for (int count = 0; count < BULLETMAX; count++)
	{
		if (icepeaBullets[count].exist)
		{
			putimagePNG(icepeaBullets[count].x, icepeaBullets[count].y, &icebullet[icepeaBullets[count].state]);
		}
	}
}
void icepeaBulletOut()
{
	for (int count = 0; count < BULLETMAX; count++)
	{
		if (icepeaBullets[count].x > 900 && icepeaBullets[count].exist == 1)
		{
			icepeaBullets[count].exist = 0;
		}
	}
}
void icepeaBulletHit()
{
	for (int count = 0; count < ZOOMMAX; count++)
	{
		if (ZM[count].exist)
		{
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (icepeaBullets[i].x > ZM[count].x + 50 && icepeaBullets[i].state == 0 && icepeaBullets[i].row == ZM[count].row && icepeaBullets[i].x < ZM[count].x + 100)
				{
					icepeaBullets[i].state = 1;
					ZM[count].life -= 15;
					ZM[count].speed = 1;
				}
			}
		}
	}
}