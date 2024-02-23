#pragma once
#include"mystruct.h"
#include"sun.h"
#include"plant.h"
#include"zoom.h"

void startMenu();									//菜单设计
void gameInit();									//游戏初始化
void updateWin();									//更新窗口画面
void userClick();									//玩家的操作
void updateinf();									//更新所有游戏信息
void updateinf2();									//补充更新游戏信息
void viewScene();									//场景巡回
void gameEnd();										//检测游戏是否结束