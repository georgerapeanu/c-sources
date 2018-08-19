#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
FILE *f=fopen("minarea.in","r");
FILE *g=fopen("minarea.out","w");
vector<int>V;
map<int,int> fr,tmp;
int val;
long double A;
void solve(vector<int> a)
{
    tmp.clear();
    for(auto it:a)tmp[it]++;
    int r=(1<<30);
    for(auto it:a)
   {
        r=min(r,fr[it]/tmp[it]);
   }
    for(auto it:tmp)
        fr[it.first]-=r*it.second;
    int h=0;
    for(auto it:a)
    {
        A=A+1.0f*r*(h+it+h)/2*abs(it);
        h+=it;
    }
}
int main()
{
    for(int i=1;i<4;i++){fscanf(f,"%d",&val);fr[i]+=val;}
    for(int i=1;i<4;i++){fscanf(f,"%d",&val);fr[-i]+=val;}
    solve({+3, -3});
    if (!fr[3]) {
        for (int i = 1; i <= 3; i++) {
            swap(fr[i], fr[-i]);
        }
    }
    solve({+3, -2, -1});
    solve({+3, -1, -1, -1});
    solve({+3, -2, +1, -2});
    solve({+3, -2, +3, -2, -2});
    solve({+2, -2});
    solve({+2, -1, -1});
    solve({+1, +1, -2});

    solve({+1, -1});
    fprintf(g,"%lld",(long long)A);
    fclose(f);
    fclose(g);
    return 0;
}
