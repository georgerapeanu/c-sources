#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int n,k;
int v[505][505];

int main(){
    
    scanf("%d %d",&n,&k);

    priority_queue<pair<int,int> > pq;

    for(int i = 1;i <= n;i++){
        pq.push({k,i});
    }
    
    for(int i = 1;i <= n;i++){
        vector<pair<int,int> > tmp;

        for(int j = 1;j <= k;j++){
            pair<int,int> a = pq.top();pq.pop();
            a.first--;
            tmp.push_back(a);
            v[i][a.second] = 1;
        }

        for(auto it:tmp){
            if(it.first){
                pq.push(it);
            }
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            printf("%d",v[i][j]);
        }
        printf("\n");
    }

    return 0;
}
