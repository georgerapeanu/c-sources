#include <bits/stdc++.h>

using namespace std;

int t;
int n;
long long w;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %lld",&n,&w);

        vector<pair<int,int > > v(n,make_pair(0,0));

        for(int i = 0;i < n;i++) {
            scanf("%d",&v[i].first);
            v[i].second = i + 1;
        }

        sort(v.begin(),v.end());

        while((int)v.size() > 0 && v.back().first > w){
            v.pop_back();
        }

        if(v.empty()){
            printf("-1\n");
            continue;
        }

        if(v.back().first >= (w + 1) / 2){
            printf("1\n%d\n",v.back().second);
            continue;
        }

        long long sum = 0;

        for(auto it:v){
            sum += it.first;
        }

        if(sum < (w + 1) / 2){
            printf("-1\n");
            continue;
        }

        sum = 0;

        for(int i = 0;i < (int)v.size();i++){
            sum += v[i].first;
            if(sum >= (w + 1) / 2){
                printf("%d\n",i + 1);
                for(int j = 0;j <= i;j++){
                    printf("%d ",v[j].second);
                }
                printf("\n");
                break;
            }
        }
    }

    return 0;
}
