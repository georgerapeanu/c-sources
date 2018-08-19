#include <stdio.h>

int sablon[50][50], cartela[8][50][50];

int main() {
  FILE *fin, *fout;
  int n, nc, l, c, i, poz;

  fin = fopen( "suprapuneri1.in", "r" );
  fout = fopen( "suprapuneri1.out", "w" );
  fscanf( fin, "%d%d", &n, &nc );
  // citeste sablonul
  for ( l = 0; l < n; l++ )
    for ( c = 0; c < n; c++ )
      fscanf( fin, "%d", &sablon[l][c] );
  for ( i = 0; i < nc; i++ ) {
    // citeste cartela si genereaza cele 8 pozitii ale ei
    for ( l = 0; l < n; l++ )
      for ( c = 0; c < n; c++ ) {
        fscanf( fin, "%d", &cartela[0][l][c] );
        cartela[1][c][n-l-1] =
          cartela[2][n-l-1][n-c-1] =
          cartela[3][n-c-1][l] =
          cartela[4][c][l] =
          cartela[5][n-l-1][c] =
          cartela[6][n-c-1][n-l-1] =
          cartela[7][l][n-c-1] = cartela[0][l][c];
      }
    // comparam cartela in cele opt pozitii
    poz = l = 0;
    while ( l < n && poz < 8 ) {
      l = c = 0;
      while ( l < n && sablon[l][c] == cartela[poz][l][c] ) {
        c++;
        if ( c >= n ) {
          l++;
          c = 0;
        }
      }
      poz++;
    }
    // daca s-a potrivit la vreuna din pozitii inseamna ca l a depasit n
    if ( l < n )
      fprintf( fout, "0\n" );
    else
      fprintf( fout, "1\n" );
  }
  fclose( fin );
  fclose( fout );

  return 0;
