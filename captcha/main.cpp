#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
FILE *f=fopen("captcha.bmp","rb");
FILE *g=fopen("captcha.out","w");
int N;
int rez=0;
typedef struct {
   unsigned short int type;                 /* Magic identifier            */
   unsigned int size;                       /* File size in bytes          */
   unsigned short int reserved1, reserved2;
   unsigned int offset;                     /* Offset to image data, bytes */
} HEADER;
typedef struct {
   unsigned int size;               /* Header size in bytes      */
   int width,height;                /* Width and height of image */
   unsigned short int planes;       /* Number of colour planes   */
   unsigned short int bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int ncolours;           /* Number of colours         */
   unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;
HEADER nu;
INFOHEADER pasa;
struct culoare{
    char a,b,c;
};
bool operator!=(culoare a,culoare b){return a.a!=b.a||a.b!=b.b||a.c!=b.c;}
culoare alb={0xFF,0xFF,0xFF};
culoare C[16][64];
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int Fill(int x,int y)
{
    int nr=0;
    queue<int> Qx,Qy;
    Qx.push(x);
    Qy.push(y);
    C[x][y]=alb;
    while(!Qx.empty())
    {
        nr++;
        x=Qx.front();Qx.pop();
        y=Qy.front();Qy.pop();
        for(int i=0;i<4;i++)
            if(0<=x+dx[i]&&x+dx[i]<16&&0<=y+dy[i]&&y+dy[i]<64&&C[x+dx[i]][y+dy[i]]!=alb)
            {
                C[x+dx[i]][y+dy[i]]=alb;
                Qx.push(x+dx[i]);
                Qy.push(y+dy[i]);
            }
    }
    return nr;
}
culoare tmp[5][5];
void copiaza(int x,int y)
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            tmp[i][j]=C[i+x][j+y];
}
int getnum(int x,int y)
{
    copiaza(x,y);
    int nr=Fill(x,y);
    switch(nr)
    {
        case 16:return 0;
        case 5:return 1;
        case 17:
            if(tmp[3][0]!=alb)
                return 2;
            else if(tmp[1][0]!=alb)
                return 5;
            else
                return 3;
        case 11:return 4;
        case 18:
            if(tmp[3][0]!=alb)
                return 6;
            else
                return 9;
        case 9:return 7;
        case 19: return 8;
    }
    return 0;
}
int sum=0;
int main()
{
    fread(&nu,sizeof(HEADER),1,f);
    fread(&pasa,sizeof(INFOHEADER),1,f);
    for(int i=15;i>=0;i--)
    {
        for(int j=0;j<64;j++)
        {
            culoare x;
            fread(&x,sizeof(culoare),1,f);
           C[i][j]=x;
        }
    }
    for(int j=0;j<64;j++)
    {
        for(int i=0;i<16;i++)
        {
            if(C[i][j]!=alb)
                sum+=getnum(i,j);
        }
    }
    fprintf(g,"%d",sum);
    fclose(f);
    fclose(g);
    return 0;
}
