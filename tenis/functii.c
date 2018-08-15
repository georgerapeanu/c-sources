#include <conio.h>
#include "tenis.h"
/************************************************************
 Considerente generale:

 - Dispuneti de functia:
 void putChar(int x, int y, char c)
 care deseneaza caracterul c la coordonatele ecran (x, y)

 - x este coloana si y este linia

 - coltul din stinga sus este (0,0)
*************************************************************/

/*
 Sterge o paleta de pe ecran:
 - paleta este verticala, pe coloana x
 - punctul cel mai de sus al paletei este la coordonatele (x, y)
 - paleta are RACKET_LEN caractere (RACKET_LEN este predefinit)
 - folositi functia putChar(int x, int y, int c)
 - sugestie: folositi caracterul ' ' pentru a suprascrie paleta
*/
void clearRacket( int x, int y ) {
       int i;
    for(i=y;i<=y+RACKET_LEN;i++)
    putChar(x,i,' ');
}

/*
 Deseneaza o paleta pe ecran:
 - paleta este verticala, pe coloana x
 - punctul cel mai de sus al paletei este la coordonatele (x, y)
 - paleta are RACKET_LEN caractere (RACKET_LEN este predefinit)
 - folositi functia putChar(int x, int y, int c)
 - sugestie: folositi caracterul '#' deoarece este mai "plin"
*/

void putRacket( int x, int y ) {
    int i;
    if(y+RACKET_LEN<=LAST_ROW)
    for(i=y;i<=y+RACKET_LEN;i++)
    putChar(x,i,'#');
    else
    for(i=LAST_ROW-RACKET_LEN+1;i<=LAST_ROW;i++)
    putChar(x,i,'#');
}

/*
 Primeste coordonatele actuale ale bilei si ale celor doua
 palete, precum si incrementele de deplasare ale bilei pe
 linie si pe coloana si muta bila la urmatoarea pozitie.
 Functia returneaza coordonatele noi, x si y, si incrementele
 noi ix si iy ca un singur numar egal cu
 ((ix + 1) * 4 + (iy + 1)) * 65536 + x * 256 + y
 - ballX, ballY sint coordonatele actuale ale bilei
 - incX, incY sint incrementele de deplasare ale bilei
 - incX si incY pot fi 1 sau -1 (nu pot fi zero)
 - paleta din stinga se afla la (FIRST_COL, leftY) cu LEFT_COL predefinit
 - paleta din dreapta se afla la (LAST_COL, rightY) cu LAST_COL predefinit
 - cind spunem "paleta se afla la" inseamna punctul cel mai de sus al ei
- atunci cind bila ajunge sus la linia FIRST_ROW ea se va reflecta corespunzator
 - atunci cind bila ajunge jos la linia LAST_ROW ea se va reflecta corespunzator
 - atunci cind bila ajunge la stinga in coloana FIRST_COL + 1 ea se va reflecta
   corespunzator numai daca paleta din stinga de pe coloana FIRST_COL este
   unde trebuie, altfel va intra pe coloana FIRST_COL
 - atunci cind bila ajunge la dreapta in coloana LAST_COL - 1 ea se va reflecta
   corespunzator numai daca paleta din dreapta de pe coloana LAST_COL este
   unde trebuie, altfel va intra pe coloana LAST_COL
 - valoarea ce trebuie returnata este o valoare compusa din patru valori:
   x, y - noile coordonate ale bilei
   ix, iy - noile incremente de deplasare ale bilei
 - functia va returna valoarea
   ((ix + 1) * 4 + (iy + 1)) * 65536 + x * 256 + y
   unde cele patru valori sint cele descrise mai sus
*/
int newCoords( int ballX, int ballY, int incX, int incY, int leftY, int rightY ) {
    int x,y,ix,iy;
    ix=incX;
    iy=incY;
    x=ballX+ix;
    y=ballY+iy;
           if(x==leftY+1)
    if(y>=FIRST_COL&&y<=FIRST_COL+RACKET_LEN)
    ix=1;
    else
    if(x==rightY-1)
    if(y>=LAST_COL&&y<=LAST_COL+RACKET_LEN)
    ix=-1;
if(y==FIRST_ROW)
iy=1;
if(y==LAST_ROW)
iy=-1;
    return ((ix + 1) * 4 + (iy + 1)) * 65536 + x * 256 + y;
}
