#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
vector<pair<pair<int,int>,int> > v;
int ans[NMAX + 5];

int main(){

    scanf("%d\n",&n);

    int lst = 0;

    set<int> avail;
    avail.insert(2 * n + 5);

    for(int i = 1;i <= 2 * n;i++){
        char c;
        int val;
        scanf("%c",&c);
        if(c == '+'){
            scanf("\n");
            lst++;
            v.push_back({{lst,lst},0});
            avail.insert(lst);
        }
        else{
            scanf("%d\n",&val);
            pair<int,int> tmp = {1e9,0};
            while((int)v.size() > 0 && v.back().second <= val){
                tmp.first = min(tmp.first,v.back().first.first);
                tmp.second = max(tmp.second,v.back().first.second);
                v.pop_back();
            }
            if(tmp.first != 1e9){
                v.push_back({tmp,val});
            }
            if(v.empty() || v.back().second > val || *avail.lower_bound(v.back().first.first) > v.back().first.second){
                printf("NO\n");
                return 0;
            }
            int ind = *avail.lower_bound(v.back().first.first);
            avail.erase(ind);
            ans[ind] = val;
        }
    }
    
    printf("YES\n");
    for(int i = 1;i <= n;i++){
        printf("%d ",ans[i]);
    }

    return 0;
}
