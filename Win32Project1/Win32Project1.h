#pragma once
#pragma comment(lib, "winmm.lib")

#include "resource.h"
#include "stdafx.h"
#include "snake.h"
#include "kbdctl.h"
#include "congfx.h"
#include <list>
#include "oglgfx.h"
#include <iostream>
#include <conio.h>
#include "StatModule.h"
#include "OptionsModule.h"
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#define FILE_NAME "../stat.txt"
#define CONFIG "../config.txt"
#define GRAPHICS_MODE "../graphics.txt"
#define BITMAP_PATH "../btm.bmp"
#define PLAYLIST "../pl1.txt"
#define ID_BT1 100    /* идентификатор для кнопочки внутри главного окна */
#define ID_BT2 200	
#define ID_BT3 300
#define ID_LIST 120


void Audio();
void Game(int argc, char **argv);
std::thread thr(Audio);
