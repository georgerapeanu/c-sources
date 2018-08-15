#include <iostream>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
unordered_map <char,char> M;
unordered_set <char> S;
vector <pair<char,char> >rez;
char A[1005],B[1005];
int N;
int main()
{
    cin.getline(A+1,1005);
    cin.getline(B+1,1005);
    N=strlen(A+1);
    for(int i=1;i<=N;i++)
    {
        if(A[i]==B[i])
        {
            if(M.find(A[i])!=M.end())
            {
                if(M[A[i]]!=B[i])
                {cout<<-1;return 0;}
            }
            else
                M[A[i]]=A[i];
        }
        else
        {
            if(M.find(A[i])==M.end())
            {
                if(M.find(B[i])==M.end())
                {
                    M[A[i]]=B[i];
                    M[B[i]]=A[i];
                }
                else
                {
                    cout<<-1;return 0;
                }
            }
            else if(M.find(B[i])==M.end())
            {
                if(M.find(A[i])==M.end())
                {
                    M[A[i]]=B[i];
                    M[B[i]]=A[i];
                }
                else
                {
                    cout<<-1;return 0;
                }
            }
            else
            {
                if(M[A[i]]!=B[i]||M[B[i]]!=A[i])
                {
                    cout<<-1;return 0;
                }
            }
        }
    }
    for(auto it:M)
    {
        if((it).first!=(it.second))
        {
            if(S.find((it).first)==S.end())
            {
                S.insert((it).first);
                S.insert((it).second);
                rez.push_back(make_pair((it).first,(it).second));
            }
        }
    }
    cout<<rez.size()<<"\n";
    for(auto it:rez)
    {
        cout<<(it).first<<" "<<(it).second<<"\n";
    }
    return 0;
}
