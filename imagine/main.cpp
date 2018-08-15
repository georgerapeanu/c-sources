#include <cstdio>
#include <fstream>
using namespace std;
FILE *f=fopen("imagine.in","r");
FILE *g=fopen("imagine.out","w");
int L,i,j;
int S[255][255];
long long lung;
void rez(pair<int,int> st,pair <int,int> dr)
{
    if((dr.first-st.first+1)*(dr.second-st.second+1)==S[dr.first][dr.second]-S[dr.first][st.second-1]-S[st.first-1][dr.second]+S[st.first-1][st.second-1])
    {
        lung+=2;
        return ;
    }
    if(S[dr.first][dr.second]-S[dr.first][st.second-1]-S[st.first-1][dr.second]+S[st.first-1][st.second-1]==0)
    {
        lung+=2;
        return ;
    }
    lung++;
    pair<int,int> mid;
    mid=make_pair((st.first+dr.first)/2,(st.second+dr.second)/2);
    rez(make_pair(mid.first+1,st.second),make_pair(dr.first,mid.second));
    rez(st,mid);
    rez(make_pair(mid.first+1,mid.second+1),dr);
    rez(make_pair(st.first,mid.second+1),make_pair(mid.first,dr.second));
}
int main()
{
    fscanf(f,"%d",&L);
    for(i=1;i<=L;i++)
        for(j=1;j<=L;j++){
            fscanf(f,"%d",&S[i][j]);
            S[i][j]+=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
        }
    rez(make_pair(1,1),make_pair(L,L));
    fprintf(g,"%lld",lung);
    fclose(f);
    fclose(g);
    return 0;
}
