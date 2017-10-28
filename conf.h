#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
// odsuniêcie od krawêdzi
#define AIR_GAP 5
// wysokoœæ i szerokoœæ platformy lewe zakoñczenie, œrodek, prawe zakoñczenie
#define SIZE 20
// wartoœæ przyspieszenia grafitacji
#define VEL 0.40f
// szerokoœæ od boków okna (ciemne ceg³y)
#define OFFSET 200

/* ZMIENNE GLOBALNE */
int gameState = 1; // status gry: 0-koniec 1-menu 2-gra 3-pauza 4-game over
int total; // aktualna liczba platform (wyko¿ystanych)
int score; // iloœæ zdobytych punktów
int schody2 = 40; // jaka tekstura platfor
/* ZMIENNE GLOBALNE  KONIEC*/
