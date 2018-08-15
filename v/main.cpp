#include <stdio.h>

int stinga[2][2000], dreapta[2][2000];

int main() {
  FILE *fin, *fout;
  int m, n, l, c, vsel, elem, sumv, maxsum, maxc, maxl, limita;

  fin = fopen( "v.in", "r" );
  fscanf( fin, "%d%d", &m, &n );
  for ( c = 0; c < n; c++ ) { // citim prima linie
    fscanf( fin, "%d", &stinga[0][c] );
    dreapta[0][c] = stinga[0][c];
  }
  vsel = 1;
  maxsum = -2000000000;
  limita = m - 1;   // calculam linia maxima care poate fi atinsa de un v
  if ( n / 2 < m )  // este fie numarul de linii
    limita = n / 2; // fie numarul de coloane supra doi
  for ( l = 1; l <= limita; l++ ) {
    for ( c = 0; c < l; c++ ) // citim in gol, elemente nefolositoare
      fscanf( fin, "%d", &elem );
    for ( c = l; c < n - l; c++ ) { // pentru elementele virf pe linie
      fscanf( fin, "%d", &elem );
      // calculam v-ul care se termina in punctul curent
      sumv = elem + stinga[1 - vsel][c-1] + dreapta[1-vsel][c+1];
      if ( sumv > maxsum ) { // testam daca avem un v mai mare
        maxsum = sumv;
        maxc = c - l;
        maxl = l;
      }
      // actualizam vectorii de sume diagonale
      stinga[vsel][c] = stinga[1 - vsel][c-1] + elem;
      dreapta[vsel][c] = dreapta[1 - vsel][c+1] + elem;
    }
    for ( c = n - l; c < n; c++ ) // citim in gol, elemente nefolositoare
      fscanf( fin, "%d", &elem );

    vsel = 1 - vsel;
  }
  fclose( fin );

  fout = fopen( "v.out", "w" );
  fprintf( fout, "%d %d %d\n", maxsum, maxc + 1, maxl + 1 );
  fclose( fout );

  return 0;
}
