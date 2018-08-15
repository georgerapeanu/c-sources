#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;
char C[100005];
unordered_map<char,int> sample;
int rez;
unordered_map <char,int> M;
int main()
{
    cin.getline(C+1,100005);
    int N=strlen(C+1);
    sample['B']=1;
    sample['u']=2;
    sample['l']=1;
    sample['b']=1;
    sample['a']=2;
    sample['s']=1;
    sample['r']=1;
    for(int i=1;i<=N;i++)
    {
        M[C[i]]++;
    }
    rez=(1<<30);
    for(auto it:sample)
    {
        rez=min(rez,M[it.first]/it.second);
    }
    cout<<rez;
    return 0;
}
