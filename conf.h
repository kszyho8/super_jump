#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
#define AIR_GAP 5 // odsuniêcie od krawêdzi
#define SIZE 20 // wysokoœæ i szerokoœæ platformy lewe zakoñczenie, œrodek, prawe zakoñczenie
#define VEL 0.40f // wartoœæ przyspieszenia grawitacji
#define OFFSET 200 // szerokoœæ od boków okna (ciemne ceg³y)

/* ZMIENNE GLOBALNE */
int gameState = 1; // status gry: 0-koniec 1-menu 2-gra 3-pauza 4-game over
int total; // aktualna liczba platform (wyko¿ystanych)
int score; // iloœæ zdobytych punktów
int schody2 = 40; // domyślna tekstura platform
/* ZMIENNE GLOBALNE  KONIEC*/
