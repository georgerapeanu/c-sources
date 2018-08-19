#include <iostream>
#include <unordered_set>
#include <set>
#include <unordered_map>
using namespace std;
unordered_set <string> cuv,newcuv;
string C;
unordered_map<char,int> frecv;
set <pair<int,char> > ord;

int N,K;
int main() {
    cin>>N>>K;
    getline(cin,C);
    for(int i=1;i<=N;i++)
    {
        getline(cin,C);
        cuv.insert(C);
    }
    int i=1;
    while(i<=K)
    {
        char c;
        ord.clear();
        frecv.clear();
        for(auto it:cuv)
        {
            frecv[(it).at(i-1)]++;
        }
        for(auto it:frecv)
        {
            ord.insert(make_pair((it).second,(it).first));
        }
        for(set <pair<int,char> > ::reverse_iterator it=ord.rbegin();it!=ord.rend();it++)
        {
            bool val;
            cout<<(*it).second<<"\n";
            cin>>val;
            cout.flush();
            if(val)
            {
                c=(*it).second;
                break;
            }
        }
        for(auto it:cuv)
        {
            if((it).at(i-1)==c)
                newcuv.insert(it);
        }
        cuv.clear();
        for(auto it:newcuv)
            cuv.insert(it);
        newcuv.clear();
        i++;
    }
    return 0;
}
