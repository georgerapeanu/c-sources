#include <cstdio>
#include <iostream>
#define zeros(x) (x&(x^(x-1)))
using namespace std;
FILE *f=fopen("arbint.in","r");
FILE *g=fopen("arbint.out","w");
int AIB[100005],V[100005];///AIB[i]-indicele maximului din intervalul i-zeros(i)+1,i
int N,M,c,x,y;
int query(int l,int r)
{
    int q,maxim=0;
    while(r>=l)
    {
        if(r-zeros(r)+1>=l) q=AIB[r],r-=zeros(r);///intervalul se incadreaza complet
        else q=r,r=r-1;///altfel luam pozitia curenta si incercam din nou data viitoare de pe poz din stanga
        if(V[maxim]<V[q])
            maxim=q;
    }
    return maxim;
}
void update(int pos,int val)
{
    V[pos]=val;
    for(int x=pos;x<=N;x+=zeros(x))
    {
        if(AIB[x]==pos)///if-ul are sens,deoarece daca zicea ca e pos siactualizam cu ceva mai mic,ar considera un maxim care nu mai exista
        {
            int z=query(x-zeros(x)+1,x-1);
            AIB[x]=(V[x] > V[z] ? x:z);///aib ii indicele maximiul dintre poz curenta,sau ce reprezinta aib[x] fara x
        }
        else
        {
            if(V[pos]>V[AIB[x]])///altfel poate putem actualiza
                AIB[x]=pos;
        }
    }
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        update(i,V[i]);
    }
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&c,&x,&y);
        if(!c)
            fprintf(g,"%d\n",V[query(x,y)]);
        else
            update(x,y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
