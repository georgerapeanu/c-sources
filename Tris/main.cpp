#include <cstdio>
using namespace std;
FILE *f=fopen("tris.in","r");
FILE *g=fopen("tris.out","w");
int V[5];
int A[5];
int B[5];
int mat[805][805];
int dy[6]={0,1,2,3,2};
int r1,r2,r3;
int y1,y2;
int x1=1,x2;
int st;
void resturi()
{
    r1=(V[1]&1);
    r2=(V[2]&1);
    r3=(V[3]&1);
}
void baga()
{
    for(int i=1;i<=4;i++){A[i]+=V[i]/2;B[i]+=V[i]/2;}
}
void haida(int V[],int y,int sens)
{
    int j=3;
    while(V[1])
    {
        mat[j][y]=st++;
        V[1]--;
        j++;
    }
    while(V[2])
    {
        mat[j][y]=st;
        mat[j+1][y]=st++;
        V[2]--;
        j+=2;
    }
    while(V[3])
    {
        mat[j][y]=st;
        mat[j+1][y]=st;
        mat[j+2][y]=st++;
        V[3]--;
        j+=3;
    }
    while(V[4])
    {
        mat[j][y]=mat[j+1][y]=mat[j+1][y+sens]=st++;
        mat[j+2][y+sens]=mat[j+3][y+sens]=mat[j+3][y]=st++;
        V[4]-=2;
        j+=4;
    }
}
int main()
{
    fscanf(f,"%d %d %d %d",&V[1],&V[2],&V[3],&V[4]);
    resturi();
    if((V[4]&3)==0)
    {
        V[4]-=4;
        y1=400;y2=403;
        mat[1][y1]=mat[2][y1]=mat[1][y1+1]=1;
        mat[1][y2-1]=mat[2][y2]=mat[1][y2]=2;
        if(!r1&&!r2&&!r3)
        {
            baga();
        }
        else if(r1&&!r2&&r3)
        {
            V[1]-=3;
            V[2]--;
            baga();
            A[1]++;A[2]++;B[3]++;
            A[1]+=2;B[2]++;
        }
        else if(!r1&&r2&&!r3)
        {
            V[1]-=2;
            baga();
            A[1]+=2;B[2]++;
        }
        else if(r1&&r2&&r3)
        {
            V[1]--;
            V[2]--;
            baga();
            A[1]++;A[2]++;B[3]++;
        }
        int tmp=3;
        for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
        mat[tmp][y1]=mat[tmp+1][y1]=mat[tmp+1][y1+1]=3;
        mat[tmp][y2]=mat[tmp+1][y2]=mat[tmp+1][y2-1]=4;
        x2=tmp+1;
        st=5;
    }
    else if((V[4]&3)==2)
    {
        V[4]-=2;
        y1=400;y2=403;
        mat[1][y1]=mat[2][y1]=mat[1][y1+1]=1;
        mat[1][y2-1]=mat[2][y2]=mat[1][y2]=2;
        int tmp=3;
        if(!r1&&!r2&&!r3)
        {
            V[2]-=2;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=3;
            mat[tmp][y2]=mat[tmp][y2-1]=4;
            st=5;
        }
        else if(r1&&!r2&&r3)
        {
            V[1]--;V[3]--;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=mat[tmp][y1+2]=3;
            mat[tmp][y2]=4;
            st=5;
        }
        else if(!r1&&r2&&!r3)
        {
            V[1]-=2;V[2]--;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=3;mat[tmp][y2]=4;
            mat[tmp][y1+1]=mat[tmp][y2-1]=5;
            st=6;
        }
        else if(r1&&r2&&r3)
        {
            V[2]-=2;
            V[2]--;
            V[1]--;
            baga();
            A[1]++;A[2]++;B[3]++;
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=3;
            mat[tmp][y2]=mat[tmp][y2-1]=4;
            st=5;        }
        x2=tmp;
    }
    else if((V[4]&3)==3)
    {
        V[4]-=3;
        y1=400;y2=403;
        mat[1][y1]=mat[2][y1]=mat[1][y1+1]=1;
        mat[1][y2-1]=mat[2][y2]=mat[1][y2]=2;
        int tmp=3;
        if(!r1&&!r2&&r3)
        {
            V[1]-=2;V[2]-=2;
            baga();
            A[1]++;A[2]++;B[3]++;
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=3;
            mat[tmp+1][y1]=mat[tmp+1][y1+1]=4;
            mat[tmp][y2]=mat[tmp+1][y2]=mat[tmp+1][y2-1]=5;
            st=6;
            x2=tmp+1;
        }
        else if(r1&&!r2&&!r3)
        {
            V[1]--;
            V[2]-=2;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp+1][y1]=3;
            mat[tmp+2][y1]=mat[tmp+2][y1+1]=4;
            mat[tmp+2][y2-1]=mat[tmp+2][y2]=mat[tmp+1][y2]=5;
            mat[tmp][y2]=6;
            st=7;
            x2=tmp+2;
        }
        else if(!r1&&r2&&r3)
        {
            V[3]--;
            V[2]--;
            V[1]-=2;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp+1][y1]=mat[tmp+2][y1]=3;
            mat[tmp+3][y1]=mat[tmp+3][y1+1]=4;
            mat[tmp+3][y2-1]=mat[tmp+3][y2]=mat[tmp+2][y2]=5;
            mat[tmp+1][y2]=6;
            mat[tmp][y2]=7;
            st=8;
            x2=tmp+3;
        }
        else if(r1&&r2&&!r3)
        {
            V[1]--;
            V[2]--;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];            mat[tmp][y1]=3;
            mat[tmp+1][y1]=mat[tmp+1][y1+1]=4;
            mat[tmp][y2]=mat[tmp+1][y2]=mat[tmp+1][y2-1]=5;
            st=6;
            x2=tmp+1;        }
    }
    else
    {
        V[4]--;
        y1=400;y2=402;
        int tmp=3;
        if(!r1&&!r2&&r3)
        {
            mat[1][y1]=1;mat[2][y1]=2;
            mat[1][y1+1]=mat[1][y2]=mat[2][y2]=3;
            V[1]-=2;
            V[3]--;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=mat[tmp][y2]=4;
            st=5;
        }
        else if(r1&&!r2&&!r3)
        {
            mat[1][y1]=mat[2][y1]=1;
            mat[1][y1+1]=mat[1][y2]=mat[2][y2]=2;
            V[1]--;V[2]-=2;V[3]--;
            baga();
            A[1]++;A[2]++;B[3]++;
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=mat[tmp][y2]=3;
            st=4;
        }
        else if(!r1&&r2&&r3)
        {
            mat[1][y1]=mat[2][y1]=1;
            mat[1][y1+1]=mat[1][y2]=mat[2][y2]=2;
            V[2]--;
            V[3]--;
            baga();
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=mat[tmp][y2]=3;
            st=4;
        }
        else if(r1&&r2&&!r3)
        {
            mat[1][y1]=1;mat[2][y1]=2;
            mat[1][y1+1]=mat[1][y2]=mat[2][y2]=3;
            V[1]-=3;V[2]--;V[3]--;
            baga();
            A[1]++;A[2]++;B[3]++;
            for(int i=1;i<=4;i++)tmp+=dy[i]*A[i];
            mat[tmp][y1]=mat[tmp][y1+1]=mat[tmp][y2]=4;
            st=5;        }
        x2=tmp;
    }
    fprintf(g,"%d %d\n",x2-x1+1,y2-y1+3);
    haida(A,y1,-1);
    haida(B,y2,1);
    for(int i=x1;i<=x2;i++)
    {
        for(int j=y1-1;j<=y2+1;j++)
        {
            fprintf(g,"%d ",mat[i][j]);
        }
        fprintf(g,"\n");
    }
    return 0;
}
