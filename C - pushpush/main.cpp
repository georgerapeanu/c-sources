#include <iostream>
#include <deque>
using namespace std;
deque<int> D;
int rev=0;
int a;
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        if(!rev)D.push_back(a);
        else D.push_front(a);
        rev^=1;
    }
    if(!rev)for(auto it:D)cout<<it<<" ";
    else for(deque<int> :: reverse_iterator it=D.rbegin();it!=D.rend();it++)cout<<*it<<" ";
    return 0;
}
