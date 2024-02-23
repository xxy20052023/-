#include"mystruct.h"

int sunnumber=50;
IMAGE imgBg;
IMAGE imgBar;
IMAGE imgCard[PLANT_COUNT];
IMAGE* imgPlant[PLANT_COUNT][20];
struct Mouse mouse;
struct Plant plantMap[5][9];
struct Sunshine sun[10];
IMAGE imgSun[29];
IMAGE imgZooms[22];
Zoom ZM[ZOOMMAX];
PeaBullet peaBullets[BULLETMAX];
IMAGE bullet[4];
IMAGE imgZoomDead[20];
IMAGE imgZoomEat[21];
IMAGE imgZoomStand[11];
int gameState = 0,zoomNumber=0;
IMAGE imgWin, imgFail;
IMAGE imgChiliBullet;
IcePeaBullet icepeaBullets[BULLETMAX];
IMAGE icebullet[4];