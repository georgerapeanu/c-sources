#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("codpatrat.in","r");
FILE *g=fopen("codpatrat.out","w");
int N,M,A[105],B[105],cant,val;
int nr;
char C[105];
int i;
bool ok=1;
void adun(int* V)
{
    V[V[0]]+=cant;
    int i=V[0];
    while(i>1&&V[i]>1)
    {
        V[i-1]+=V[i]/2;
        V[i]%=2;
        i--;
    }
    if(V[1]>1)
        ok=0;
}
void scad(int* V)
{
     V[V[0]]-=cant;
     int i=V[0];
     while(i>1&&V[i]<0)
     {
         V[i-1]+=V[i]/2+V[i]%2;
         V[i]=-1*(V[i]%2);
         i--;
     }
     if(V[1]<0)
        ok=0;
}
bool digi(char c)
{
    return '0'<=c&&c<='9';
}
int main()
{
    fgets(C+1,105,f);
    A[0]=B[0]=strlen(C+1)-1;
    for(i=1;i<=A[0];i++)
    {
        switch(C[i])
        {
            case '1':A[i]=0;B[i]=0;break;
            case '2':A[i]=0;B[i]=1;break;
            case '3':A[i]=1;B[i]=1;break;
            case '4':A[i]=1;B[i]=0;break;
        }
    }
    while(fgets(C,105,f)!=NULL&&ok)
    {
        cant=0;
        i=2;
        while(digi(C[i]))
        {
            cant=cant*10+C[i]-'0';
            i++;
        }
        nr++;
        switch(C[0])
        {
            case 'U':scad(A);break;
            case 'D':adun(A);break;
            case 'L':scad(B);break;
            case 'R':adun(B);break;
        }
    }
    if(!ok)
        fprintf(g,"%d",nr);
    else
    {
        for(i=1;i<=A[0];i++)
        {
            if(A[i])
                if(B[i])
                    val=3;
                else
                    val=4;
            else
                if(B[i])
                    val=2;
                else
                    val=1;
            fprintf(g,"%d",val);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
