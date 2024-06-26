#include <cstdio>
#include <set>
#include <vector>
using namespace std;
FILE *f=fopen("sir4.in","r");
FILE *g=fopen("sir4.out","w");
set <int> nr;
vector <int> v[10];
int k;
int main()
{
    fscanf(f,"%d",&k);
    k=(((k*k)%1000)/100)*10+(((k*k)%100)/10);
    while(nr.find(k)==nr.end())
    {
        nr.insert(k);
        fprintf(g,"%d ",k);
        k=(((k*k)%1000)/100)*10+(((k*k)%100)/10);
    }
    fprintf(g,"\n");
    for(set <int> :: iterator it=nr.begin();it!=nr.end();it++)
    {
        if(*it<10)
        {
            v[*it].push_back(*it);
        }
        else
        {
            v[*it/10].push_back(*it);
        }
    }
    for(int i=0;i<=9;i++)
    {
        for(vector <int>::iterator it=v[i].begin();it!=v[i].end();it++)
        fprintf(g,"%d ",*it);
    }
    fclose(f);
    fclose(g);
    return 0;
}
