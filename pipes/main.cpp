#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
int S[4005];
char C[4005];
int N,i,M,j;
bool ok;
int main()
{
    cin>>N;
    cin.getline(C,4000);
    for(i=1;i<=N;i++)
    {
        ok=1;
        cin.getline(C+1,4000);
        M=strlen(C+1);
        for(j=1;j<=M&&ok;j++)
        {
            switch (C[j])
            {
                case '(':S[++S[0]]=1;break;
                case '[':S[++S[0]]=2;break;
                case '{':S[++S[0]]=3;break;
                case '|':{
                    if(S[0]==0||S[S[0]]!=4)
                        S[++S[0]]=4;
                    else
                        S[0]--;
                    break;
                }
                case ')':if(S[0]==0||S[S[0]]!=1) ok=0;else S[0]--; break;
                case ']':if(S[0]==0||S[S[0]]!=2) ok=0;else S[0]--;break;
                case '}':if(S[0]==0||S[S[0]]!=3) ok=0;else S[0]--;break;
            }
        }
        if(ok==1&&!S[0])
            cout<<"YES\n";
        else
            cout<<"NO\n";
        S[0]=0;
    }
    return 0;
}
