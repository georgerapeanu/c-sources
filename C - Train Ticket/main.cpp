#include <iostream>
#include <cstdlib>
using namespace std;
string rez;
int V[5];
char C[10];
void btr(int pas,int sum)
{
    if(pas>4)
    {
        if(sum==7)
        {
            rez+="=7";
            cout<<rez;
            exit(0);
        }
        return ;
    }
    rez+="+";rez+=(V[pas]+'0');
    btr(pas+1,sum+V[pas]);
    rez[rez.size()-2]='-';
    btr(pas+1,sum-V[pas]);
    rez.pop_back();
    rez.pop_back();
}
int main()
{
    cin.getline(C+1,5);
    for(int i=1;i<5;i++)
        V[i]=C[i]-'0';
    rez+=(V[1]+'0');
    btr(2,V[1]);
    return 0;
}
