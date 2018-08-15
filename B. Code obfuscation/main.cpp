#include <iostream>
#include <cstring>
using namespace std;
char C[505];
char c='a';
int main()
{
    cin.getline(C,505);
    int N=strlen(C);
    for(int i=0;i<N;i++)
    {
        if(C[i]>c){cout<<"NO";return 0;}
        if(C[i]==c)
        {
            c++;
            if(c>'z'+1)
            {
                cout<<"NO";return 0;
            }
        }
    }
    cout<<"YES";
    return 0;
}
