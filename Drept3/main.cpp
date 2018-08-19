#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
FILE *f=fopen("drept3.in","r");
FILE *g=fopen("drept3.out","w");
int N,YMAX,XMAX;
int V[10005];///V[i]-cate patrate contin la pasul actual coordonata i
vector<pair<int,int> > pnou[10005];///pnou[i]-ce patrate intra la y=i,unde pe abscisa si ce dimensiuni au
vector<pair<int,int> > pafara[10005];///pafara[i]-ce patrate ies la y=i,unde pe abscisa si ce dimensiuni au
int x,y,d;
int a,b;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d %d",&x,&y,&d);
        pnou[y].push_back(make_pair(x,d));
        pafara[y+d].push_back(make_pair(x,d));
        YMAX=max(YMAX,y+d);
        XMAX=max(XMAX,x+d);
    }
    for(int i=0;i<=YMAX;i++)
    {
        for(auto it:pnou[i])///actualizam V de data trecuta,ocupandu-ne de patratele noi
        {
            V[it.first]++;
            V[it.first+it.second]--;
        }
        for(auto it:pafara[i])///le scoatem pe cele vechi
        {
            V[it.first]--;
            V[it.first+it.second]++;
        }
        int cpatrate=0;
        for(int i=0;i<=XMAX;i++)///pentru fiecare x vedem cate patrate contin coordonata la pasul actual
        {
            cpatrate+=V[i];
            if(cpatrate)///daca avem vreun patrate
                a++;
            b=max(b,cpatrate);
        }
    }
    fprintf(g,"%d\n%d",a,b);
    fclose(f);
    fclose(g);
    return 0;
}
