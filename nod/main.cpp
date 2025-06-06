#include <cstdio>
#include <cstring>
#include <map>
#include <fstream>
using namespace std;
FILE *f=fopen("nod.in","r");
FILE *g=fopen("nod.out","w");
int i,j,tip,P,R,C,m,k;
map<char,int> V;
int val[4][21];
char c[210],standard;
int pivot[4];
int comp(int i)
{
    if(val[1][i]<pivot[1])
        return -1;
    if(val[1][i]>pivot[1])
        return 1;
    if(val[2][i]<pivot[2])
        return -1;
    if(val[2][i]>pivot[2])
        return 1;
    if(val[3][i]<pivot[3])
        return -1;
    if(val[3][i]>pivot[3])
        return 1;
    return 0;
}
void sortare(int st,int dr)
{
    pivot[1]=val[1][(st+dr)/2];
    pivot[2]=val[2][(st+dr)/2];
    pivot[3]=val[3][(st+dr)/2];
    int i=st,j=dr;
    while(i<=j)
    {
        while(comp(i)==-1)
            i++;
        while(comp(j)==1)
            j--;
        if(i<=j)
        {
            int aux[4];
            aux[1]=val[1][i];
            aux[2]=val[2][i];
            aux[3]=val[3][i];
            val[1][i]=val[1][j];
            val[2][i]=val[2][j];
            val[3][i]=val[3][j];
            val[1][j]=aux[1];
            val[2][j]=aux[2];
            val[3][j]=aux[3];
            i++;
            j--;
        }
    }
    if(j>st) sortare(st,j);
    if(i<dr) sortare(i,dr);
}
int main()
{
    fscanf(f,"%d\n",&tip);
    V['M']=1000;
    V['D']=500;
    V['C']=100;
    V['L']=50;
    V['X']=10;
    V['V']=5;
    V['I']=1;
    V[' ']=0;
    for(i=1;i<=3;i++)
    {
        fgets(c,210,f);
        m=strlen(c);
        for(j=0;j<m;j++)
        {
            if(c[j]==' '||c[j]=='\n')
            {
                k=j-1;
                ++val[i][0];
                standard=' ';
                while(k>=0&&c[k]!=' ')
                {
                    if(V[c[k]]>=V[standard])
                    {
                        val[i][val[i][0]]+=V[c[k]];
                        standard=c[k];
                    }
                    else
                    {
                        val[i][val[i][0]]-=V[c[k]];
                    }
                    k--;
                }
            }
        }
    }
    if(tip==1)
            for(i=1;i<=3;i++,fprintf(g,"\n"))
            for(j=1;j<=val[i][0];j++)
                fprintf(g,"%d ",val[i][j]);
    else
    {
        fscanf(f,"%d %d %d\n",&P,&R,&C);
        sortare(1,val[1][0]);
        standard=1;
        for(i=1;i<=P;i++)
        {
            for(j=1;j<=R;j++)
            {
                for(k=1;k<=C;k++)
                {
                    fscanf(f,"%s",&c);
                    if(i==val[1][standard]&&j==val[2][standard]&&k==val[3][standard])
                    {
                        fprintf(g,"%s ",c);
                        standard++;
                    }
                }
                fscanf(f,"\n");
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
