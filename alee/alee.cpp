#include <stdio.h>
#define DimMaxParc 177
#define DimMaxCoada 30625


const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, 1, 0, -1};

typedef struct
           {
             unsigned char l, c;
           }Element;

typedef Element Coada[DimMaxCoada];

int A[DimMaxParc][DimMaxParc];

int ix, iy, ox, oy;
int n, m;
int NrDale;


void Citire(void)
{
  int k, i, j;

  FILE * Fin=freopen("alee.in", "r", stdin);

  scanf("%d%d", &n, &m);
  for (i=1; i<=n; i++)
    for (j=1; j<=n; j++) A[i][j] = -2;
  for (k=1; k<=m; k++)
    {
      scanf("%d %d", &i, &j);
      A[i][j] = -1;
    }
  scanf("%d %d %d %d", &ix, &iy, &ox, &oy);
  fclose(Fin);
}

void Bordare(void)
{
  int i, j;
  for (i=1; i<=n; i++)
    {A[i][0] = -1;A[i][n+1] = -1;
     A[0][i] = -1;A[n+1][i] = -1;}
}

void DeterminNrDale(void)
{
  Coada C;
  int IncC, SfC, k;
  Element x, y;
  x.l = ix; x.c = iy; A[ix][iy] = 1;
  IncC = SfC = 0; C[IncC] = x;
  while (IncC <=SfC && A[ox][oy]==-2)
    {
      x = C[IncC++];
      for (k=1; k<=4; k++)
        {
          y.l = x.l + dx[k];  y.c = x.c + dy[k];
          if (A[y.l][y.c]==-2)
            {
             A[y.l][y.c] = A[x.l][x.c]+1;
              C[++SfC] =y;

            }
        }
    }
   if (A[ox][oy]==-2) printf("Nu exista solutie\n");
      else NrDale=A[ox][oy];

}

void Afisare(void)
{
  FILE * Fout=freopen("alee.out", "w", stdout);
  printf("%d\n", NrDale);
  fclose(Fout);
}

void main(void)
{
  Citire();
  Bordare();
  DeterminNrDale();
  Afisare();
}
