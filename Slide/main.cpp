#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int64;
vector<int64> solve(string s){
    s=string(s.size()+1,'.')+s;
    vector<int64> V(s.size(),0);
    vector<int> Go_left(s.size(),0);
    vector<int> Seg_left(s.size(),0);
    int last=0;
    int n=s.size();
    for(int i=1;i<n;i++){
        Go_left[i]=last;
        if(s[i]=='.')last=i;
    }
    int segments=0;
    for(int i=1;i<n;i++){
        if(s[i]!='.'&&(s[i]!=s[i-1]))segments++;
        Seg_left[i]=segments;
        if(s[i]=='.')segments=0;
    }
    for(int i=n-1;i;){
        if(s[i]=='.')
        {
            i--;
            continue;
        }
        int pos=Go_left[i];
        int num_bad=Seg_left[i];
        int64 ans=0;
        char c=s[i];
        while(s[i]==c)
        {
            ans+=num_bad;
            num_bad+=Seg_left[pos];
            pos=Go_left[pos];
            V[i]=ans;
            i--;
        }
    }
    return vector<int64>(V.begin()+n/2+1,V.end());
}
int main(){
    freopen("slide.in","r",stdin);
    freopen("slide.out","w",stdout);
    string s;
    cin>>s;
    auto Left=solve(s);
    reverse(s.begin(),s.end());
    auto Right=solve(s);
    reverse(Right.begin(),Right.end());
    reverse(s.begin(),s.end());
    int64 rez=0;
    //cout<<s<<"\n";
    //for(auto it:Left)cout<<it<<" ";cout<<"\n";
    //for(auto it:Right)cout<<it<<" ";cout<<"\n";
    for(int i=0;i<s.size();i++)
        rez+=min(Left[i],Right[i]);
    cout<<rez;
    return 0;
}
