#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("numar.in","r");
FILE *g=fopen("numar.out","w");
int b,nr,a,N;
vector <pair<int,int>> V;
int main()
{
    fscanf(f,"%d",&nr);
    nr*=2;
    N=sqrt(nr);
    for(b=1;b<=N;b++)
    {
        if(nr%b==0)
        {
            if(((nr/b)-b+1)%2==0&&b!=1)
            {
                a=((nr/b)-b+1)/2;
                V.push_back(make_pair(a,b));
            }
            if((b+1-(nr/b))%2==0)
            {
                V.push_back(make_pair((b+1-(nr/b))/2,nr/b));
            }
        }
    }
    sort(V.begin(),V.end());
    for(vector<pair<int,int>> ::reverse_iterator it=V.rbegin();it!=V.rend();it++)
        fprintf(g,"%d %d\n",(*it).first,(*it).second);
    fclose(f);
    fclose(g);
    return 0;
}
