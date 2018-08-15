#include <cstdio>
#include <ctime>
#include <bitset>
#include <algorithm>
using namespace std;
int N;
bitset<1000000> used;
int rez;
int V[105][7];
int pw[7]={1,1,10,100,1000,10000,100000};
int C[7];
int getpos(int val,int pos)
{
    while(pos>1){pos--;val/=10;}
    return val%10;
}
void rotst(int &val)
{
    int newval=0;
    newval+=getpos(val,1)*100000;
    newval+=getpos(val,2)*10;
    newval+=getpos(val,3)*10000;
    newval+=getpos(val,4)*1000;
    newval+=getpos(val,5)*1;
    newval+=getpos(val,6)*100;
    val=newval;
}
void rotb(int &val)
{
    int newval=0;
    newval+=getpos(val,1)*10;
    newval+=getpos(val,2)*100;
    newval+=getpos(val,3)*1000;
    newval+=getpos(val,4)*1;
    newval+=getpos(val,5)*10000;
    newval+=getpos(val,6)*100000;
    val=newval;
}
void rot3(int &val)
{
    int newval=0;
    newval+=getpos(val,1)*1;
    newval+=getpos(val,2)*100000;
    newval+=getpos(val,3)*100;
    newval+=getpos(val,4)*10000;
    newval+=getpos(val,5)*10;
    newval+=getpos(val,6)*1000;
    val=newval;
}
void rotstV(int i)
{
    swap(V[i][5],V[i][3]);
    swap(V[i][3],V[i][6]);
    swap(V[i][6],V[i][1]);
}
void rotbV(int i)
{
    swap(V[i][2],V[i][3]);
    swap(V[i][1],V[i][2]);
    swap(V[i][4],V[i][1]);
}
void rot3V(int i)
{
    swap(V[i][5],V[i][4]);
    swap(V[i][4],V[i][6]);
    swap(V[i][6],V[i][2]);
}
int schimb(int x)
{
    int rez=0;
    for(int i=1;i<=6;i++)if(C[i]!=V[x][i])rez++;
    return rez;
}
void eval(int cul)
{
    if(used[cul])return ;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                rot3(cul);
                used[cul]=1;
            }
            rotb(cul);
        }
        rotst(cul);
    }
    int tmp=0,R=0;
    for(int i=1;i<=N;i++)
    {
        tmp=6;
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                for(int l=0;l<4;l++)
                {
                    tmp=min(tmp,schimb(i));
                    rot3V(i);
                }
                rotbV(i);
            }
            rotstV(i);
        }
        R+=tmp;
        if(R>=rez)return;
    }
    rez=R;
}
int ord[]={0,1,2,3,4,5,6};
void btr(int pas,int cul)
{
    if(pas>6)eval(cul);
    else for(int i=0;i<=6;i++){C[pas]=i;btr(pas+1,cul+ord[i]*pw[pas]);}
}
int main()
{
    //srand(time(NULL));random_shuffle(ord,ord+7);
    scanf("%d",&N);rez=6*N;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=6;j++)
        {
            scanf("%d",&V[i][j]);
        }
    }
    btr(1,0);
    printf("%d",rez);
    return 0;
}
