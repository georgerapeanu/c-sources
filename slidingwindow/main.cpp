#include <cstdio>
#include <set>
using namespace std;
FILE *f=fopen("slidingwindow.in","r");
FILE *g=fopen("slidingwindow.out","w");
int N,D;
int A[1000001];
multiset<int> S;
int rez=(1<<30);
multiset<int> ::iterator it;
int main()
{
    fscanf(f,"%d%d",&N,&D);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&A[i]);
        if(i>D+1) {it=S.find(A[i-D-1]);S.erase(it);}
        it=S.lower_bound(A[i]);
        if(it!=S.end())
            rez=min(rez,*it-A[i]);
        if(it!=S.begin()){it--;rez=min(rez,A[i]-*it);}
        S.insert(A[i]);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
