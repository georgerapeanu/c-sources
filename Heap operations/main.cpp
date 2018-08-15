#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
char C[100];
struct cmp{bool operator() (int a,int b){return a>b;}};
priority_queue <int,vector<int>,cmp> H;
char rez[1000001][100];
int N,i,nr,M;
char* t(int nr)
{
    char R[20];
    sprintf(R,"%d",nr);
    return R;
}
char* concat(char C1[],char C2[])
{
    char C3[100];
    strcpy(C3,C1);
    strcat(C3,C2);
    return C3;
}
int main()
{
    ///freopen("1.in","r",stdin);
    ///freopen("1.out","w",stdout);
    cin>>N;
    cin.getline(C,22);
    while(N--)
    {
        cin.getline(C,22);
        if(C[0]=='i')
        {
            i=0;
            while(C[i]!=' ')
                i++;
            i++;
            nr=0;
            while('0'<=C[i]&&C[i]<='9')
            {
                nr=nr*10+C[i]-'0';
                i++;
            }
            strcpy(rez[M++],C);
            H.push(nr);
        }
        else if(C[0]=='r')
        {
            if(H.empty())
            {
                strcpy(rez[M++],"insert 0");
                strcpy(rez[M++],C);
            }
            else
            {
                strcpy(rez[M++],C);
                H.pop();
            }
        }
        else
        {
           i=0;
            while(C[i]!=' ')
                i++;
            i++;
            nr=0;
            while('0'<=C[i]&&C[i]<='9')
            {
                nr=nr*10+C[i]-'0';
                i++;
            }
            while(!H.empty()&&H.top()<nr)
            {
                H.pop();
                strcpy(rez[M++],"removeMin");
            }
            if(H.empty()||H.top()!=nr)
            {
                strcpy(rez[M++],concat("insert ",t(nr)));
                strcpy(rez[M++],C);
            }
        }
    }
    cout<<M<<"\n";
    for(i=0;i<M;i++)
    {
        cout<<rez[i]<<"\n";
    }
    return 0;
}
