#pragma once
#include "../generale/libs.hpp"

/* ELENCO COLORI */

#define MENU_BACKGROUND         8
#define MENU_TEXT               9
#define MENU_HL_TEXT            10
#define MENU_HL_BACKGROUND      11


#define MAIN_TITLE_TEXT         12
#define MAIN_TITLE_BACKGROUND   13

#define GAME_BACKGROUND         14
#define PLAYER_COLOR            15
#define PLAYER_BULLET_COLOR     16
#define ENEMY_BULLET_COLOR      17
#define HEARTS                  18

#define DEFAULT                 19

#define DOOR_BACKGROUND         20
#define DOOR_KEY_BACKGROUND     21

#define DOOR_FOREGROUND         22
#define DOOR_KEY_FOREGROUND     23

#define MAP_SPAWN_EMPTY         24   
#define MAP_NORMAL_EMPTY        25
#define MAP_BOSS_EMPTY          26

#define MAP_SPAWN_WALL          27   
#define MAP_NORMAL_WALL         28
#define MAP_BOSS_WALL           29

#define MINIMAP_UNKNOWN_GREY    30



/* ELENCO COPPIE DI COLORI */

#define MENU_HIGHLIGHT              1
#define MENU_NORMAL                 2

#define MAIN_TITLE                  3

#define PLAYER_COLOR_PAIR           4
#define PLAYER_BULLET_PAIR          5
#define ENEMY_BULLET_PAIR           6
#define HEARTS_PAIR                 7

#define DOOR_PAIR                   10
#define DOOR_KEY_PAIR               11

#define MAP_SPAWN_PAIR              12
#define MAP_NORMAL_PAIR             13
#define MAP_BOSS_PAIR               14

#define MINIMAP_SPAWN_PAIR          15    
#define MINIMAP_NORMAL_PAIR         16
#define MINIMAP_BOSS_PAIR           17
#define MINIMAP_UNKNOWN_PAIR        18
#define MINIMAP_UNKNOWN_PAIR_TEXT   19

#define PLAYER_COLOR_PAIR_E         20
#define PLAYER_COLOR_PAIR_N         21
#define PLAYER_COLOR_PAIR_B         22
#define PLAYER_BULLET_PAIR_E        23       
#define PLAYER_BULLET_PAIR_N        24       
#define PLAYER_BULLET_PAIR_B        25       
#define ENEMY_BULLET_PAIR_E         26
#define ENEMY_BULLET_PAIR_N         27
#define ENEMY_BULLET_PAIR_B         28


#define FRAME_OF_E              0
#define FRAME_OF_N              1
#define FRAME_OF_B              2

void initializeColors();