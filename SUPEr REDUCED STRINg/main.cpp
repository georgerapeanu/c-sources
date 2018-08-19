#include <iostream>
#include <cstring>
using namespace std;
char C[105];
char rez[105];
int N,i,j,cnt;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin.getline(C,105);
    N=strlen(C);
    for(i=0;i<N;i++)
    {
        rez[cnt]=C[i];
        while(cnt>=1&&rez[cnt]==rez[cnt-1])
            cnt-=2;
        cnt++;
    }
    rez[cnt]='\0';
    if(cnt!=0)
        cout<<rez;
    else
        cout<<"Empty String";
    return 0;
}
