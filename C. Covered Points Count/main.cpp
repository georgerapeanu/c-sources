#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector< pair<long long,int> > Ev;

long long ans[200005];
int N;
int active;

bool cmp(pair<long long,int> a,pair<long long,int> b){
    if(a.first != b.first){
        return a < b;
    }
    return a.second > b.second;
}

int main(){
    scanf("%d",&N);

    for(int i = 1;i <= N;i++){
        long long l,r;
        scanf("%I64d %I64d",&l,&r);
        Ev.push_back({l,1});
        Ev.push_back({r,-1});
    }

    sort(Ev.begin(),Ev.end(),cmp);

    int last = 0;

    for(int i = 1;i < (int)Ev.size();i++){
        if(Ev[i].first != Ev[last].first){
            ans[active] += Ev[last].first - Ev[last - 1].first - 1;
            int mx_active = active;
            for(int j = last;j < i;j++){
                mx_active += max(Ev[j].second,0);
                active += Ev[j].second;
            }
            ans[mx_active]++;
            last = i;
        }
    }

    ans[active] += Ev[last].first - Ev[last - 1].first - 1;
    int mx_active = active;
    for(int j = last;j < (int)Ev.size();j++){
        mx_active += max(Ev[j].second,0);
        active += Ev[j].second;
    }
    ans[mx_active]++;

    for(int i = 1;i <= N;i++){
        printf("%I64d ",ans[i]);
    }
    return 0;
}
