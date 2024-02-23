#pragma once
#include"mystruct.h"


void plantDraw();										//画出所有已经种植的植物
void peaBulletGenerate();								//产生子弹
void peaBulletUpdate();									//更新子弹
void peaBulletDraw();									//画出子弹
void peaBulletOut();									//删除那些飞出屏幕的子弹
void peaBulletHit();									//检测子弹是否击中僵尸
void plantUpdate();										//更新植物数据
int plantLife(int type);								//初始不同植物的血量
void chiliBurn();										//辣椒燃烧
void cherryBurn();										//樱桃炸弹爆炸
void icepeaBulletGenerate();							//产生寒冰子弹
void icepeaBulletUpdate();								//更新寒冰子弹
void icepeaBulletDraw();								//画出寒冰子弹
void icepeaBulletOut();									//删除那些飞出屏幕的寒冰子弹
void icepeaBulletHit();									//检测寒冰子弹是否击中僵尸
