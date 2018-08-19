#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
FILE *f=fopen("referat.in","r");
FILE *g=fopen("referat.out","w");
int N,L,T;
int len[100005];
int dis[100005];
int l[100005];///lungimea minima pe care trebuia sa o aiba un cuvant sau o grupare de cuvinte care sa cada pe randul i,astfel incat in final sa avem cu cel putin un rand in plus
vector<int> cuv[100005];
int nr=1;
int val;
int main()
{
    fscanf(f,"%d %d %d",&N,&L,&T);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        if(len[nr]+val>L)
        {
            nr++;
        }
        len[nr]+=val;
        cuv[nr].push_back(val);
    }
    l[nr+1]=1;
    len[nr+1]=L;
    for(int i=nr;i;i--)
    {
        l[i]=L-len[i]+1;
        int s=0;
        int ind=cuv[i].size()-1,u;
        while(ind>=0&&s<l[i+1])
        {
            s+=cuv[i][ind];
            u=cuv[i][ind];
            ind--;
        }
        l[i]=max(l[i],L-len[i]+s-u+1);
    }
    for(int i=1;i<=T;i++)
    {
        fscanf(f,"%d",&val);
        int rez=0;
        for(int i=nr;i;i--)
        {
            if(val+len[i]>L)
            {
                int s=0;
                for(int j=cuv[i].size()-1;j>=0;j--)
                {
                    if(len[i]-s+val>L)
                    {
                        rez+=(val+s>=l[i+1]);
                        s+=cuv[i][j];
                    }
                    else
                    {
                        rez+=(s>=l[i+1]);
                    }
                }
            }
        }
        rez+=(val+len[1]>L&&val>=l[1]);
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
