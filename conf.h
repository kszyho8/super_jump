#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
// odsuni�cie od kraw�dzi
#define AIR_GAP 5
// wysoko�� i szeroko�� platformy lewe zako�czenie, �rodek, prawe zako�czenie
#define SIZE 20
// warto�� przyspieszenia grafitacji
#define VEL 0.40f
// szeroko�� od bok�w okna (ciemne ceg�y)
#define OFFSET 200

/* ZMIENNE GLOBALNE */
int gameState = 1; // status gry: 0-koniec 1-menu 2-gra 3-pauza 4-game over
int total; // aktualna liczba platform (wyko�ystanych)
int score; // ilo�� zdobytych punkt�w
int schody2 = 40; // jaka tekstura platfor
/* ZMIENNE GLOBALNE  KONIEC*/
